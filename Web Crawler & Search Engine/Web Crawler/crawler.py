import logging
import re
from urllib.parse import urlparse, urljoin, parse_qs, urlunparse
from bs4 import BeautifulSoup
import lxml
from itertools import islice
from collections import Counter
from difflib import SequenceMatcher


logger = logging.getLogger(__name__)


class Crawler:
    """
    This class is responsible for scraping urls from the next available link in frontier and adding the scraped links to
    the frontier
    """

    # ******************* CONSTANTS ********************
    MAX_URL_LENGTH = 256  # https://docs.squiz.net/funnelback/docs/latest/reference/configuration-options/collection-options/crawler.max_url_length.html
    STOP_WORDS = [
        "a",
        "about",
        "above",
        "after",
        "again",
        "against",
        "all",
        "am",
        "an",
        "and",
        "any",
        "are",
        "aren't",
        "as",
        "at",
        "be",
        "because",
        "been",
        "before",
        "being",
        "below",
        "between",
        "both",
        "but",
        "by",
        "can't",
        "cannot",
        "could",
        "couldn't",
        "did",
        "didn't",
        "do",
        "does",
        "doesn't",
        "doing",
        "don't",
        "down",
        "during",
        "each",
        "few",
        "for",
        "from",
        "further",
        "had",
        "hadn't",
        "has",
        "hasn't",
        "have",
        "haven't",
        "having",
        "he",
        "he'd",
        "he'll",
        "he's",
        "her",
        "here",
        "here's",
        "hers",
        "herself",
        "him",
        "himself",
        "his",
        "how",
        "how's",
        "i",
        "i'd",
        "i'll",
        "i'm",
        "i've",
        "if",
        "in",
        "into",
        "is",
        "isn't",
        "it",
        "it's",
        "its",
        "itself",
        "let's",
        "me",
        "more",
        "most",
        "mustn't",
        "my",
        "myself",
        "no",
        "nor",
        "not",
        "of",
        "off",
        "on",
        "once",
        "only",
        "or",
        "other",
        "ought",
        "our",
        "ours",
        "ourselves",
        "out",
        "over",
        "own",
        "same",
        "shan't",
        "she",
        "she'd",
        "she'll",
        "she's",
        "should",
        "shouldn't",
        "so",
        "some",
        "such",
        "than",
        "that",
        "that's",
        "the",
        "their",
        "theirs",
        "them",
        "themselves",
        "then",
        "there",
        "there's",
        "these",
        "they",
        "they'd",
        "they'll",
        "they're",
        "they've",
        "this",
        "those",
        "through",
        "to",
        "too",
        "under",
        "until",
        "up",
        "very",
        "was",
        "wasn't",
        "we",
        "we'd",
        "we'll",
        "we're",
        "we've",
        "were",
        "weren't",
        "what",
        "what's",
        "when",
        "when's",
        "where",
        "where's",
        "which",
        "while",
        "who",
        "who's",
        "whom",
        "why",
        "why's",
        "with",
        "won't",
        "would",
        "wouldn't",
        "you",
        "you'd",
        "you'll",
        "you're",
        "you've",
        "your",
        "yours",
        "yourself",
        "yourselves",
    ]  # (https://www.ranks.nl/stopwords)

    # --------------------------------------------------
    # ********* ANALYTICS FUNCTIONS AND HELPERS ********

    def tokenizeText(self, content):
        content = content.lower() + "."

        # for character in content:
        #     if (not character.isascii()) or (
        #         not character.isalnum() and not character.isspace()
        #     ):
        #         if character != "'":
        #             content = content.replace(character, " ")

        # words_list = content.split(" ")

        words_list = []
        word = ""

        for character in content:
            if (
                "a" <= character.lower() <= "z"
                or character.isdigit()
                or character == "'"
            ):
                word += character
            else:
                if word != "":
                    words_list.append(word)
                    word = ""  # reset words

        result_list = []
        for word in words_list:
            if word not in Crawler.STOP_WORDS:
                result_list.append(word)
        return result_list

    def countTokenFrequencies(self, words_list):
        token_frequencies = dict()
        for word in words_list:
            if word in token_frequencies:
                token_frequencies[word] += 1
            else:
                token_frequencies[word] = 1
        return token_frequencies

    def A1_trackSubDomain(self, url):
        """
        Keep track of the subdomains that it visited, and count how many different URLs it has
        processed from each of those subdomains.
        Example) http://www.google.com/search~~~~~~, then we need www.google.com -> netloc
        """
        try:
            parsed = urlparse(url)
            subdomain = parsed.netloc
            if subdomain in self.subdomain_count:
                self.subdomain_count[subdomain] += 1
            else:
                self.subdomain_count[subdomain] = 1
        except:
            pass

    # A2 is combined in start_crawling()

    # A3 is combined in start_crawling() and is_valid()

    def A4_findLongestFetchedPage(self, plainText, url):
        # ---------- find the longest page that has been fetched ---------------
        words_list = self.tokenizeText(plainText)
        if len(words_list) > self.numWordsInLongestPage:
            self.numWordsInLongestPage = len(words_list)
            self.longestPage = url
            # print(plainText)
            # print("--------------------------------\n\n\n")

    def A5_findTop50Words(self, plainText):
        # ------- find top 50 common tokens among fetched page ----------
        words_list = self.tokenizeText(plainText)
        token_frequencies = self.countTokenFrequencies(words_list)
        for key, value in token_frequencies.items():  # merge 2 dicts
            if key in self.top50WordsFrequency:
                self.top50WordsFrequency[key] += value
            else:
                self.top50WordsFrequency[key] = value
        counter = Counter(self.top50WordsFrequency)
        self.top50WordsFrequency = dict(counter.most_common(50))

    def export_analytics(self):
        """
        Write analytics results into file
        """
        with open("Analytics.txt", "w", encoding="utf-8") as writer:
            # Analytics 1
            writer.write("---- Analytics 1: Subdomain detected ----\n")
            for subdomain, count in self.subdomain_count.items():
                writer.write(f"     {subdomain}: {count}\n")
            writer.write("\n\n")

            # Analytics 2
            writer.write("---- Analytics 2: Page with the most valid out links ----\n")
            writer.write(f"     {self.maxValidOutLinksPage}\n")
            writer.write(f"     Number of out links: {self.maxValidOutLinks}")
            writer.write("\n\n")

            # Analytics 3
            writer.write(
                "---- Analytics 3: List of downloaded URLs and identified traps ----\n"
            )
            writer.write(f"     Downloaded URLs:\n")
            for url in self.downloaded_url:
                writer.write(f"     {url}\n")
            writer.write("\n\n")
            writer.write(f"     Identified traps:\n")
            for trap, type in self.identified_trap.items():
                writer.write(f"     {trap} --- {type}\n")
            writer.write("\n\n")

            # Analytics 4
            writer.write("---- Analytics 4: Longest page ----\n")
            writer.write(f"     {self.longestPage}\n")
            writer.write(f"     Number of words: {self.numWordsInLongestPage}")
            writer.write("\n\n")

            # Analytics 5
            writer.write("---- Analytics 5: The 50 most common words  ----\n")
            for word, freq in self.top50WordsFrequency.items():
                writer.write(f"     {word}: {freq}\n")
            writer.write("\n\n")

    # ---------------------------------------------------
    # ********* CORE CRAWLER FUNCTIONS AND HELPERS ********

    def __init__(self, frontier, corpus):
        self.frontier = frontier
        self.corpus = corpus

        # use this to recognize if urls have similar pattern, which might be crawler traps
        self.url_patterns = {}

        # use this to remember visited base urls for identifying fragment traps
        self.visited_base_urls = set()

        # for dynamic url, store query if url contain '?' '&' '='
        self.dynamic_url_query = []

        # for determining redirected domains
        self.redirected_domains = []

        # use this to determine if a page has different url versions
        self.url_with_versions = dict()

        # Analytics 1: Tracking Subdomain
        self.subdomain_count = dict()

        # Analytics 2. keep track of a webpage's valid out link count
        self.maxValidOutLinks = 0
        self.maxValidOutLinksPage = ""

        # Analytics 3: List of downloaded URLs and identified traps
        self.downloaded_url = []
        self.identified_trap = dict()

        # Analytics 4: longest page in terms of number of words
        self.numWordsInLongestPage = 0
        self.longestPage = ""

        # Analytics 5: 50 most common words in the entire set of pages, Ignore stop words ("English Stopwords" from https://www.ranks.nl/stopwords)
        self.top50WordsFrequency = dict()

    def start_crawling(self):
        """
        This method starts the crawling process which is scraping urls from the next available link in frontier and adding
        the scraped links to the frontier
        """
        visited_url = 0

        while self.frontier.has_next_url():
            url = self.frontier.get_next_url()
            logger.info(
                "Fetching URL %s ... Fetched: %s, Queue size: %s",
                url,
                self.frontier.fetched,
                len(self.frontier),
            )
            url_data = self.corpus.fetch_url(url)

            numValidOutlinks = 0  # reset num of valid out links
            next_link_list = self.extract_next_links(url_data)
            for next_link in next_link_list:
                if self.is_valid(url, next_link):
                    if self.is_static_url(next_link, next_link_list):
                        if self.corpus.get_file_name(next_link) is not None:
                            self.frontier.add_url(next_link)  # add link to frontier
                            # print(next_link)

                            # ------ Analytics 3 -----
                            self.downloaded_url.append(next_link)

                        numValidOutlinks += 1

            # visited_url += 1
            # if visited_url == 5000:
            #     self.export_analytics()
            #     break

            # -------- Analytics 2: find link with max valid outlinks -----------
            if numValidOutlinks > self.maxValidOutLinks:
                self.maxValidOutLinks = numValidOutlinks
                self.maxValidOutLinksPage = (
                    url_data["final_url"]
                    if url_data["is_redirected"]
                    else url_data["url"]
                )

        # when frontier has no URL left
        self.export_analytics()

    def extract_next_links(self, url_data):
        """
        this method access a page and get all links from that page.

        The url_data coming from the fetch_url method will be given as a parameter to this method. url_data contains the
        fetched url, the url content in binary format, and the size of the content in bytes. This method should return a
        list of urls in their absolute form (some links in the content are relative and needs to be converted to the
        absolute form). Validation of links is done later via is_valid method. It is not required to remove duplicates
        that have already been fetched. The frontier takes care of that.

        Suggested library: lxml

        This function extracts links from the content of a fetched webpage.
        Input: url_data which is a dictionary containing the content and required meta-data for a downloaded
        webpage. Following is the description for each key in the dictionary:
            url: the requested url to be downloaded
            content: the content of the downloaded url in binary format. None if url does not exist in the corpus
            size: the size of the downloaded content in bytes. 0 if url does not exist in the corpus
            content_type: Content-Type from the response http headers. None if the url does not exist in the corpus or content-type wasn't provided
            http_code: the response http status code. 404 if the url does not exist in the corpus
            is_redirected: a boolean indicating if redirection has happened to get the final response
            final_url: the final url after all of the redirections. None if there was no redirection.

        Output: list of URLs in string form. Each URL should be in absolute form. It is not required to remove
        duplicates that have already been fetched. The frontier takes care of ignoring duplicates.
        """
        outputLinks = []
        try:
            if url_data["http_code"] != 404:  # if the url exists in the corpus
                content = url_data["content"]
                for encoding in ["utf-8", "latin-1", "utf-16"]:
                    try:
                        content = content.decode(encoding)
                        break  # Break the loop if decoding succeeds
                    except:
                        return outputLinks
                content = content.replace("\x00", "")

                soup = BeautifulSoup(content, "lxml")
                current_URL = (
                    url_data["final_url"]
                    if url_data["is_redirected"]
                    else url_data["url"]
                )
                plainText = soup.get_text()

                # ------------ detect rederected domain --------------------------------
                parsed = urlparse(current_URL)
                netloc = parsed.netloc
                path_components = parsed.path.strip("/").split("/")[:1]
                parent_dir = netloc + "/" + "/".join(path_components)
                if url_data["is_redirected"]:
                    if (
                        parent_dir > "www.ics.uci.edu/"
                        and parent_dir not in self.redirected_domains
                    ):
                        self.redirected_domains.append(parent_dir)

                # ------- find <a> tags in current page ------------
                a_tags = soup.find_all("a")
                for a_tag in a_tags:
                    relativeURL = a_tag.get("href")
                    if url_data["is_redirected"] == True:
                        # if redirection happened, then url_data["final_url"] is base url
                        a_absoluteURL = urljoin(url_data["final_url"], relativeURL)
                    else:
                        # if redirection didn't happen, then url_data["url"] is base url
                        a_absoluteURL = urljoin(url_data["url"], relativeURL)

                    outputLinks.append(a_absoluteURL)

                # -------------- Analysis -----------------------
                self.A1_trackSubDomain(current_URL)
                self.A4_findLongestFetchedPage(plainText, current_URL)
                self.A5_findTop50Words(plainText)

            return outputLinks
        except:
            a_absoluteURL = ""
            outputLinks.append(a_absoluteURL)
            return outputLinks

    def has_repeating_sub_directories(self, url):
        """
        Check for repeating sub-dirctories.
        Example: https://example.com/a/a/a/a/b/b/b/a/index.html

        Tokenize by '/' and count word by using dictionary
        If frequency of one word is over 3, then treat as repeating_sub_directories
        """
        directories = url.split("/")
        directory_count = {}

        for directory in directories:
            if directory in directory_count:
                directory_count[directory] += 1
            else:
                directory_count[directory] = 1

            if directory_count[directory] > 3:
                return True

        return False

    def is_private_url(self, url):
        # intranet is private network fo users within an organization, crawler cannot access
        parsed = urlparse(url)
        hostname = parsed.hostname
        path = parsed.path
        if hostname:
            host_type = hostname.split(".")[0]
            if host_type == "intranet" or path.endswith("private"):
                return True
        return False

    def has_many_params(self, url):
        parsed = urlparse(url)
        query = parsed.query.split("&")
        num_params = len(query)
        if num_params > 5:
            return True
        return False

    def is_php_url_with_extra_directory_depth(self, url):
        parsed = urlparse(url)
        path = parsed.path
        directory_segments = path.split("/")
        if len(directory_segments) > 3 and path.endswith(".php"):
            # https://docs.squiz.net/funnelback/docs/latest/reference/configuration-options/collection-options/crawler.max_dir_depth.html
            return True
        return False

    def has_session_ID(self, url):
        parsed = urlparse(url)
        session_id_params = [
            "sess_id",
            "session_id",
            "jsessionid",
            "phpsessid",
            "sid",
            "sessionid",
        ]
        for param in session_id_params:
            if param in parsed.query:
                return True
        return False

    def is_redirected_to_parent_directory(self, url):
        parsed = urlparse(url)
        netloc = parsed.netloc
        query = parse_qs(parsed.query)
        path_components = parsed.path.strip("/").split("/")[:1]
        parent_dir = netloc + "/" + "/".join(path_components)

        if "id" not in query and parent_dir in self.redirected_domains:
            return True
        return False

    def is_calendar_trap(self, url):
        parsed = urlparse(url)
        path_segments = parsed.path.strip("/").split("/")

        # REGEX EXPRESSION TO CHECK FOR DATES IN URL
        date_pattern = re.compile(
            r"(?:\d{4}[-/]\d{1,2}[-/]\d{1,2})|(?:\d{1,2}[-/]\d{1,2}[-/]\d{4})|(?:\d{4}\d{1,2}\d{1,2})|(?:\d{1,2}\w+[-/]\d{4})|(?:\d{4}[-/]\w+[-/]\d{1,2})"
        )

        modified_segments = []
        numeric_segments = []

        for segment in path_segments:
            if date_pattern.match(segment):
                # If the segment matches the date pattern, replace it with '*'
                modified_segments.append("*")
                numeric_segments.append(segment)
            else:
                modified_segments.append(segment)

        url_pattern = "/".join(modified_segments)

        if url_pattern in self.url_patterns:
            for numeric_segment in numeric_segments:
                if numeric_segment not in self.url_patterns[url_pattern]:
                    self.url_patterns[url_pattern].update(numeric_segments)
                    return True  # Indicative of a potential calendar trap
            return False
        else:
            # New pattern
            self.url_patterns[url_pattern] = set(numeric_segments)
            return False

    def include_take_action_params(self, url):
        parsed = urlparse(url)
        query = parse_qs(parsed.query)
        share_param = query.get("share")
        if share_param:
            return True

        action_param = query.get("action")
        if action_param:
            if query.get("action") in [["edit"], ["login"], ["download"], ["upload"]]:
                return True
        return False

    def is_fragmented_url(self, url):
        # Parse the URL and reconstruct without the fragment
        parsed_url = urlparse(url)
        base_url_with_query = urlunparse(
            (
                parsed_url.scheme,
                parsed_url.netloc,
                parsed_url.path,
                parsed_url.params,
                parsed_url.query,
                "",
            )
        )

        # Check if the base URL has already been visited
        if base_url_with_query in self.visited_base_urls:
            return True

        self.visited_base_urls.add(base_url_with_query)
        return False

    def is_static_url(self, url, extracted_link_list):
        """
        If more than 10 urls are similar with current url, then consider as dynamic url
        """
        parsed = urlparse(url)
        query_list = parse_qs(parsed.query)
        if "id" not in query_list and (("?" in url) or ("&" in url)) and ("=" in url):
            threshold = 10
            count = 0
            dynamic_url_list = []

            for target_url in extracted_link_list:
                ratio = SequenceMatcher(None, url, target_url).ratio()
                if ratio > 0.9:
                    count += 1
                    dynamic_url_list.append(target_url)

            if count > threshold:
                dynamic_url_list.append(url)

                for dynamic_url in dynamic_url_list:
                    self.identified_trap[dynamic_url] = "Dynamic url"

                return False
        else:
            return True

    def have_different_versions(self, url):
        parsed = urlparse(url)
        query_list = parse_qs(parsed.query)
        if "version" in query_list and len(query_list) == 1:
            # if "version" is the only query
            return True
        return False

    def is_valid(self, current_url, url):
        """
        Function returns True or False based on whether the url is valid and has to be fetched or not. This is a great place to
        filter out crawler traps. Duplicated urls will be taken care of by frontier. You don't need to check for duplication
        in this method

        Input: URL is the URL of a web page in string form
                current_url is the url of the parant webpage where url is extracted from
        Output: True if URL is valid, False if the URL otherwise.
        """

        parsed = urlparse(url)
        # this return ParseResult object, including attributes: scheme, netloc, path, params, query, fragment

        try:
            if parsed.scheme not in set(["http", "https"]):
                # self.identified_trap[url] = "Wrong Scheme"
                return False

            elif not ".ics.uci.edu" in parsed.hostname or re.match(
                ".*\.(css|js|bmp|gif|jpe?g|ico"
                + "|png|tiff?|mid|mp2|mp3|mp4"
                + "|wav|avi|mov|mpeg|ram|m4v|mkv|ogg|ogv|pdf"
                + "|ps|eps|tex|ppt|pptx|doc|docx|xls|xlsx|names|data|dat|exe|bz2|tar|msi|bin|7z|psd|dmg|iso|epub|dll|cnf|tgz|sha1"
                + "|thmx|mso|arff|rtf|jar|csv"
                + "|rm|smil|wmv|swf|wma|zip|rar|gz|pdf|bam)$",
                parsed.path.lower(),
            ):
                return False

            elif len(url) > Crawler.MAX_URL_LENGTH:
                self.identified_trap[url] = "Long URL"
                return False

            elif self.has_repeating_sub_directories(url):
                self.identified_trap[url] = "Repeating sub-directories"
                return False

            # elif self.include_take_action_params(url):
            #     self.identified_trap[url] = "Includes redirecting trap params"
            #     return False

            elif self.is_redirected_to_parent_directory(url):
                self.identified_trap[url] = "Redirected loop trap"
                return False

            elif self.have_different_versions(url):
                self.identified_trap[url] = "Different-version trap"
                return False

            elif self.is_private_url(url):
                self.identified_trap[url] = "Private (intranet) URL"
                return False

            elif self.is_php_url_with_extra_directory_depth(url):
                self.identified_trap[url] = ".php with excessive depth of directory"
                return False

            elif self.has_many_params(url):
                self.identified_trap[url] = "Too many params in URL"
                return False

            elif self.has_session_ID(url):
                self.identified_trap[url] = "Has session ID"
                return False

            elif self.is_calendar_trap(url):
                self.identified_trap[url] = "Calendar trap"
                return False

            elif self.is_fragmented_url(url):
                self.identified_trap[url] = "Fragment trap"
                return False

            else:
                return True

        except TypeError:
            print("TypeError for ", parsed)
            return False
