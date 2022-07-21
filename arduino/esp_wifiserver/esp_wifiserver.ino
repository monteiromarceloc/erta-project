#include <WiFi.h>
#include <HCSR04.h>

#define gpio_1_N_motor      23
#define gpio_1_P_motor      22
#define gpio_2_N_motor      19
#define gpio_2_P_motor      21

#define LED_PIN   14
#define PIN_TRIGGER   5
#define PIN_ECHO      18
#define MIN_DIST      30

bool found_obstacle = false;
const char* ssid = "Marcelo's Galaxy M32";
const char* password = "11111111";

WiFiServer server(80);
HCSR04 hc(PIN_TRIGGER, PIN_ECHO);

void setup() {
  pinMode(gpio_1_N_motor, OUTPUT);
  pinMode(gpio_1_P_motor, OUTPUT);
  pinMode(gpio_2_N_motor, OUTPUT);
  pinMode(gpio_2_P_motor, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
    
  Serial.begin(115200);
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
  digitalWrite(LED_PIN, HIGH);

  server.begin();

}

int value = 0;

void loop() {

  // Verifica distância

  if (hc.dist() < MIN_DIST) {
    Serial.print("Distancia: ");
    Serial.println( hc.dist() );
    delay(100);
    if (!found_obstacle) {
      Serial.println("Obstáculo identificado");
      digitalWrite(gpio_1_N_motor, HIGH);
      digitalWrite(gpio_1_P_motor, HIGH);
      digitalWrite(gpio_2_N_motor, HIGH);
      digitalWrite(gpio_2_P_motor, HIGH);
      found_obstacle = true;
    }
  } else {
    found_obstacle = false;
  }  

  // Recebe requisição do servidor

  WiFiClient client = server.available();

  if (client) {
    String currentLine = "";
    while(client.connected()) {
      if(client.available()) {
        char c = client.read();
        if (c == '\n') {
          if (currentLine.length() == 0) { // Fim da request, envia HTTP respose
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

        // Aciona motores

        if(currentLine.endsWith("GET /F") && !found_obstacle) {
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
          digitalWrite(gpio_1_N_motor, HIGH);
          digitalWrite(gpio_1_P_motor, LOW);
           
          digitalWrite(gpio_2_N_motor, LOW);
          digitalWrite(gpio_2_P_motor, HIGH);
          break;
        }
        
        if(currentLine.endsWith("GET /E")) {
          Serial.println("Ligando motores pra esquerda");
          digitalWrite(gpio_1_N_motor, LOW);
          digitalWrite(gpio_1_P_motor, HIGH);
           
          digitalWrite(gpio_2_N_motor, HIGH);
          digitalWrite(gpio_2_P_motor, LOW);
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
