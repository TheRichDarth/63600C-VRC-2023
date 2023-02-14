//Configuration Variables:
#include "vex.h"
#include "iostream"

bool displayImages = true;
const int imageCount = 10; //Number of elements in names[] 
const std::string names[imageCount] = {"Cjuly.png", "WAY.png", "hal.png", "PIKA.png", "wheel.png", "corespace.png", "drow.png", "spaghetti.png", "cartridge.png"};


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