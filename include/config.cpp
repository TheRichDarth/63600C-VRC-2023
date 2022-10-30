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
int readyPressDelay = 10;
//indexTime is the number of drive while() cycles between contracting and extending the index pneumatic
int indexTime = 10;



/* Game Auton Routines
 * 0: Do Nothing
 * 1: Push preloads into low goal
 * 2: Spin Roller to RED (Can be used in Skills)
 *      -Starts on Left Side
 * 3: Spin Roller to BLUE
 *      -Starts on Right Side
 * 
 * Skills Routines:
 * 4: Spin Roller, Shoot preloads into low goal and spins another roller (To RED for Skills)
 * 
 */

int autonSelect = 1;
const int numAutonRoutines = 12;
const std::string autonRoutineNames[numAutonRoutines] = {
    "0. Do Nothing",
    "1. PushPreload",
    "2. RED-Spin Roller",
    "3. BLUE-Spin Roller",

    "4. Skills-33",
    "5. Xyz",
    "6. Xyz",
    "7. Xyz",

    "8. Xyz",
    "9. Xyz",
    "10. Xyz",
    "11. Xyz"
};
const std::string autonRoutineDescriptions[numAutonRoutines] = {
    "0 points. Does nothing. Still nothing. Doesn't move; doesn't score. Just sits there. You can do better than this. Make a better choice.",
    "2 points. Pushes preloads into the low goal. Drives forward and then backward about 2 feet.",
    "10 points. Drives backward slightly and automatically spins roller for RED for the remainder of the auton period. It sometimes needs a second but it gets there in the end. Usually.",
    "10 points. Drives backward slightly and automatically spins roller for BLUE for the remainder of the auton period. It sometimes needs a second but it gets there in the end. Usually.",
    
    "33 points. (Sometimes) Scores the first roller, shoots preloads into the opposite side's high goal and then spins another roller. Has only scored 23 points in a competition.",
    "n points",
    "n points",
    "n points",
    
    "n points",
    "n points",
    "n points",
    "n points"
};
const color routineColors[numAutonRoutines] = {
    color(230),
    color(69,232,80),
    color(232,80,69),
    color(80, 69, 232),

    color(161,69,232),
    color(232,69,221),
    color(232,69,140),
    color(80,69,232),

    color(252,244,52),
    color(255,255,255),
    color(156,89,209),
    color(44,44,44) 
};

int autonSelectScreen = 0;
int autonSelectBank = 0;
int maxAutonBank = 3;
bool finalAutonSelection = false;

bool enableFlywheel = false;
int readyPress = 0;
int flywheelDelay = 0;