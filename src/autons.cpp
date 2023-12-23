#include "autons.hpp"
#include "globals.h"
#include "main.h"
#include "pros/adi.h"
#include "pros/motors.hpp"
#include "pros/rtos.hpp"
#include "lemlib/api.hpp"



void safeRight(){

    chassis.setPose(0, 0, 0); // X: 0, Y: 0, Heading: 0

    intake(intakein); // intake in

    chassis.moveTo(10, 0, 90, 50); // move to triball under hang bar and pick it up

    chassis.follow(safeRight1_txt, 15, 2000, false, false); 
}

void rushRight(){


}

void safeLeft(){

    chassis.setPose(0, 0, 0); // X: 0, Y: 0, Heading: 0

    intake(idle); // intake idle

    chassis.follow(safeLeft1_txt, 15, 2000, true, false); 
    chassis.waitUntilDone();

    chassis.follow(safeLeft2_txt, 15, 2000, false, true); 
    chassis.waitUntil(30);
    wings(out);
    chassis.waitUntil(45);
    wings(in);
    chassis.waitUntilDone();
}

void rushLeft(){
    chassis.setPose(0, 0, 0); // X: 0, Y: 0, Heading: 0

    intake(idle); // intake idle

    chassis.follow(rushLeft1_txt, 15, 2000, false, true); 
    chassis.waitUntil(30);
    wings(out);
    chassis.waitUntilDone();
    wings(in);

    chassis.moveTo(10, 0, 270, 50);
    chassis.waitUntil(30);
    intake(intakeout);
    
    chassis.follow(rushLeft2_txt, 15, 2000, false, true); 
    chassis.waitUntil(30);
    wings(out);
    chassis.waitUntil(45);
    wings(in);
    chassis.waitUntilDone();

}

void skills(){


}

void nothing(){

    // this is it
    // this auto does literally nothing bro whay are you reading this 😭😭😭

}

void tuning1(){

    intake(idle);
    
    chassis.setPose(0, 0, 0);
    chassis.moveTo(0, 10, 0, 2000);
    

}



void tuning2(){
    chassis.arcade(100, 0);

    chassis.setPose(0, 0, 0);
    chassis.turnTo(30, 0 , 2000);
    

}

void tuning3(){
    chassis.follow(safeLeft1_txt, 15, 4000, false);
}

    
