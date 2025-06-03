#include "BlynkConfig.h"
#include <BlynkSimpleEsp32.h>
#include <WiFi.h>
#include "Blinker/blinker.h"
#include "Blynk/blynk_callbacks.h"
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
const char* blynkAuthToken  = "GfQRY55Aul1gIJJpG4-5BxJM5JQLQrtq";
// ─────────────────────────────────────────────────────────────
// 3) WLAN-Zugangsdaten
// ──────────────────────────────────────────────────────────────
const char* wifiSsid     = "Werkstatt";
const char* wifiPassword = "test@2012";

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

    Serial.print("Verbinde mit WLAN ");
    Serial.print(wifiSsid);
    Serial.println(" …");
    WiFi.begin(wifiSsid, wifiPassword);

    unsigned long startMillis = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - startMillis < 10000) {
        Serial.print(".");
        delay(500);
    }

    if (WiFi.status() != WL_CONNECTED) {
        Serial.println();
        Serial.println("Fehler: Konnte mich nicht mit dem WLAN verbinden!");
        // An dieser Stelle abbrechen oder Endlosschleife:
        return; 
    }

    // 3) Wenn wir hier sind, ist das WLAN verbunden:
    Serial.println();
    Serial.print("WLAN verbunden! Lokale IP ist: ");
    Serial.println(WiFi.localIP());

    // 6.1) Blinker-Lib initialisieren (PinMode OUTPUT wird hier gesetzt)
    blinker.begin();

    // 6.2) Mit WLAN + Blynk-Server verbinden
    Blynk.begin(blynkAuthToken, wifiSsid, wifiPassword);


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