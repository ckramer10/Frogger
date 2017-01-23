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
/** @file map_public.h */
#ifndef MAP_PUBLIC_H
#define MAP_PUBLIC_H

/// The enum define the status of a grid on the map
typedef enum {
    GRID_SIDE_WALK=0,   //Side_walk
    GRID_CANDY,         ///A candy
    GRID_BIG_CANDY,     // Bigger candy!
    GRID_ROAD_L,        //Road left
    GRID_ROAD,          //Middle of the road
    GRID_ROAD_R,        //Road right
    GRID_V_LINE,        //V_line
    GRID_SIDE_WALK_2,
} GRID_STATUS;

/// The structure to store the information of a grid
typedef struct {
    int x;               ///< The upper-left corner of the grid. It is the x coordinate on the screen.
    int y;               ///< The upper-left corner of the grid. It is the y coordinate on the screen.
    GRID_STATUS status;  ///< See enum GRID_STATUS
} GRID;

/** Call map_init() once at the begining of your code
    @brief It initialize the map structure and draw the map.
*/
void map_init(void);

/** Remove the candy/big-candy from map
    @brief It could be called by Pacman when it eat the cookie.
    @param grid_x The horizontal position in the grid.
    @param grid_y The vertical position in the grid.
    @return 1:There is a candy be eaten. 0:The is no candy at the grid.
*/
bool map_eat_candy(int grid_x, int grid_y, int *, int*);

/** Get the information about the grid
    @param grid_x The horizontal position in the grid.
    @param grid_y The vertical position in the grid.
    @return The data structure of the grid. You could access the contents by using the_grid.x , the_grid.status ... etc.
*/
GRID map_get_grid_status(int grid_x, int grid_y);

/** Draw the grid
    @param grid_x The horizontal position in the grid.
    @param grid_y The vertical position in the grid.
*/
void map_draw_grid(unsigned grid_x, unsigned grid_y);

/** Get the number of remaining candy.
    @brief The game should be ended when there is no candy.
    @return The number of remaining cookie.
*/
int  map_remaining_candy(void);

#endif //MAP_H