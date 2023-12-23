#pragma once

#include "main.h"
#include "pros/adi.hpp"
#include "pros/motors.hpp"
#include "lemlib/api.hpp"




extern pros::Motor cataMotor;
extern bool cata_override;
extern bool cataState;
extern int intakeState;
extern bool in;
extern bool out;
extern bool yes;
extern bool no;
extern int off;
extern int idle;
extern int intakeout;
extern int intakein;
extern bool fire;
extern bool stop;
extern pros::Motor intakeMotor;
extern pros::Rotation rotation;
extern pros::ADIDigitalOut hangpiss;
extern pros::ADIDigitalOut wingspiss;
extern pros::ADIDigitalOut blockerpiss;
extern pros::Controller con1;
extern lemlib::Chassis chassis;
extern lemlib::Drivetrain drivetrain;
extern lemlib::OdomSensors sensors;


ASSET(safeRight1_txt);
ASSET(safeRight2_txt);
ASSET(safeLeft1_txt);
ASSET(safeLeft2_txt);
ASSET(rushLeft1_txt);
ASSET(rushLeft2_txt);




extern void cataTask();
extern void intakeTask();
extern void lower();
extern void wings(bool state);
extern void blocker(bool state);
extern void lift(bool state);
extern void intake(bool state);
extern void cata(bool state);
extern pros::Controller con1;
extern void screen();
extern void intake(int state);