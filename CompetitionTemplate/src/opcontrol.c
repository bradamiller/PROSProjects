
#include "Main.h"

/*
 * Put user teleop code in this function.
 * This currently contains test code so you can verify it's operation. It
 * simply operates motor 1 for 1/2 second on and 1/2 second off for 120
 * seconds as a way of knowing that everything is working. Replace this test
 * code with your teleop code.
 */
void teleop() {
  while (1) {
    motorSet(1, 40);
    wait(500);
    motorSet(1, 0);
    wait(500);
  }
}
