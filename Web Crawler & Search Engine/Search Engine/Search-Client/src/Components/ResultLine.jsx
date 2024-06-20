import React from "react";

function ResultLine(props){
    let url = props.url;

    // Check if the URL starts with http:// or https:// so that it's recognized as an absolute url
    if (!url.startsWith('http://') && !url.startsWith('https://')) 
        url = 'http://' + url;
    

    return(
        <div className="resultLine">
            <h1>{props.title}</h1>
            <a href={url}>{url}</a>
        </div>
    )
}

export default ResultLine;