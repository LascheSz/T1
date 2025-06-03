#include "blinker.h"

// Konstruktor
Blinker::Blinker(int pinVL, int pinHL, int pinVR, int pinHR): _pinVL(pinVL), _pinHL(pinHL), _pinVR(pinVR), _pinHR(pinHR), _currentMode(OFF), _lastToggleTime(0), _ledState(false) {}

// Pins initialisieren
void Blinker::begin() {
    pinMode(_pinVL, OUTPUT);
    pinMode(_pinHL, OUTPUT);
    pinMode(_pinVR, OUTPUT);
    pinMode(_pinHR, OUTPUT);
    setLEDs(false, false, false, false);
}

// Modus setzen
void Blinker::setMode(Mode mode) {
    _currentMode = mode;
    // beim Moduswechsel LEDs aus und Zeit resetten
    _ledState = false;
    _lastToggleTime = millis();
    setLEDs(false, false, false, false);
}

// Loop-Methode
void Blinker::update() {
    unsigned long currentTime = millis();

    // alle 500ms toggeln
    if (currentTime - _lastToggleTime >= _blinkInterval) {
        _lastToggleTime = currentTime;
        _ledState = !_ledState;

        switch (_currentMode) {
            case OFF:
                setLEDs(false, false, false, false);
                break;
            case LEFT:
                setLEDs(_ledState, _ledState, false, false);
                break;
            case RIGHT:
                setLEDs(false, false, _ledState, _ledState);
                break;
            case HAZARD:
                setLEDs(_ledState, _ledState, _ledState, _ledState);
                break;
        }
    }
}

// interne Helferfunktion
void Blinker::setLEDs(bool vl, bool hl, bool vr, bool hr) {
    digitalWrite(_pinVL, vl ? HIGH : LOW);
    digitalWrite(_pinHL, hl ? HIGH : LOW);
    digitalWrite(_pinVR, vr ? HIGH : LOW);
    digitalWrite(_pinHR, hr ? HIGH : LOW);
}
