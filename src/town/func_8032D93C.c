#include "common.h"
#include "m2c_compat.h"

void townApplyTargetGridRectangle();            /* extern */

/* Calls townApplyTargetGridRectangle with parameters 0x10 and 7. */
void townApplyRectanglePreset10x7(void) {
    townApplyTargetGridRectangle(0x10, 7);
}
