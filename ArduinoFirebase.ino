#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// WiFi config
#define WIFI_SSID "Juanca"
#define WIFI_PASS "1017132275"

// Firebase
#define FIREBASE_HOST "arduinocf.firebaseio.com"
#define FIREBASE_AUTH "Pyf1b6bXL3FbaX9XsncC2IRvDPVY1A70eMBJ3Jjb"

const int ledpin = D0;
const int soundpin = A0;
const int threshold = 40;

void setup() {
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print(".");

  pinMode(ledpin, OUTPUT);
  pinMode(soundpin, INPUT);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("Se ha conectado con la ip: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  setSoundSensorValue();
  getSoundSensorValue();
}

void setSoundSensorValue() {
  int soundVal = analogRead(soundpin);
  if (soundVal >= threshold) {
    Firebase.set("/sensors/bigsound", soundVal);
    digitalWrite(ledpin, HIGH);
    if (Firebase.failed()) {
      Serial.println("Fallo la escritura en /bigsound");
      Serial.println(Firebase.error());
    }
  } else {
    digitalWrite(ledpin, LOW);
  }
}

void getSoundSensorValue() {
  Serial.print("El valor del sensor de sonidos es: ");
  Serial.println(Firabase.getInt("/sensors/bigsound"));
  delay(1000);
}

// secret: Pyf1b6bXL3FbaX9XsncC2IRvDPVY1A70eMBJ3Jjb
// database: https://arduinocf.firebaseio.com/
