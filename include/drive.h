#include "robot-config.h"

using namespace vex;

// Constants
enum Constants {
  REST = 10,                                    // The angle of the rest position
  TOWER_1 = 420,                                // The angle of the Level 1 towers
  TOWER_2 = 620,                                // The angle of the Level 2 towers
  STACK = 100                                   // The angle of the lift when stacking
};

// Global variables
int MASTER_POWER = 100;                         // The master power for all driving
int HAND_POWER = 90;                            // The power of the hands
float INCHES_PER_DEGREE = (4.0 * 3.14) / 360;   // The number of inches in 1 degree of the wheels
float TURNING_RATIO = 22.3 / 4.0;               // The ratio of the rotation of the robot to the rotation of a wheel
float INCHES_PER_TILE = 23.2;                   // The length of a tile in inches
int dew1X;                                      // Will hold the X value of the RIGHT analog stick
int dew1Y;                                      // Will hold the Y value of the RIGHT analog stick
int dew2X;                                      // Will hold the X value of the LEFT analog stick
int dew2Y;                                      // Will hold the Y value of the LEFT analog stick
int armsManual = false;                         // Will be true if the arms move up manually rather than automatically
int armLevel = REST;                            // Will hold the level of the arm


// Control scheme
int liftUp();
int liftDown();
int armsUp();
int armsDown();
int switchArms();
int handsIn();
int handsOut();
int stacking();

// Manual driving methods
void driveForward(int power);
void forwardRight(int power, int intensity);
void forwardLeft(int power, int intensity);
void driveBackward(int power);
void backwardRight(int power, int intensity);
void backwardLeft(int power, int intensity);
void stop();

// Autonomous driving methods
void driveTiles(int power, float tiles);
void driveBackwardTiles(int power, float tiles);
void turnRight(int power, float degrees);
void turnLeft(int power, float degrees);

// Arm methods
void moveLeftArmUp();
void moveRightArmUp();
void moveLeftArmDown();
void moveRightArmDown();
void moveArmsUp();
void moveArmsDown();
void keepArmsUp();
void moveAndKeepArmsUp();

// Hand methods
void moveHandsIn(int power);
void moveHandsOut(int power);
void stopHands();

// Other methods
void stopAll();
void stack();
void tower();