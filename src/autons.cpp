#include "autons.hpp"
#include "globals.h"
#include "main.h"
#include "pros/adi.h"
#include "pros/motors.hpp"
#include "pros/rtos.hpp"
#include "lemlib/api.hpp"
#include "globals.cpp"


void safeRight(){

    intake(intakein);
    chassis.follow(6ballsafe1_txt, 15, 2000, false);
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