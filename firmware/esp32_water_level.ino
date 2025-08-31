// ESP32 Water Level Monitor with HC-SR04
#include <WiFi.h>
// --- USER CONFIG (optional REST) ---
const char* WIFI_SSID = "YOUR_SSID";
const char* WIFI_PASS = "YOUR_PASS";
const char* REST_HOST = "your-project.firebaseio.com"; // example host
const int   REST_PORT = 80; // use 443 with WiFiClientSecure for HTTPS
const char* REST_PATH = "/water-level.json?auth=YOUR_TOKEN";
// -----------------------------------

const int TRIG = 5;
const int ECHO = 18;

long measureDistanceCM() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  long duration = pulseIn(ECHO, HIGH, 30000); // timeout 30ms
  if (duration == 0) return -1;
  float cm = duration / 58.0;
  return (long)cm;
}

void setup() {
  Serial.begin(115200);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  // Optional WiFi connect
  // WiFi.begin(WIFI_SSID, WIFI_PASS);
  // while (WiFi.status() != WL_CONNECTED) { delay(300); Serial.print("."); }
  // Serial.println("\nWiFi connected.");
  Serial.println("{"status":"ready"}");
}

void pushToREST(long cm) {
  WiFiClient client;
  if (!client.connect(REST_HOST, REST_PORT)) {
    Serial.println("{"error":"rest_connect_failed"}");
    return;
  }
  String body = String("{\"distance_cm\":") + cm + ",\"ts\":" + millis() + "}";
  String req = String("POST ") + REST_PATH + " HTTP/1.1\r\n" +
               "Host: " + REST_HOST + "\r\n" +
               "Content-Type: application/json\r\n" +
               "Content-Length: " + body.length() + "\r\n\r\n" +
               body;
  client.print(req);
  delay(50);
  client.stop();
}

void loop() {
  long cm = measureDistanceCM();
  if (cm < 0) {
    Serial.println("{"error":"no_echo"}");
  } else {
    Serial.print("{"distance_cm":");
    Serial.print(cm);
    Serial.print(","ts":");
    Serial.print(millis());
    Serial.println("}");
    // pushToREST(cm); // <-- enable after setting WiFi + REST config
  }
  delay(1000);
}
