const Client = require("./client"); 

//create client
const voteClient = new Client(); 

var catVotes = 0;
var dogVotes = 0;

//listen to server response and save votes to catVotes and dogVotes
voteClient.sendMessage("GET Votes HTTP/1.1") 
.then((data) => { 
console.log("Received: ${data}");
catVotes = data["cat"];
dogVotes = data["cat"];
}).catch((err) => console.error(err));  

function catOnClick() {
  //add vote for cat
  catVotes += 1;
  //display both
  document.getElementById("cat clicks").innerHTML = catVotes;
  document.getElementById("dog clicks").innerHTML = dogVotes;
  //send cat vote to chain server
  voteClient.sendMessage("POST Cat HTTP/1.1") 
  .catch((err) => console.error(err));
};

function dogOnClick() {
  //add vote for dog
  dogVotes += 1;
  //display both
  document.getElementById("cat clicks").innerHTML = catVotes;
  document.getElementById("dog clicks").innerHTML = dogVotes;
  //send dog vote to chain server
  voteClient.sendMessage("POST Dog HTTP/1.1") 
  .catch((err) => console.error(err));
};


