
/*
 * User autonomous code goes in the autonomous function
 */
#include "main.h"

/*
 * Put user autonomous code in this function.
 * This currently contains test code so you can verify it's operation. It
 * simply operates motor 10 for 1/2 second on and 1/2 second off for 20
 * seconds as a way of knowing that everything is working. Replace this test
 * code with your autonomous code.
 *
 * If you install a jumper in Digital Input 12, the autonomous code will not
 * run. This is for testing teleop without the need to wait for autonomous to
 * finish for each test.
 */
void autonomous() {
  while (1) {
    motorSet(10, 40);
    wait(500);
    motorSet(10, 0);
    wait(500);
  }
}
