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

void catapultSkills1(){
    //Step 0: Prepare catapult
    //Lower catapult until limit switch is pressed
    while(!catapultLimitSwitch.pressing()){
        catapultMotor.spin(forward,catapultVelocity,velocityUnits::pct);
    }
    wait(2,sec);
    catapultMotor.stop(brake);
    //Step 1: Spin first roller
    //1.1 Drive into roller
    driveFwd(1,inches);
    //1.2 Spin Roller
    rollerMotor.spinFor(forward, 4*87.75,rotationUnits::deg,80,velocityUnits::pct);

    //Step 2: Move to and spin second roller; Pick up disc.
    //2.1 Back up and turn right 90 degrees
    driveRev(12,inches);
    turnRight(3,rev);
    //2.2 Intake disc
    rollerMotor.spin(reverse,100,pct);
    //2.3 Drive into second roller
    driveFwd(36,inches);
    //2.4 Spin roller
    rollerMotor.spinFor(forward, 4*87.75,rotationUnits::deg,80,velocityUnits::pct);
    //Step 3: Move to and fire the catapult
    //3.1 back up and turn right 90 deg
    driveRev(2,inches);
    turnRight(3,rev);
    //3.2 drive towards high goal
    driveFwd(24*2+8,inches);
    //3.3 fire catapult
    while(catapultLimitSwitch.pressing()){
        catapultMotor.spin(forward,catapultVelocity,velocityUnits::pct);
    }
    wait(4,sec);
    //Step 4: Endgame
    //4.1 Move to position
    driveRev(3*24,inches);
    turnLeft(4.5,rev);

    //4.2 fire endgame
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