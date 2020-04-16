/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       DSTA                                                      */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Program for Tower Takeover                    */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LeftDrive            motor         11              
// RightDrive           motor         20              
// Lift1                motor         16               
// Lift2                motor         15              
// LeftArm              motor         1               
// RightArm             motor         10              
// LeftHand             motor         2               
// RightHand            motor         9              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

competition Competition;

void pre_auton(void) {
  // Initialize robot configuration
  vexcodeInit(); 

  // Reset encoders
  LeftDrive.resetRotation();
  RightDrive.resetRotation();
  LeftArm.resetRotation();
  RightArm.resetRotation();
  LeftHand.resetRotation();
  RightHand.resetRotation();
  Lift1.resetRotation();
  Lift2.resetRotation();
  Brain.Screen.drawImageFromFile("DSTA.png", 0, 0);
}

void autonomous(void) {
  auton();
}

void usercontrol(void) {

  // Main loop
  while (1) {

    // Read the values from the remote controller
    dew1X = Controller1.Axis1.position(); // This is the RIGHT analog stick.
    dew1Y = Controller1.Axis2.position(); // This is the RIGHT analog stick.
    dew2X = Controller1.Axis4.position(); // This is the LEFT analog stick.
    dew2Y = Controller1.Axis3.position(); // This is the LEFT analog stick.

    LeftDrive.spin(vex::directionType::fwd, (dew1Y + dew2X) / 2, vex::velocityUnits::pct);
    RightDrive.spin(vex::directionType::fwd, (dew1Y - dew2X) / 2, vex::velocityUnits::pct);


    // Lift Controls
    if (liftUp()) {
      Lift1.spin(vex::directionType::fwd, 20, vex::velocityUnits::pct);
      Lift2.spin(vex::directionType::fwd, 20, vex::velocityUnits::pct);
    } else if (liftDown()) {
      Lift1.spin(vex::directionType::rev, 20, vex::velocityUnits::pct);
      Lift2.spin(vex::directionType::rev, 20, vex::velocityUnits::pct);
    } else {
      Lift1.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
      Lift2.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
    }

    // Arm Controls
    if(armsManual) {
      if (armsUp()) {
        LeftArm.spin(directionType::fwd, 30, percentUnits::pct);
        RightArm.spin(directionType::fwd, 30, percentUnits::pct);
      } else if(armsDown()) {
        LeftArm.spin(directionType::fwd, -30, percentUnits::pct);
        RightArm.spin(directionType::fwd, -30, percentUnits::pct);
      } else {
        LeftArm.spin(directionType::fwd, 0, percentUnits::pct);
        RightArm.spin(directionType::fwd, 0, percentUnits::pct);
      }
    }
    else {
      if (armsUp()) vex::thread t(moveAndKeepArmsUp);
      else if (armsDown()) vex::thread t(moveArmsDown);
    }
    
    // Hand Controls
    if (handsIn()) moveHandsIn(HAND_POWER);
    else if (handsOut()) moveHandsOut(10);
    else stopHands();
  }

  // Stacking Controls
  if(stacking()) stack();

  // Check if arms should be manual
  if(switchArms()) armsManual = !armsManual;

  // Sleep the task for a short amount of time to prevent wasted resources.
  vex::task::sleep(20);
}

int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
