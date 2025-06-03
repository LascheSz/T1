#ifndef MOTOR_H
#define MOTOR_H

class Motor {
private:
    int pinIN1, pinIN2;
    int channel1, channel2;

public:
    Motor(int in1, int in2, int ch1, int ch2);
    void vorwaerts(int speed = 255);
    void rueckwaerts(int speed = 255);
    void stop();
};

#endif
