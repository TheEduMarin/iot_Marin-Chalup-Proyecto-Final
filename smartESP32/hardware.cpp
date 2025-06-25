#include "hardware.h"
#include <Arduino.h>  

float medirVelocidadEntreSensores(ultrasonicsens& sensor1, ultrasonicsens& sensor2, float distancia_entre_sensores_cm) {
  Serial.println("Esperando detección en sensor 1...");
  while (true) {
    float d1 = sensor1.getDistance();
    if (d1 > 0 && d1 < 10) {
      Serial.println("Sensor 1 detectó objeto");
      break;
    }
    delay(20);
  }

  unsigned long t_inicio = millis();

  Serial.println("Esperando detección en sensor 2...");
  while (true) {
    float d2 = sensor2.getDistance();
    if (d2 > 0 && d2 < 10) {
      Serial.println("Sensor 2 detectó objeto");
      break;
    }
    delay(20);
  }

  unsigned long t_fin = millis();
  float tiempo_s = (t_fin - t_inicio) / 1000.0;
  float velocidad_cm_s = distancia_entre_sensores_cm / tiempo_s;

  Serial.print("Tiempo: ");
  Serial.print(tiempo_s);
  Serial.print(" s | Velocidad: ");
  Serial.print(velocidad_cm_s);
  Serial.println(" cm/s");

  return velocidad_cm_s;
}
