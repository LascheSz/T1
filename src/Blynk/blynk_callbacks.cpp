#include "blynk_callbacks.h"  // Enthält nun BlynkConfig + BlynkApiArduino + Blinker

extern Blinker blinker;     // Verweist auf dieselbe Instanz aus main.cpp

// ──────────────────────────────────────────────────────────────────────────────
// Definition von setupBlynkCallbacks() – **nur hier**!
// ──────────────────────────────────────────────────────────────────────────────
void setupBlynkCallbacks() {
    Serial.println("Blynk-Callbacks registriert");
}

// ──────────────────────────────────────────────────────────────────────────────
// ALLE BLYNK_WRITE(Vx)-Handler – **genau einmal** in diesem File!
// ──────────────────────────────────────────────────────────────────────────────

// Linker Blinker (V0)
BLYNK_WRITE(V0) {
        int state = param.asInt();
        if (state == 1) {
            blinker.setMode(Blinker::LEFT);
        } else {
            blinker.setMode(Blinker::OFF);
        }
}

// Rechter Blinker (V1)
BLYNK_WRITE(V1) {
    int state = param.asInt();
    if (state == 1) {
        blinker.setMode(Blinker::RIGHT);
    } else {
        blinker.setMode(Blinker::OFF);
    }
}

// Warnblinker (V2)
BLYNK_WRITE(V2) {
    int state = param.asInt();
    if (state == 1) {
        blinker.setMode(Blinker::HAZARD);
    } else {
        blinker.setMode(Blinker::OFF);
    }
}
