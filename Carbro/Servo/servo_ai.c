#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

#define SERVO_PIN 18

int main() {
    if (wiringPiSetupGpio() == -1) {
        printf("Unable to initialize WiringPi\n");
        return 1;
    }

    softPwmCreate(SERVO_PIN, 0, 200); // Initialize the PWM pin for servo control

    printf("Rotating servo motor...\n");

while(1)
{
    // Rotate servo motor to 0 degrees
    softPwmWrite(SERVO_PIN, 15);
    delay(2000);

    // Rotate servo motor to 90 degrees
    softPwmWrite(SERVO_PIN, 24);
    delay(1000);

    // Rotate servo motor to 180 degrees
    softPwmWrite(SERVO_PIN, 33);
    delay(1000);
}
    printf("Done rotating servo motor.\n");

    return 0;
}
