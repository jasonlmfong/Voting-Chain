var catVotes = 0;

function catOnClick() {
  const xhttp = new XMLHttpRequest();
  xhttp.onload = function() {
    document.getElementById("cat clicks").innerHTML = this.responseText;
  }
  xhttp.open("GET", "0.0.0.0");
  xhttp.send();
  catVotes += 1;
  document.getElementById("cat clicks").innerHTML = catVotes;
};

var dogVotes = 0;

function dogOnClick() {
    dogVotes += 1;
    document.getElementById("dog clicks").innerHTML = dogVotes;
  };