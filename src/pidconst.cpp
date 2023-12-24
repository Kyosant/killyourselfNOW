#include "main.h"
#include "lemlib/api.hpp"



// forward/backward PID
lemlib::ControllerSettings linearController(100, // proportional gain (kP)
                                            0, //intergal gain (kI)
                                            30, // derivative gain (kD)
                                            0, //antiWindup
                                            1, // small error range, in inches
                                            100, // small error range timeout, in milliseconds
                                            3, // large error range, in inches
                                            500, // large error range timeout, in milliseconds
                                            20 // maximum acceleration (slew)
);



// turning PID
lemlib::ControllerSettings angularController(10, // proportional gain (kP)
                                             0, //intergal gain (kI)
                                             10, // derivative gain (kD)
                                             1, //antiWindup
                                             1, // small error range, in degrees
                                             100, // small error range timeout, in milliseconds
                                             3, // large error range, in degrees
                                             500, // large error range timeout, in milliseconds
                                             0 // maximum acceleration (slew). 0 means no limit
);