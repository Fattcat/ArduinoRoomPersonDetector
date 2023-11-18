#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char *ssid = "your-ssid";
const char *password = "your-password";
const int laserPin = D1; // Pin pre laserový modul
const int redLEDPin = D2; // Pin pre červenú LED diódu
const int port = 80;

ESP8266WebServer server(port);

void setup()
{
  Serial.begin(115200);
  pinMode(laserPin, INPUT);
  pinMode(redLEDPin, OUTPUT);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(250);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, handleRequest);
  server.begin();
}

void loop()
{
  int laserState = digitalRead(laserPin);

  if (laserState == HIGH)
  {
    // Laser modul je prerušený
    digitalWrite(redLEDPin, HIGH); // Zapne červenú LED diódu
    sendCommandToOtherESP();
  }
  else
  {
    // Laser modul nie je prerušený
    digitalWrite(redLEDPin, LOW); // Vypne červenú LED diódu
  }

  server.handleClient();
  delay(1000); // Interval prečítania stavu laserového modulu
}

void sendCommandToOtherESP()
{
  // Implementujte kód pre odoslanie HTTP požiadavky na druhý ESP8266
  // Tu by ste mohli použiť funkciu klienta na odoslanie GET požiadavky na IP adresu a port druhého ESP8266
}
