from flask import Flask, request, jsonify
from flask_cors import CORS
import json
from dataProcessor import CorpusProcessor

app = Flask(__name__)
CORS(app, resources={r"/*"})


result_list_of_dicts = []
user_query = ""


@app.route("/", methods=["POST"])
def post_query():
    try:
        data = request.json.get("data")
        user_query = data["query"]

        search_result = getResult(user_query)
        result_list_of_dicts.clear()  # clear old data
        # can't use result_list_of_dicts = [] # unknown reason

        for title, url, value in search_result:
            if len(title) > 100:
                title = title[:100] + "..."

            title.replace("\n", "").replace("\xa0", "").replace(
                "\\", ""
            )  # remove escape character

            if not url.startswith("www."):
                url = "www." + url

            result_list_of_dicts.append({"title": title, "url": url})

        response_data = {
            "status": "success",
            "message": f"Received query: {user_query}",
        }
        # print(jsonify(response_data))

        return jsonify(response_data), 200
    except Exception as e:
        error_response = {"status": "error", "message": str(e)}
        print("error")
        return jsonify(error_response), 500


@app.route("/", methods=["GET"])
def get_data():
    data = {"result": f"{result_list_of_dicts}", "status": "success"}
    print(jsonify(data))
    return jsonify(data)


# -------------------------


def getResult(query):
    indexer = CorpusProcessor()  # construct an object of CorpusProcessor class
    result = indexer.getQueryResult(query)
    return result

    """ -------- EXAMPLE FORMAT of returned result from getQueryResult() -------
        [
            ('QUASAR: Quality Aware Sensing Architecture (ACM SIGMOD Record 2004)', 'www.ics.uci.edu/~dvk/pub/SIGMODR04_dvk.html',  0.571024809242835), 
            ('Fully-dynamic min-cut', 'fano.ics.uci.edu/cites/Document/Fully-dynamic-min-cut.html', 0.08568559496487349), 
            ('Info Session – Women in Information and Computer Sciences', 'wics.ics.uci.edu/category/news/info-session?afg12_page_id=2&afg44_page_id=4&afg34_page_id=4&afg15_page_id=2&afg42_page_id=2&afg22_page_id=2', 0.05803728206671481)
        ]
           
    """


# --------------------------

if __name__ == "__main__":
    # indexer = CorpusProcessor()  # construct an object of CorpusProcessor class
    # indexer.processCorpus()  # process the corpus before running app
    # (we can call processCorpus() with dataProcessor.py instead)

    app.run(host="0.0.0.0", debug=True)  # app runs on localhost:5000
