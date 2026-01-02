#include <wiringPi.h>
#include <stdio.h>

#define BUZZER 21

void buzz(int noteFreq, int duration) {
  int halveWaveTime = 1000000 / (noteFreq * 2);
  int waves = duration * noteFreq;
  for (int i = 0; i < waves; i++) {
    digitalWrite(BUZZER, HIGH);
    delayMicroseconds(halveWaveTime);
    digitalWrite(BUZZER, LOW);
    delayMicroseconds(halveWaveTime);
  }
}

void play() {
  int t = 0;
  int notes[] = { 262, 294, 330, 262, 262, 294, 330, 262, 330, 349, 392, 330, 349, 392, 392, 440, 392, 349, 330, 262, 392, 440, 392, 349, 330, 262, 262, 196, 262, 262, 196, 262 };
  int duration[] = { 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 1000, 500, 500, 1000, 250, 250, 250, 250, 500, 500, 250, 250, 250, 250, 500, 500, 500, 500, 1000, 500, 500, 1000 };
  int notesCount = sizeof(notes) / sizeof(int);
  for (int i = 0; i < notesCount; i++) {
    buzz(notes[i], duration[t]);
    delay(duration[t] * 0.1);
    t++;
  }
}

int main(void) {
  wiringPiSetupGpio();
  pinMode(BUZZER, OUTPUT);
  play();
  return 0;
}
