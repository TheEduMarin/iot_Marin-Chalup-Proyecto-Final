#ifndef AWS_H
#define AWS_H

#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <WiFi.h>

#include "hardware.h"

extern MG90S servo;
extern PubSubClient client;
extern WiFiClientSecure net;

extern int speedLimit;
extern String gateState;
extern int lastSpeedDetected;

void limpiarGateStatePegado();
void verificarYCorregirShadowInconsistente();
void configurarAWS();
void reconectarAWS();
void publishVelocity(int velocidad_cmps);
void callbackMQTT(char* topic, byte* payload, unsigned int length);

#endif
