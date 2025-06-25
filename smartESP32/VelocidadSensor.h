
#ifndef VELOCIDAD_SENSOR_H
#define VELOCIDAD_SENSOR_H

#include "hardware.h" 

class VelocidadSensor {
private:
    ultrasonicsens& sensor1;
    ultrasonicsens& sensor2;
    enum Estado { ESPERANDO_SENSOR_1, ESPERANDO_SENSOR_2, CALCULANDO_VELOCIDAD };
    Estado estado = ESPERANDO_SENSOR_1;

    unsigned long tiempoInicio = 0;
    unsigned long tiempoFin = 0;
    float distanciaCm = 10.0;

    int velocidadActual = 0;
    bool nuevaVelocidad = false;

public:
    VelocidadSensor(ultrasonicsens& s1, ultrasonicsens& s2, float distancia = 10.0)
      : sensor1(s1), sensor2(s2), distanciaCm(distancia) {}

    void actualizar();
    bool hayNuevaVelocidad() const { return nuevaVelocidad; }
    int obtenerVelocidad() {
      nuevaVelocidad = false;
      return velocidadActual;
    }
};

#endif
