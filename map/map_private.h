/*Gatech ECE2035 2015 SUMMER ROBOFROGGER
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
#ifndef MAP_PRIVATE_H
#define MAP_PRIVATE_H

#include "mbed.h"

#ifndef ULCD_4DGL_H_
#define ULCD_4DGL_H_
#include "uLCD_4DGL.h"
#endif

#include "globals.h"
#include "map_public.h"

// It defines the settings for drawing the map
#define SIDE_WALK_COLOR_2    0x999999
#define SIDE_WALK_COLOR    0x198C19
#define LINE_COLOR  0xE5E500
#define CANDY_COLOR  0xFF7F7F
#define CANDY_RADIUS 1
#define BIG_CANDY_RADIUS 2
#define WHITE 0xFFFFFF



// It defines the values used in the DEFAULT_MAP
#define MAP_ATTRIBUTE_SIDE_WALK   0 //side walk
#define MAP_ATTRIBUTE_CANDY       1 //candy
#define MAP_ATTRIBUTE_BIG_CANDY   2 //big candy
#define MAP_ATTRIBUTE_ROAD_L      3 //left side of the road    
#define MAP_ATTRIBUTE_ROAD        4 //middle of the road
#define MAP_ATTRIBUTE_ROAD_R      5 //right side of the road
#define MAP_ATTRIBUTE_V_LINE      6 //finish line
#define MAP_ATTRIBUTE_SIDE_WALK_2 7 


#define DEFAULT_MAP {\
0,   0,   0,   7,   3,   4,   5,   3,   4,   5,   3,   4,   5,   7,   6,   6,   6,  \
0,   0,   0,   7,   3,   4,   5,   3,   4,   5,   3,   4,   5,   7,   6,   6,   6,  \
0,   0,   0,   7,   3,   4,   5,   3,   1,   5,   3,   4,   5,   7,   6,   6,   6,  \
0,   0,   0,   7,   3,   4,   5,   3,   4,   5,   3,   1,   5,   7,   6,   6,   6,  \
0,   0,   0,   7,   3,   1,   5,   3,   4,   5,   3,   4,   5,   7,   6,   6,   6,  \
0,   0,   0,   7,   3,   4,   5,   3,   4,   5,   3,   4,   5,   7,   6,   6,   6,  \
0,   0,   0,   7,   3,   4,   5,   3,   4,   5,   3,   4,   5,   7,   6,   6,   6,  \
0,   0,   0,   7,   3,   4,   5,   3,   1,   5,   3,   4,   5,   7,   6,   6,   6,  \
0,   0,   0,   7,   3,   4,   5,   3,   4,   5,   3,   1,   5,   7,   6,   6,   6,  \
0,   0,   0,   7,   3,   4,   5,   3,   4,   5,   3,   4,   5,   7,   6,   6,   6,  \
0,   0,   0,   7,   3,   1,   5,   3,   4,   5,   3,   4,   5,   7,   6,   6,   6,  \
0,   0,   0,   7,   3,   4,   5,   3,   1,   5,   3,   4,   5,   7,   6,   6,   6,  \
0,   0,   0,   7,   3,   4,   5,   3,   4,   5,   3,   4,   5,   7,   6,   6,   6,  \
0,   0,   0,   7,   3,   1,   5,   3,   4,   5,   3,   4,   5,   7,   6,   6,   6,  \
0,   0,   0,   7,   3,   4,   5,   3,   1,   5,   3,   2,   5,   7,   6,   6,   6,  \
0,   0,   0,   7,   3,   4,   5,   3,   4,   5,   3,   4,   5,   7,   6,   6,   6, }

// Here defines some useful macros
#define IDX2X(idx)  (idx%NUM_GRID_X)
#define IDX2Y(idx)  (idx/NUM_GRID_X)
#define XY2IDX(x,y) (y*NUM_GRID_X+x)

void map_draw(void);


#endif //MAP_H