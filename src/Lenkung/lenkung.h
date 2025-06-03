#ifndef LENKUNG_H
#define LENKUNG_H

#include <ESP32Servo.h>

/*
  Klasse Lenkung kapselt:
   - Das Servo-Objekt
   - Mapping von Blynk-Slider (0–100) auf Winkel (minWinkel–maxWinkel)
   - Eine Methode, die vom BLYNK_WRITE-Callback aufgerufen wird
*/

class Lenkung {
public:
    // Konstruktor: pin ist der GPIO-Pin, an dem das Servo hängt.
    // minWinkel / maxWinkel legen den erlaubten Servobereich (z.B. 30°…150°) fest.
    Lenkung(int pin, int minWinkel = 0, int maxWinkel = 180);

    // Muss in setup() aufgerufen werden, damit das Servo am Pin ge-attachet wird.
    void begin();

    // Falls Du später den Arbeitsbereich dynamisch ändern willst:
    void setzeBereich(int minWinkel, int maxWinkel);

    // Wird vom BLYNK_WRITE(V4)-Callback aufgerufen: receiveValue ∈ [0..100]
    void handleValue(int receiveValue);

private:
    Servo servo;        // Das Servo-Objekt
    int servoPin;       // GPIO-Pin für Servo (PWM-fähig)
    int minWinkel;      // Minimaler Winkel (z.B. 30)
    int maxWinkel;      // Maximaler Winkel (z.B. 150)
};

#endif // LENKUNG_H
