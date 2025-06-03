#ifndef BLINKER_H
#define BLINKER_H

#include <Arduino.h>
#include "Blinker/blinker.h"

class Blinker {
public:
    // Blinker Modi
    enum Mode {
        OFF,
        LEFT,
        RIGHT,
        HAZARD
    };

    // Konstruktor - Pins angeben
    Blinker(int pinVL, int pinHL, int pinVR, int pinHR);

    // Initialisierung - muss in setup() aufgerufen werden
    void begin();

    // Modus setzen
    void setMode(Mode mode);

    // Loop-Methode - muss in loop() aufgerufen werden
    void update();

private:
    int _pinVL, _pinHL, _pinVR, _pinHR;
    Mode _currentMode;

    // Für Blinktakt
    unsigned long _lastToggleTime;
    bool _ledState;
    const unsigned long _blinkInterval = 500; // 500ms = 0.5s an/aus

    // interne Helfer
    void setLEDs(bool vl, bool hl, bool vr, bool hr);
};

#endif // BLINKER_H
