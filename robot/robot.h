#ifndef ROBOT_H
#define ROBOT_H

#define ROBOT_COLOR 0xFFFFFF

void robot_init(int grid_x, int grid_y, int*,int*);
void robot_draw(int grid_x, int grid_y);
void robot_clear(int grid_x, int grid_y);

#endif