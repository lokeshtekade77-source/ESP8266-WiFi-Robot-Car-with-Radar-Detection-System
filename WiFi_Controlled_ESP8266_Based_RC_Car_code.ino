#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

// ===== MOTOR PINS =====
int in1 = D5;  // LEFT MOTOR
int in2 = D6;
int in3 = D7;  // RIGHT MOTOR
int in4 = D8;

// ===== BUZZER =====
int buzPin = D2;

// ===== SPEED =====
int speedVal = 700;

// ===== SERVO + ULTRASONIC =====
Servo radarServo;

int servoPin = D3;
int trigPin = D4;
int echoPin = D0;

// ===== RADAR =====
int angle = 0;
int dir = 1;
unsigned long lastRadar = 0;
String radarData = "0,0";

// ===== WIFI =====
String ssid = "MyESPwifi";
String pass = "11111111";

ESP8266WebServer server(80);

// ===== SAFETY =====
unsigned long lastCmdTime = 0;

// ===== DECLARATIONS =====
void sendRadarData();
void radarPage();

// ================= SETUP =================
void setup(){

Serial.begin(115200);

pinMode(in1, OUTPUT);
pinMode(in2, OUTPUT);
pinMode(in3, OUTPUT);
pinMode(in4, OUTPUT);
pinMode(buzPin, OUTPUT);

pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);

radarServo.attach(servoPin);

Stop();

// WIFI
WiFi.begin(ssid, pass);
Serial.print("Connecting");

while(WiFi.status()!=WL_CONNECTED){
  delay(300);
  Serial.print(".");
}

Serial.println();
Serial.print("IP: ");
Serial.println(WiFi.localIP());

// ROUTES
server.on("/", handleCommand);
server.on("/radar", radarPage);
server.on("/data", sendRadarData);

server.begin();

startupSound();
}

// ================= LOOP =================
void loop(){

server.handleClient();
handleRadar();

// 🔥 AUTO STOP (important)
if(millis() - lastCmdTime > 1000){
  Stop();
}
}

// ================= COMMAND =================
void handleCommand(){

if(server.hasArg("State")){

String cmd = server.arg("State");

Serial.println(cmd);

// update timer
lastCmdTime = millis();

// movement
if(cmd=="F") Forward();
else if(cmd=="B") Backward();
else if(cmd=="L") TurnLeft();
else if(cmd=="R") TurnRight();
else if(cmd=="S") Stop();

// speed
else if(cmd=="1") speedVal = 400;
else if(cmd=="2") speedVal = 700;
else if(cmd=="3") speedVal = 1023;

// siren
else if(cmd=="V") sirenSound();
}

server.send(200,"text/plain","OK");
}

// ================= RADAR =================
void handleRadar(){

if(millis() - lastRadar < 60) return;
lastRadar = millis();

radarServo.write(angle);

// ultrasonic
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

long dur = pulseIn(echoPin, HIGH, 8000);
int dist = dur * 0.034 / 2;

radarData = String(angle) + "," + String(dist);

// click sound
if(dist > 0 && dist < 80){
  tone(buzPin, 2000, 15);
}

// sweep
angle += dir;
if(angle >= 180 || angle <= 0) dir = -dir;
}

// ================= MOTOR CONTROL =================

// ✅ FIXED FORWARD/BACKWARD
void Forward(){
digitalWrite(in1, HIGH);
digitalWrite(in2, LOW);

digitalWrite(in3, HIGH);
digitalWrite(in4, LOW);
}

void Backward(){
digitalWrite(in1, LOW);
digitalWrite(in2, HIGH);

digitalWrite(in3, LOW);
digitalWrite(in4, HIGH);
}

// ✅ FIXED TURNING
void TurnRight(){
// left forward, right backward
digitalWrite(in1, HIGH);
digitalWrite(in2, LOW);

digitalWrite(in3, LOW);
digitalWrite(in4, HIGH);
}

void TurnLeft(){
// right forward, left backward
digitalWrite(in1, LOW);
digitalWrite(in2, HIGH);

digitalWrite(in3, HIGH);
digitalWrite(in4, LOW);
}

void Stop(){
digitalWrite(in1, LOW);
digitalWrite(in2, LOW);
digitalWrite(in3, LOW);
digitalWrite(in4, LOW);
}

// ================= SOUNDS =================
void startupSound(){
tone(buzPin, 800, 100);
delay(150);
tone(buzPin, 1200, 100);
}

void sirenSound(){
for(int i=0;i<8;i++){
  tone(buzPin, 800);
  delay(80);
  tone(buzPin, 1500);
  delay(80);
}
noTone(buzPin);
}

// ================= RADAR DATA =================
void sendRadarData(){
server.send(200,"text/plain",radarData);
}

// ================= RADAR WEB =================
void radarPage(){

String page = R"====(
<!DOCTYPE html>
<html>
<head>
<style>
body{background:black;color:lime;text-align:center;}
canvas{background:black;}
</style>
</head>

<body>

<h2>RADAR</h2>
<canvas id="c" width="600" height="400"></canvas>

<script>

var c=document.getElementById("c");
var ctx=c.getContext("2d");

function draw(angle,dist){

ctx.fillStyle="rgba(0,0,0,0.2)";
ctx.fillRect(0,0,600,400);

var cx=300, cy=400;

// grid
ctx.strokeStyle="green";
for(let r=60;r<=300;r+=60){
ctx.beginPath();
ctx.arc(cx,cy,r,Math.PI,2*Math.PI);
ctx.stroke();
}

// sweep
var x=cx+300*Math.cos(angle*Math.PI/180);
var y=cy-300*Math.sin(angle*Math.PI/180);

ctx.beginPath();
ctx.moveTo(cx,cy);
ctx.lineTo(x,y);
ctx.strokeStyle="lime";
ctx.stroke();

// object
if(dist>0 && dist<200){
var dx=cx+dist*2*Math.cos(angle*Math.PI/180);
var dy=cy-dist*2*Math.sin(angle*Math.PI/180);

ctx.beginPath();
ctx.arc(dx,dy,5,0,6.28);
ctx.fillStyle="red";
ctx.fill();
}
}

setInterval(()=>{
fetch("/data")
.then(r=>r.text())
.then(t=>{
let p=t.split(",");
draw(parseInt(p[0]),parseInt(p[1]));
});
},80);

</script>

</body>
</html>
)====";

server.send(200,"text/html",page);
}