#include <stdlib.h>
#include <wiringPi.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

#include "motors.h"
#include "speed_encoder.h"
int main() {
   // run(4);
   int m1 = init("motor1","config2");
   int m2 = init("motor2","config1");
   allForward(15);
  
   activate(100);
   sleep(1);
   stopAll();
   printf("Hello, World!");
   return 0;
}
