#include "globals.h"
#include "lemlib/api.hpp"
#include "main.h"
#include "pros/adi.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/motors.hpp"
#include "pros/screen.hpp"
#include "pidconst.h"




// drivetrain motors
pros::Motor flm(20, pros::E_MOTOR_GEARSET_06, true); 
pros::Motor blbm(19, pros::E_MOTOR_GEARSET_06, true); 
pros::Motor bltm(18, pros::E_MOTOR_GEARSET_06, false); 
pros::Motor frm(11, pros::E_MOTOR_GEARSET_06, false); 
pros::Motor brbm(12, pros::E_MOTOR_GEARSET_06, false); 
pros::Motor brtm(13, pros::E_MOTOR_GEARSET_06, true); 

// dt motors for constructor
pros::MotorGroup leftMotors({flm, blbm,bltm});
pros::MotorGroup rightMotors({frm, brbm, brtm});

// inertial sensor


// other motors
pros::Motor cataMotor(17, pros::E_MOTOR_GEARSET_36, false);
pros::Motor intakeMotor(14, pros::E_MOTOR_GEARSET_06, false);

//other sensors
pros::Imu inertial(8);
pros::Rotation rotation(2);
pros::ADIDigitalIn lim('D');

// dt struct
lemlib::Drivetrain drivetrain(&leftMotors, // left motor group
                              &rightMotors, // right motor group
                              10.3125, // 10 inch track width
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
pros::ADIDigitalOut wingleft('A');
pros::ADIDigitalOut wingright('B');
pros::ADIDigitalOut hangpiss('C');
pros::ADIDigitalOut blockerpiss('D');
pros::ADIDigitalOut liftpiss('E');

// controller
pros::Controller con1 (pros::E_CONTROLLER_MASTER);





// word variables for easier workflow
bool in = true;
bool out = false;
bool yes = true;
bool no = false;
bool left = true;
bool right = true;
int off = 0;
int idle = 15;
int intakeout = -600;
int intakein = 600;
bool fire = true;
bool stop = false;
bool up = true;
bool down = false;

// yeah idek
bool cata_override = false;
bool cataState = true;
int intakeState = off;
int catapos = rotation.get_angle() / 100;

// static assets
/*ASSET(safeRight1_txt);
ASSET(safeRight2_txt);
ASSET(safeLeft1_txt);
ASSET(safeLeft2_txt);
ASSET(rushLeft1_txt);
ASSET(rushLeft2_txt);*/


void cata(bool state){
  cata_override = state;
};





void lower() {
    
    if (!(rotation.get_angle() >= 3100)) {
        cataMotor = 127;
    } else {
        
    }

}


void wings(bool state) {
  if (state == left) {
    wingleft.set_value(state);
  }
  if (state == right) {
    wingright.set_value(state);
  }
  else{
    wingleft.set_value(state);
    wingright.set_value(state);
  }
 
    
}

void blocker(bool state) {

  blockerpiss.set_value(state);
    
}

void intake(int state) {
    intakeState = state;
}

void lift(bool state){
  liftpiss.set_value(state);
}


// task def 

void cataTask() {
  
  while (true) {
    
   
    int catapos = rotation.get_angle() / 100;

    if (!cata_override){
      if (abs(catapos >= 31)) {
        cataMotor = 0;
        cataState = true;
      }
    }

    if (cata_override){
      
      if (!abs(catapos >= 31) && (cataState == false)) {
        // move catapult down until its reached loading position
        cataMotor = 127;
        
      } else if (abs(catapos >= 31)){
        cata_override = true;
        cataMotor = 127;
  
        pros::delay(600);
        cata_override = false;
        cataState = false;
      }

    }

    

    pros::delay(10);
  }
}

void intakeTask(){

    while (true) {
       
      intakeMotor = intakeState;
      pros::delay(10);
    }
    
    
}

void screen(){
    while (true) {
        lemlib::Pose pose = chassis.getPose(); // get chassis position
        pros::lcd::print(0, "X: %f", pose.x);
        pros::lcd::print(1, "Y: %f", pose.y);
        pros::lcd::print(2, "Theta: %f", pose.theta);
        pros::delay(10);
    }
}
