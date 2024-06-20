import React, { useEffect } from "react";
import ResultLine from "./ResultLine";
import data from "../data";
// import { searchResults } from "./SearchBox";

function ResultBox(props){
    const {result} = props;
    // console.log(typeof(result)) //result is a python string althought it looks like a dict
    // console.log(result)



    if (typeof(result) === 'string'){
        let format_adjusted_result = result.replace(/'/g, '"');
        let json_result = []
        try {
            json_result = JSON.parse(format_adjusted_result); //to use json.parse(), string must have javascript json format
        
        } catch {
            json_result = [{title: 'Error in Json parsing (Please check Console.log to see your search results instead)', url: 'www.ics.uci.edu'}]
            console.log(format_adjusted_result)
        }
    
        return (
            <div>
                <div className="resultBox">
                    {json_result.map((item, index) => (
                        <ResultLine
                        key={index}
                        title={item.title}
                        url={item.url}
                    />
                    )) }
                </div>
            </div>
        )
    } else {
        return (
            <div>
                <div className="resultBox">
                    
                </div>
            </div>
        )
    }
}

export default ResultBox;