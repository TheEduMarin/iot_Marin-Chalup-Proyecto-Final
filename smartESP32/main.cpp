#include "aws.h"
#include "VelocidadSensor.h"  



struct WiFiNetwork {
  const char* ssid;
  const char* password;
};

WiFiNetwork networks[] = {
  {"UCB-IoT", "sistemasyteleco"},
  {"Mordor", "M4rin5Net"}
};

String selectedSSID;
String selectedPassword;

void conectarWiFiPorSerial() {
  Serial.println("Selecciona la red WiFi:");
  for (int i = 0; i < sizeof(networks) / sizeof(networks[0]); i++) {
    Serial.print(i);
    Serial.print(": ");
    Serial.println(networks[i].ssid);
  }
  Serial.println("Ingresa el número de la red y presiona Enter:");

  int seleccion = -1;
  while (seleccion < 0 || seleccion >= (int)(sizeof(networks) / sizeof(networks[0]))) {
    if (Serial.available()) {
      seleccion = Serial.parseInt();
      if (seleccion >= 0 && seleccion < (int)(sizeof(networks) / sizeof(networks[0]))) {
        Serial.print("Seleccionaste: ");
        Serial.println(networks[seleccion].ssid);
        selectedSSID = networks[seleccion].ssid;
        selectedPassword = networks[seleccion].password;
      } else {
        Serial.println("Selección inválida. Intenta de nuevo:");
        seleccion = -1;
      }
    }
    delay(100);
  }

  Serial.print("Conectando a ");
  Serial.println(selectedSSID);
  WiFi.begin(selectedSSID.c_str(), selectedPassword.c_str());

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado");
}


ultrasonicsens sensor1(22, 23);
ultrasonicsens sensor2(14, 12);
VelocidadSensor velocidadSensor(sensor1, sensor2, 10.0);  

void setup() {
  Serial.begin(115200);
  conectarWiFiPorSerial();



  servo.begin();             
  configurarAWS(); 
  verificarYCorregirShadowInconsistente();       
  limpiarGateStatePegado();
}

void loop() {
  if (!client.connected()) {
    reconectarAWS();  
  }

  client.loop();  

  velocidadSensor.actualizar();  

  if (velocidadSensor.hayNuevaVelocidad()) {
    int velocidad = velocidadSensor.obtenerVelocidad();
    lastSpeedDetected = velocidad;
    publishVelocity(velocidad);  


  }

  delay(20); 
}
