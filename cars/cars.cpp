#include "cars.h"
//#include "mbed.h"
//#include "globals.h"
//#include "map_public.h"


//=======================================================================
//Private Functions
bool collision(int x, int y, car_t *car, bool b) {
        if ((x == (car->car_blk_x)) && (y == (car->car_blk_y)) && (b != true)) {
            uLCD.background_color(RED);
            uLCD.textbackground_color(RED);
            uLCD.color(WHITE);
            uLCD.cls();
            uLCD.locate(6,8);
            uLCD.printf("SPLAT!");
            uLCD.background_color(BLACK);
            uLCD.textbackground_color(BLACK);
            uLCD.color(BLUE);
            return 1;
        }      
        return 0;
    }
void car_up(car_t * g)
{
    //Need if statement to loop around
    if (g->car_blk_y == 0)
    {
        car_move(g,g->car_blk_x, 15);
        return;
    } 

    car_move(g, g->car_blk_x, g->car_blk_y-1);
    return;
}

//Function to choose car direction
//This can probably be merged with drive function
void car_down(car_t * g)
{
    if (g->car_blk_y == 15) {
        car_move(g, g->car_blk_x, 0);
    }
    car_move(g, g->car_blk_x, g->car_blk_y+1);
    return;
}

void clean_blk(unsigned int blk_x, unsigned int blk_y)
{
    GRID grid_info = map_get_grid_status(blk_x,blk_y);
    uLCD.filled_rectangle(grid_info.x, grid_info.y, grid_info.x+GRID_SIZE-1, grid_info.y+GRID_SIZE+1, BACKGROUND_COLOR);
    return;
}

void drawCar(car_t * g, int grid_x, int grid_y)
{
    GRID grid_info = map_get_grid_status(grid_x,grid_y);
    int pos_x = grid_info.x + GRID_RADIUS;
    int pos_y = grid_info.y + GRID_RADIUS;
    uLCD.filled_rectangle(pos_x-GRID_RADIUS, pos_y, pos_x+GRID_RADIUS-2,pos_y+GRID_RADIUS+2,g->car_color);
    return;
    
}
//This moves the car from tile to tile

void car_move(car_t * g, unsigned int new_blk_x, unsigned int new_blk_y)
{
    // clean up ghost at old position
    clean_blk(g->car_blk_x, g->car_blk_y);
    // clean the block at new position
    clean_blk(new_blk_x, new_blk_y);
    // draw the ghost at new position
    drawCar(g, new_blk_x, new_blk_y);

    // recover map component
    map_draw_grid(g->car_blk_x, g->car_blk_y);

    g->car_blk_x = new_blk_x;
    g->car_blk_y = new_blk_y;
    return;
}


//==============================================================================
//Public Functions


void car_init(car_t * g, int lane, CAR_MOTION x) {
   g->lane = lane;
   g->car_motion = x;
   if(g->lane == 1) 
   {    g->car_blk_x = 4;
        g->car_blk_y = 0;    
        drawCar(g, 4, 0);
        return;
    }
    if (g->lane == 2)
    {
        g->car_blk_x = 9;
        g->car_blk_y = 0;
        drawCar(g, 9, 0);
        return;
    }
        
    if (g->lane == 3)
    {
        g->car_blk_x = 12;
        g->car_blk_y = 0;
        drawCar(g, 12, 0);
        return;
       }
    if (g->lane == 4)
    {
        g->car_blk_x = 7;
        g->car_blk_y = 10;
        drawCar(g, 7, 10);
        return;
       }
    if (g->lane == 5)
    {
        g->car_blk_x = 10;
        g->car_blk_y = 0;
        drawCar(g, 10, 0);
        return;
       }   

return;
}

void drive(car_t * g)
{
    switch (g->car_motion) {
        case CAR_UP:
            car_up(g);
            break;
        case CAR_DOWN:
            car_down(g);
            break;
        default:
            break;
    }
    return;
}
