using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor LeftDrive;
extern motor RightDrive;
extern motor Lift1;
extern motor LeftArm;
extern motor RightArm;
extern motor LeftHand;
extern motor RightHand;
extern motor Lift2;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );