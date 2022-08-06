//load polls data to store separately, for the addition of new polls
//const users = require("./pollsJason.json");

//console.log(users);

fetch("./students.json").then(response => {
   return response.json();
}).then(jsondata => console.log(jsondata));

let polls = [
    { name: "kirby character", "active status": "yes", "votes": "10" }
];

//table builder
function generateTableHead(table, data) {
    let thead = table.createTHead();
    let row = thead.insertRow();
    for (let key of data) {
        let th = document.createElement("th");
        let text = document.createTextNode(key);
        th.appendChild(text);
        row.appendChild(th);
    }
}
  
function generateTable(table, data) {
    for (let element of data) {
        let row = table.insertRow();
        for (key in element) {
            let cell = row.insertCell();
            let text = document.createTextNode(element[key]);
            cell.appendChild(text);
        }
    }
}
  
let table = document.querySelector("table");
let data = Object.keys(polls[0]);
generateTable(table, polls);
generateTableHead(table, data);

//https://bobbyhadz.com/blog/javascript-import-json-file