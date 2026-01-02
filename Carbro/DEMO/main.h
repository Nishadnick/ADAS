#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <wiringPi.h>
#include <time.h>
#include <lcd.h>
#include <string.h>

#define PIN_TO_CIRCUIT 8
#define LDR_LED 11

#define GPIO_SERVO 13

#define MOTOR_ENABLE 27
#define MOTOR_CPIN 12
#define MOTOR_APIN 6

#define RS 25
#define E 24
#define D4 23
#define D5 17
#define D6 18
#define D7 22
#define ROW 2
#define COL 16
#define PIN_MODE 4

#define GPIO_TRIGGER 20
#define GPIO_ECHO 21

#define GPIO_PWM_LED 19

#define MOTOR_ENABLE 27
#define MOTOR_CPIN 12
#define MOTOR_APIN 6

#define START_STOP_BUTTON 16

#define BUZZER 5

void park_mode(void);
void drive_mode(void);
void rc_time(int);
#endif
