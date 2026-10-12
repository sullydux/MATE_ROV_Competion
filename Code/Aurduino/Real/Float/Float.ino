#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h>

const char* ssid     = "NSA Van 32";
const char* password = "Hard-Pass";

WebServer server(80);
Servo myservo;

const int ledPin16 = 16;
const int ledPin17 = 17;
const int servoPin = 13;

String statePin16 = "off";
String statePin17 = "off";
int turny = 0;

const char PAGE[] PROGMEM = R"rawliteral(
<!DOCTYPE html><html>
<head>
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<link rel="icon" href="data:,">
	<style>
		html { font-family: monospace; display: inline-block; margin: 0px auto; text-align: center; }
		.button { background-color: yellowgreen; border: none; color: white; padding: 16px 40px;
			font-size: 32px; margin: 2px; cursor: pointer; }
		.button2 { background-color: gray; }
	</style>
</head>
<body>
	<h1>ESP32 Web Server</h1>
	<p>Control Servo State | Current: <span id="pos">-</span></p>
	<p><button id="b16" class="button">RIGHT</button></p>
	<p><button id="b17" class="button">ON</button></p>
	<script>
		let s16 = "off", s17 = "off";
		const b16 = document.getElementById("b16");
		const b17 = document.getElementById("b17");
		const posEl = document.getElementById("pos");

		function update(d) {
			s16 = d.s16;
			s17 = d.s17;
			b16.textContent = (s16 === "off") ? "RIGHT" : "LEFT";
			b16.className = "button" + (s16 === "off" ? "" : " button2");
			b17.textContent = (s17 === "off") ? "ON" : "OFF";
			b17.className = "button" + (s17 === "off" ? "" : " button2");
			posEl.textContent = d.pos;
		}

		function send(path) {
			fetch(path).then(r => r.json()).then(update).catch(() => {});
		}

		b16.onclick = () => send(s16 === "off" ? "/16/on" : "/16/off");
		b17.onclick = () => send(s17 === "off" ? "/17/on" : "/17/off");

		send("/state");
		setInterval(() => send("/state"), 2000);
	</script>
</body>
</html>
)rawliteral";

void sendState() {
	String json = "{\"s16\":\"" + statePin16 + "\",\"s17\":\"" + statePin17 + "\",\"pos\":" + String(myservo.read()) + "}";
	server.send(200, "application/json", json);
}

void handleRoot() {
	server.send_P(200, "text/html", PAGE);
}

void handle16On() {
	statePin16 = "on";
	myservo.write(0);
	sendState();
}

void handle16Off() {
	statePin16 = "off";
	myservo.write(180);
	sendState();
}

void handle17On() {
	statePin17 = "on";
	turny = 0;
	sendState();
}

void handle17Off() {
	statePin17 = "off";
	turny = 1;
	sendState();
}

void handleNotFound() {
	server.send(404, "text/plain", "Not found");
}

void setup() {
	Serial.begin(115200);

	pinMode(ledPin16, OUTPUT);
	digitalWrite(ledPin16, 0);
	pinMode(ledPin17, OUTPUT);
	digitalWrite(ledPin17, 0);

	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);

	myservo.setPeriodHertz(50);
	myservo.attach(servoPin, 500, 2400);
	myservo.write(90);

	WiFi.softAP(ssid, password);
	Serial.println("");
	Serial.println("IP address: ");
	Serial.println(WiFi.softAPIP());

	server.on("/", handleRoot);
	server.on("/state", sendState);
	server.on("/16/on", handle16On);
	server.on("/16/off", handle16Off);
	server.on("/17/on", handle17On);
	server.on("/17/off", handle17Off);
	server.onNotFound(handleNotFound);
	server.begin();
}

void loop() {
	server.handleClient();

	if (turny == 1) {
		myservo.write(180);
		myservo.write(0);
	}
}