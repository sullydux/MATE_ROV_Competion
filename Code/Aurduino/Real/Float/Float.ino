#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h> 
#include <PID_v1.h>
#include <string>
#include <cmath>
#include "MS5837.h"
#include <BH1750.h>

/*
Hello dear readers of this code. This will be my only comment.
Webpage: http://192.168.4.1
Good luck furture Charlie or other viewers/editors.
*/

String Number_of_Company = "Unknown";

const char* ssid     = "NSA Van 37";
const char* password = "Hard-Pass";
const int servoPin = 13;
int on_mission = 0;
int go = 0;
int messurement_number = 1;

const int DATA_COUNT = 17;

struct part_data {
	String Number_De_Company = Number_of_Company;
	String Zulu_Time;
	float Pressure = 0.0;
	float Depth = 0.0;
	float Sun_Levels = 0.0;
	float Temperature = 0.0;
};
part_data data[DATA_COUNT];
MS5837 sensor;
BH1750 lightMeter;
WebServer server(80);
Servo myservo;

const char PAGE[] PROGMEM = R"rawliteral(
<!DOCTYPE html><html>
<head>
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<title>ESP32 Float Web Server</title>
	<link rel="icon" href="data:,">
	<style>
		:root { color-scheme: dark; }
		html { font-family: monospace; display: inline-block; margin: 0px auto; text-align: center; }
		.button { background-color: #60a5fa; border: none; color: white; padding: 16px 40px;
			font-size: 32px; margin: 2px; cursor: pointer; }
		table { border-collapse: collapse; }
		th, td { border: 1px solid #444; padding: 0.5rem; min-width: 2rem; text-align: center; }
	</style>
</head>
<body>
	<h1>ESP32 Float Web Server</h1>
	<p><button class="button" data-name="Start_Mission">Start Mission</button></p>
	<p><button class="button" data-name="Reload">Reload Chart</button></p>
	<p><button class="button" data-name="Reset">Reset Data (no confirmation)</button></p>
	<p><button class="button" data-name="Emergency_Emergency_Emergency">Insert Emergency Data</button></p>
	<script>
		const keys = ["company", "zulu", "pressure", "depth", "light", "temp"];
		function fill(d) {
			const rows = document.querySelectorAll("table tr");
			d.data.forEach((e, c) => keys.forEach((k, r) => {
				rows[r + 1].cells[c + 1].textContent = e[k];
			}));
		}
		document.querySelectorAll("button").forEach(b => {
			b.onclick = () => {
				fetch("/" + b.dataset.name)
					.then(r => b.dataset.name === "Reload" ? r.json().then(fill) : null)
					.catch(() => {});
			};
		});
	</script>
	<table>
		<tr>
			<th>Depth: </th>
			<th>-2M Way Down</th><th>-2M Way Down</th><th>-2M Way Down</th><th>-2M Way Down</th><th>-2M Way Down</th><th>-2M Way Down</th><th>-2M Way Down</th><th>-2M Way Down</th><th>-4M</th><th>-3.5M</th><th>-3M</th><th>-2.5M</th><th>-2M</th><th>-1.5M</th><th>-1M</th><th>-0.5M</th><th>0M</th>
		</tr>
		<tr>
			<th>Company Number</th>
			<td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td>
		</tr>
		<tr>
			<th>Zulu Time</th>
			<td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td>
		</tr>
		<tr>
			<th>Pressure</th>
			<td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td>
		</tr>
		<tr>
			<th>Depth</th>
			<td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td>
		</tr>
		<tr>
			<th>Light</th>
			<td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td>
		</tr>
		<tr>
			<th>Temperature</th>
			<td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td><td></td>
		</tr>
	</table>
</body>
</html>
)rawliteral";

void handleRoot() {
	server.send_P(200, "text/html", PAGE);
}

void Start_Mission() {
	Serial.println("Start_Mission");
	if (on_mission == 1) {
		server.send(451, "text/plain", "Impatient for next mission art thou.");
		messurement_number = 1;
		return;
	}
	else {
		server.send(200, "text/plain", "'Things are now set in motion that cannot be undone' - Gandalf");
		on_mission = 1;
    myservo.write(0);
    delay(200);
    myservo.write(180);
    delay(200);
		sensor.read();
		data[messurement_number].Sun_Levels = lightMeter.readLightLevel()
		data[messurement_number].Pressure = sensor.pressure()
		on_mission = 0;
		messurement_number = 1;
		return;
	}
}

void Reload() {
	Serial.println("Reload");
	String json = "{\"data\":[";
	for (int i = 0; i < DATA_COUNT; i++) {
		if (i > 0) json += ",";
		json += "{\"company\":\"" + data[i].Number_De_Company + "\"";
		json += ",\"zulu\":\"" + data[i].Zulu_Time + "\"";
		json += ",\"pressure\":" + String(data[i].Pressure, 2);
		json += ",\"depth\":" + String(data[i].Depth, 2);
		json += ",\"light\":" + String(data[i].Sun_Levels, 2);
		json += ",\"temp\":" + String(data[i].Temperature, 2);
		json += "}";
	}
	json += "]}";
	server.send(200, "application/json", json);
}

void Reset() {
	Serial.println("Reset");
	server.send(200, "text/plain", "Warning - Data has been completely and uterly swept into the trash can - Warning");
	for (int i = 0; i < DATA_COUNT; i++){
		data[i].Number_De_Company = Number_of_Company;
		data[i].Zulu_Time = "0000-00-00 00:00:00";
		data[i].Depth = 0.0;
		data[i].Pressure = 0.0;
		data[i].Sun_Levels = 0.0;
		data[i].Temperature = 0.0;
	}
}

void Emergency_Emergency_Emergency() {
	Serial.println("Emergency_Emergency_Emergency");
	server.send(200, "text/plain", "Warning - Emergency Data has been loaded - Warning");
	for (int i = 0; i < DATA_COUNT; i++){
		data[i].Number_De_Company = Number_of_Company;
		data[i].Zulu_Time = "2038-01-19 03:14:06";
		data[i].Depth = 4294967296;
		data[i].Pressure = 65536.0;
		data[i].Sun_Levels = 256.0;
		data[i].Temperature = 16.0;
	}
}

void handleNotFound() {
	server.send(404, "text/plain", "Not found");
}

void setup() {
	Serial.begin(115200);
	Wire.begin();
	lightMeter.begin();

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
  myservo.setPeriodHertz(50);
  myservo.attach(servoPin, 500, 2400);


	Reset();
	Reload();
}

void loop() {
	server.handleClient();
}