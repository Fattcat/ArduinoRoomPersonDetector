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

  server.on("/red_led_on", HTTP_GET, handleRedLedOn);
  server.on("/red_led_off", HTTP_GET, handleRedLedOff);
  server.begin();
}

void loop()
{
  int laserState = digitalRead(laserPin);

  if (laserState == HIGH)
  {
    // Laser modul je prerušený
    digitalWrite(redLEDPin, HIGH); // Zapne červenú LED diódu
  }
  else
  {
    // Laser modul nie je prerušený
    digitalWrite(redLEDPin, LOW); // Vypne červenú LED diódu
  }

  server.handleClient();
  delay(1000); // Interval prečítania stavu laserového modulu
}

void handleRedLedOn()
{
  digitalWrite(redLEDPin, HIGH); // Zapne červenú LED diódu
}

void handleRedLedOff()
{
  digitalWrite(redLEDPin, LOW); // Vypne červenú LED diódu
}
