#include <wiringPi.h>
#include <stdio.h>
#include <softPwm.h>

#define MOTOR_PIN1 0  // GPIO 17
#define MOTOR_PIN2 1  // GPIO 18
#define SWITCH_PIN 2  // GPIO 27

int motorSwitchState = LOW;
float motorSpeedForward = 0;
float motorSpeedBackward = 0;

void toggleSwitch()
 {
    if (motorSwitchState == LOW)
    {   digitalWrite(SWITCH_PIN, HIGH);
        motorSwitchState = HIGH;    }
    else {    digitalWrite(SWITCH_PIN, LOW);
        motorSwitchState = LOW;    }
}

void forwardSpeedIncrease()
{
    motorSpeedForward += 0.1;
    if (motorSpeedForward >= 1)
    {   motorSpeedForward = 1;    }

    printf("Increased speed of motor forward. Current speed = %f\n", motorSpeedForward);
    softPwmWrite(MOTOR_PIN1, (int)(motorSpeedForward*100));
}

void forwardSpeedReduce()
{
    motorSpeedForward -= 0.1;
    if (motorSpeedForward <= 0) {
        motorSpeedForward = 0;
    }
    printf("Reduced speed of motor forward. Current speed = %f\n", motorSpeedForward);
    softPwmWrite(MOTOR_PIN1, (int)(motorSpeedForward*100));
}

void backwardSpeedIncrease() {
    motorSpeedBackward += 0.1;
    if (motorSpeedBackward >= 1) {
        motorSpeedBackward = 1;
    }
    printf("Increased speed of motor backward. Current speed = %f\n", motorSpeedBackward);
    softPwmWrite(MOTOR_PIN2, (int)(motorSpeedBackward*100));
}

void backwardSpeedReduce() {
    motorSpeedBackward -= 0.1;
    if (motorSpeedBackward <= 0) {
        motorSpeedBackward = 0;
    }
    printf("Reduced speed of motor backward. Current speed = %f\n", motorSpeedBackward);
    softPwmWrite(MOTOR_PIN2, (int)(motorSpeedBackward*100));
}

int main(void) {
    wiringPiSetup();
    pinMode(MOTOR_PIN1, OUTPUT);
    pinMode(MOTOR_PIN2, OUTPUT);
    pinMode(SWITCH_PIN, OUTPUT);

    softPwmCreate(MOTOR_PIN1, 0, 100);  // initialize PWM for motor pin1
    softPwmCreate(MOTOR_PIN2, 0, 100);  // initialize PWM for motor pin2

    softPwmWrite(MOTOR_PIN1, 0);  // set motor pin1 to 0% duty cycle initially
    softPwmWrite(MOTOR_PIN2, 0);  // set motor pin2 to 0% duty cycle initially

    while (1) {
        if (digitalRead(MOTOR_PIN1) == HIGH || digitalRead(MOTOR_PIN2) == HIGH) {
            toggleSwitch();
        }
        delay(100);
    }

    return 0;
}
