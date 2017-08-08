/*
 * Field Management Software
 * Manages the autonomous and teleop parts of the game using "gentlemans"
 * start - that is everyone connects their joystick to the robot and waits
 * for the announcers "1...2...3...go", then you press any button and
 * the autonomous and teleop sequence begins.
 * 1. Wait for any digital joystick button to be pressed before starting
 *    automonous period.
 * 2. Start the autonnomous() function as a task and wait for "autoTime"
 *    seconds. Then delete the autonomous task and stop the motors.
 * 3. Start the teleop() function as a task and wait for "teleopTime"
 *    seconds. Then delete the teleop task and stop the motors.
 *
 * User code (the robot program) goes in the autonomous() function in the
 * auto.c file and in the teleop() function in the opcontrol.c file. Do not
 * put any user code in this file.
 *
 * Any code added to the initialize() method in init.c will run before either
 * autonomous or teleop begins. If you must restart the robot in the middle of
 * a match for any reason, keep in mind that the autonomous() code will run
 * first even if the autonomous period has ended.
 */
#include "main.h"

const long autoTime = 20;
const long teleopTime = 120;

void teleoptask(void *parameter) {
	teleop();
	delay(teleopTime * 1000L);
}

void autotask(void *parameter) {
	autonomous();
	delay(autoTime * 1000L);
}

/*
 * This is the actual PROS operatorControl functions which will be started when
 * the robot connects to the joystick controller. It in turn will wait for the
 * joystick button to be pressed, then run the "autonomous()" user function
 * followed by the "teleop()" user functions.
 *
 * Do not put user code here!
 */
void operatorControl() {
	// wait for a button press before starting the match so that radios have time
	// to sync
	for (int buttonPressed = false; !buttonPressed; ) {
		for (int group = 5; group <= 8; group++) {
			buttonPressed |= joystickGetDigital(1, group, JOY_UP);
			buttonPressed |= joystickGetDigital(1, group, JOY_DOWN);
		}
		for (int group = 7; group <= 8; group++) {
			buttonPressed |= joystickGetDigital(1, group, JOY_LEFT);
			buttonPressed |= joystickGetDigital(1, group, JOY_RIGHT);
		}
	}

	// run the autonomous task if the jumper is not installed in digital port 1.
	// if the jumper is installed, it is assumed that you want to skip the
	// autonomous code for testinging the teleop code only.
	if (digitalRead(12)) {
		TaskHandle autoHandle = taskCreate(autotask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
		delay(autoTime * 1000L);
		taskDelete(autoHandle);
		motorStopAll();
	}

	// run the teleop task always (no pin for disabling it)
	TaskHandle teleopHandle = taskCreate(teleoptask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
	delay(teleopTime * 1000L);
	taskDelete(teleopHandle);
	motorStopAll();
}
