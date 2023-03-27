#include <stdlib.h>
#include "tonc.h"

#define NUM_STARS 50

typedef u16 COLOR;

typedef struct {
    int x, y;
    COLOR color;
} Star;

Star stars[NUM_STARS];

void init_starfield() {
    for(int i=0; i<NUM_STARS; i++) {
        stars[i].x = rand() % SCREEN_WIDTH;
        stars[i].y = rand() % SCREEN_HEIGHT;
        stars[i].color = RGB15(31,31,31);
    }
}

void set_pixel(int x, int y, COLOR color) {
    
    vid_mem[y * SCREEN_WIDTH + x] = color;
}

void update_and_draw_starfield() {
    for(int i=0; i<NUM_STARS; i++) {
        // Save the current position of the star
        int x_prev = stars[i].x;
        int y_prev = stars[i].y;

        // Update the position of the star
        stars[i].x -= 1;
        if(stars[i].x < 0) {
            stars[i].x = SCREEN_WIDTH;
            stars[i].y = rand() % SCREEN_HEIGHT;
        }

        // Redraw the background over the previous position of the star
        set_pixel(x_prev, y_prev, RGB15(0,0,0));

        // Draw the star in its new position
        set_pixel(stars[i].x, stars[i].y, stars[i].color);
    }
}


int main() {
    // Initialize the GBA
    REG_DISPCNT = DCNT_MODE3 | DCNT_BG2;
	
	init_starfield();

	while(1) {
		vid_vsync();
		update_and_draw_starfield();
	}

	return 0;
}
