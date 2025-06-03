#ifndef BLYNK_CONFIG_H
#define BLYNK_CONFIG_H

// ──────────────────────────────────────────────────────────────
// Blynk 2.0: Template ID und Device Name müssen VOR dem Include
//           von BlynkSimpleEsp32.h definiert sein.
// ──────────────────────────────────────────────────────────────
#define BLYNK_TEMPLATE_ID   "TMPL4P2yLMyJJ"
#define BLYNK_DEVICE_NAME   "T1BusESP32"

// Wenn du statt TEMPLATE_ID/DEVICE_NAME lieber TEMPLATE_NAME nutzen
// möchtest, kannst du hier z. B. auch
//   #define BLYNK_TEMPLATE_NAME  "Dein_Template_Name"
// definieren. Für SES (Blynk IoT) reichen die zwei oberen Makros.
//
// Der Auth‐Token wird im Code selbst als `const char*` deklariert,
// weil wir ihn nicht als Makro überall haben wollen.

#endif // BLYNK_CONFIG_H
