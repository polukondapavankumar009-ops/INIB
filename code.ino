#include <WiFi.h>


const char* ssid = "LED";
const char* password = "123456789";

WiFiServer server(80);

int ledPin = 2;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {

  WiFiClient client = server.available();

  if (!client) {
    return;
  }

  String request = client.readStringUntil('\r');
  client.flush();

  if (request.indexOf("/LED=ON") != -1) {
    digitalWrite(ledPin, HIGH);
  }

  if (request.indexOf("/LED=OFF") != -1) {
    digitalWrite(ledPin, LOW);
  }

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");

  client.println("<html>");
  client.println("<h1>Smart LED Control</h1>");
  client.println("<a href=\"/LED=ON\">Turn LED ON</a><br>");
  client.println("<a href=\"/LED=OFF\">Turn LED OFF</a>");
  client.println("</html>");
}