#include "main.h"
#include "lemlib/api.hpp"




//move all ts bruh 😭😭😭------------------------------------------------

pros::Controller con1();

//drivetrain motors
pros::Motor flm(1, pros::E_MOTOR_GEARSET_06, false); 
pros::Motor blbm(2, pros::E_MOTOR_GEARSET_06, false); 
pros::Motor bltm(3, pros::E_MOTOR_GEARSET_06, true); 
pros::Motor frm(4, pros::E_MOTOR_GEARSET_06, true); 
pros::Motor brbm(5, pros::E_MOTOR_GEARSET_06, true); 
pros::Motor brtm(6, pros::E_MOTOR_GEARSET_06, false); 

pros::MotorGroup leftMotors({flm, blbm,bltm});
pros::MotorGroup rightMotors({frm, brbm, brtm});

// inertial sensor
pros::Imu inertial_sensor(2); // port 2


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
                            &inertial_sensor // inertial sensor
);

// forward/backward PID
lemlib::ControllerSettings linearController(10, // proportional gain (kP)
                                            30, // derivative gain (kD)
                                            1, // small error range, in inches
                                            100, // small error range timeout, in milliseconds
                                            3, // large error range, in inches
                                            500, // large error range timeout, in milliseconds
                                            20 // maximum acceleration (slew)
);

// turning PID
lemlib::ControllerSettings angularController(2, // proportional gain (kP)
                                             10, // derivative gain (kD)
                                             1, // small error range, in degrees
                                             100, // small error range timeout, in milliseconds
                                             3, // large error range, in degrees
                                             500, // large error range timeout, in milliseconds
                                             0 // maximum acceleration (slew). 0 means no limit
);

// create the chassis
lemlib::Chassis chassis(drivetrain, linearController, angularController, sensors);
////////////////////////////////////////////////////////////////////////////


/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	chassis.calibrate();
	
	// print odom values to the brain
    pros::Task screenTask([&]() {
        while (true) {
            lemlib::Pose pose = chassis.getPose(); // get chassis position
            pros::lcd::print(0, "X: %f", pose.x);
            pros::lcd::print(1, "Y: %f", pose.y);
            pros::lcd::print(2, "Theta: %f", pose.theta);
            pros::delay(10);
        }
    });
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */


void opcontrol() {
    // loop forever
    while (true) {
        // get left y and right x positions
        int leftY = con1().get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = con1().get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

        // move the robot. T value is X value
        chassis.curvature(leftY, rightX, 12.4);

        // delay to save resources
        pros::delay(10);
    }
}
