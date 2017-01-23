#include "mbed.h"
#include "globals.h"
#include "map_public.h"
#include "robot.h"

// Following code will only draw the Robot on the screen. You are expected to modify most of the functions here.
// All other necessary functions will be implemented by you. Ex: the movement of roboFrogger, calculate the score ... etc.

void robot_init(int grid_x, int grid_y, int* score,int* lives){

    map_eat_candy(grid_x,grid_y, score,lives); //clear the candy on the grid.
    robot_draw(grid_x,grid_y);

}

void robot_draw(int grid_x, int grid_y){
    
    GRID grid_info = map_get_grid_status(grid_x,grid_y);
    // Calculate the actual position of the grid
    int frog_x = grid_info.x + GRID_RADIUS;
    int frog_y = grid_info.y + GRID_RADIUS;
    
    // MAKE
    uLCD.filled_circle(frog_x, frog_y, 2, 0x0000FF);
    uLCD.filled_rectangle(frog_x-2,frog_y+1,frog_x+2,frog_y+3,0xFFFFFF);
    //uLCD.line(frog_x-1, frog_y+4,frog_x-1, frog_y+5, 0xFF0000);//legs
    //uLCD.line(frog_x+2, frog_y+4,frog_x+2, frog_y+5, 0xFF0000);
    uLCD.line(frog_x+2, frog_y+1,frog_x+4, frog_y+1, 0x0000FF);//hands
    uLCD.line(frog_x-2, frog_y+1,frog_x-4, frog_y+1, 0x0000FF); 
}

void robot_clear(int grid_x, int grid_y){
    
    GRID grid_info = map_get_grid_status(grid_x,grid_y);
    //Fill the grid (a rectangle) with BACKGROUND_COLOR to clear the roboFrogger
    uLCD.filled_rectangle(grid_info.x, grid_info.y, grid_info.x+GRID_SIZE-1, grid_info.y+GRID_SIZE-1, BACKGROUND_COLOR);
    
}
