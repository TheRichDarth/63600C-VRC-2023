#include "vex.h"
#include "autonFunctions.cpp"

/* Push Preloads:
 * Drives forward and backward to push preload discs into the low goal.
 * Scores two points
 * 100% success rate
 */
void pushPreloads(){
    driveFwd(2,rotationUnits::rev,30,velocityUnits::pct);
    driveRev(2,rotationUnits::rev,30,velocityUnits::pct);
}
/* rollerSpinAuton:
 * Drives forward slightly into the roller on the left side and spins the roller.
 */
void roller2(bool onRedSide = true){
    // driveFwd(1,rotationUnits::rev,30,velocityUnits::pct, true);
    rightDrivetrain.setTimeout(10,sec);
    rightDrivetrain.spinFor(300,rotationUnits::deg,100,velocityUnits::pct, false);
    wait(1,sec);
    //90 degrees times 3.25/
    rollerMotor.spinFor(forward, 2*87.75,rotationUnits::deg,80,velocityUnits::pct);
}




/* Game Auton Routines
 * 0: Do Nothing
 * 1: Push preloads into low goal
 * 2: Spin Roller to US (Can be used in Skills
 */
void runAuton(int autonSelect){
    switch (autonSelect){
    case 0:
        break;
    case 1:
        pushPreloads();
        break;
    case 2:
        roller2();
        break;
    default:
        break;
    }
}