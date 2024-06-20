import React from "react";


import Header from "../Components/Header";
import SearchBox from "../Components/SearchBox";




function Home(){
    return (
        <div>
            <Header />
            <SearchBox 
                placeholder="What are you looking for?"
                marginTop = "200px"
            />
            
        </div>
    )     
}

export default Home;

