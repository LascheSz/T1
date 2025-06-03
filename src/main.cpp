#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "Blinker/blinker.h"
#include "Blynk/blynk_callbacks.h"
#include "BlynkConfig.h"

// ──────────────────────────────────────────────────────────────
// 1) Blinker-Pins definieren (mit Semikolon!)
// ──────────────────────────────────────────────────────────────
const int PIN_VL = 15;   // linker vorderer Blinker
const int PIN_HL = 21;   // linker hinterer Blinker
const int PIN_HR = 25;   // rechter hinterer Blinker
const int PIN_VR = 13;   // rechter vorderer Blinker

// ──────────────────────────────────────────────────────────────
// 2) Blynk-Zugangsdaten
// ──────────────────────────────────────────────────────────────
const char* blynkTemplateId = "TMPL4P2yLMyJJ";       // aus deinem Blynk-Projekt
const char* blynkAuthToken  = "GfQRY55Aul1gIJJpG4-5BxJM5JQLQrtq";
const char* blynkDeviceName = "T1BusESP32";          // beliebiger Name

// ──────────────────────────────────────────────────────────────
// 3) WLAN-Zugangsdaten
// ──────────────────────────────────────────────────────────────
const char* wifiSsid     = "Werkstatt";
const char* wifiPassword = "test@2021";

// ──────────────────────────────────────────────────────────────
// 4) Globale Instanz deiner Blinker-Klasse anlegen
//    (Konstruktor bekommt die vier Pins in der Reihenfolge VL, HL, VR, HR)
// ──────────────────────────────────────────────────────────────
Blinker blinker(PIN_VL, PIN_HL, PIN_VR, PIN_HR);

// ──────────────────────────────────────────────────────────────
// 5) Blynk-Callback-Prototyp in dieser Datei (muss vor setup() stehen)
// ──────────────────────────────────────────────────────────────
void setupBlynkCallbacks();

// ──────────────────────────────────────────────────────────────
// 6) setup()
// ──────────────────────────────────────────────────────────────
void setup() {
    Serial.begin(115200);
    Serial.println("Starte ESP32 mit Blynk...");

    // 6.1) Blinker-Lib initialisieren (PinMode OUTPUT wird hier gesetzt)
    blinker.begin();

    // 6.2) Mit WLAN + Blynk-Server verbinden
    Blynk.begin(blynkAuthToken, wifiSsid, wifiPassword);

    // 6.3) Blynk-Callbacks registrieren (unten definiert)
    setupBlynkCallbacks();

    // 6.4) Starte initial im Modus OFF (nur zur Sicherheit)
    blinker.setMode(Blinker::OFF);
}

// ──────────────────────────────────────────────────────────────
// 7) loop()
// ──────────────────────────────────────────────────────────────
void loop() {
    // 7.1) Blynk-Library „atmen“ lassen, damit alle Callbacks laufen
    Blynk.run();

    // 7.2) Hier läuft deine Blinker-Logik (Toggeln der LEDs gemäß Interval)
    blinker.update();

    // 7.3) Manuelles Wechseln im 5-Sekunden-Zyklus wird NICHT mehr genutzt,
    //       weil wir nun alles über Blynk steuern wollen:
    /*
    static unsigned long lastSwitch = millis();
    static int state = 0;
    if (millis() - lastSwitch > 5000) {
        lastSwitch = millis();
        switch (state) {
            case 0: blinker.setMode(Blinker::LEFT);    break;
            case 1: blinker.setMode(Blinker::RIGHT);   break;
            case 2: blinker.setMode(Blinker::HAZARD);  break;
            case 3: blinker.setMode(Blinker::OFF);     break;
        }
        state = (state + 1) % 4;
    }
    */
}

// ──────────────────────────────────────────────────────────────
// 8) Blynk-Callbacks (Switch/Schalter in der App auf V0, V1, V2, V3)
//    jeder Schalter in der App sendet 1=ON oder 0=OFF auf den virtuellen Pin.
//    Wenn bei V0 der Switch = „ON“, soll der linke Blinker an gehen usw.
// ──────────────────────────────────────────────────────────────
void setupBlynkCallbacks() {
    // Hinweis: du kannst die Callback-Definitionen auch direkt hier reinschreiben
    //         oder alternativ in eine separate Datei auslagern. Hier behalte ich
    //         alles in einer Datei, um es übersichtlich zu halten.
}

// ──────────────────────────────────────────────────────────────
// 9) Callback-Funktionen (einfach direkt unter setupBlynkCallbacks):
//    - V0 = Linker Blinker (LEFT)
//    - V1 = Rechter Blinker (RIGHT)
//    - V2 = Hazard (beide Blinker gleichzeitig)
//    - V3 = OFF (beide Blinker aus)
// ──────────────────────────────────────────────────────────────

// Linker Blinker (V0):
BLYNK_WRITE(V0) {
    int state = param.asInt(); // 1 = Switch ON, 0 = Switch OFF
    if (state == 1) {
        Serial.println("Blynk: V0→ LEFT");
        blinker.setMode(Blinker::LEFT);
    } else {
        Serial.println("Blynk: V0→ OFF");
        blinker.setMode(Blinker::OFF);
    }
}

// Rechter Blinker (V1):
BLYNK_WRITE(V1) {
    int state = param.asInt();
    if (state == 1) {
        Serial.println("Blynk: V1→ RIGHT");
        blinker.setMode(Blinker::RIGHT);
    } else {
        Serial.println("Blynk: V1→ OFF");
        blinker.setMode(Blinker::OFF);
    }
}

// Hazard-Funktion (V2):
BLYNK_WRITE(V2) {
    int state = param.asInt();
    if (state == 1) {
        Serial.println("Blynk: V2→ HAZARD");
        blinker.setMode(Blinker::HAZARD);
    } else {
        Serial.println("Blynk: V2→ OFF");
        blinker.setMode(Blinker::OFF);
    }
}

// Komplett ausschalten (V3):
BLYNK_WRITE(V3) {
    int state = param.asInt();
    if (state == 1) {
        Serial.println("Blynk: V3→ OFF");
        blinker.setMode(Blinker::OFF);
    }
    // Bei V3 ignorieren wir „0“, weil OFF ja „OFF“ bleibt.
}
