import { useState, useEffect, useParams } from 'react';
import React from "react";
import { json, useNavigate } from 'react-router-dom';
import axios from 'axios'


function SearchBox(props){

    // -------- hooks -----------
    const navigate = useNavigate();
    const [query, setQuery] = useState("");
    const setResult = props.setResult;
    // useEffect(()=>{
    //     fetchData();
    // }, []);


    // -------- functions -----------
    // async function fetchData(){
    //     try{
    //         const response = await fetch("http://localhost:5000/");
    //         const jsonData = await response.json();
    //         // console.log(jsonData) // log out search result from get method
    //         // setResult(jsonData["result"])     
    //         // console.log(result)  
    //         return jsonData["result"]

    //     } catch(error) {
    //         console.log('Error: ', error)
    //     }
    // }

    async function postData(data){
        try{
            const response = await fetch("http://localhost:5000/",{
                method: 'POST',
                headers: {'Content-Type': 'application/json'},
                body: JSON.stringify({data})
            });
            const jsonData = await response.json();
            // console.log(jsonData)  // log out input query from post method
        } catch(error) {
            console.log('Error: ', error)
        }


        // axios.post('http://127.0.0.1:5000/', data, {  withCredentials: true    })
        // .then (response => console.log(response.data))
        // .catch(err => console.log(err))
    }

    function handleInputChange(event){
        // console.log(event.target.value);
        setQuery(event.target.value);
    }

    async function handleSubmit(event){
        event.preventDefault();
        
        let regex = /^[^a-zA-Z0-9]+$/;

        if (query === "" || regex.test(query)) return;
        const data = {
            query: query
        }
        await postData(data);

        navigate(`/result/${query}`)

        
    }

    

    // -------- returned component -----------
    
    return(
        <div className="searchBox" style={{marginTop: `${props.marginTop}`}}> 
            <a href="/">
                <img className="logo" src="anteater.png" alt="Logo"/>
            </a>            
            <form onSubmit={handleSubmit}>
                <input 
                    onChange={handleInputChange} 
                    type="text" 
                    placeholder={props.placeholder}
                    value={query}
                />
                <button type="submit">Go</button>
            </form>
            
        </div>
    )
}

export default SearchBox
// export {result};