#include <stdio.h>
#include <sense/sense.h>
#include <string.h>
/**
 * Emily Oldham
 * main2.c
 * This file takes in users input and reads the color, it then changes the x color to the users color
 * returns an error if color does not work and if user types in blank it will not appear either
 * */

int main(){
	int red=getColor(255,0,0);
	int green=getColor(0,255,0);
	int blue=getColor(0,0,255);
	int blank=getColor(0,0,0);
	int color;
	pi_framebuffer_t* fb=getFBDevice();
	clearBitmap(fb->bitmap,blank);
	char input[10];
	printf("What color would you like to make the x, red, green or blue? \n");
	scanf("%s", input);
	if (strcmp(input,"red")== 0 ){
		color = red; 
	}else if (strcmp(input, "blue") == 0){
		color = blue;
	}else if (strcmp(input, "green") == 0){
		color = green;
	}else if (strcmp(input,"blank") == 0){
		color = blank;
	}else{
		printf("That is not a valid color \n");
		color = blank;
	}
			
	for (int i=0;i<8;i++){
		setPixel(fb->bitmap,i,i,color);
		setPixel(fb->bitmap,i,7-i,color);
	}
	freeFrameBuffer(fb);
}
