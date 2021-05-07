char homepageFirstPart[] PROGMEM = R"=====(
<html>
<head>
<style>
h1 {
color: white;
font-family: sans-serif;
font-size:80vw;
margin:0;
}

#progressbar {
  width: 80%;
  margin: 0 auto;
  border-radius: 13px;
  padding: 5px;
  border-style: solid;
  border-color: white;
  border-width: thick;
}

#progressbar>div {
  background-color: white;
  width: 40%;
  /* Adjust with JavaScript */
  height: 100px;
  border-radius: 10px;
}

.center {
  margin: 0;
  position: absolute;
  top: 50%;
  left: 50%;
  -ms-transform: translate(-50%, -50%);
  transform: translate(-50%, -50%);
  width: 100%;
  height: 100%;
}
</style>
</head>
<body>

<div style="width:100%;height:10%;"></div>

<div style="width:100%;height:60%;text-align:center;">
  <h1> <span id="count">0</span> </h1>
</div>

<div style="width:100%;height:20%;text-align:center">
  <div id="progressbar">
    <div id="bar"></div>
  </div>
</div>

<div id="bottomDiv" style="width:100%;height:10%;"></div>

</body>

<script>
var limit = 10;
var count = 5;

try{
var socket = new WebSocket('ws://' + location.hostname + ':81/');
socket.onopen = function () {
  console.log("Opened socket");
};
socket.onerror = function (error) {
};
socket.onmessage = function (e) {
  console.log('Server: ', e.data);
  if( e.data.includes("Error") ){
    //document.getElementById("bottomDiv").innerHTML = e.data;
  }
  else{
  count = Number(e.data);
  updateView();
  //var date = new Date;
  //document.getElementById("bottomDiv").innerHTML = date.toString();
  }
};

socket.onclose = function () {
  console.log('WebSocket connection closed');
};
}
catch{}

function pollCount(){
  var xhr = new XMLHttpRequest();
  xhr.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      count = Number(this.responseText);
      updateView();
    }
  };
  xhr.open("GET", "/count", true);
  xhr.send();
}

function pollLimit(){
  var xhr = new XMLHttpRequest();
  xhr.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      limit = Number(this.responseText);
      updateView();
    }
  };
  xhr.open("GET", "/limit", true);
  xhr.send();
}

function updateColor(){
document.body.style.backgroundColor = "red";
}

function updateProgressBar(){
  percentage = (count/limit) * 100;
  if(percentage > 100){
  percentage = 100;
  }
  if(percentage < 0){
  percentage = 0;
  }
  
  document.getElementById("bar").style.width = percentage + "%";
  
}

function updateBackground(){
  var color = "#99CB38";
  if(count >= limit){
  color = "red";
  }
  document.body.style.backgroundColor = color;
}

function pollingFunction()
{
  console.log("updating!");
  pollCount();
  updateView();
}

function updateView(){
  document.getElementById("count").innerHTML = count;
  updateProgressBar();
  updateBackground();
}

function initPage(){
  pollLimit();
  pollCount();
  updateView();
}

initPage();
</script>

</html>
)=====";
