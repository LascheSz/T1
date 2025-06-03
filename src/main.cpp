#include "BlynkConfig.h"
#include <BlynkSimpleEsp32.h>
#include <WiFi.h>
#include "Blinker/blinker.h"
#include "Blynk/blynk_callbacks.h"
// ──────────────────────────────────────────────────────────────
// Blinker-Pins definieren
// ──────────────────────────────────────────────────────────────
const int PIN_VL = 15;   // linker vorderer Blinker
const int PIN_HL = 21;   // linker hinterer Blinker
const int PIN_HR = 25;   // rechter hinterer Blinker
const int PIN_VR = 13;   // rechter vorderer Blinker

// ──────────────────────────────────────────────────────────────
const int pinServo = 32;
const int channel = 0;
const int frequency = 50;
const int resolution = 8;
int angle = 0;
// ──────────────────────────────────────────────────────────────

// ──────────────────────────────────────────────────────────────
// Blynk-Zugangsdaten ( Authtoken)
// ──────────────────────────────────────────────────────────────
const char* blynkAuthToken  = "GfQRY55Aul1gIJJpG4-5BxJM5JQLQrtq";
// ─────────────────────────────────────────────────────────────
// WLAN-Zugangsdaten
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
        return; 
    }

    // WLAN verbindung hergestellt
    Serial.println();
    Serial.print("WLAN verbunden! Lokale IP ist: ");
    Serial.println(WiFi.localIP());

    // Blinker-Lib initialisieren (pinMode für alle LED auf OUTPUT und setzen der Pins)
    blinker.begin();

    // Mit WLAN + Blynk-Server verbinden
    Blynk.begin(blynkAuthToken, wifiSsid, wifiPassword);

    ledcSetup(channel, frequency, resolution);
    ledcAttachPin(pinServo, channel);

   Serial.println("Geben Sie einen Winkel zwischen 0° bis 180° ein: ");


    // 6.4) Starte initial im Modus OFF (nur zur Sicherheit)
    blinker.setMode(Blinker::OFF);
}

// ──────────────────────────────────────────────────────────────
// 7) loop()
// ──────────────────────────────────────────────────────────────
void loop() {

    if (Serial.available() > 0)
  {
    angle = Serial.parseInt(); 

    Serial.println("Eingabe: ");
    Serial.println(angle);
  }

  // Variante 1
  int duty = 25 * angle/180 + 6;
  
  ledcWrite(channel, duty);
  delay(100);

    Blynk.run(); // Blynk-Events abarbeiten

    blinker.update(); // Blinker-Logik aktualisieren

}