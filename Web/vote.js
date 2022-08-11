sendAMessage("\\getTotalVotes")
//server.listen(8080, "0.0.0.0", backlog, callback);
//listen to server response and save votes to catVotes and dogVotes

var catVotes = 0;
var dogVotes = 0;

function catOnClick() {
  //add vote for cat
  catVotes += 1;
  //display both
  document.getElementById("cat clicks").innerHTML = catVotes;
  document.getElementById("dog clicks").innerHTML = dogVotes;
  sendAMessage("\\voteCat")
};

function dogOnClick() {
  //add vote for dog
  dogVotes += 1;
  //display both
  document.getElementById("cat clicks").innerHTML = catVotes;
  document.getElementById("dog clicks").innerHTML = dogVotes;
  sendAMessage("\\voteDog")
};

//send message to server backend
function sendAMessage(msg) {
  var c = net.createConnection(8080, "0.0.0.0");
  c.on("connect", function() {
  // connected to TCP server.
  c.write(msg);
  });
}