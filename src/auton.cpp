#include "vex.h"

using namespace vex;

void auton() {
  // Close side for blue
  if(Brain.ThreeWirePort.A) {
    Brain.Screen.print("Blue Close");
    moveHandsIn(HAND_POWER);
    driveTiles(80, 0.5);
    stopHands();
    turnRight(80, 90);
    moveHandsIn(HAND_POWER);
    driveTiles(80, 1);
    turnRight(60, 45);
    stopHands();
    driveTiles(30, 0.3);
    stack();
  }
  // Far side for blue
  else if(Brain.ThreeWirePort.B) {
    Brain.Screen.print("Blue Far");
    moveHandsIn(HAND_POWER);
    driveTiles(80, 1.2);
    stopHands();
    turnLeft(80, 160);
    driveTiles(80, 2);
    stack();
  }
  // Close side for red
  else if(Brain.ThreeWirePort.C) {
    Brain.Screen.print("Red Close");
    moveHandsIn(HAND_POWER);
    driveTiles(80, 0.5);
    stopHands();
    turnLeft(80, 90);
    moveHandsIn(HAND_POWER);
    driveTiles(80, 1);
    turnLeft(60, 45);
    stopHands();
    driveTiles(30, 0.3);
    stack();
  }
  // Far side for red
  else if(Brain.ThreeWirePort.D){
    Brain.Screen.print("Red Far");
    moveHandsIn(HAND_POWER);
    driveTiles(80, 1.2);
    stopHands();
    turnRight(80, 160);
    driveTiles(80, 2);
    stack();
  }
  // Skills
  else if(Brain.ThreeWirePort.E){
    Brain.Screen.print("Skills");
    Brain.Screen.print("Red Far");
    moveHandsIn(HAND_POWER);
    driveTiles(80, 1.2);
    stopHands();
    turnRight(80, 160);
    driveTiles(80, 2);
    stack();
    turnLeft(80, 180);
    moveHandsIn(HAND_POWER);
    driveTiles(80, 2.2);
    vex::task::sleep(200);
    stopHands();
    driveTiles(50, -0.2);
    turnRight(40, 15);
    tower();

  }
}