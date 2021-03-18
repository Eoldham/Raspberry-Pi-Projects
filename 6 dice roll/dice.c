#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sense/sense.h>
#include "main.h"
#include <time.h>
/**
 * Emily Oldham
 * Dice.c
 * 4/13/20
 * This File holds the method getDice, it accepts a sense_fb_bitmap_t and a uint16_t
 * It has no return. 
 * The way it works is it uses rand() to pick a number between 1 and 6. That number, using a switch 
 * statement is then used to place the corresponding dice image onto the screen. There is a 
 * while loop that keeps count of how many dice have been put on the board and since 
 * the dice are only 3x3 the while loop also determines where on the board the dice should
 * be placed. 
 * */
 
void getDice(sense_fb_bitmap_t *screen, uint16_t color ){
	srand(time(0));
	//These are the Dice 1 through 6
	uint16_t dice1[3][3] = {
		{0,0,0},{0,0xFFF,0},{0,0,0}
	};

	uint16_t dice2[3][3] = {
		{0,0,0xFFF},{0,0,0},{0xFFF,0,0}
	};

	uint16_t dice3[3][3] = {
		{0,0,0xFFF},{0,0xFFF,0},{0xFFF,0,0}
	};

	uint16_t dice4[3][3] = {
		{0xFFF,0,0xFFF},{0,0,0},{0xFFF,0,0xFFF}
	};

	uint16_t dice5[3][3] = {
		{0xFFF,0,0xFFF},{0,0xFFF,0},{0xFFF,0,0xFFF}
	};

	uint16_t dice6[3][3] = {
		{0xFFF,0,0xFFF},{0xFFF,0,0xFFF},{0xFFF,0,0xFFF}
	};

	int diceRoll;
	int x,y,setx,sety;
	int count = 1;
	//The while loop that keeps count of how many dice are on the screen 
	while (count < 5){
		if (count == 1){
			setx = 0;
			sety = 0;
		}else if (count == 2){
			setx = 5; 
			sety = 0;
		}else if (count == 3){
			setx = 0;
			sety = 5;
		}else if (count == 4){
			setx = 5;
			sety = 5;
		}
		//This is the random dice number	
		diceRoll = rand() % 6 +1;

		//Switch statement that actually creates each dice and sets the pixels
			switch (diceRoll){
				case 1:
					for ( x = setx; x < setx + 3; x++){
						for ( y = sety; y < sety + 3; y++){
							setPixel(screen,x,y,color & dice1[x - setx ][y - sety]);
							}
						}
					break;
				case 2:
					for (x = setx; x < setx + 3; x++) {
						for (y = sety; y < sety + 3; y++){
							setPixel(screen, x, y, color & dice2[x - setx][y - sety]);
							}
						}
					break;
				case 3:
					for (x = setx; x <setx + 3; x++){
						for (y = sety; y< sety + 3; y++){
							setPixel(screen,x,y,color & dice3[x-setx][y-sety]);
							}
						}
					break;
				case 4: 
					for (x = setx; x < setx + 3; x++){
						for (y = sety; y < sety + 3; y++){
							setPixel(screen, x, y, color & dice4[x-setx][y -sety]);
							}
						}
					break;
				case 5:
					for (x = setx; x <setx + 3; x++){
						for (y = sety; y < sety + 3; y++){
							setPixel(screen, x, y, color & dice5[x-setx][y-sety]);
						}
					}
					break;
				case 6: 
					for (x = setx; x < setx + 3; x++){
						for (y = sety; y< sety + 3; y++){
							setPixel(screen, x, y, color & dice6[x-setx][y-sety]);
							}
						}
					break;
				default: 
					count = count -1;
					break;
			}
			count ++;
	}
}

