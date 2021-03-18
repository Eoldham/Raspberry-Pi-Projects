#include <stdio.h>
#include <sense/sense.h>
#include <unistd.h>
#include<signal.h>
#include <stdlib.h>
#include <linux/input.h>
#include "main.h"

/**
 * Emily Oldham
 * main.c
 * 4/13/20
 * Ths file holds the main method along with a callBack function and an interrupt handler. 
 * This file is where shaking is decteted along with where the joystick is implemented. 
 * */


pi_framebuffer_t* fb;
int joystickCounter = 1;
uint16_t color;

/**
 * This is the interrupt_handler function that allows you to exit when ctrl c is pressed
 * */
int run = 1;
void interrupt_handler(int sig){
	run = 0;
}

/**
 * This is the function called when the joystick is pressed, depending on the counter number
 * it changes the color and then replaces the dice with the same dice but in a different
 * color. 
 * */
void callbackFn(unsigned int code){
	pi_framebuffer_t* fb=getFBDevice();
	//This is where the color is calculated
	if (joystickCounter == 1){
		color = getColor(0,255,0);
		joystickCounter++;
	}else if (joystickCounter == 2){
		color = getColor(255,0,0);
		joystickCounter++;
	}else if (joystickCounter == 3){
		color = getColor(0,0,255);
		joystickCounter = 1;
	}
	
	int blank = getColor(0,0,0);
	int j,i;
	//This is where it replaces the dice
	for ( j = 0; j < 8; j++){
		for (i = 0; i < 8; i++){
			if (fb->bitmap->pixel[j][i] != blank){
				setPixel(fb->bitmap,i,j,color);
			}
		}
	}
}

/**
 * This is the main method
 * It first off sets all of the necessary variables and pointers
 * Then if a device is detected it will start a while run loop, to determined if the 
 * device is being shaken, every time the timer reaches 30 the accelData is found.
 * Only data.z is checked which means it is best for the device to be shaked up and down. 
 * It also checks for the joystick being pressed which allows for colors to be changed. 
 * */
int main(){
	color = getColor (0,0,255);
	int timer = 0;
	pi_i2c_t*  device;
	pi_joystick_t* joystick = getJoystickDevice();
	coordinate_t data;
	signal(SIGINT, interrupt_handler);
	pi_framebuffer_t* fb=getFBDevice();
	device = geti2cDevice();
	if(device){
		configureAccelGyro(device);
		while(run){
			usleep(2000);
			while(run && getAccelData(device,&data)){
				if(timer == 30){
					while (run){
						getAccelData(device,&data);
					//Checking to see if shaken
					if (data.z > 1.5 || data.z < 0 || data.x > 1 ){
						//This is what creates the dice
						getDice(fb->bitmap,color);
					}
					//This checks to see if joystick was pressed
					pollJoystick(joystick,callbackFn,1000);
						}
				timer = 0;
				}
				timer++;
			}
		}
		printf("\nExiting...\n");
	}
	clearBitmap(fb->bitmap,0);
	freeFrameBuffer(fb);
	freeJoystick(joystick);
	freei2cDevice(device);
	return 0;
}
