/**
 * Emily Oldham
 * main.c
 * 4/20/2020
 * This file is the main for the program clock
 * This file is supposed to take the time from the users computer then conver it to binary 
 * and put it out to the raspberry pi screen. Blue is for hours, green is for minutes
 * and red is for seconds. 
 *
 * */
# include <sense/sense.h>
# include <signal.h>
# include <time.h>
# include <stdio.h>

int run = 1;

//InterruptHandler is what allows you to exit when ctrl-c is pressed.
void interruptHandler(){
	run = 0;
}

/**
 * This is drawScreen, it accpets three ints and a sense_fb_bitmap_t. This is where the 
 * screen is created and displayed. Each for loop calculates the binary for the hour, minute
 * and second and lights up the correct led with the color if there is a 1. 
 *
 * */
void drawScreen (int hour, int min, int sec, sense_fb_bitmap_t *screen){

	//Clears screen
	clearBitmap(screen, 0);
	
	//Display for hours
	for (int i = 0; hour > 0; i++){
		if ( hour % 2 == 1){
			setPixel(screen, 1, i, getColor(0,0,255));
		}
		hour = hour/2;	
	}
	//Display for minute
	for (int i = 0; min > 0; i++){
		if (min % 2 == 1){
			setPixel(screen, 3, i, getColor(0,255,0));
		}
		min = min/2;
	}
	//Display for seconds
	for (int i = 0; sec > 0; i++){
		if (sec % 2 == 1){
			setPixel(screen, 5, i, getColor(255,0,0));
		}
		sec = sec/2;
	}

}

int main(){
	int count = 0;
	sense_fb_bitmap_t screen;
	uint16_t color;
	uint16_t blue = getColor(0,0,255) ;
	uint16_t red = getColor (255,0,0) ;
	uint16_t green = getColor (0,255,0);
	pi_framebuffer_t* fb = getFBDevice();
	
	//Time Setup:
	time_t rawtime;
	struct tm *local;

	signal(SIGINT,interruptHandler);
	while(run){
		//Gets time	
		time (&rawtime);
		local = localtime ( &rawtime );
		
		//Checks the time about every second
		if (count == 100000){
			//Sets the hour,second,minutre
			int hour = local -> tm_hour;
			int min = local -> tm_min;
			int sec = local -> tm_sec;
			
			printf("Local time: %d, %d, %d, \n", hour, min, sec );
		
			drawScreen(hour,min,sec, fb-> bitmap );
				
			
			count = 0;
		}

		count++;
	}
	//End of program
	printf("Exit\n");
	clearBitmap(fb->bitmap, 0);
	freeFrameBuffer(fb);
	return 0;
}
