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
*              the a motor encoder sensor is hooked up the raspberrypi to read the actial peed
*              of the wheel.
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
#include <wiringPiSPI.h>

#define PI 3.14159265358979323846


int Gpin;
int MISO;
int MOSI;
int SCLK;
static const int CHANNEL=0;
int max_speed_hz = 5000000;

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
    int prevws_value = digitalRead(Gpin);
    clock_t start = clock();
    while(1){
        int signal  = digitalRead(Gpin);
        // if(signal == prevws_value){
        //     //  printf("%d\n",prevws_value);
        //     prevws_value = signal;
        //     continue;}
        if(signal != prevws_value){
            exitCount++;
            printf("%d\n",exitCount);
        }
        prevws_value = signal;
        if(exitCount==rot){
            clock_t end = clock();
            float seconds = (float)(end - start) / CLOCKS_PER_SEC;
            //calculateing speed
            // i could include the radius of the wheel but it might not me necesarry 
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

// this part of the code does not work, cannot communitate to the LS7
int init_LSI(int miso, int mosi, int sclk){
    if(wiringPiSetup()<0){
        printf("WiringPiSetUp failed");
        return-1;
    }
    MISO = miso;
    MOSI = mosi;
    SCLK = sclk;
    // Configure the interface.
   // CHANNEL insicates chip select,
   // 500000 indicates bus speed.
    int fd = wiringPiSPISetup (CHANNEL, max_speed_hz);
    if(fd<0){
        printf("SPI setup error");
    };
    printf("Init result: %d\n",fd);
    clearLSI();
    // pinMode(MISO,OUTPUT);
    // pinMode(MOSI,INPPUT);
    // pinMode(SCLK,OUTPUT);
}

int clearLSI(){
    // char buff[0] = 0x76;
    char* send =  (char*) malloc(5 * sizeof(char));
    if(wiringPiSPIDataRW (CHANNEL, send, 1)<0){
        printf("SPI Data error");
        return -1;
    }
    sleep(5);
    return 0;
}

int active_LSI(){
    // the size of 5bytes for the LS7366R data
    char* send =  (char*) malloc(5 * sizeof(char));
    send[0] ='0';
    
    init_LSI(12,13,14);
    printf("%d\n",wiringPiSPIDataRW (CHANNEL,send,4));
    printf("hex%x\n",send);
    printf("%n ",send[0]);
    
    return 0;
}