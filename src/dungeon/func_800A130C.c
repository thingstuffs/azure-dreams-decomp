#include "common.h"
#include "m2c_compat.h"

void func_800A90E8();                        /* extern */

/* Sends the two-byte command 1, 0x12. */
void func_800A6A6C(void) {
    s8 command[2];

    command[0] = 1;
    command[1] = 0x12;
    func_800A90E8((s8 *)&command[0]);
}
