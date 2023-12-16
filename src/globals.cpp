#include "lemlib/api.hpp"
#include "main.h"
#include "pros/adi.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/motors.hpp"
#include "pros/screen.hpp"
#include "pidconst.cpp"




// drivetrain motors
pros::Motor flm(1, pros::E_MOTOR_GEARSET_06, false); 
pros::Motor blbm(2, pros::E_MOTOR_GEARSET_06, false); 
pros::Motor bltm(3, pros::E_MOTOR_GEARSET_06, true); 
pros::Motor frm(4, pros::E_MOTOR_GEARSET_06, true); 
pros::Motor brbm(5, pros::E_MOTOR_GEARSET_06, true); 
pros::Motor brtm(6, pros::E_MOTOR_GEARSET_06, false); 

// dt motors for constructor
pros::MotorGroup leftMotors({flm, blbm,bltm});
pros::MotorGroup rightMotors({frm, brbm, brtm});

// inertial sensor


// other motors
pros::Motor cataMotor(20, pros::E_MOTOR_GEARSET_18, false);
pros::Motor intakeMotor(14, pros::E_MOTOR_GEARSET_06, true);

//other sensors
pros::Imu inertial(2); // port 2
pros::Rotation rotation(8);
pros::ADIDigitalIn lim('D');

// dt struct
lemlib::Drivetrain drivetrain(&leftMotors, // left motor group
                              &rightMotors, // right motor group
                              10, // 10 inch track width
                              lemlib::Omniwheel::NEW_275, // using new 3.25" omnis
                              450, // drivetrain rpm is 360
                              2 // chase power is 2. If we had traction wheels, it would have been 8
);

// odometry struct
lemlib::OdomSensors sensors(nullptr, // vertical tracking wheel 1, set to nullptr as we don't have one
                            nullptr, // vertical tracking wheel 2, set to nullptr as we don't have a second one
                            nullptr, // horizontal tracking wheel 1, set to nullptr as we don't have one
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &inertial // inertial sensor
);

// create the chassis
lemlib::Chassis chassis(drivetrain, linearController, angularController, sensors);

// pistons
pros::ADIDigitalOut wingspiss('A');
pros::ADIDigitalOut hangpiss('B');
pros::ADIDigitalOut blockerpiss('C');

// controller
pros::Controller con1 (pros::E_CONTROLLER_MASTER);





// word variables for easier workflow
bool in = true;
bool out = false;
bool yes = true;
bool no = false;
int off = 0;
int idle = 5;
int intakeout = -600;
int intakein = 600;


// yeah idek
bool cata_override = false;
bool cataState = true;
int intakeState = off;
int catapos = rotation.get_angle() / 100;

// static assets
ASSET(safeRight1_txt);


void fire() {

  cata_override = true;
  cataMotor = 127;
  
  pros::delay(500);
  cata_override = false;
  cataState = false;
 
}


void lower() {
    
    if (!(rotation.get_angle() >= 3100)) {
        cataMotor = 127;
    } else {
        
    }

}


void wings(bool state) {

  wingspiss.set_value(state);
    
}

void blocker(bool state) {

  blockerpiss.set_value(state);
    
}

void intake(int state) {
    intakeState = state;
}


// task def 

void cata_task_fn() {
  
  while (true) {
    
   
    int catapos = rotation.get_angle() / 100;

    if (!abs(catapos >= 31) && (cataState == false)) {
      // move catapult down until its reached loading position
      cataMotor = 127;
      

    } else if (!cata_override && abs(catapos >= 31) ) {
      cataMotor = 0;
      cataState = true;
    }
    

    

    pros::delay(10);
  }
}

void intakeTask(){

    while (true) {
        
        if (con1.get_digital(DIGITAL_L1)) {
            intake(intakein);
        }else if (con1.get_digital(DIGITAL_L2)) {
            intake(intakeout);
        }else if ((con1.get_digital(DIGITAL_L1)) && (con1.get_digital(DIGITAL_L2))){
            intake(off);
        }else{
            intake(idle);
        }

        intakeMotor = intakeState;
    }
    

}
