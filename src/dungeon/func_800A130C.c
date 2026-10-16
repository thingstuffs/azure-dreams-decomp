#include "common.h"
#include "m2c_compat.h"

void clearSelectedItemFlag400();                        /* extern */

/* Sends the two-byte command 1, 0x12. */
void clearItemFlag400ForEggOne(void) {
    s8 command[2];

    command[0] = 1;
    command[1] = 0x12;
    clearSelectedItemFlag400((s8 *)&command[0]);
}
