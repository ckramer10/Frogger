#include "mbed.h"
//#include "cars.h"
#include "map_public.h"
#include "globals.h"


//void clearCar(int lane);
//void moveCar(int whichOne);         // 1 -> lane 1. 2 -> lane 2 etc



/// The enum defines the motion of the car
typedef enum {
    CAR_UP=0, ///< move up
    CAR_DOWN, ///< move down
} CAR_MOTION;

typedef struct 
{
    unsigned int car_blk_x;   ///< horizontal position in the grid
    unsigned int car_blk_y;   ///< vertical position in the grid
    unsigned int car_color;   ///< color of the car
    unsigned int lane;         //car lane
    CAR_MOTION car_motion;  ///< the motion of the car  
} car_t;

void car_move(car_t * g, unsigned int new_blk_x, unsigned int new_blk_y); //A function to move the car
//void drawCar(car_t * g, int grid_x, int grid_y);   // @param lane @param color I don't think this function needs to be public
void car_init(car_t * g, int lane,CAR_MOTION x); // Initialize a car
void drive(car_t*);
bool collision(int x, int y, car_t *car, bool b);
