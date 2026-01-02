
#include <stdio.h>
#include <wiringPi.h>

int main(void)
{
    // Switch: Physical pin 31, BCM GPIO6, and WiringPi pin 22.
    const int button = 4;

    wiringPiSetup();

    pinMode(5, OUTPUT);

//    pullUpDnControl(button, PUD_UP);
	pinMode(button, INPUT);
    while (1){
        if (digitalRead(button) == LOW) {
            fprintf(stderr, "Switch is pressed\n");
		printf("BUTTON PRESSED.......\n");
		//pinMode(5, INPUT);
		digitalWrite(5, HIGH);
        } else {
		digitalWrite(5, LOW);
		//pinMode(5, OUTPUT);
            fprintf(stdout, "Switch is released\n");
            }
            delay(50);
    }

    return 0;
}
