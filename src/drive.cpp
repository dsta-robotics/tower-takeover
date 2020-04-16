#include "vex.h"

using namespace vex;

// Control scheme
int liftUp() { return Controller1.ButtonX.pressing(); }
int liftDown() { return Controller1.ButtonB.pressing(); }
int armsUp() { return Controller1.ButtonR1.pressing(); }
int armsDown() { return Controller1.ButtonR2.pressing(); }
int switchArms() { return Controller1.ButtonRight.pressing(); }
int handsIn() { return Controller1.ButtonL1.pressing(); }
int handsOut() { return Controller1.ButtonL2.pressing(); }
int stacking() { return Controller1.ButtonLeft.pressing(); }

// Manual driving methods
void driveForward(int power) {
  LeftDrive.spin(vex::directionType::fwd, power, vex::velocityUnits::pct);
  RightDrive.spin(vex::directionType::fwd, power, vex::velocityUnits::pct);
}
void forwardRight(int power, int intensity) {
  LeftDrive.spin(vex::directionType::fwd, power, vex::velocityUnits::pct);
  RightDrive.spin(vex::directionType::fwd, power - intensity, vex::velocityUnits::pct);
}
void forwardLeft(int power, int intensity) {
  LeftDrive.spin(vex::directionType::fwd, power - intensity, vex::velocityUnits::pct);
  RightDrive.spin(vex::directionType::fwd, power, vex::velocityUnits::pct);
}
void driveBackward(int power) {
  LeftDrive.spin(vex::directionType::rev, power, vex::velocityUnits::pct);
  RightDrive.spin(vex::directionType::rev, power, vex::velocityUnits::pct);
}
void backwardRight(int power, int intensity) {
  LeftDrive.spin(vex::directionType::rev, power, vex::velocityUnits::pct);
  RightDrive.spin(vex::directionType::rev, power - intensity, vex::velocityUnits::pct);
}
void backwardLeft(int power, int intensity) {
  LeftDrive.spin(vex::directionType::rev, power - intensity, vex::velocityUnits::pct);
  RightDrive.spin(vex::directionType::rev, power, vex::velocityUnits::pct);
}
void stop() {
  LeftDrive.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
  RightDrive.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
}

// Autonomous driving methods
void driveTiles(int power, float tiles) {
  int degrees = INCHES_PER_TILE * (tiles / INCHES_PER_DEGREE);
  LeftDrive.startRotateFor(degrees, vex::rotationUnits::deg, power, vex::velocityUnits::pct);
  RightDrive.rotateFor(degrees, vex::rotationUnits::deg, power, vex::velocityUnits::pct);
}
void turnRight(int power, float degrees) {
  float turningDegrees = TURNING_RATIO * degrees;
  LeftDrive.startRotateFor((turningDegrees / 2), vex::rotationUnits::deg, power, vex::velocityUnits::pct);
  RightDrive.rotateFor(-(turningDegrees / 2), vex::rotationUnits::deg, -power, vex::velocityUnits::pct);
}
void turnLeft(int power, float degrees) {
  float turningDegrees = TURNING_RATIO * degrees;
  LeftDrive.startRotateFor(-(turningDegrees / 2), vex::rotationUnits::deg, -power, vex::velocityUnits::pct);
  RightDrive.rotateFor((turningDegrees / 2), vex::rotationUnits::deg, power, vex::velocityUnits::pct);
}

// Arm methods
void moveLeftArmUp() {
  LeftArm.rotateTo(armLevel - 20, rotationUnits::deg, 50, velocityUnits::pct);
}
void moveRightArmUp() {
  RightArm.rotateTo(armLevel, rotationUnits::deg, 50, velocityUnits::pct);
}
void moveLeftArmDown() {
  LeftArm.rotateTo(armLevel, rotationUnits::deg, -50, velocityUnits::pct);
}
void moveRightArmDown() {
  RightArm.rotateTo(armLevel, rotationUnits::deg, -50, velocityUnits::pct);
}
void moveArmsUp() {
  switch(armLevel) {
    case REST: armLevel = TOWER_1; break;
    case TOWER_1: armLevel = TOWER_2; break;
  }
  vex::thread t(moveLeftArmUp);
  vex::thread u(moveRightArmUp);
}
void moveArmsDown() {
  switch(armLevel) {
    case TOWER_2: armLevel = TOWER_1; break;
    case TOWER_1: armLevel = REST; break;
  }
  vex::thread t(moveLeftArmDown);
  vex::thread s(moveRightArmDown);
}
void keepArmsUp() {
  LeftArm.spin(directionType::fwd, 1.6, percentUnits::pct);
  RightArm.spin(directionType::fwd, 1.6, percentUnits::pct);
}
void moveAndKeepArmsUp() {
  moveArmsUp();
  keepArmsUp();
}

// Hand methods
void moveHandsIn(int power) {
  LeftHand.spin(vex::directionType::fwd, power, vex::velocityUnits::pct);
  RightHand.spin(vex::directionType::fwd, power, vex::velocityUnits::pct);
}
void moveHandsOut(int power) {
  LeftHand.spin(vex::directionType::rev, power, vex::velocityUnits::pct);
  RightHand.spin(vex::directionType::rev, power, vex::velocityUnits::pct);
}
void stopHands() {
  LeftHand.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
  RightHand.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
}

// Other methods
void stopAll() {
  LeftDrive.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
  RightDrive.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
  LeftArm.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
  RightArm.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
  LeftHand.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
  RightHand.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
  Lift1.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
  Lift2.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
}
void stack() {
  Lift1.startRotateTo(STACK, rotationUnits::deg, 30, velocityUnits::pct);
  Lift2.startRotateTo(STACK, rotationUnits::deg, 30, velocityUnits::pct);
  moveHandsOut(10);
  driveBackward(8);
  vex::task::sleep(500);
  stopAll();
}
void tower() {
  LeftArm.spin(vex::directionType::fwd, 60, vex::velocityUnits::pct);
  RightArm.rotateTo(4000, rotationUnits::deg, 60, velocityUnits::pct);
  LeftArm.spin(vex::directionType::fwd, 0, vex::velocityUnits::pct);
  //driveTiles(40, 0.2);
  moveHandsOut(30);
  vex::task::sleep(500);
  stopHands();
  //driveTiles(40, -0.2);
  moveArmsDown();
}
