// Include header files for platform
#include "mbed.h"
#include "wave_player.h"
#include "SDFileSystem.h"
#include "Shiftbrite.h"
#include <vector>
#include "MMA8452.h" 

// Include header files for roboFrogger project
#include "globals.h"
#include "map_public.h"
#include "robot.h"
#include "cars.h"

//Platform initialization
DigitalIn right_pb(p24);  // push bottom
DigitalIn left_pb(p21); // push bottom
DigitalIn up_pb(p22);    // push bottom
DigitalIn down_pb(p23);  // push bottom
DigitalOut myled(p26);   // led 
AnalogOut DACout(p18);
wave_player waver(&DACout);
uLCD_4DGL uLCD(p9,p10,p11); // LCD (serial tx, serial rx, reset pin;)
Serial pc(USBTX,USBRX);     // used by Accelerometer
MMA8452 acc(p28, p27, 100000); // Accelerometer
SDFileSystem sd(p5, p6, p7, p8, "sd"); //SD card

//Global Variables
int score = 0; //intialize score
int level = 1; //intialize level
static int lives = 3; //intialize lives
int highScore = 0; //intialize highscore
bool invincible = false; 
void gameover(); //declare game over method
void menu() { //this method creates the main screen that appears at the beginning of the game
    uLCD.background_color(BLUE);
    uLCD.textbackground_color(BLUE);
    uLCD.color(WHITE);
    uLCD.cls();
    uLCD.locate(4,2);
    uLCD.printf("RoboFrogger");
    uLCD.locate(2,9);
    uLCD.printf("Press Up Button");
    uLCD.locate(5,10);
    uLCD.printf("to Begin.");
    while (1) {
        if (down_pb == 0) {
            break;
        }
    }
}

int main()
{
     // Initialize the buttons
    left_pb.mode(PullUp);  // The variable left_pb will be zero when the pushbutton for moving the player left is pressed
    right_pb.mode(PullUp); // The variable rightt_pb will be zero when the pushbutton for moving the player right is pressed
    up_pb.mode(PullUp);    //the variable fire_pb will be zero when the pushbutton for firing a missile is pressed
    down_pb.mode(PullUp);  //the variable fire_pb will be zero when the pushbutton for firing a missile is pressed

    // Initialize the timer and call menu
    menu();
    int tick, pre_tick;
    int powerUp = 0;
    srand (time(NULL));
    Timer timer;
    timer.start();
    tick = timer.read_ms();
    pre_tick = tick;

    // Generate Level 1 Screen
    uLCD.background_color(BLACK);
    uLCD.textbackground_color(BLACK);
    uLCD.color(BLUE);
    uLCD.cls();
    uLCD.locate(5,8);
    uLCD.printf("Level 1");
    wait(2);
    
    //Initilize map and robofrogger
    uLCD.cls();
    map_init();
    robot_init(0,8, &score,&lives);
    double x_, y_, z_;
    double x=0;
    double y=8;
    
    //Initialize Cars
    car_t car1;
    car_t car2;
    car_t car3;
    car_t car4;
    car_t car5;
    
    //Initialize Car Colors
    car1.car_color = RED;
    car2.car_color = BLUE;
    car3.car_color = WHITE;
    car4.car_color = GREEN;
    car5.car_color = LGREY;
    
    // Initialize variable to store random car direction
    int car1d;
    int car2d;
    int car3d;
    int car4d;
    int car5d;
    
    //These statements generate a random direction for each car by generating a number 1-10 and then assigning directions with an if statement
    int car1dd = (rand()%(10));
    if (car1dd < 5) {
        car1d = 0; 
    } else {
        car1d = 1;
    } 
    int car2dd = (rand()%(10));
    if (car2dd < 5) {
        car2d = 0;
    } else {
        car2d = 1;
    } 
    int car3dd = (rand()%(10));
    if (car3dd < 5) {
        car3d = 0;
    } else {
        car3d = 1;
    } 
    int car4dd = (rand()%(10));
    if (car4d < 5) {
        car4d = 0;
    } else {
        car4d = 1;
    } 
    int car5dd = (rand()%(10));
    if (car5dd < 5) {
        car5d = 0;
    } else {
        car5d = 1;
    } 
    
    //Initialize the first 3 cars
    car_init(&car1, 1, (CAR_MOTION) car1d);
    car_init(&car2, 2, (CAR_MOTION) car2d);
    car_init(&car3, 3, (CAR_MOTION) car3d);
    
    // 1. Begin the game loop
    while(1) {
        drive(&car1); //mvoe first three cars
        drive(&car2);
        drive(&car3);
        if (level == 2) { //move cars based on levels
            drive(&car4);       
        }
        
        if (level == 3) {
            drive(&car4);
            drive(&car5);
        }
            
        tick = timer.read_ms(); // Read current time
        acc.readXYZGravity(&x_,&y_,&z_);  
        uLCD.locate(1,1);
        uLCD.printf("Lives:%d Score:%d",lives,score); 
        if((tick-pre_tick)>500) { // Time step control
            pre_tick = tick; // update the previous tick
        }
        
        if( x_ > .3) { // acc right
            robot_clear(x,y);
            map_draw_grid(x,y);
            x = x + 1;
            if (x > 16 ) {
                x = 0;
            }    
            robot_draw(x,y);
        }
        if( x_ < -.3) { // acc left
            robot_clear(x,y);
            map_draw_grid(x,y);
            x = x - 1;
            if (x < 0 ) {
                x = 0;
            }    
            robot_draw(x,y);
        }
        if( y_ < -.3) { // acc down
            robot_clear(x,y);
            map_draw_grid(x,y);
            y = y + 1;
            if (y > 15 ) {
                y = 0;
            }    
            robot_draw(x,y);
        }
        if( y_ > .3) { // acc up
            robot_clear(x,y);
            map_draw_grid(x,y);
            y = y - 1;
            if (y  < 0 ) {
                y = 15;
            }    
            robot_draw(x,y);
        }   
        if (up_pb == 0) { //right
            robot_clear(x,y);
            map_draw_grid(x,y);
            x = x + 1;
            if (x > 16 ) {
                x = 0;
            }    
            robot_draw(x,y);
        }
        if (left_pb == 0) { //left
            robot_clear(x,y);
            map_draw_grid(x,y);
            x = x - 1;
            if (x < 0 ) {
                x = 0;
            } 
            robot_draw(x,y);
        }
        if (down_pb == 0) { // up
            robot_clear(x,y);
            map_draw_grid(x,y);
            y = y - 1;
            if (y < 0  ) {
                y = 15;
            } 
            robot_draw(x,y);
        }
        if (right_pb == 0) { //down
            robot_clear(x,y);
            map_draw_grid(x,y);
            y = y + 1;
            if (y  > 15 ) {
                y = 0;
            } 
            robot_draw(x,y);
        }
        map_eat_candy(x,y,&score,&lives); //eat candy on map
        if (collision(x,y,&car1,invincible) == 1) { //car 1 collision 
            lives = lives - 1;
            if (invincible == false) {
                if (lives == 0) {
                    break;
                } else {
                    wait(2);
                    robot_clear(x,y);
                    uLCD.cls();
                    map_init();
                    robot_init(0,8, &score,&lives);
                    x=0;
                    y=8;
                }
            } else {
                robot_init(x,y, &score, &lives);
            }
        }
        if (collision(x,y,&car2,invincible) == 1) { //car2  collision check
            lives = lives - 1;
            if (lives == 0) {
                break;
            } else {
                wait(2);
                robot_clear(x,y);
                uLCD.cls();
                map_init();
                robot_init(0,8, &score,&lives);
                x=0;
                y=8;
            }
        }
        if (collision(x,y,&car3,invincible) == 1) { //car 3 collision
            lives = lives - 1;
            if (lives == 0) {
                break;
            } else {
                wait(2);
                robot_clear(x,y);
                uLCD.cls();
                map_init();
                robot_init(0,8, &score,&lives);
                x=0;
                y=8;
            }
        }
       if ( level == 2 && collision(x,y,&car4,invincible) == 1) { //car 4 collision
                lives = lives - 1;
                if (lives == 0) {
                    break;
                } else {
                    wait(2);
                    robot_clear(x,y);
                    uLCD.cls();
                    map_init();
                    robot_init(0,8, &score,&lives);
                    x=0;
                    y=8;
                }
        }
        
        if ( level == 3 && collision(x,y,&car4,invincible) == 1) { //car 4 collision check
                lives = lives - 1;
                if (lives == 0) {
                    break;
                } else {
                    wait(2);
                    uLCD.cls();
                    map_init();
                    robot_init(0,8, &score,&lives);
                    x=0;
                    y=8;
                }
        }
        
        if ( level == 3 && collision(x,y,&car5,invincible) == 1) { //car 4 and 5 collision check
                lives = lives - 1;
                if (lives == 0) {
                    break;
                } else {
                    wait(2);
                    uLCD.cls();
                    map_init();
                    robot_init(0,8, &score,&lives);
                    x=0;
                    y=8;
                }
        }
        
        if ( up_pb == 0 && down_pb == 0 && left_pb== 0 && right_pb == 0) { //checks for Force Advance
            
            level = level + 1;
            if ( level == 2 || level == 3) {
                uLCD.locate(2,8);
                uLCD.printf("Level Completed");
            }
            if (level == 2) {
                wait(2);
                robot_clear(x,y);
                uLCD.cls();
                uLCD.locate(5,8);
                uLCD.printf("Level 2");
                wait(2);
                uLCD.cls();
                map_init();
                robot_init(0,8, &score,&lives);
                car_init(&car4, 4 , (CAR_MOTION) car4d);
            
            } else if (level == 3) {
                wait(2);
                robot_clear(x,y);
                uLCD.cls();
                uLCD.locate(5,8);
                uLCD.printf("Level 3");
                wait(2);
                uLCD.cls();
                map_init();
                robot_init(0,8, &score,&lives);
                car_init(&car4, 4 , (CAR_MOTION) car4d);
                car_init(&car5, 5 , (CAR_MOTION) car5d);
            } else {
                break;
            }
            x=0;
            y=8;
            
        }
        
        if ( left_pb == 0 && down_pb == 0 && (powerUp == 0)) { //Invincibility
           myled = 1;
           invincible = true;
           powerUp++;
        }   
        
        if (x == 14) { //checks if Robot has reached finish line
            invincible = false;
            myled = 0;
            score = score + 10;
            level = level + 1;
            
            if ( level == 2 || level == 3) {
                uLCD.locate(2,8);
                uLCD.printf("Level Completed");
            }
          
            if (level == 2) {
                wait(2);
                robot_clear(x,y);
                uLCD.cls();
                uLCD.locate(5,8);
                uLCD.printf("Level 2");
                wait(2);
                uLCD.cls();
                map_init();
                robot_init(0,8, &score,&lives);
                car_init(&car4, 4 , (CAR_MOTION) car4d);
            
            } else if (level == 3) {
                wait(2);
                robot_clear(x,y);
                uLCD.cls();
                uLCD.locate(5,8);
                uLCD.printf("Level 3");
                wait(2);
                uLCD.cls();
                map_init();
                robot_init(0,8, &score,&lives);
                car_init(&car4, 4 , (CAR_MOTION) car4d);
                car_init(&car5, 5 , (CAR_MOTION) car5d);
            } else {
                break;
            }
            x=0;
            y=8;
            
        }
    }
    gameover();
}

void gameover() { // this method created the end menu for either winning the game or running out of lives
    uLCD.background_color(BLUE);
    uLCD.textbackground_color(BLUE);
    uLCD.color(WHITE);
    uLCD.cls();
    if (lives == 0) {
    uLCD.locate(5,2);
    uLCD.printf("GAME OVER");
    } else {
        uLCD.locate(5,2);
    uLCD.printf("You Win!");
    }
    if (score > highScore) {
        highScore = score;
    } else if (highScore == 0) {
        highScore = score;
    }
    uLCD.locate(2,9);
    uLCD.printf("High Score: %d", highScore);
    uLCD.locate(2,11);
    uLCD.printf("Press up button");
    uLCD.locate(3,12);
    uLCD.printf("to play again.");
    while(1) {
        if (down_pb == 0) {
            lives = 3;
            score = 0;
            level = 1;
            main();
        }
    }
}


