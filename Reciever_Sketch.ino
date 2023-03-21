#include <SoftwareSerial.h>
#include <SimpleCLI.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const byte rxPin = 4;
const byte txPin = 5;
SoftwareSerial Serial2(rxPin, txPin);

SimpleCLI cli;

unsigned long lastTime = 0;

String ssid;
String pswd;
bool connect;
unsigned long contime;

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  Serial.println("\nStarted");

  Command connectCmd = cli.addCmd("connect", [](cmd * ptr) {
    Command cmd(ptr);
    ssid = cmd.getArgument("ssid").getValue();
    pswd = cmd.getArgument("password").getValue();
    connect = true;

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    WiFi.begin(ssid.c_str(), pswd.c_str());

    Serial2.println("OK");

    Serial.println("Connecting to");
    Serial.println("SSID: " + ssid);
    Serial.println("Password: " + pswd);

    for (int i = 0; i < 1000 && WiFi.status() != WL_CONNECTED; i++) {
      delay(10);
    }

    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("Connected!");
      Serial2.println("Connected!");
      contime = millis();
    } else {
      Serial.println("Error");
      Serial2.println("Error");
      WiFi.disconnect();
      connect = false;
    }
  });
  connectCmd.addPosArg("s/sid");
  connectCmd.addPosArg("p/assword");
}

void loop() {
  if (Serial2.available()) {
    String input = Serial2.readString();
    cli.parse(input);
  }
  if (millis() - lastTime > 2000 && connect) {
    /*
      lastTime = millis();
      HTTPClient http;
      http.begin("http://192.162.4.1/test.html");
      http.end();*/

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();

    Serial.print("Reconnecting...");
    Serial2.print("Reconnecting...");

    WiFi.begin(ssid.c_str(), pswd.c_str());
    for (int i = 0; i < 1000 && WiFi.status() != WL_CONNECTED; i++) {
      delay(10);
    }

    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("Connected!");
      Serial2.println("Connected!");
      connect = true;
      contime = millis();
    } else {
      Serial.println("Error");
      Serial2.println("Error");
      WiFi.disconnect();
    }
  }
}
