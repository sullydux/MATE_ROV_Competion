#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h> 
#include <PID_v1.h>
#include <string>
#include <cmath>

/*
Hello dear readers of this code. This will be my only comment.
Good luck furture Charlie or other viewers/editors.
*/

String Number_De_Company = "Unknown";

const char* ssid     = "NSA Van 37";
const char* password = "Hard-Pass";
const int servoPin = 13;
int on_mission = 0;


struct A_Sixteenth_Of_All_Data_Ever_Needed_To_Function {
	String Number_De_Company = Number_De_Company;
	String Zulu_Time;
	float Pressure;
	float Depth;
	float Sun_Levels;
	float Temperature;
};
A_Sixteenth_Of_All_Data_Ever_Needed_To_Function All_Data_Ever_Needed_To_Function[16];

WebServer server(80);
Servo myservo;

const char PAGE[] PROGMEM = R"rawliteral(
<!DOCTYPE html><html>
<head>
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<title>ESP32 Float Web Server</title>
	<link rel="icon" href="data:,">
	<style>
		html { font-family: monospace; display: inline-block; margin: 0px auto; text-align: center; }
		.button { background-color: #60a5fa; border: none; color: white; padding: 16px 40px;
			font-size: 32px; margin: 2px; cursor: pointer; }
	</style>
</head>
<body>
	<h1>ESP32 Float Web Server</h1>
	<p><button class="button" data-name="Start_Mission">Start Mission (button wont work untill finish)</button></p>
	<p><button class="button" data-name="Reload">Reload Chart</button></p>
	<p><button class="button" data-name="Reset">Reset Data (no confirmation)</button></p>
	<p><button class="button" data-name="Emergency_Emergency_Emergency">Insert Emergency Data</button></p>
	<script>
		document.querySelectorAll("button").forEach(b => {
			b.onclick = () => fetch("/" + b.dataset.name).catch(() => {});
		});
	</script>
</body>
</html>
)rawliteral";

void handleRoot() {
	server.send_P(200, "text/html", PAGE);
}

void Start_Mission() {
	Serial.println("Start_Mission");
	server.send(200, "text/plain", "'Things are now set in motion that cannot be undone' - Olórin");
	on_mission
}

void Reload() {
	Serial.println("Reload");
	server.send(200, "text/plain", "Friendly reminder: if you spam this no one will be angry");
}

void Reset() {
	Serial.println("Reset");
	server.send(200, "text/plain", "Warning - Data has been completely and uterly swept into the trash can - Warning");
	for (int i = 0; i < 16; i++){
		All_Data_Ever_Needed_To_Function[i].Number_De_Company = Number_De_Company;
		All_Data_Ever_Needed_To_Function[i].Zulu_Time = "2027-01-01 00:00:01";
		All_Data_Ever_Needed_To_Function[i].Depth = 0.0;
		All_Data_Ever_Needed_To_Function[i].Pressure = 0.0;
		All_Data_Ever_Needed_To_Function[i].Sun_Levels = 0.0;
		All_Data_Ever_Needed_To_Function[i].Temperature = 0.0;
	}
}

void Emergency_Emergency_Emergency() {
	Serial.println("Emergency_Emergency_Emergency");
	server.send(200, "text/plain", "Warning - Emergency Data has been loaded - Warning");
	for (int i = 0; i < 16; i++){
		All_Data_Ever_Needed_To_Function[i].Number_De_Company = Number_De_Company;
		All_Data_Ever_Needed_To_Function[i].Zulu_Time = "2038-01-19 03:14:06";
		All_Data_Ever_Needed_To_Function[i].Depth = 9324726210.0343;
		All_Data_Ever_Needed_To_Function[i].Pressure = 65536.0;
		All_Data_Ever_Needed_To_Function[i].Sun_Levels = 256.0;
		All_Data_Ever_Needed_To_Function[i].Temperature = 16.0;
	}
}

void handleNotFound() {
	server.send(404, "text/plain", "Not found");
}

void setup() {
	Serial.begin(115200);

	WiFi.softAP(ssid, password);
	Serial.println("");
	Serial.println("IP address: ");
	Serial.println(WiFi.softAPIP());

	server.on("/", handleRoot);
	server.on("/Start_Mission", Start_Mission);
	server.on("/Reload", Reload);
	server.on("/Reset", Reset);
	server.on("/Emergency_Emergency_Emergency", Emergency_Emergency_Emergency);
	server.onNotFound(handleNotFound);
	server.begin();
}

void loop() {
	server.handleClient();
}