var catVotes = 0;

function catOnClick() {
  catVotes += 1;
  document.getElementById("cat clicks").innerHTML = catVotes;
};

var dogVotes = 0;

function dogOnClick() {
    dogVotes += 1;
    document.getElementById("dog clicks").innerHTML = dogVotes;
  };