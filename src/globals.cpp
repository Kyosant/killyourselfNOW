#include "globals.h"
#include "lemlib/api.hpp"
#include "main.h"
#include "pros/adi.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/motors.hpp"
#include "pros/screen.hpp"




// other motors
pros::Motor cataMotor(17, pros::E_MOTOR_GEARSET_36, false);
pros::Motor intakeMotor(14, pros::E_MOTOR_GEARSET_06, false);

//other sensors
pros::Imu inertial(8);
pros::Rotation rotation(2);
pros::ADIDigitalIn lim('D');

// controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// drive motors
pros::Motor flm(-20, pros::E_MOTOR_GEARSET_06); 
pros::Motor blbm(-19, pros::E_MOTOR_GEARSET_06); 
pros::Motor bltm(18, pros::E_MOTOR_GEARSET_06); 
pros::Motor frm(11, pros::E_MOTOR_GEARSET_06); 
pros::Motor brbm(12, pros::E_MOTOR_GEARSET_06); 
pros::Motor brtm(-13, pros::E_MOTOR_GEARSET_06); 

// motor groups
pros::MotorGroup leftMotors({flm, blbm, bltm}); // left motor group
pros::MotorGroup rightMotors({frm, brbm, brtm}); // right motor group

// Inertial Sensor on port 8
pros::Imu imu(8);


// drivetrain settings
lemlib::Drivetrain drivetrain(&leftMotors, // left motor group
                              &rightMotors, // right motor group
                              10.3125, // 10 inch track width
                              lemlib::Omniwheel::NEW_275, // using new 3.25" omnis
                              450, // drivetrain rpm is 360
                              2 // chase power is 2. If we had traction wheels, it would have been 8
);

// lateral motion controller
lemlib::ControllerSettings linearController(250, // proportional gain (kP)
                                            0, // integral gain (kI)
                                            5, // derivative gain (kD)
                                            3, // anti windup
                                            1, // small error range, in inches
                                            100, // small error range timeout, in milliseconds
                                            3, // large error range, in inches
                                            500, // large error range timeout, in milliseconds
                                            30 // maximum acceleration (slew)
);

// angular motion controller
lemlib::ControllerSettings angularController(3, // proportional gain (kP)
                                             0, // integral gain (kI)
                                             10, // derivative gain (kD)
                                             3, // anti windup
                                             1, // small error range, in degrees
                                             100, // small error range timeout, in milliseconds
                                             3, // large error range, in degrees
                                             500, // large error range timeout, in milliseconds
                                             0 // maximum acceleration (slew)
);

// sensors for odometry
// note that in this example we use internal motor encoders (IMEs), so we don't pass vertical tracking wheels
lemlib::OdomSensors sensors(nullptr, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            nullptr, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
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
