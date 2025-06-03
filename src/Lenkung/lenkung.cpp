#include "lenkung.h"
#include <Arduino.h>  // für map(), constrain(), Serial

// Konstruktor initialisiert die Membervariablen
Lenkung::Lenkung(int pin, int minW, int maxW)
  : servoPin(pin), minWinkel(minW), maxWinkel(maxW) {}

// Muss in setup() aufgerufen werden, um das Servo zu attachen
void Lenkung::begin() {
    servo.attach(servoPin);
    // Auf Mittelstellung initialisieren:
    int mittelWinkel = (minWinkel + maxWinkel) / 2;
    mittelWinkel = constrain(mittelWinkel, 0, 180);
    servo.write(mittelWinkel);
    Serial.print("Lenkung: Initialer Winkel = ");
    Serial.println(mittelWinkel);
}

// Bereich bei Bedarf ändern
void Lenkung::setzeBereich(int minW, int maxW) {
    minWinkel = minW;
    maxWinkel = maxW;
}

// Wird im BLYNK_WRITE(V4)-Callback aufgerufen
void Lenkung::handleValue(int receiveValue) {
    // receiveValue ∈ [0..100]
    int winkel = map(receiveValue, 0, 100, minWinkel, maxWinkel);
    winkel = constrain(winkel, 0, 180);
    servo.write(winkel);

    // Debug-Ausgabe
    Serial.print("Lenkung: Slider = ");
    Serial.print(receiveValue);
    Serial.print(" → Winkel = ");
    Serial.println(winkel);
}
