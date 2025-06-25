#include "aws.h"


const char* aws_endpoint = "a3ovfyx2pmf1sk-ats.iot.us-east-1.amazonaws.com";
const int aws_port = 8883;
const char* thingName = "RompeMuellesIoT";


const char* ca_cert = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";

const char* client_cert = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWTCCAkGgAwIBAgIUWV6O88ES9XZCFz+LdsQjMwZUDewwDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTI1MDUyNDIxMjAz
MVoXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAL0Mz59lv0o7GB8EQk/l
uVyPffqno1WwW2KWvOFwrYu0FAuLR4eyYAUU+jlGhukgIFn++hY5UmkYmppiWIPm
o+SaMz0sTrki6EjloGHOd3q3sABttO6cx0lDNMV5o1iBu3+e0xD+F/zCUkg5a/vf
ZKR019RyocownOlkgql0ab3sAEaXWbJxIoEGh3qm6W33k743uS/5oL4KhZ66UWF6
UnrGLxuklrb+5Hulue16Jb9ZBfOZgzKMv/Itbrzzy9b5pp/m1Bh04UdmKJhPlp+N
BM/GalQa7twdwOhHCC8KE+WuD08/vrarR1XqsOGMnteuvbHXzx3LyoZ/TFfTxJBe
+NcCAwEAAaNgMF4wHwYDVR0jBBgwFoAUpANGCN0744cMGW9qL6ZGdv7T7+cwHQYD
VR0OBBYEFGob458/kFJonTAtUlg6wMPYYijAMAwGA1UdEwEB/wQCMAAwDgYDVR0P
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQCXo8+pmsRxY6yWz84OPc9g9zY1
fD/zimiOeGOLPSfM45yNAumG947uAcIUeV96g+6wMYvBp+Ijwtj227TSOqWzYx+D
i8mmp0WGN/VdBzip9/b1I5u2OiNlAbe6cCBaIE+HT/+k2gPj8DA/xHNFxtfwCxCU
BCIWMImJTeA9YywzXyuX2HQzVI029x3eCCrY+X2JXKe+1QwrwkFKB6A62RMa2GK6
SsUBvoi3tmpBcw/yDCSNA3IFWvAGg54PZQSyh8JY7ljS7mbSwkGqSB9iRzdKlqdl
tT+RDNnZakuBK0QjA1IHYPBWHzbQriet+3GTExXVabweHD4P4XxaE6DgO0OR
-----END CERTIFICATE-----
)KEY";

const char* client_key = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEowIBAAKCAQEAvQzPn2W/SjsYHwRCT+W5XI99+qejVbBbYpa84XCti7QUC4tH
h7JgBRT6OUaG6SAgWf76FjlSaRiammJYg+aj5JozPSxOuSLoSOWgYc53erewAG20
7pzHSUM0xXmjWIG7f57TEP4X/MJSSDlr+99kpHTX1HKhyjCc6WSCqXRpvewARpdZ
snEigQaHeqbpbfeTvje5L/mgvgqFnrpRYXpSesYvG6SWtv7ke6W57Xolv1kF85mD
Moy/8i1uvPPL1vmmn+bUGHThR2YomE+Wn40Ez8ZqVBru3B3A6EcILwoT5a4PTz++
tqtHVeqw4Yye1669sdfPHcvKhn9MV9PEkF741wIDAQABAoIBAAEgAGRMcLT6YQxe
NB7RmSbJ29AQC1LJN+IAT6NvzjiUm8Ht1EEkeJnPJCYPG2JrxIWElOxo7uqdMN5W
U3yFdNg5arCkgNttL8CvTSMH3YInca6u+HKrECyJb9j0/lnae8kooszpFi904JR5
cwEOtUSdRWOIQxo269gftv9XKAHvUPa9VxmamwLKNKq3adaKN2sVAmudV/tGXnmq
nelfFV45HXqLCxnRC1qZIpGESL2BUbCBI4k3sUEUD6aye02irA1Qq14Edel18AJz
NipEgyBbAl8+ilv1cKGQ8Cl88UZ3DiJ1RdpJSF1xlIvDP4M4GHVkIw9sWK4ezyRp
vxTNxQECgYEA9Z79eu7YEdBgwax9qJo9F7Px7PMAh/uiwA03bEauhMmbZbJdcN+d
k+inQIFGoCsm7JGUZR3PVPjoDZLvm5ws9nEzFEnaiH4m9Pj+ExcJIEVNqRzVOZMF
0uGlWZw4SWh2LTe0dmDS3/Wa6gyaFplUjM1uaDGERVi6TOzuI6urVBcCgYEAxQnc
7eXsrqAYWDxip0H4NuvMCDfgaw+hsypk+h4U1gYu68TVKocz6RiUrtIKp9m8eVWp
MYoWYUctRRjczbD4N2lONtKnhXlDfOLIk6EDolSOmFoelXM8TTOM2u397QLouGaz
xqfOyVxouiKJ+3cPkmC9IFHBi2++6uxIbAT2uUECgYAR4YAsieS670OL9eWz936J
EjWDfXFFdQE1IAEv5blgu1iPv7tjszPCh8ZdQMwGbv3HbRWzgscMNY6XJmJBHs57
JmSEjpfVJfHqFZJRi3TDn6f2rr2rElPzNTAXZPMIDQ3FXu/JSmUvnq6naUFycbkh
AveNqEUr0zjEzt7LQ/0WAwKBgQCP4t300/x8oOhmNuKL5X7PDG4YakV1qRqZ7ZGD
nMf2atmEzl4kCkt8Irkg2L1zSWt653UAeihRrVp/pOJJSrxYKow1OKugqqb/4dQ7
Ck/PERR4aQcAeABHGCf6D+VoWMF9N3J81ToKjXLkyigc/Brg98fkfA9sNZQjlZxl
VVKegQKBgHizRV+quKhrzHGCWECsZn9V7j/0/3+l9yyW2KUafhoTK4DQBYqz9o5T
wpb99vEc8vx6ofootUwwhMAsak7FGP4VQXQoPqkv6ttRQPqcdzn0cjx/2qLaopPX
hE27/Dn4TKCToN4mJ0gR7l0MHaW4IQyFSCz31gO7qroXnPt9oJgd
-----END RSA PRIVATE KEY-----
)KEY";


MG90S servo(13);
WiFiClientSecure net;
PubSubClient client(net);

int speedLimit = 20;
String gateState = "close";
int lastSpeedDetected = 0;

void configurarAWS() {
  net.setCACert(ca_cert);
  net.setCertificate(client_cert);
  net.setPrivateKey(client_key);
  client.setServer(aws_endpoint, aws_port);
  client.setCallback(callbackMQTT);

  Serial.print("Conectando a AWS IoT...");
  while (!client.connected()) {
    if (client.connect(thingName)) {
      Serial.println("¡Conectado!");
      client.subscribe("$aws/things/RompeMuellesIoT/shadow/update/delta");
    } else {
      Serial.print(".");
      delay(1000);
    }
  }
}

void reconectarAWS() {
  while (!client.connected()) {
    Serial.print("Reconectando...");
    if (client.connect(thingName)) {
      Serial.println("Conectado de nuevo");
      client.subscribe("$aws/things/RompeMuellesIoT/shadow/update/delta");
    } else {
      Serial.print(".");
      delay(1000);
    }
  }
}

void callbackMQTT(char* topic, byte* payload, unsigned int length) {
  Serial.println("Callback ejecutado");

  StaticJsonDocument<512> doc;
  auto error = deserializeJson(doc, payload, length);
  if (error) {
    Serial.println("Error parseando JSON");
    return;
  }

  if (doc["state"]["gateState"]) {
    String desiredGateState = doc["state"]["gateState"].as<String>();
    Serial.print("Delta recibido gateState: ");
    Serial.println(desiredGateState);

    if (desiredGateState == "open" && gateState != "open") {
      Serial.println("Abriendo puerta...");
      servo.open();
      gateState = "open";

      delay(3000);  

      Serial.println("Cerrando puerta...");
      servo.close();
      gateState = "close";

      StaticJsonDocument<256> report;
      report["state"]["reported"]["gateState"] = gateState;
      report["state"]["desired"]["gateState"] = nullptr;

      String jsonStr;
      serializeJson(report, jsonStr);

      Serial.println("Publicando estado actualizado del shadow...");
      Serial.println(jsonStr);

      bool ok = client.publish("$aws/things/RompeMuellesIoT/shadow/update", jsonStr.c_str());
      if (ok) {
        Serial.println("Shadow update enviado");
      } else {
        Serial.println("ERROR al enviar shadow update");
      }

      // Loop adicional para asegurar procesamiento
      unsigned long start = millis();
      while (millis() - start < 1500) {
        client.loop();
        delay(10);
      }
    }
  }
}


void limpiarGateStatePegado() {

  StaticJsonDocument<256> doc;
  doc["state"]["reported"]["gateState"] = "close";
  doc["state"]["desired"]["gateState"] = nullptr; 

  String json;
  serializeJson(doc, json);
  client.publish("$aws/things/RompeMuellesIoT/shadow/update", json.c_str());

  Serial.println("Intentando limpiar gateState pegado a 'open'...");
}

void publishVelocity(int velocidad_cmps) {
  StaticJsonDocument<256> doc;
  doc["state"]["reported"]["lastSpeedDetected"] = velocidad_cmps;
  doc["state"]["reported"]["speedLimit"] = speedLimit;
  doc["state"]["reported"]["gateState"] = gateState;

  String payload;
  serializeJson(doc, payload);
  client.publish("$aws/things/RompeMuellesIoT/shadow/update", payload.c_str());

  Serial.print("Velocidad publicada (cm/s): ");
  Serial.println(velocidad_cmps);
}
void verificarYCorregirShadowInconsistente() {
  Serial.println("⏳ Verificando shadow por estado inconsistente...");

  WiFiClientSecure httpsClient;
  httpsClient.setCACert(ca_cert);
  httpsClient.setCertificate(client_cert);
  httpsClient.setPrivateKey(client_key);

  if (!httpsClient.connect(aws_endpoint, 443)) {
    Serial.println(" No se pudo conectar para GET shadow");
    return;
  }

  String url = "/things/RompeMuellesIoT/shadow";
  httpsClient.print(String("GET ") + url + " HTTP/1.1\r\n" +
                    "Host: " + aws_endpoint + "\r\n" +
                    "Connection: close\r\n\r\n");


  String payload = "";
  bool headersDone = false;
  while (httpsClient.connected()) {
    String line = httpsClient.readStringUntil('\n');
    if (!headersDone) {
      if (line == "\r") headersDone = true;
    } else {
      payload += line;
    }
  }


  StaticJsonDocument<1024> doc;
  auto err = deserializeJson(doc, payload);
  if (err) {
    Serial.println(" Error parseando shadow GET");
    return;
  }

  JsonObject state = doc["state"];
  JsonObject desired = state["desired"];
  JsonObject reported = state["reported"];

  const char* repGate = reported["gateState"];
  const char* desGate = desired["gateState"];
if (repGate) {
  gateState = String(repGate);
  Serial.print("🛈 Estado inicial reportado: ");
  Serial.println(gateState);
}

  if ((!desGate || strlen(desGate) == 0) && repGate && String(repGate) == "open") {
    Serial.println("⚠ Estado inconsistente detectado: open en reported sin desired");
    

    StaticJsonDocument<256> patch;
    patch["state"]["reported"]["gateState"] = "close";
    patch["state"]["desired"]["gateState"] = nullptr;

    String json;
    serializeJson(patch, json);
    client.publish("$aws/things/RompeMuellesIoT/shadow/update", json.c_str());

    Serial.println(" Shadow corregido automáticamente");
  } else {
    Serial.println("✔Shadow consistente");
  }
}
