assignment4 : main.c motors.h motors.c speed_encoder.h speed_encoder.c
	gcc -I wall main.c motors.c motors.h speed_encoder.h speed_encoder.c -lwiringPi -o assignment4
rm:
	rm assignment4
