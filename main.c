
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

unsigned int GRID_ROW = 13;
unsigned int GRID_COL = 4;

void printBuffer(unsigned int data[GRID_ROW*GRID_COL] ) {
    printf("===========\n");
    for (int i=0; i<GRID_ROW; i++) {
        for (int j=0; j<GRID_COL; j++) {
            printf("%d, ", data[i*j]);
        }
        printf("\n");
    }
    printf("\n");
}

void spread_fire(unsigned int data[GRID_ROW*GRID_COL]) {
    for (int x = 0; x < GRID_ROW-1; x++) {
        for (int y = 0; y < GRID_COL; y++) {
            unsigned int r_val = (rand() % 3 ) - 5;
            unsigned int prev = y * GRID_ROW + x;
            unsigned int curr = prev - GRID_ROW;
            data[curr] = data[prev] - (r_val & 1);
        }
    }
    printBuffer(data);
}

void init_fire_effect(unsigned int data[GRID_ROW*GRID_COL]) {
    // init flame buffer
    memset(data, 0, GRID_ROW * GRID_COL * sizeof(unsigned int));
    for (int i=0; i<GRID_ROW; i++) {
        data[(GRID_COL-1) * GRID_ROW + i] = 5;
    }
}

int main()
{
    srand(time(NULL));
    unsigned int fire_colors[5] = {0,1,2,3,4};
    unsigned int frame_buf[GRID_WIDTH*GRID_HEIGHT];
    init_fire_effect(frame_buf);
    printBuffer(frame_buf);

    spread_fire(frame_buf);
    spread_fire(frame_buf);
    spread_fire(frame_buf);
    spread_fire(frame_buf);
    spread_fire(frame_buf);
    spread_fire(frame_buf);
    spread_fire(frame_buf);
    spread_fire(frame_buf);
    spread_fire(frame_buf);
    spread_fire(frame_buf);

    printf("Hello world!\n");
    return 0;
}
