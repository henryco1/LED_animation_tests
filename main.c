#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define GRID_ROW 13
#define GRID_COL 4

void printBuffer(unsigned int data[GRID_ROW*GRID_COL] )
{
    printf("===========\n");
    for (int i=0; i<GRID_ROW*GRID_COL; i++)
    {
        printf("%d, ", data[i]);
        if (i % GRID_COL == 3)
        {
            printf("\n");
        }
    }
    printf("\n");
}

void spread_fire(unsigned int data[GRID_ROW*GRID_COL])
{
    for (int x = 0; x < GRID_ROW; x++)
    {
        for (int y = 1; y < GRID_COL; y++)
        {
            unsigned int r_val = (rand() % 3 ) - 3;
            unsigned int prev = y * GRID_ROW + x;
            unsigned int curr = prev - GRID_ROW;
            data[curr] = data[prev] - (r_val & 3);
        }
    }
    printBuffer(data);
}

void init_fire_effect(unsigned int data[GRID_ROW*GRID_COL])
{
    // init flame buffer
    memset(data, 0, GRID_ROW * GRID_COL * sizeof(unsigned int));
    for (int i=0; i<GRID_ROW; i++)
    {
        data[(GRID_COL-1) * GRID_ROW + i] = 5;
    }
}

void run_fire_effect(unsigned int data[GRID_ROW*GRID_COL])
{
    init_fire_effect(data);
    for (int i=0; i<10; i++)
    {
        spread_fire(data);
    }
}

/*
Matrix style digital rain
- falling pixel stream
- any column in the grid can have a pixel stream
- each pixel stream has a chance randomly appears from the top
- the head of the pixel stream has its own bright color
- each stream has a different length and speed
- each stream is darkest at the top and brightest at the bottom
- each stream must completely traverse the column before a new stream is generated

strategies
1. struct of pixel stream nodes
- initialize pixel stream struct node for each column
- loop through the grid and get the node at each column
- given each column,
    - if a stream already exists in the column
        - if the node already has a stream
            - compute the current position of the stream head
                - if the head is negative, continue to the next index of the stream
                - else if the head_idx >= 0, set that index as the curr_head_pos
            - iterate through the stream col indices; for each positive index,
                - update the colors of the stream
                    - note this assumes you can't run out of colors
                    - divide the rest of the stream into blocks of size (GRID_COL - length) / 2
                    - color each block according to the digital rain color key
                - else the stream index is negative, so we have the current position of the stream tail
                    - from the position of the curr_head_pos, keep iterating through the stream indices until we reach a negative number
                    - the previous index is the curr_tail_pos
    - otherwise, a stream has a chance to appear
        - if a stream is randomly generated, update the node and initialize the stream
            - compute the current position of the stream head
            - randomly generate the stream length
            - color the head
            - initialize thes stream speed
        - else the stream was not generated, so continue to the next node

2. An invisible layer of nodes that holds data for digital rain streams
- initialize a 1D grid width array of rain structs for each column in the 2d array display
    - each struct contains all properties of the rain stream including position, stream size, speed, col_is_raining
- traverse the 1D array of structs and get the current struct
    - for each struct,
        - if col_is_raining == true
            - update the properties of the struct
            - pass the relevant properties to the 2D array display
        - else if col_is_raining != false
            - randomly determine of a col will be raining
            - if col_is_raining becomes true, run the rain_update() function
            - else, continue
*/

typedef struct
{
    unsigned int row;
    unsigned int col;
    unsigned int speed;
    unsigned int size;
    unsigned int col_is_raining;
    unsigned int head;
    unsigned int tail;
    unsigned int block_size;
} rainNode;

/*
Initializes the rainNodes that model the behavior of the rain in each column
Each rainNode is a "cloud" that controls the rain that falls from it
*/
rainNode* init_digital_rain(unsigned int data[GRID_ROW*GRID_COL])
{
    unsigned int min_speed_val = 1;
    unsigned int max_speed_val = 3;
    unsigned int min_size_val = 2;
    unsigned int max_size_val = 8;
    rainNode rain_cloud[GRID_ROW];
    memset(data, 0, GRID_ROW * GRID_COL * sizeof(unsigned int));

    for (int i=0; i<GRID_ROW; i++)
    {
        rain_cloud[i].row = i;
        rain_cloud[i].col = -1;
        rain_cloud[i].speed = rand() % (max_speed_val + 1 - min_speed_val) + min_speed_val;
        rain_cloud[i].size = rand() % (max_size_val + 1 - min_size_val) + min_size_val;
        rain_cloud[i].col_is_raining = 0;
        rain_cloud[i].head = 0;
        rain_cloud[i].tail = rain_cloud[i].head - rain_cloud[i].size;
        rain_cloud[i].block_size = rain_cloud[i].size / 4;
    }
    return rain_cloud;
}

/*
This function computes the current position of each rain stream. The position
data is computed in the rain_cloud.
*/
void update_rain_cloud(rainNode* rain_cloud)
{

}

/*
This reads the rainCloud data and puts in the display buffer. This function
updates each column of the display buf.

The display data is a global just in case I want to have an
accelerometer interrupt system and update the display data.
*/
void display_digital_rain(unsigned int data[GRID_ROW*GRID_COL], rainNode* rain_cloud)
{

}

void run_digital_rain(unsigned int data[GRID_ROW*GRID_COL])
{
    rainNode* rain_cloud = init_digital_rain(data);
    for (int i=0; i<10; i++)
    {
        update_rain_cloud(rain_cloud);
        display_digital_rain(data, rain_cloud);
    }
}

/*
UV Mapping
- map a 2d plane to a parametric figure
- parameterization of a cylinder
    - convert x,y to polar
        - r = √ ( x2 + y2 )
        - θ = tan-1 ( y / x )
        - z = z (this would be the row

*/

int main()
{
    srand(time(NULL));
    unsigned int frame_buf[GRID_ROW*GRID_COL];

    run_fire_effect(frame_buf);
    run_digital_rain(frame_buf);

    return 0;
}
