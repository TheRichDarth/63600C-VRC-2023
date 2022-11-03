//Configuration Variables:
#include "vex.h"
#include "iostream"

bool displayImages = false;
const int imageCount = 10; //Number of elements in names[] 
const std::string names[imageCount] = {"Cjuly.png", "WAY.png", "hal.png", "PIKA.png", "wheel.png", "corespace.png", "drow.png", "spaghetti.png", "cartridge.png"};
bool autoRollerSpinning = true;

bool enableSlowDrive = true;
bool enableFwdRevSlowDrive = false;
bool enableLeftRightSlowDrive = true;
bool enableTurnSlowDrive = true;
bool enableXDriveBrainPrinting = true;

//enableFlywheelSpeedControl controls the flywheel speed on the up and down buttons of Controller1
//Cannot be enabled alongside enableFwdRevSlowDrive
bool enableFlywheelSpeedControl = true; 
// flywheelSpeed is the initial speed of the flywheel
int flywheelSpeed = 99;
// flywheelSpeedStep is the number of steps the flywheelSpeed is adjusted by each time the button is pressed
int flywheelSpeedStep = 5;

//readyPressDelay is the number of drive while() cycles between accepting single-press actions like launching a disc or pressing the brain screen.
int readyPressDelay = 2;
//indexTime is the number of drive while() cycles between contracting and extending the index pneumatic
int indexTime = 7;




bool enableFlywheel = false;
int readyPress = 0;
int flywheelDelay = 0;