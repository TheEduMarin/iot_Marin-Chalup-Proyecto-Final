
#include "VelocidadSensor.h"
#include <Arduino.h>

void VelocidadSensor::actualizar() {
    switch (estado) {
        case ESPERANDO_SENSOR_1: {
            float d1 = sensor1.getDistance();
            if (d1 > 0 && d1 < 10) {
                Serial.println("Sensor 1 detectó objeto");
                tiempoInicio = millis();
                estado = ESPERANDO_SENSOR_2;
            }
            break;
        }
        case ESPERANDO_SENSOR_2: {
            float d2 = sensor2.getDistance();
            if (d2 > 0 && d2 < 10) {
                Serial.println("Sensor 2 detectó objeto");
                tiempoFin = millis();
                estado = CALCULANDO_VELOCIDAD;
            }
            break;
        }
        case CALCULANDO_VELOCIDAD: {
            float tiempoSeg = (tiempoFin - tiempoInicio) / 1000.0;
            if (tiempoSeg > 0) {
                float vel = distanciaCm / tiempoSeg;
                Serial.print("Velocidad calculada: ");
                Serial.print(vel);
                Serial.println(" cm/s");

                int velEntera = (int)vel;
                if (velEntera != velocidadActual) {
                    velocidadActual = velEntera;
                    nuevaVelocidad = true;
                }
            }
            estado = ESPERANDO_SENSOR_1;
            break;
        }
    }
}
