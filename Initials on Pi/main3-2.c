#include <stdio.h>
#include <sense/sense.h>
#include <string.h>
/**
 * Emily Oldham
 * main3.c
 * This is just like main2.c but instead of an x it prints out an EO. I did this by changing the lights
 * blank if they were certain coordinates. I added an inputColor so that I could keep the users
 * original input and set it to the input color after every light is lit. 
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
	int inputColor;
	for (int i=0;i<8;i++){
		for (int k = 0; k < 8; k++){
			inputColor = color;
		if ((i == 1 || i == 2 || i == 5 || i == 6) && (k == 2 || k == 3 || k == 5 || k ==6 || k == 1 )){
		       inputColor = blank;
		}
 		if ((i == 4 || i == 3) && (k == 6 || k == 5)){
			inputColor = blank;
			}
		if (k == 3){
			inputColor = blank;
		}		
		setPixel(fb->bitmap,i,k,inputColor);
		}
	}
	freeFrameBuffer(fb);
	}
