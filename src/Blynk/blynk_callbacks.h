#ifndef BLYNK_CALLBACKS_H
#define BLYNK_CALLBACKS_H

// ──────────────────────────────────────────────────────────────────────────────
// Schritt 1: Template‐Makros bekanntmachen
// ──────────────────────────────────────────────────────────────────────────────
#include "BlynkConfig.h"

// ──────────────────────────────────────────────────────────────────────────────
// Schritt 2: Nur Makros und Typen aus BlynkApiArduino.h einbinden
// ➔ KEIN globales Objekt "Blynk" erzeugen
// ──────────────────────────────────────────────────────────────────────────────
#include <BlynkApiArduino.h>  
//  → Enthält: BLYNK_WRITE(Vx)‐Makro, Klasse Param (param.asInt()), etc.
//    aber **kein** `BlynkClass Blynk;`-Definition.

// ──────────────────────────────────────────────────────────────────────────────
// Schritt 3: Deine eigene Blinker‐Klasse
// ──────────────────────────────────────────────────────────────────────────────
#include "Blinker/blinker.h"

// ──────────────────────────────────────────────────────────────────────────────
// Schritt 4: Deklaration der Callback‐Setup‐Funktion
//           (Wird in blynk_callbacks.cpp definiert)
// ──────────────────────────────────────────────────────────────────────────────
void setupBlynkCallbacks();

#endif // BLYNK_CALLBACKS_H
