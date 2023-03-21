#include <SoftwareSerial.h>
#include <SimpleCLI.h>
#include <ESP8266WiFi.h>

const byte rxPin = 5;
const byte txPin = 4;
SoftwareSerial Serial2(rxPin, txPin);

SimpleCLI cli;

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600);
  
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  
  Serial.println("\nStarted");
  
  Command apCmd = cli.addCmd("ap", [](cmd* ptr){
    Command cmd(ptr);
    String ssid = cmd.getArgument("ssid").getValue();
    String password = cmd.getArgument("password").getValue();
    String channel = cmd.getArgument("channel").getValue();
    
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    WiFi.softAP(ssid.c_str(), password.c_str(), channel.toInt());//, hidden, max_connection);

    Serial2.println("connect -ssid \"" + ssid + "\" -password \"" + password + "\"");
    
    Serial.println("Started AP");
    Serial.println("SSID: " + ssid);
    Serial.println("Password: " + password);
    Serial.println("Channel: " + channel);
  });
  apCmd.addPosArg("s/sid");
  apCmd.addPosArg("p/assword");
  apCmd.addPosArg("c/h/annel");
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readString();
    cli.parse(input);
  }
  if(Serial2.available()){
    Serial.print(Serial2.readString());
  }
}
