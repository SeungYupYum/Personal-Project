import os
import string
from bs4 import BeautifulSoup
import nltk  # this helps tokenize the text
import json
from lxml import etree, html
import mysql.connector
import re
import sys
import math


class CorpusProcessor:
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

    NUM_UNIQUE_DOCS = 33182  # result from milestone 1

    def __init__(self, limitNumCorpus=-1):
        self.limitNumCorpus = int(limitNumCorpus)
        self.visited_document = set()
        self.inverted_index = {}
        self.frequency_dic = {}
        # ---------
        self.posting_list_count = dict()
        self.tf_by_doc = dict()
        self.tf_idf_sum_squares = dict()
        # ---------
        # [doc_ID, doc_URL, doc_title, freq_in_doc, indices, importance_degree, tf, idf, nv]
        self.postings_dict = {}
        # all token that is in the document
        self.docID_map_token = {}

        self.number_of_doc = 0

    def tokenizeText(self, content):
        content = content.lower()
        token_list = nltk.word_tokenize(content)
        filtered_tokens = []

        trimed_token_list = [
            token.rstrip('`~!@#$%^&*()-_+=/?.>,<";:]}[{]') for token in token_list
        ]
        trimed_token_list = [
            token.rstrip("`~!@#$%^&*()-_+=/?.>,<';:]}[{]") for token in token_list
        ]
        trimed_token_list = [
            token.lstrip("`~!@#$%^&*()-_+=/?.>,<';:]}[{]") for token in token_list
        ]
        trimed_token_list = [
            token.lstrip('`~!@#$%^&*()-_+=/?.>,<";:]}[{]') for token in token_list
        ]

        for token in trimed_token_list:
            if token not in CorpusProcessor.STOP_WORDS:
                if len(token) > 1:
                    if token.isalnum() and token.isascii():
                        if not (
                            token.isdigit() and (len(token) < 4 or 4 < len(token) < 9)
                        ):  # 4 digits num can be year, 10 digit nums can be phone number
                            filtered_tokens.append(token)

        return filtered_tokens

    def countWordFreq(self, words_list, freq_dict):
        """
        Assume words_list = list of word that is already tokenzied
        Cound word frequency, and return dictionary
        """
        word_count = freq_dict

        for word in words_list:
            if word in word_count:
                word_count[word] += 1
            else:
                word_count[word] = 1

        return word_count

    def calculateWordWeight(self, words_list, weight_dict, weight):
        """
        Assume words_list = list of word that is already tokenzied
        weight is the weight of token, title += 0.4, heading 1 += 0.3, heading 2 += 0.2, heading 3 += 0.1, bold += 0.1 else += 0.01

        Cound word frequency, and return dictionary
        """
        weight_count = weight_dict

        for word in words_list:
            if word in weight_count:
                weight_count[word] += weight
            else:
                weight_count[word] = weight

        return weight_count

    def findWordIndices(self, words_list, indices_dict):
        # distinct_words_list = list(set(words_list))

        for word in words_list:
            occurrences = []
            for index, value in enumerate(words_list):
                if value == word:
                    occurrences.append(index)
            indices_dict[word] = occurrences
        return indices_dict

    def processCorpus(self):
        # --------------- Establish a connection to MySQL server ----------------
        conn = mysql.connector.connect(
            host="127.0.0.1", user="root", password="", database="search_engine"
        )
        if conn.is_connected():
            cursor = conn.cursor()  # Create a cursor object to execute SQL queries

        cursor.execute("CREATE DATABASE IF NOT EXISTS search_engine;")
        cursor.execute("USE search_engine;")
        cursor.execute("DROP TABLE IF EXISTS inverted_index;")
        cursor.execute(
            """
            CREATE TABLE inverted_index(
                token VARCHAR(100),
                doc_ID VARCHAR(50),
                doc_URL TEXT,
                doc_title TEXT,
                freq_in_doc INT,
                indices_in_doc TEXT,
                importance_degree FLOAT,
                tf FLOAT,
                df INT,
                idf FLOAT,
                tf_idf FLOAT,
                normalized_vector FLOAT,
                PRIMARY KEY (token, doc_ID)
            ); """
        )

        # ----------------- Open bookkeeping.json and load the data ----------------
        with open("WEBPAGES_RAW/bookkeeping.json", "r", encoding="utf-8") as file:
            links_dict = json.load(file)

        current_directory = os.path.dirname(os.path.abspath(__file__))
        files_base_directory = current_directory + "/WEBPAGES_RAW/"

        # ------------------------ loop through all docs to tokenize words and store tf and some metadata--------------------------------------------------
        if self.limitNumCorpus == -1:
            iterable = links_dict.items()
        else:
            iterable = list(links_dict.items())[: self.limitNumCorpus]

        for relative_path, url in iterable:
            file_dir = files_base_directory + relative_path
            file_url = url

            self.visited_document.add(relative_path)

            print(f"Processing file {relative_path}")

            if os.path.isfile(file_dir):
                with open(file_dir, "r", encoding="utf-8") as file:
                    # if file dont have <html>, excluded
                    first_three_lines = [file.readline().lower() for i in range(3)]
                    if not any("html" in line for line in first_three_lines):
                        continue

                    parser = etree.HTMLParser()
                    tree = etree.parse(file_dir, parser)  # Parse HTML file

                    root = tree.getroot()  # Get the root element of the HTML tree

                    # for each file, create these dicts, data of these dict will then be stored i sql database when we're done with inverted indexing the file
                    word_freq_dictionary = dict()
                    word_weight_dictionary = dict()
                    word_indices_dictionary = dict()
                    num_words_in_doc = 0

                    # --------- measure tokens' frequency and importance by it's weight -----------
                    # adding weight rules: title += 0.4, heading 1 += 0.3, heading 2 += 0.2, heading 3 += 0.1, bold += 0.1 else += 0.01

                    # ----- measure <title> ------
                    title_tags = tree.xpath("//title")
                    tokenized_title = []
                    doc_title = (
                        title_tags[0].text
                        if title_tags and title_tags[0].text is not None
                        else ""
                    )

                    for tag in title_tags:
                        if tag.text is not None:
                            tokenized_title += self.tokenizeText(tag.text)
                    num_words_in_doc += len(tokenized_title)

                    word_freq_dictionary = self.countWordFreq(
                        tokenized_title, word_freq_dictionary
                    )
                    word_weight_dictionary = self.calculateWordWeight(
                        tokenized_title, word_weight_dictionary, 0.4
                    )

                    # ----- measure <b>, <strong>, <em> ------
                    bold_tags = tree.xpath("//b")
                    strong_tags = tree.xpath("//strong")
                    em_tags = tree.xpath("//em")
                    bse_tags = [
                        tag
                        for tag in (bold_tags + strong_tags + em_tags)
                        if tag.text is not None
                    ]
                    tokenized_bse = []
                    for tag in bse_tags:
                        tokenized_bse += self.tokenizeText(tag.text)
                    num_words_in_doc += len(tokenized_bse)
                    word_freq_dictionary = self.countWordFreq(
                        tokenized_bse, word_freq_dictionary
                    )
                    word_weight_dictionary = self.calculateWordWeight(
                        tokenized_bse, word_weight_dictionary, 0.1
                    )

                    # ----- measure <h1>, <h2>, <h3> ------
                    h1_tags = tree.xpath("//h1")
                    tokenized_h1 = []
                    for tag in h1_tags:
                        if tag.text is not None:
                            tokenized_h1 += self.tokenizeText(tag.text)
                    num_words_in_doc += len(tokenized_h1)
                    word_freq_dictionary = self.countWordFreq(
                        tokenized_h1, word_freq_dictionary
                    )
                    word_weight_dictionary = self.calculateWordWeight(
                        tokenized_h1, word_weight_dictionary, 0.3
                    )

                    h2_tags = tree.xpath("//h2")
                    tokenized_h2 = []
                    for tag in h2_tags:
                        if tag.text is not None:
                            tokenized_h2 += self.tokenizeText(tag.text)
                    num_words_in_doc += len(tokenized_h2)
                    word_freq_dictionary = self.countWordFreq(
                        tokenized_h2, word_freq_dictionary
                    )
                    word_weight_dictionary = self.calculateWordWeight(
                        tokenized_h2, word_weight_dictionary, 0.2
                    )

                    h3_tags = tree.xpath("//h3")
                    tokenized_h3 = []
                    for tag in h3_tags:
                        if tag.text is not None:
                            tokenized_h3 += self.tokenizeText(tag.text)
                    num_words_in_doc += len(tokenized_h3)
                    word_freq_dictionary = self.countWordFreq(
                        tokenized_h3, word_freq_dictionary
                    )
                    word_weight_dictionary = self.calculateWordWeight(
                        tokenized_h3, word_weight_dictionary, 0.1
                    )

                    # ----- measure <a> ------
                    a_tags = tree.xpath("//a")
                    tokenized_a = []
                    for tag in a_tags:
                        if tag.text is not None:
                            tokenized_a += self.tokenizeText(tag.text)
                    num_words_in_doc += len(tokenized_a)

                    word_freq_dictionary = self.countWordFreq(
                        tokenized_a, word_freq_dictionary
                    )
                    word_weight_dictionary = self.calculateWordWeight(
                        tokenized_a, word_weight_dictionary, 0.1
                    )
                    # ----- measure other non-important elements  ----

                    general_text_tags = tree.xpath(
                        "//text()[not(ancestor::h1 | ancestor::h2 | ancestor::h3 | ancestor::a | ancestor::title | ancestor::b | ancestor::strong | ancestor::em)]"
                    )
                    tokenized_general_tags = []
                    for tag in general_text_tags:
                        tokenized_general_tags += self.tokenizeText(tag)
                    num_words_in_doc += len(tokenized_general_tags)
                    word_freq_dictionary = self.countWordFreq(
                        tokenized_general_tags, word_freq_dictionary
                    )
                    word_weight_dictionary = self.calculateWordWeight(
                        tokenized_general_tags, word_weight_dictionary, 0.01
                    )

                    # ------ fine indices of each word ----------
                    text_list = tree.xpath(
                        "//text()[not(ancestor::script | ancestor::style)]"
                    )
                    plain_text = " ".join(text.strip() for text in text_list)
                    tokenized_text = self.tokenizeText(plain_text)
                    word_indices_dictionary = self.findWordIndices(
                        tokenized_text, word_indices_dictionary
                    )

                    # --------- insert result into database ----------
                    for word, freq in word_freq_dictionary.items():
                        if word in word_indices_dictionary:
                            token = word
                            doc_ID = relative_path
                            doc_URL = file_url
                            freq_in_doc = freq
                            indices = " ".join(
                                map(str, word_indices_dictionary.get(word))
                            )  # convert [] to str
                            importance_degree = word_weight_dictionary.get(word)
                            num_words_in_doc = num_words_in_doc
                            tf = math.log(freq_in_doc) + 1

                            full_list = [
                                doc_URL,
                                doc_title,
                                freq_in_doc,
                                indices,
                                importance_degree,
                                tf,
                            ]

                            if token in self.postings_dict:

                                self.postings_dict[token][doc_ID] = full_list
                            else:
                                self.postings_dict[token] = {doc_ID: full_list}
                            """ --------- original_dic: -----------
                            {
                                'school': {
                                    '0/10': ('fano.ics.uci.edu/cites/Author/Murray-Sherk.html', 'Murray Sherk', 2, '6 24', 0.02, 1.6931471805599454),
                                    '0/100': ('fano.ics.uci.edu/cites/Document/Fully-dynamic-min-cut.html', 'Fully-dynamic min-cut', 1, '35', 0.01, 1.0)å
                                },
                            }
                            """

                            if doc_ID in self.docID_map_token:
                                self.docID_map_token[doc_ID].append(token)
                            else:
                                self.docID_map_token[doc_ID] = [token]
                            """ ---------- docID_map_token ----------
                            {
                                '0/10': [
                                    'murray', 'sherk', 'univ', 'waterloo', 'school', 'computer', 'science', 
                                    'msherk', 'author', 'editor', 'reviewer', 'ary', 'eppstein', 'publications', 
                                    'citation', 'database', 'authors', 'fano', 'experimental', 'web', 'server', 
                                    'information', 'uc', 'irvine'
                                ],
                            }
                            """

        # ------------------------- after finishing loop, create 4 more columns df, idf, tf_idf, nomalized_vector ----------------
        print(
            "finish make [doc_ID, doc_URL, doc_title, freq_in_doc, indices, importance_degree, tf] dic"
        )
        print("start to process df,idf,tf-idf, NV")

        number_of_document = len(self.docID_map_token)
        for docID, terms_list in self.docID_map_token.items():
            for term in terms_list:

                term_posting_dict = self.postings_dict.get(term)  # dict
                df = len(term_posting_dict)
                idf = math.log(number_of_document / (1 + df))

                if docID in term_posting_dict:
                    doc_info = term_posting_dict.get(docID)
                    doc_info.append(df)  # 6th item in doc_info list
                    doc_info.append(idf)  # 7th item in doc_info list
                    tf_idf = doc_info[5] * idf
                    doc_info.append(tf_idf)  # 8th item in doc_info list

        print("finish calculating df, idf, tf_idf")
        print("start calculating normalized vector")

        for docID, token_list in self.docID_map_token.items():
            document_length = 0

            for token in token_list:
                docs_dict = self.postings_dict.get(token)
                if docID in docs_dict:
                    tf_idf = docs_dict[docID][8]
                    document_length += tf_idf**2
                else:
                    document_length = 0  # or handle the case when docID is not found

            document_length = math.sqrt(
                document_length
            )  # square root the calulated value to get document length
            for token in token_list:
                docs_dict = self.postings_dict.get(token)
                if docID in docs_dict:
                    doc_info = docs_dict.get(docID)
                    # print(doc_info)

                    tf_idf = doc_info[8]
                    nv = tf_idf / document_length
                    doc_info.append(nv)

            print("finish calculate everything for document:", docID)
        print("finish calculating nv eveyrthing")
        print("put info into sql")

        for token, docs_dict in self.postings_dict.items():
            for doc_ID, doc_info in docs_dict.items():

                doc_URL = doc_info[0]
                doc_title = doc_info[1]
                freq_in_doc = doc_info[2]
                indices = doc_info[3]
                importance_degree = doc_info[4]
                tf = doc_info[5]
                df = doc_info[6]
                idf = doc_info[7]
                tf_idf = doc_info[8]
                nv = doc_info[9]
                cursor.execute(
                    "INSERT INTO inverted_index VALUES(%s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s)",
                    (
                        token,
                        doc_ID,
                        doc_URL,
                        doc_title,
                        freq_in_doc,
                        indices,
                        importance_degree,
                        tf,
                        df,
                        idf,
                        tf_idf,
                        nv,
                    ),
                )
                conn.commit()

        print("finish to put in it to sql everything. DONE")

        cursor.close()
        conn.close()  # Close the connection

    def getQueryResult(self, query):
        # ----------- connect to DB --------------------
        conn = mysql.connector.connect(
            host="127.0.0.1", user="root", database="search_engine"
        )
        if conn.is_connected():
            cursor = conn.cursor()  # Create a cursor object to execute SQL queries

        cursor.execute("USE search_engine;")

        # ---------------- retrieve list of related documents from database ---------------------
        query_tokens = self.tokenizeText(query)
        sql_query = (
            "SELECT DISTINCT doc_ID FROM inverted_index WHERE token IN ({})".format(
                ",".join(["%s"] * len(query_tokens))
            )
        )
        cursor.execute(sql_query, query_tokens)
        document_list = cursor.fetchall()
        number_of_documents = CorpusProcessor.NUM_UNIQUE_DOCS

        user_query_dictionary = {}
        output = {}
        # EX) User query: "I am fool"
        # document list = [document list that contain 'I', 'am', 'fool']
        # user query dic= {'I':[tf,idf,tf-idf, NV], 'am':[tf,idf,tf-idf, NV], 'fool':[tf,idf,tf-idf, NV]}

        # ------------------ calculate cosine similarity and creat user query dictionary -----------------
        for query_token in query_tokens:
            count_token = query_tokens.count(query_token)
            tf = 1 + math.log(count_token)  # weight of token in query

            # df = len(self.postings_dict.get(query_token))
            cursor.execute(
                "SELECT df FROM inverted_index WHERE token = %s HAVING df IS NOT NULL LIMIT 1",
                (query_token,),
            )
            num_docs_contain_this_token = cursor.fetchone()
            df = num_docs_contain_this_token[0]

            idf = math.log(number_of_documents / (1 + df))
            tf_idf = tf * idf
            if query_token not in user_query_dictionary:
                user_query_dictionary[query_token] = [tf, idf, tf_idf]

        # calculating NV for each term
        user_query_length = math.sqrt(
            sum(value[2] ** 2 for value in user_query_dictionary.values())
        )
        for key, value in user_query_dictionary.items():
            normalized_vector = value[2] / user_query_length
            user_query_dictionary[key].append(normalized_vector)

        # print(user_query_dictionary)

        # ----------- get the result -------------
        for document in document_list:
            document_ID = document[0]
            placeholders = ", ".join(["%s"] * len(query_tokens))
            sql_query = "SELECT token, normalized_vector, importance_degree, doc_title, doc_URL FROM inverted_index WHERE doc_ID = %s AND token IN ({})".format(
                placeholders
            )
            cursor.execute(sql_query, [document_ID] + query_tokens)

            # cursor.execute(sql_query, [token] + query_tokens)
            results = cursor.fetchall()

            score = 0
            title = ""
            url = ""

            # print(results)
            for row in results:
                token = row[0]
                normalized_vector = row[1]
                importance_degree = row[2]
                user_query_normalized_vector = user_query_dictionary[token][3]
                score += (
                    normalized_vector * user_query_normalized_vector
                ) + importance_degree
                title = row[3]
                url = row[4]

            if document not in output:
                output[document] = (title, url, score)

        # sorted_output contains result docID:score in descending order
        sorted_output = dict(
            sorted(output.items(), key=lambda item: item[1][-1], reverse=True)
        )

        # ----------- close connection to DB --------------------
        cursor.close()
        conn.close()

        return list(sorted_output.values())[:20]  # list of lists, limit 20

        # return rows

    def main(self):
        # self.processCorpus()
        query = input("Type your query: ")
        result = self.getQueryResult(query)
        if not result is None:
            print(result)
        else:
            print("No result")


if __name__ == "__main__":
    limit = input(
        "Enter the limit of corpuses you want to process (or -1 to process all): "
    )
    indexer = CorpusProcessor(limit)
    indexer.main()
