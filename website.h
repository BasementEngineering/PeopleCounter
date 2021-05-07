#include <avr/pgmspace.h>

char homepage[] PROGMEM = R"=====(
<html>
<head>
<style>h1{color:white;font-family:sans-serif;margin:0}body{margin:0}#wrapper{padding:0;margin:0;height:100%;width:100%;white-space:nowrap}#leftSpacer{margin:0;padding:0;display:block;float:left;height:100%}#content{margin:0;padding:0;widht:10%;height:100%;display:block;float:left}#progressbar{width:80%;margin:0 auto;border-radius:13px;padding:5px;border-style:solid;border-color:white;border-width:thick}#bar{background-color:white;width:40%;height:100%;border-radius:10px}.center{display:flex;justify-content:center;align-items:center}</style>
</head>
<body>
<div id="wrapper">
<div id="leftSpacer"></div>
<div id="content">
<div style="width:100%;height:5%"></div>
<div class="center" style="width:100%;height:70%;text-align:center">
<span><h1 id="count">0</h1></span>
</div>
<div style="width:100%;height:15%;text-align:center">
<div id="progressbar">
<div id="bar"></div>
</div>
</div>
<div style="width:100%;height:10%"></div>
</div>
</div>
</body>
<script>/*<![CDATA[*/var limit=9;var count=99;var portraitMode=false;try{var socket=new WebSocket('ws://'+location.hostname+':81/');socket.onopen=function(){console.log("Opened socket");};socket.onerror=function(error){};socket.onmessage=function(e){console.log('Server: ',e.data);count=Number(e.data);updateView();};socket.onclose=function(){console.log('WebSocket connection closed');};}
catch{}
function pollCount(){var xhr=new XMLHttpRequest();xhr.onreadystatechange=function(){if(this.readyState==4&&this.status==200){count=Number(this.responseText);updateView();}};xhr.open("GET","/count",true);xhr.send();}
function pollLimit(){var xhr=new XMLHttpRequest();xhr.onreadystatechange=function(){if(this.readyState==4&&this.status==200){limit=Number(this.responseText);updateView();}};xhr.open("GET","/limit",true);xhr.send();}
function updateColor(){document.body.style.backgroundColor="red";}
function updateProgressBar(){percentage=(count/limit)*100;if(percentage>100){percentage=100;}
if(percentage<0){percentage=0;}
document.getElementById("bar").style.width=percentage+"%";}
function updateBackground(){var color="#99CB38";if(count>=limit){color="red";}
document.body.style.backgroundColor=color;}
function pollingFunction()
{console.log("updating!");pollCount();updateView();}
function updateView(){adjustFontSize();document.getElementById("count").innerHTML=count;updateProgressBar();updateBackground();}
function adjustFontSize(){var fontSize=65;if(portraitMode){if(count>=10&&count<100){fontSize=50;}
else if(count>=100){fontSize=30;}}
else{fontSize=80;if(count>=100){fontSize=60;}}
console.log("Font size: "+fontSize);document.getElementById('count').setAttribute("style","font-size:"+fontSize+"vh;");}
function adjustToScreen(){var w=window.innerWidth;var h=window.innerHeight;var contentWidth=w;var spacerWidth=0;if(w<h){portraitMode=true;}
if(portraitMode){document.getElementById('leftSpacer').setAttribute("style","width:5%");document.getElementById('content').setAttribute("style","width:90%");}
else{spacerWidth=0;contentWidth=h;spacerWidth=Math.floor((w-contentWidth)/2);document.getElementById('leftSpacer').setAttribute("style","width:"+spacerWidth+"px");document.getElementById('content').setAttribute("style","width:"+contentWidth+"px");}
console.log("Content width: "+contentWidth);console.log("Spacer width: "+spacerWidth);}
function initPage(){pollLimit();pollCount();updateView();adjustToScreen();adjustFontSize();}
initPage();/*]]>*/</script>
</html>
)=====";

char correctionForm[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<body>

<h1>Settings<h1>
<form action="/setParameters">
  Set Count:<br>
  <input type="number" name="count" value="-1"><br>
  Set limit:<br>
  <input type="limit" name="limit" value="-1"><br>
  <input type="submit" value="Submit">
</form>
<p>-1 = no change</p>

</body>
</html>
)=====";
