#include "vex.h"
#include "autonFunctions.cpp"

/* Push Preloads:
 * Drives forward and backward to push preload discs into the low goal.
 * Scores two points
 * 100% success rate
 */
void pushPreloads(){
    driveRev(2,rotationUnits::rev,30,velocityUnits::pct);
    driveFwd(2,rotationUnits::rev,30,velocityUnits::pct);

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
/**
 * @brief Used to check whether the catapult is in the upper zone of its travel.
 * This zone is the highest point and a bit below to account for error.
 * 
 * @return true when the catapult is in this zone
 * @return false else
 */
/**
 * @brief Used to check whether the catapult is in the upper zone of its travel.
 * This zone is the highest point and a bit below to account for error.
 * 
 * @return true when the catapult is in this zone
 * @return false else
 */
bool acataZone1(){
  return catapultRotationSensor.angle(deg)>270;
  }
/**
 * @brief Used to check whether the catapult is in the hold zone of its travel
 * This zone is the point at which the catapult waits for firing.
 * 
 * @return true when the catapult is in this zone
 * @return false else
 */
bool acataZone2(){
  return catapultRotationSensor.angle(deg)<220;
}
bool acataZone3(){
  return catapultRotationSensor.angle(deg)<218.5;
}
/**
 * @brief PURPLE skills routine from volume 3 page 44.
 * 
 */
void catapultSkills1(){
    //Step 0: Prepare catapult
    //Lower catapult until limit switch is pressed
    driveTimeout(1000,msec);
    // while(!acataZone2()){
    //     catapultMotor.spin(forward,catapultVelocity*3/4,velocityUnits::pct);
    // }
    // wait(2,sec);
    // catapultMotor.stop(brake);
    //Step 1: Spin first roller
    //1.1 Drive into roller
    rightDrivetrain.spinFor(230,deg,20,velocityUnits::pct, false);
    wait(200,msec);
    //1.2 Spin Roller
    rollerMotor.spinFor(forward, 4*95,rotationUnits::deg,80,velocityUnits::pct);
    wait(600,msec);
    rightDrivetrain.stop(brake);
    driveTimeout(5,sec);
    //Step 2: Move to and spin second roller; Pick up disc.
    //2.1 Back up and turn right 90 degrees
    // driveRev(12,inches, 30, velocityUnits::pct, true);
    driveRev(6.5,inches);
    // driveRev(2,rotationUnits::rev);
    //driveRev(convertToInch(12,inches)/(3.25*3.141592*48/72),rotationUnits::rev,30,velocityUnits::pct, true);
    turnRight(1.8,rev);
    wait(200,msec);
    //2.2 Intake disc
    rollerMotor.spin(reverse,100,pct);
    wait(300,msec);
    // //2.3 Drive into second roller
    driveRev(-28,inches);
    // //2.4 Spin roller
    turnLeft(0.6,rev);
    wait(2,sec);
    rollerMotor.stop(coast);
    wait(200,msec);
    driveFwd(6,inches);
    wait(50,msec);
    leftDrivetrain.spinFor(230,deg,20,velocityUnits::pct, false);
    rollerMotor.spinFor(forward, 4*87.75,rotationUnits::deg,80,velocityUnits::pct);

    /*
    //Step 3: Move to and fire the catapult
    //3.1 back up and turn right 90 deg
    driveRev(2,inches);
    turnRight(3.1,rev);
    //3.2 drive towards high goal
    driveFwd(24*2+8,inches);
    //3.3 fire catapult
    while(!acataZone1()){
        catapultMotor.spin(forward,catapultVelocity,velocityUnits::pct);
    }
    wait(1,sec);
    //3.4 Reset catapult
    while(!acataZone2()){
        catapultMotor.spin(forward,catapultVelocity,velocityUnits::pct);
    }
    
    //Step 4: Pick up two discs and fire into the blue goal
    //Step 4.1:  Back up and turn 90 degrees right to be able to line up
    driveRev(6,inches);
    turnRight(3.1,rev);

    //Step 4.2 drive forward and turn right 45 degrees
    driveFwd(24,inches);
    turnRight(1.6,rev);

    //Step 4.3 Intake while driving forward
    intakeMotors.spin(fwd,100,pct);
    driveFwd(55,inches,20,velocityUnits::pct);

    //Step 4.4: Move to fire position:
    turnRight(1.6,rev);
    driveFwd(24,inches);
    turnLeft(3.1,rev);
    driveFwd(6,inches);

    //Step 4.5 Fire catapult
    while(!acataZone1()){
        catapultMotor.spin(forward,catapultVelocity,velocityUnits::pct);
    }
    wait(1,sec);
    //4.6 Reset catapult
    while(!acataZone2()){
        catapultMotor.spin(forward,catapultVelocity,velocityUnits::pct);
    }
    //Step 5: move and fire endgame

    */
}
const double rollerSpinSkills = 3.85*87.75;
void catapultSkills2(){
    //Step 1: Fire Catapult preloads
    //1.1: Preload catapult
    while(!catapultLimitSwitch.pressing()){
        catapultMotor.spin(forward,catapultVelocity,velocityUnits::pct);
    }
    wait(1,sec);
    //1.2 Fire catapult
    while(catapultLimitSwitch.pressing()){
        catapultMotor.spin(forward,catapultVelocity,velocityUnits::pct);
    }
    catapultMotor.stop(brake);
    wait(1,sec);
    //Step 2: Move to and score roller 1
    //Step 2.1 Back up 3 tiles 
    driveRev(8.2,rev);
    //Step 2.2 Turn right 90 degrees
    turnRight(1.19,rev);
    //Step 2.3 drive into roller
    driveTimeout(3,sec);
    driveFwd(1.31,rev);

    //Abridged Routine. 
    //Step 2.1 Drive 1 inch into roller
    Controller1.rumble("-.-.-");
    driveTimeout(1,sec);
    //driveFwd(1,inches);
    rollerMotor.setTimeout(2,sec);
    rightDrivetrain.spinFor(forward,1*360,rotationUnits::deg,30,velocityUnits::pct,true);
    //Step 2.4 turn roller
    rollerMotor.spinFor(forward, 4*87.75,rotationUnits::deg,80,velocityUnits::pct);
    wait(1,sec);
    //Step 3: Move to and score roller 2
    //Step 3.1 Back up 1 tile
    driveTimeout(4,sec);
    driveRev(4.21,rev);
    //Step 3.2 turn right 90 degrees
    turnRight(1.25,rev);
    //Step 3.3 drive one tile into roller
    driveTimeout(3,sec);
    driveFwd(3.2,rev);
    //Step 3.4 spin roller
    rollerMotor.spinFor(forward, 4*96,rotationUnits::deg,80,velocityUnits::pct);
    
    //Step 4: Turn and launch Endgame
    //Step 4.1 back up one tile
    turnRight(0.15,rev);
    //VERSION 1: LAUNCH ENDGAME::
    driveTimeout(4,sec);
    driveRev(4,rev);
    //Step 4.2 turn left 45 degrees
    turnLeft(0.7,rev);
    //Step 4.3 back up 0.5 tiles
    driveFwd(3,rev);
    turnLeft(2.5,rev);
    //Step 4.4 fire endgame
    for(int i = 0; i<4; i++){
        endgameL.set(true);
        endgameR.set(true);
        
        wait(1,sec);
        endgameL.set(false);
        endgameR.set(false);
        
        wait(1,sec);
    }
    

    // //VERSION 2: MORE ROLLERS

    // //Step 4:Drive through low goal
    // //Step 4.1 back up 2 inches
    // driveRev(0.55,rev);
    // //Step 4.2 turn right 90 degrees
    // turnRight(1.21,rev);
    // //Step 4.2 drive forward through low goal
    // driveTimeout(15,sec);
    // driveFwd(16,rev);
    // //Step 4.3 align on front of robot
    // driveTimeout(3,sec);
    // driveFwd(1,rev);
    // //STep 4.4 back up and turn right 90 degrees
    // //Step 4.5 back up and align on the other wall
    // //Step 4.6 drive forward to rollers
    // //Step 5: Drive to roller 3
    // //Step 6: Drive to roller 4
}
/**
 * @brief Shoots three discs into the high goal from the right side then scores the roller
 * 
 */
void rightGame1(){
    //Step 1: Lower catapult
    while(!acataZone2()){
        catapultMotor.spin(forward,catapultVelocity,velocityUnits::pct);
    }
    catapultMotor.stop(brake);
    //Step 2: Drive to auton line
    driveFwd(28/(3.25*3.141592*48/72), rotationUnits::rev, 35, velocityUnits::pct);
    wait(100,msec);
    //Step 3 Shoot Disc 1
    while(!acataZone1()){

        catapultMotor.spin(forward,catapultVelocity,velocityUnits::pct);
    }

    catapultMotor.stop(coast);
    //Step 4: Shoot Disc 2
    //4.1 Lower catapult
    while(!acataZone2()){
        catapultMotor.spin(forward,catapultVelocity,velocityUnits::pct);
    }
    catapultMotor.stop(brake);
    //4.2 Intake disc into catapult
    rollerMotor.spinFor(reverse,2,seconds,30,velocityUnits::pct);
    rollerMotor.stop(coast);
    //Backs up a bit to prevent jams
    rollerMotor.spinFor(forward,0.5,seconds,50,velocityUnits::pct);
    wait(300,msec);
    //4.3: Fire catapult
    while(!acataZone1()){
        catapultMotor.spin(forward,catapultVelocity,velocityUnits::pct);
    }
    catapultMotor.stop(brake);
    wait(100,msec);
   
    // // Step 6: Shoot Disc 3

    //Step 5: Get Roller
    //5.1 Drive back 6 inches
    driveRev(6,inches);
    //5.2 turn right 90 degrees
    turnRight(1.8,rev);
    //5.3 Drive forward 12 inches
    driveFwd(19,inches);
    //5.4 Turn right about 125 degrees
    turnRight(0.42,rev);
    //5.5 Drive forward 12 inches
    driveFwd(7,inches);
    //5.6 Score roller
    leftDrivetrain.spin(forward,80,velocityUnits::pct);
    wait(100,msec);
    rightDrivetrain.spinFor(230,deg,20,velocityUnits::pct, false);
    wait(100,msec);
    rollerMotor.spinFor(forward, 4*84,rotationUnits::deg,80,velocityUnits::pct);
    

}


/* Game Auton Routines
 * 0: Do Nothing
 * 1: Push preloads into low goal
 * 2: Spin Roller to US (Can be used in Skills
 * 4: Right game
 * 
 * Skills Auton Routines:
 * 3: Catapult skills 1: Purple! (Roller-roller-fire-fire 5)
 * 5: State Skills
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
    case 3:
        catapultSkills1();
        break;
    case 4:
        rightGame1();
        break;
    case 5:
        catapultSkills2();
        break;
    default:
        break;
    }
}