#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_800A07E8;

typedef struct S_800A0958_0 {
    u8 pad_00[0x50];
    M2C_UNK * unk_50;
    u8 pad_54[0x1A];
    u16 unk_6E;
} S_800A0958_0;   /* arg0 in func_800A0958 */

/* Decrease the door opening angle and switch handlers when closed. */
void func_800A0958(S_800A0958_0 *door) {
    u16 opening_angle;

    opening_angle = door->unk_6E - 0x40;
    door->unk_6E = opening_angle;
    if ((opening_angle << 0x10) <= 0) {
        door->unk_6E = 0U;
        door->unk_50 = &D_800A07E8;
    }
}
