#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_800E2970;

typedef struct S_80017560_0 {
    u8 pad_00[0xC];
    s16 unk_0C;
} S_80017560_0;   /* var_v0 in func_80017560 */

/* Clears the field at offset 0x0C in each of the 36 table entries. */
void func_80017560(void) {
    s8 *entry;
    s32 remaining;

    entry = &D_800E2970;
    remaining = 0x24;
    do {
        ((S_80017560_0 *)entry)->unk_0C = 0;
        remaining -= 1;
        entry += 0x14;
    } while (remaining > 0);
}
