#ifndef FOO_H_
#define FOO_H_

#include <stdlib.h>
#include <wiringPi.h>
#include <time.h>
#include <string.h>
#include <wiringPiSPI.h>


int init_encoder(int);
int activate(int);
int init_LSI(int,int,int);
int active_LSI();
int clearLSI();
#endif // FOO_H_