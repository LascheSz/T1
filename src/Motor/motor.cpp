#include "motor.h"
#include <Arduino.h>

Motor::Motor(int in1, int in2, int ch1, int ch2) : pinIN1(in1), pinIN2(in2), channel1(ch1), channel2(ch2) {
    ledcSetup(channel1, 1000, 8); // 1 kHz, 8 Bit Auflösung
    ledcAttachPin(pinIN1, channel1);

    ledcSetup(channel2, 1000, 8);
    ledcAttachPin(pinIN2, channel2);

    stop();
}

void Motor::vorwaerts(int speed) {
    ledcWrite(channel1, speed);
    ledcWrite(channel2, 0);
}

void Motor::rueckwaerts(int speed) {
    ledcWrite(channel1, 0);
    ledcWrite(channel2, speed);
}

void Motor::stop() {
    ledcWrite(channel1, 0);
    ledcWrite(channel2, 0);
}
