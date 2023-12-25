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

    chassis.moveToPoint(10, 0, 1000, true); // move to triball under hang bar and pick it up

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

    chassis.moveToPoint(10, 0, 1000, true);
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

    chassis.setPose(0, 0, 0);
    chassis.moveToPoint(0, 10, 1110, true, 127, true);
    chassis.waitUntilDone();

}



void tuning2(){

   

    chassis.setPose(0, 0, 0);
    chassis.turnTo(30, 0 , 2000, true, 127, true);
    

}

void tuning3(){
    
    intake(idle);
    chassis.setPose(-38, -52, 270);
    chassis.follow(safeLeft1_txt, 15, 4000, true);
    chassis.waitUntil(10);
    intake(intakein);
    chassis.waitUntil(30);
    intake(intakeout);
}


void tuning4(){

    chassis.setPose(12, 12, 0);
    intake(idle);

    chassis.follow(test1_txt, 5, 4000, true);
    intake(intakein);
    chassis.follow(test2_txt, 5, 4000, false);
    intake(idle);
    chassis.follow(test3_txt, 4, 4000, false);
    intake(intakeout);
    chassis.follow(test4_txt, 5, 4000, true);
    intake(idle);
    cata(fire);
    chassis.moveToPose(12, 12, 0, 1100);

}
    
