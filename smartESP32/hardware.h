#include <ESP32Servo.h>

#ifndef HARDWARE_H
#define HARDWARE_H


class ultrasonicsens {
private:
  int echopin; 
  int trigger;

  long readUltrasonicDistance(int triggerPin, int echoPin) {
    pinMode(triggerPin, OUTPUT);
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);       
    pinMode(echoPin, INPUT);
    return pulseIn(echoPin, HIGH, 20000); 
  }

public:
  ultrasonicsens(int echopin, int trigger) {
    this->echopin = echopin;
    this->trigger = trigger;
  }

  long getDistance() {
    return 0.01723 * readUltrasonicDistance(trigger, echopin);  
  }

};


class MG90S {
private:
  Servo servo;
  int pin;


  const int velocidadAbierta = 1800;
  const int velocidadCerrada = 1200;
  const int neutro = 1500;
  const int tiempo90 = 200;

public:
  MG90S(int servoPin) : pin(servoPin) {}

  void begin() {
    servo.setPeriodHertz(50);
    servo.attach(pin, 1000, 2000);
    stop();
  }

  void open() {
    Serial.println("Servo: OPEN (giro invertido)");
    servo.writeMicroseconds(velocidadAbierta);
    delay(tiempo90);
    stop();
  }

  void close() {
    Serial.println("Servo: CLOSE (giro invertido)");
    servo.writeMicroseconds(velocidadCerrada);
    delay(tiempo90);
    stop();
  }

  void stop() {
    servo.writeMicroseconds(neutro);
  }
};

float medirVelocidadEntreSensores(ultrasonicsens& sensor1, ultrasonicsens& sensor2, float distancia_entre_sensores_cm = 10.0);


#endif 