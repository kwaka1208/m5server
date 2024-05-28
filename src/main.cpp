#include <Arduino.h>
#include <M5Stack.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include "wifi_setting.h"

const char* ssid = SSID;
const char* password = PASS;

void handleRoot();
WebServer httpServer(80);

void setup() {
  M5.begin();
  M5.Lcd.setTextSize(2);

  Serial.begin(115200);
  Serial.println();
  Serial.println("Booting Sketch...");
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(ssid, password);

  httpServer.on("/", handleRoot);
  httpServer.on("/", handleRoot);
  httpServer.begin();

  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    WiFi.begin(ssid, password);
    delay(500);
    M5.Lcd.print(".");
  }
  M5.Lcd.print("\r\nWiFi connected\r\nIP address: ");
  M5.Lcd.println(WiFi.localIP());
}


void loop() {
  httpServer.handleClient();
} 

void handleRoot() {
  String index = 
            "<!DOCTYPE html><html>\n" 
            "<head>\n" 
            "<title>Time Setting</title>\n" 
            "</head>\n"
            "<body>\n"
            "1234"
            "</body>\n</html>\n";

  httpServer.send(200, "text/html", index);  
}