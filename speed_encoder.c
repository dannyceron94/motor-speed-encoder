/**************************************************************
* Class: CSC-615-01 Spring 2020
* Name: Danny Daneth Ceron Garcia
* Student ID: 918581149
* Project: <Assignment 4 - Speed encoder>
*
* File: <speed_encoder.c>
*
* DescriptioMon: At a high level explanation, this program access and set up pins in which
*              dc motor is hooked up to and send electric current to make the motor rotate
*              one pins sets the modulation to specify the speed of the motor
*              2 other pins are use pass current to make the motors rotate, depending on
*              the direction of the current the motor will rotate backwards of forward.
*
*
*              
* sources: https://www.electronicwings.com/raspberry-pi/raspberry-pi-pwm-generation-using-python-and-c
*          https://github.com/sbcshop/MotorShield/blob/master/PiMotor.py
**************************************************************/
#include "speed_encoder.h"

#include <stdlib.h>
#include <wiringPi.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include<time.h>

#define PI 3.14159265358979323846


int Gpin;
void hello(){
    printf("hello from the speed_encoder file");
}

int init_encoder(int pinNum){
    if(wiringPiSetup()<0){

        printf("WiringPiSetUp failed");
        return-1;
    }
    Gpin = pinNum;
    pinMode(Gpin,INPUT);
    // digitalWrite(Gpin, HIGH);
    // digitalWrite(Gpin, LOW);

    return 0;
}

int activate(int rot){
    init_encoder(28);
    int exitCount=0;
    int quit=0;
    clock_t start = clock();
    while(1){
        int pinnn = 0;
        pinnn = digitalRead(Gpin);
        if(pinnn==0){
            exitCount++;
        }
        if(exitCount==rot){
            clock_t end = clock();
            float seconds = (float)(end - start) / CLOCKS_PER_SEC;
            //calculateing speed
            float angularSpeed =  (2*PI)/seconds;
            printf("%f cm/s,%f m/s %f km/s\n",angularSpeed*3,angularSpeed*0.03,angularSpeed*0.00003);
            // resetting values for next calculation
            exitCount = 0;
            quit++;
            clock_t start = clock();
        }
        if(quit>20){break;}
    }
    return 0;
}
