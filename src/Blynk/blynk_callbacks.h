#ifndef BLYNK_CALLBACKS_H
#define BLYNK_CALLBACKS_H

// ──────────────────────────────────────────────────────────────────────────────
// Template‐Makros bekanntmachen
// ──────────────────────────────────────────────────────────────────────────────
#include "BlynkConfig.h"

// ──────────────────────────────────────────────────────────────────────────────
// Nur Makros und Typen aus BlynkApiArduino.h einbinden
// ➔ KEIN globales Objekt "Blynk" erzeugen
// ──────────────────────────────────────────────────────────────────────────────
#include <BlynkApiArduino.h>  
//  → Enthält: BLYNK_WRITE(Vx)‐Makro, Klasse Param (param.asInt()), etc.
//    aber **kein** `BlynkClass Blynk;`-Definition.

// ──────────────────────────────────────────────────────────────────────────────
// Eigene Klasse
// ──────────────────────────────────────────────────────────────────────────────
#include "Blinker/blinker.h"
#include "Lenkung/lenkung.h"
// ─────────────────────────────────────────────────────────────────────────────
// Globale Instanzen der Klassen Blinker und Lenkung
// ──────────────────────────────────────────────────────────────────────────────
extern Blinker blinker;
extern Lenkung lenkung;
// ──────────────────────────────────────────────────────────────────────────────
// Deklaration der Callback‐Setup‐Funktion
//           (Wird in blynk_callbacks.cpp definiert)
// ──────────────────────────────────────────────────────────────────────────────
void setupBlynkCallbacks();

#endif // BLYNK_CALLBACKS_H
