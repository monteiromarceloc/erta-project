#include <BearSSLHelpers.h>
#include <ESP8266WiFiGratuitous.h>
#include <WiFiServerSecureBearSSL.h>
#include <ESP8266WiFiScan.h>
#include <WiFiUdp.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiType.h>
#include <ESP8266WiFiMulti.h>
#include <CertStoreBearSSL.h>
#include <WiFiClientSecureBearSSL.h>
#include <ESP8266WiFi.h>
#include <WiFiServerSecure.h>
#include <WiFiServer.h>
#include <WiFiClient.h>
#include <ArduinoWiFiServer.h>
#include <WiFiClientSecure.h>

String ssid = "1104";
String password = "65496549";

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(13, OUTPUT);
  delay(100);
  
  Serial.println();

  WiFi.begin(ssid, password);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();

}

int value = 0;

void loop() {
  WiFiClient client = server.available();

  if (client) {
    Serial.println("New Client.");
    String currentLine = "";
    while(client.connected()) {
      if(client.available()) {
        char c = client.read();
        
        if (c == '\n') {
          if (currentLine.length() == 0) {
            // End of HTTP request, so send response
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("Comando recebido com sucesso");
            client.println();
            break;
          } else {
            Serial.println(currentLine);
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }

        
        // Process request
        if(currentLine.endsWith("GET /F")) {
          Serial.println("Ligando motores pra frente");
        }
        
        if(currentLine.endsWith("GET /T")) {
          Serial.println("Ligando motores pra tras");
        }
        
        if(currentLine.endsWith("GET /D")) {
          Serial.println("Ligando motores pra direita");
        }
        
        if(currentLine.endsWith("GET /E")) {
          Serial.println("Ligando motores pra esquerda");
        }
      }
    }
    
    client.stop();
    Serial.println("Client disconnected.");
  }
}