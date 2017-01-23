 /* Gatech ECE2035 2015 SUMMER ROBOFROGGER
 * Copyright (c) 2015 Gatech ECE2035
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "map_private.h"

GRID map[NUM_GRID];
int num_candy = 0;

void map_init(){
    int i;
    int start_x = (SIZE_X-GRID_SIZE*NUM_GRID_X)/2;
    int start_y = (SIZE_Y-GRID_SIZE*NUM_GRID_Y);
    char temp_wall_type[] = DEFAULT_MAP;

    for(i=0;i<NUM_GRID;i++){
        map[i].x = start_x + IDX2X(i)*GRID_SIZE;
        map[i].y = start_y + IDX2Y(i)*GRID_SIZE;
        switch(temp_wall_type[i]){
            case MAP_ATTRIBUTE_SIDE_WALK:
                map[i].status = GRID_SIDE_WALK;
                break;
            case MAP_ATTRIBUTE_SIDE_WALK_2:
                map[i].status = GRID_SIDE_WALK_2;
                break;
            case MAP_ATTRIBUTE_CANDY:
                map[i].status = GRID_CANDY;
                num_candy++;
                break;
            case MAP_ATTRIBUTE_BIG_CANDY:
                map[i].status = GRID_BIG_CANDY;
                num_candy++;
                break;
            case MAP_ATTRIBUTE_V_LINE:
                map[i].status = GRID_V_LINE;
                break;
            case MAP_ATTRIBUTE_ROAD_L:
                map[i].status = GRID_ROAD_L;
                break;
            case MAP_ATTRIBUTE_ROAD_R:
                map[i].status = GRID_ROAD_R;
                break;
            default:
                map[i].status = GRID_ROAD;
                break;
        }
    }
    map_draw();
}

void map_draw(){
    int i;
    for(i=0;i<NUM_GRID;i++){
        map_draw_grid(IDX2X(i), IDX2Y(i));
    }
}

void map_draw_grid(unsigned grid_x, unsigned grid_y)
{
    unsigned i=XY2IDX(grid_x,grid_y);
    if(map[i].status==GRID_SIDE_WALK) {
        uLCD.filled_rectangle(map[i].x, map[i].y, map[i].x+GRID_SIZE-1, map[i].y+GRID_SIZE-1, SIDE_WALK_COLOR);
    } else if(map[i].status==GRID_SIDE_WALK_2) {
        uLCD.filled_rectangle(map[i].x, map[i].y, map[i].x+GRID_SIZE-1, map[i].y+GRID_SIZE-1, SIDE_WALK_COLOR_2);
    } else if(map[i].status==GRID_CANDY) {
        uLCD.filled_circle(map[i].x+GRID_RADIUS, map[i].y+GRID_RADIUS, CANDY_RADIUS, CANDY_COLOR);
    } else if(map[i].status==GRID_BIG_CANDY) {
        uLCD.filled_circle(map[i].x+GRID_RADIUS, map[i].y+GRID_RADIUS, BIG_CANDY_RADIUS, CANDY_COLOR);
    } else if(map[i].status==GRID_ROAD_L) {
        if ((grid_x!=4)and ((grid_y%3)!=2)) {
            //draw line on the LEFT
            uLCD.filled_rectangle(map[i].x, map[i].y, map[i].x+1, map[i].y+GRID_SIZE-1, LINE_COLOR);
        }
    } else if(map[i].status==GRID_ROAD_R) {
        if ((grid_x!=12)and ((grid_y%3)!=2)) {
            //draw line on the RIGHT
            uLCD.filled_rectangle(map[i].x+GRID_SIZE-1, map[i].y, map[i].x+GRID_SIZE, map[i].y+GRID_SIZE-1, LINE_COLOR);
        }
    } else if(map[i].status==GRID_V_LINE) {
        if ((((grid_x%2)==1)and ((grid_y%2)==0)) or (((grid_x%2)==0)and ((grid_y%2)==1))) {
            uLCD.filled_rectangle(map[i].x, map[i].y, map[i].x+GRID_SIZE-1, map[i].y+GRID_SIZE-1, WHITE);
        } 
    }
}

GRID map_get_grid_status(int grid_x, int grid_y){
    return map[XY2IDX(grid_x,grid_y)];
}

bool map_eat_candy(int grid_x, int grid_y, int *score, int *lives) {
    int idx=XY2IDX(grid_x,grid_y);
    
    if(map[idx].status==GRID_CANDY){
        map[idx].status = GRID_ROAD;
        num_candy--;
        *score = *score + 1;
        return 1;
    }
    
    if(map[idx].status==GRID_BIG_CANDY){
        map[idx].status = GRID_ROAD;
        num_candy--;
        *lives += 1;
        *score += 2;
        return 1;
    }
    return 0;
}

int map_remaining_candy(void){
    return num_candy;
}

