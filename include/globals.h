#pragma once
#include "main.h"
#include "pros/adi.hpp"
#include "pros/motors.hpp"



extern pros::Motor cata;
extern bool cata_override;
extern bool state;
extern bool in;
extern bool out;
extern bool yes;
extern bool no;
extern int off;
extern int idle;
extern int intakeout;
extern int intakein;
extern pros::Motor intakeMotor;
extern pros::Rotation rotation;
extern pros::ADIDigitalOut hangpiss;
extern pros::ADIDigitalOut wingspiss;
extern pros::ADIDigitalOut blockerpiss;
extern pros::Controller con1;





extern void cata_task_fn();
extern void intakeTask();
extern void fire();
extern void lower();
extern void wings(bool state);
extern void blocker(bool state);
extern void lift(bool state);
extern void intake(bool state);
extern pros::Controller con1;
extern void screen();