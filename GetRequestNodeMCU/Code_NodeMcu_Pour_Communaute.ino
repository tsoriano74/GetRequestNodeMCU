#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>


const char* ssid = "Nom Wifi";
const char* password = "Code Wifi";

// Pins utilisés sur le NodeMCU
int button1 = 2; //D1
int button2 = 5; //D2
int button3 = 4; //D3
int button4 = 0; //D4
int button1State = 0;
int button2State = 0;
int button3State = 0;
int button4State = 0;
int lastButton1State = 0;
int lastButton2State = 0;
int lastButton3State = 0;
int lastButton4State = 0;
String statut_ON = "%20On";
String satut_OFF = "%20Off";
String prise1 = "1";
String prise2 = "2";
String prise3 = "3";
String prise4 = "4";

String serverName = "http://....IP de la prise..../cm?cmnd=Power";

//Delay de protection
unsigned long lastTime = 0;
unsigned long timerDelay = 500;

void setup() {
  Serial.begin(115200);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(button4, INPUT_PULLUP);

  WiFi.begin(ssid, password);
  Serial.println("Connection");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connecté au WiFi avec l'adresse IP: ");
  Serial.println(WiFi.localIP());

  Serial.println("Let's go");
}

void loop() {
  
  button1State = digitalRead(button1);
  button2State = digitalRead(button2);
  button3State = digitalRead(button3);
  button4State = digitalRead(button4);

  if ((millis() - lastTime) > timerDelay) {  

    if (WiFi.status() == WL_CONNECTED) { //Si connecté au Wifi

      if (button1State != lastButton1State) { //Si interrupteur 1 change d'état
        if (button1State == 1) {              //Si interrupteur 1 est ON
          httpGetRequest(prise1, statut_ON);  //Effectue une requête HTTP pour allumer la prise 1
        }
        else if (button1State == 0) {         //Si interrupteur 1 est OFF
          httpGetRequest(prise1, satut_OFF);  //Effectue une requête HTTP pour éteindre la prise 1
        }
      }

      if (button2State != lastButton2State) {
        if (button2State == 1) {
          httpGetRequest(prise2, statut_ON);
        }
        else if (button2State == 0) {
          httpGetRequest(prise2, satut_OFF);
        }
      }

      if (button3State != lastButton3State) {
        if (button3State == 1) {
          httpGetRequest(prise3, statut_ON);
        }
        else if (button3State == 0) {
          httpGetRequest(prise3, satut_OFF);
        }
      }

      if (button4State != lastButton4State) {
        if (button4State == 1) {
          httpGetRequest(prise4, statut_ON);
        }
        else if (button4State == 0) {
          httpGetRequest(prise4, satut_OFF);
        }
      }
      
      lastButton1State = button1State;
      lastButton2State = button2State;
      lastButton3State = button3State;
      lastButton4State = button4State;
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}


void httpGetRequest(String prise, String etat) {

  HTTPClient http;

  String serverPath = serverName + prise + etat; 

  http.begin(serverPath.c_str());

  int httpResponseCode = http.GET();
  Serial.println("Send request");

}
