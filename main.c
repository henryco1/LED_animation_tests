
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

unsigned int GRID_WIDTH = 4;
unsigned int GRID_HEIGHT = 13;

void printBuffer(unsigned int data[GRID_WIDTH*GRID_HEIGHT] ) {
    printf("===========\n");
    for (int i=0; i<GRID_WIDTH*GRID_HEIGHT; i++) {
        printf("%d, ", data[i]);
        if ((i+1) % GRID_WIDTH == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

void spread_fire(unsigned int data[GRID_WIDTH*GRID_HEIGHT]) {
    for (int x = 1; x < GRID_HEIGHT; x++) {
        for (int y = 0; y < GRID_WIDTH; y++) {
            unsigned int r_val = (rand() % 3 ) - 5;
            unsigned int prev = y * GRID_WIDTH + x;
            unsigned int curr = prev - GRID_WIDTH;
            data[curr] = data[prev] - (r_val & 1);
        }
    }
    printBuffer(data);
}

void init_fire_effect(unsigned int data[GRID_WIDTH*GRID_HEIGHT]) {
    // init flame buffer
    memset(data, 0, GRID_WIDTH * GRID_HEIGHT * sizeof(unsigned int));
    for (int i=0; i<GRID_WIDTH; i++) {
        data[(GRID_HEIGHT-1) * GRID_WIDTH + i] = 5;
    }
}

int main()
{
    srand(time(NULL));
    unsigned int fire_colors[5] = {0,1,2,3,4};
    unsigned int frame_buf[GRID_WIDTH*GRID_HEIGHT];
    init_fire_effect(frame_buf);
    printBuffer(frame_buf);

    printf("Hello world!\n");
    return 0;
}
