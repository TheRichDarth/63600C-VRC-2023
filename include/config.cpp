//Configuration Variables:
#include "vex.h"
#include "iostream"

bool displayImages = true;
const int imageCount = 10; //Number of elements in names[] 
const std::string names[imageCount] = {"Cjuly.png", "WAY.png", "hal.png", "PIKA.png", "wheel.png", "corespace.png", "drow.png", "spaghetti.png", "cartridge.png"};
bool autoRollerSpinning = true;

bool enableSlowDrive = true;
bool enableFwdRevSlowDrive = true;
bool enableLeftRightSlowDrive = true;
bool enableTurnSlowDrive = true;
bool enableXDriveBrainPrinting = false;

//enableFlywheelSpeedControl controls the flywheel speed on the up and down buttons of Controller1

bool enableFlywheelSpeedControl = true; 
// flywheelSpeed is the initial speed of the flywheel
double flywheelSpeed = 12;
// flywheelSpeedStep is the number of steps the flywheelSpeed is adjusted by each time the button is pressed
double flywheelSpeedStep = 0.5;

double flywheelMinSpeed = 9.0;

//readyPressDelay is the number of drive while() cycles between accepting single-press actions like launching a disc or pressing the brain screen.
int readyPressDelay = 20;
/**
 * @brief indexTime is the number of drive while() cycles between contracting and extending the index pneumatic
 */
int indexTime = 10;
int indexTimeBetweenDiscs = 40;




bool enableFlywheel = false;
int readyPress = 0;
int flywheelDelay = 0;
bool Controller2PressedLast = false;
bool Controller1PressedLast = false;
bool driverStarted = false;



//Catapult Configuration
/**
 * @brief What state the catapult is in during driver.
 *  ---------- 
 * 0: Catapult raised post-fire. Catapult is initialized this way.
 * 1: Lowering catapult into intake-position. Lowering is stopped when limit switch is pressed
 * 2: Catapult is in ready-to-fire position and awaiting the fire button.
 * 3: Catapult is in the process of moving downward to fire
 * 
 */
int catapultDriverState = 0;

bool catapultAutoLowering = false;

timer catapultTimer;
int catapultVelocity = 50; // PCT
const int catapultLowerMaxTime =7000;
const int catapultFireMaxTime = 2000;