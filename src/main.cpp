#include "main.h"
#include "lemlib/api.hpp"
#include "autons.hpp"
#include "globals.h"



/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {

    //set catapult task
    pros::Task cata_task(cataTask);
    cataState = true;

    //set intake task
    pros::Task intake_task(intakeTask);
    intakeState = off;

    //calibrate lem chassis
	chassis.calibrate();
    chassis.setPose(0, 0, 0); // X: 0, Y: 0, Heading: 0

	// print odom values to the brain
    pros::lcd::initialize();
    pros::Task screen_task(screen);
    
    
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
void autonomous() {
    
    tuning2();
}

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
    // This is preference to what you like to drive on.
    
    // loop forever
    while (true) {

        // get left y and right x positions
        int leftY = con1.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = con1.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

        // move the robot. T value is X value
        chassis.arcade(leftY, rightX, 0.7);
        
        // intake shi
        if (con1.get_digital(DIGITAL_L1)) {
            intake(intakein);
        }else if (con1.get_digital(DIGITAL_L2)) {
            intake(intakeout);
        }else{
            intake(idle);
        }

        if (con1.get_digital(DIGITAL_R1)) {
            cata(fire);
        }

        if (con1.get_digital(DIGITAL_R2)) {
            wings(out);
        }else {
            wings(in);
        }

        if (con1.get_digital(DIGITAL_X)) {
            lift(up);
        }else if (con1.get_digital(DIGITAL_B)) {
            lift(down);
        }


        // delay to save resources
        pros::delay(10);


    }
}
