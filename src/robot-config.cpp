#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen 
brain  Brain;

// VEXcode device constructors

//Deprecated motor declarations from first robot
motor frontLeftMotor = motor(PORT17, ratio18_1, false);
motor backLeftMotor = motor(PORT16, ratio18_1, false);
motor backRightMotor = motor(PORT19, ratio18_1, true);
motor frontRightMotor = motor(PORT18, ratio18_1, true);

//Main driver controller
controller Controller1 = controller(primary);

//Deprecated motor declarations from first robot
motor flywheelMotorsMotorA = motor(PORT20, ratio6_1, true);
motor flywheelMotorsMotorB = motor(PORT15, ratio6_1, false);
motor_group flywheelMotors = motor_group(flywheelMotorsMotorA, flywheelMotorsMotorB);

//Deprecated pneumatic declarations from first robot
digital_out indexPneumatic = digital_out(Brain.ThreeWirePort.H);
//Deprecated optical sensor declarations for automatic roller spinning
optical bottomOptical = optical(PORT2);
optical topOptical = optical(PORT1);
motor rollerMotor = motor(PORT5, ratio18_1, true);
motor intakeMotorsMotorA = motor(PORT10, ratio6_1, true);
motor intakeMotorsMotorB = motor(PORT13, ratio6_1, false);
motor_group intakeMotors = motor_group(intakeMotorsMotorA, intakeMotorsMotorB);
controller Controller2 = controller(controllerType::partner);
pot redSwitch = pot(Brain.ThreeWirePort.C);
distance leftDistance = distance(PORT3);

//digital_out endgameCylinder = digital_out(Brain.ThreeWirePort.B);
digital_out endgame = digital_out(Brain.ThreeWirePort.B);

//Tank Drive motor declarations
motor leftDrivetrainA = motor(PORT10,ratio6_1,true);
motor leftDrivetrainB = motor(PORT9,ratio6_1,true);
motor leftDrivetrainC = motor(PORT8,ratio6_1, false);
motor_group leftDrivetrain = motor_group(leftDrivetrainA,leftDrivetrainB,leftDrivetrainC);

motor rightDrivetrainA = motor(PORT1,ratio6_1,false);
motor rightDrivetrainB = motor(PORT3,ratio6_1,false);
motor rightDrivetrainC = motor(PORT2,ratio6_1, true);
motor_group rightDrivetrain = motor_group(rightDrivetrainA,rightDrivetrainB,rightDrivetrainC);

motor catapultMotor = motor(PORT4,ratio36_1,false);
triport TWexpander = triport(PORT6);
limit catapultLimitSwitch = limit(/*TWexpander.G*/Brain.ThreeWirePort.A);




/*vex-vision-config:begin*/
//vision visionAim = vision (PORT14, 50);
/*vex-vision-config:end*/



// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}