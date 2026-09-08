#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_800A092C;

typedef struct S_800A08F0_0 {
    u8 pad_00[0x50];
    M2C_UNK * unk_50;
    u8 pad_54[0x1A];
    u16 unk_6E;
} S_800A08F0_0;   /* arg0 in func_800A08F0 */

/* Increase the door opening angle and switch handlers when fully open. */
void func_800A08F0(S_800A08F0_0 *door) {
    u16 opening_angle;

    opening_angle = door->unk_6E + 0x40;
    door->unk_6E = opening_angle;
    if ((s16) opening_angle >= 0x400) {
        door->unk_6E = 0x400U;
        door->unk_50 = &D_800A092C;
    }
}
