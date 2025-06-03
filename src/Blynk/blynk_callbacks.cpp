#include "blynk_callbacks.h"
#include <Arduino.h>
#include "BlynkConfig.h"   // Blynk-Konfiguration

// Beispiel für Button V0
BLYNK_WRITE(V0) // Blinker Links
{
    int state = param.asInt();

    if (state == 1) {
        blinker.setMode(Blinker::LEFT);
    }else if (state == 0) {
        blinker.setMode(Blinker::OFF);
    }
};

BLYNK_WRITE(V1) // Blinker Rechts
{
    int state = param.asInt();

    if (state == 1) {
        blinker.setMode(Blinker::RIGHT);
    }else if (state == 0) {
        blinker.setMode(Blinker::OFF);
    }

};

BLYNK_WRITE(V2) // Warnblinker
{
    int state = param.asInt();

    if (state == 1) {
        blinker.setMode(Blinker::WARNING);
    }else if (state == 0) {
        blinker.setMode(Blinker::OFF);
    }
};


void setupBlynkCallbacks()
{
    Serial.println("Blynk-Callbacks registriert");
}
