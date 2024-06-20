import React, { useEffect } from "react";
import { useState } from "react";
import Header from "../Components/Header";
import ResultBox from "../Components/ResultBox";
import SearchBox from "../Components/SearchBox";
import { useParams, useLocation, json } from "react-router-dom";

function Result(){
    // const location = useLocation();
    // const data = location.state;
    const {query} = useParams();
    const [result, setResult] = useState([]);
    
    useEffect(() => {

        // fetch data
        async function fetchData(){
            try{
                const response = await fetch("http://localhost:5000/");
                const jsonData = await response.json();
                // console.log(jsonData) // log out search result from get method
                setResult(jsonData["result"])
                // console.log(jsonData["result"])
            } catch(error) {
                console.log('Fetch result Error: ', error)
            }
        }
        fetchData()
    }, [query])

    useEffect(() => {
        // console.log(result);
    }, [result])

    return (
        <div>
            <Header />
            {/* <SearchBox placeholder={data.userQuery}/> */}
            <SearchBox placeholder={query} marginTop = "100px" result={result} setResult={setResult} />
            <ResultBox result={result} />
           

        </div>
    )     
}

export default Result;

