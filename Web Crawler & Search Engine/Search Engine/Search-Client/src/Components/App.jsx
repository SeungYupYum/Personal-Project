import React from "react";
import {BrowserRouter, Routes, Route} from "react-router-dom";  
import Home from "../pages/Home";
import Result from "../pages/Result";



function App(){
    return (
        <div>
            <BrowserRouter>
                <Routes>
                    <Route path="/" element={<Home/>}/>
                    <Route path="/result/:query" element={<Result/>}/>
                </Routes>
            </BrowserRouter>
            
        </div>
    )     
}

export default App;
