#include "API.h"
#include "RobotDrive.h"

static int leftFrontMotor, rightFrontMotor, leftRearMotor, rightRearMotor;

static int clip(int value) {
  if (value < -127) value = -127;
  if (value > 127) value = 127;
  return value;
}

void driveInit2(int leftMotor, int rightMotor) {
  driveInit4(leftMotor, 0, rightMotor, 0);
}

void driveInit4(int leftFront, int leftRear, int rightFront, int rightRear) {
  leftFrontMotor = leftFront;
  rightFrontMotor = rightFront;
  leftRearMotor = leftRear;
  rightRearMotor = rightRear;
}

void driveTank(int leftPower, int rightPower) {
  leftPower = clip(leftPower);
  rightPower = clip(rightPower);
  motorSet(leftFrontMotor, leftPower);
  if (leftRearMotor != 0) motorSet(leftRearMotor, leftPower);
  motorSet(rightFrontMotor, -rightPower);
  if (rightRearMotor != 0) motorSet(rightRearMotor, -rightPower);
}

void driveArcade(int power, int turn) {
  power = clip(power);
  turn = clip(turn);
  int leftSpeed = power + turn;
  int rightSpeed = power - turn;
  driveTank(leftSpeed, rightSpeed);
}

void driveStop() {
  driveTank(0, 0);
}
