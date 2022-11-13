using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern motor frontLeftMotor;
extern motor backLeftMotor;
extern motor backRightMotor;
extern motor frontRightMotor;
extern controller Controller1;
extern motor_group flywheelMotors;
extern digital_out indexPneumatic;
extern digital_out endgame;
extern optical bottomOptical;
extern optical topOptical;
extern motor rollerMotor;
extern motor_group intakeMotors;
extern signature visionAim__SIG_1;
extern signature visionAim__SIG_2;
extern signature visionAim__SIG_3;
extern signature visionAim__SIG_4;
extern signature visionAim__SIG_5;
extern signature visionAim__SIG_6;
extern signature visionAim__SIG_7;
extern vision visionAim;
extern controller Controller2;
extern pot redSwitch;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );