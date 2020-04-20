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
    pinMode(pinNum,INPUT);





    return 0;
}

int activate(int rot){
    init_encoder(21);
    int tempCount = rot;
    int exitCount;
    while(tempCount>0){
        printf("%d",digitalRead(Gpin));
        if(digitalRead(Gpin)==0){
            printf("%d\n",digitalRead(Gpin));
            tempCount = tempCount-1;
        }
        
        if(digitalRead(Gpin)>0){
            printf("%d",digitalRead(Gpin));
           exitCount++;
        }
       
    }
    return 0;
}
