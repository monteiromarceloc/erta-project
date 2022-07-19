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

#define IN_1      3
#define IN_2      4
#define IN_3      5
#define IN_4      6

String ssid = "1104";
String password = "65496549";

WiFiServer server(80);

void configura_gpios_controle_motor(void)
{
    pinMode(IN_1, OUTPUT);
    pinMode(IN_2, OUTPUT);
    pinMode(IN_3, OUTPUT);
    pinMode(IN_4, OUTPUT);
}
 
/* Função: controle um motor (freia, movimento anti-horário, movimento horário
 *         ou ponto morto)
 * Parâmetros: motor a ser controlado e ação desejada
 * Retorno: nenhum
 */
void controla_motor(char acao)
{
    int gpio_1_N_motor = IN_1;
    int gpio_1_p_motor = IN_2;
    int gpio_2_N_motor = IN_3;
    int gpio_2_p_motor = IN_4;

}
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
          digitalWrite(gpio_1_N_motor, LOW);
            digitalWrite(gpio_1_P_motor, HIGH);
           
            digitalWrite(gpio_2_N_motor, LOW);
            digitalWrite(gpio_2_P_motor, HIGH);
            break;
        }
        
        if(currentLine.endsWith("GET /T")) {
          Serial.println("Ligando motores pra tras");
          digitalWrite(gpio_1_P_motor, LOW);
            digitalWrite(gpio_1_N_motor, HIGH);
           
            digitalWrite(gpio_2_P_motor, LOW);
            digitalWrite(gpio_2_N_motor, HIGH);
            break;
        }
        
        if(currentLine.endsWith("GET /D")) {
          Serial.println("Ligando motores pra direita");
          digitalWrite(gpio_1_N_motor, LOW);
            digitalWrite(gpio_1_P_motor, HIGH);
           
            digitalWrite(gpio_2_N_motor, HIGH);
            digitalWrite(gpio_2_P_motor, HIGH);
            break;
        }
        
        if(currentLine.endsWith("GET /E")) {
          Serial.println("Ligando motores pra esquerda");
           digitalWrite(gpio_1_N_motor, HIGH);
            digitalWrite(gpio_1_P_motor, HIGH);
           
            digitalWrite(gpio_2_N_motor, LOW);
            digitalWrite(gpio_2_P_motor, HIGH);
            break;
        }

        if(currentLine.endsWith("GET /S")) {
          Serial.println("Freando motores");
            digitalWrite(gpio_1_N_motor, HIGH);
            digitalWrite(gpio_1_P_motor, HIGH);
           
            digitalWrite(gpio_2_N_motor, HIGH);
            digitalWrite(gpio_2_P_motor, HIGH);
            break;
        }
      }
    }
    
    client.stop();
    Serial.println("Client disconnected.");
  }
}
