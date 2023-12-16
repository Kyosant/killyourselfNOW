#include "autons.hpp"
#include "globals.h"
#include "main.h"
#include "pros/adi.h"
#include "pros/motors.hpp"
#include "pros/rtos.hpp"
#include "lemlib/api.hpp"
#include "globals.cpp"


void safeRight(){

    chassis.setPose(0, 0, 0); // X: 0, Y: 0, Heading: 0

    intake(intakein); // intake in

    chassis.moveTo(10, 0, 1000, 50); // move to triball under hang bar and pick it up

    chassis.follow(safeRight1_txt, 15, 2000, false, false); 
}

void rushRight(){


}

void safeLeft(){


}

void rushLeft(){


}

void skills(){


}

void nothing(){

    // this is it
    // this auto does literally nothing bro whay are you reading this 😭😭😭

}