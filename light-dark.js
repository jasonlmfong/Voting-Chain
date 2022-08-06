var myStorage = window.localStorage;
var element;


//lightmode/darkmode controller
function storageIsLightMode() {
    return myStorage.getItem("light-mode") === "true";
}

function setLightMode() {
    element.classList.add("light-mode");
    myStorage.setItem("light-mode", true);
}

function setDarkMode() {
    element.classList.remove("light-mode");
    myStorage.setItem("light-mode", false);
}

function toggledl() {
    if(storageIsLightMode()) {
        setDarkMode();
    } else {
        setLightMode();
    }
}

window.addEventListener("DOMContentLoaded", function () {
    element = window.document.body;
    if(storageIsLightMode()) {
        setLightMode();
        window.document.getElementById("light-toggle").setAttribute("checked","checked");
    } else {
        setDarkMode();
    }
});