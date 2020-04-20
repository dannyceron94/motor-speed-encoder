#ifndef FOO_H_
#define FOO_H_

#include <stdlib.h>
#include <wiringPi.h>
#include <time.h>
#include <string.h>

void hello();
int init_encoder(int);
int activate(int);
#endif // FOO_H_