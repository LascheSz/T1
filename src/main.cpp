// Project: Blinker-Steuerung mit Blynk und ESP32
// ──────────────────────────────────────────────────────────────
// 1) Blynk-Server und WLAN-Verbindung
// ──────────────────────────────────────────────────────────────
#include "BlynkConfig.h"
#include <BlynkSimpleEsp32.h>
#include <WiFi.h>
#include "Blinker/blinker.h"
#include "Blynk/blynk_callbacks.h"
#include <TM1637Display.h>
#include <TimeLib.h>
#include <Arduino.h>
// ──────────────────────────────────────────────────────────────
// Blinker-Pins definieren
// ──────────────────────────────────────────────────────────────
const int PIN_VL = 15;   // linker vorderer Blinker
const int PIN_HL = 21;   // linker hinterer Blinker
const int PIN_HR = 25;   // rechter hinterer Blinker
const int PIN_VR = 13;   // rechter vorderer Blinker
const int PIN_SERVO = 32;   // Servo-Steuer-Pin für Lenkung
#define CLK 17
#define DIO 16
int prevMinute = -1;
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
// 4) Globale Instanz Einer Klasse anlegen
// ──────────────────────────────────────────────────────────────
Blinker blinker(PIN_VL, PIN_HL, PIN_VR, PIN_HR); // Blinker-Instanz anlegen (linker vorderer, linker hinterer, rechter vorderer, rechter hinterer Pin)
Lenkung lenkung(PIN_SERVO, 30, 150); // Lenkung initialisieren (Servo-Pin, min/max Winkel)
// ──────────────────────────────────────────────────────────────
// 5) Blynk-Callback-Prototyp in dieser Datei (muss vor setup() stehen)
// ──────────────────────────────────────────────────────────────
void setupBlynkCallbacks();
// ──────────────────────────────────────────────────────────────
// 6) setup()
// ──────────────────────────────────────────────────────────────

TM1637Display display(CLK, DIO);

void setup() {
    Serial.begin(115200);
    Serial.println("Starte ESP32 mit Blynk...");

    // TM1637 initialisieren: Helligkeit setzen & löschen
    display.setBrightness(0x0f);
    display.clear();

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
    lenkung.begin();

    // Mit WLAN + Blynk-Server verbinden
    Blynk.begin(blynkAuthToken, wifiSsid, wifiPassword);
    
    
    configTzTime("CET-1CEST,M3.5.0/02:00,M10.5.0/03:00", "pool.ntp.org", "time.nist.gov");

    Serial.print("Warte auf NTP-Sync ");

    struct tm timeinfo;
    while (true) {
        // getLocalTime füllt timeinfo und gibt true zurück, wenn gültiger Zeitstempel da ist
        if (getLocalTime(&timeinfo)) {
            break;
        }
        Serial.print(".");
        delay(200);
    }
    Serial.println(" OK!");


    // 6.4) Starte initial im Modus OFF (nur zur Sicherheit)
    blinker.setMode(Blinker::OFF);

    

}
// ──────────────────────────────────────────────────────────────
// 7) loop()
// ──────────────────────────────────────────────────────────────
void loop() {

     struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
    // Falls NTP noch nicht da ist, skippe
        return;
    }

    int stunde  = timeinfo.tm_hour;   // 0..23
    int minuten = timeinfo.tm_min; 

    Serial.print("Aktuelle Zeit: ");
    Serial.print(stunde);
    Serial.print(":");
    Serial.print(minuten);
    Serial.println();


    if (minuten != prevMinute) {
        prevMinute = minuten;
        
        String hourString;
        if (stunde < 10) {
            hourString = "0" + String(stunde);
        }else {
            hourString = String(stunde);
        }

        String minuteString;
        if (minuten < 10) {
            minuteString = "0" + String(minuten);
        } else {
            minuteString = String(minuten);
        }

        int hhmm = stunde + minuten; // HHMM-Format für TM1637
        display.clear();
        display.showNumberDecEx(hhmm, 0b01000000, true);

    }

    Blynk.run(); // Blynk-Events abarbeiten

    blinker.update(); // Blinker-Logik aktualisieren

}