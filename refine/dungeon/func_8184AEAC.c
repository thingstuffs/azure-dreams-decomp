#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003DB94();  /* extern */
M2C_UNK func_800478B8();                      /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
extern M2C_UNK D_800DEB28;

typedef struct S_800246AC_0 {
    u16 unk_00;
    u16 unk_02;
    u8 pad_04[0x4];
    s16 unk_08;
} S_800246AC_0;   /* arg0 in func_800246AC */

typedef struct S_800246AC_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_800246AC_1;   /* arg2 in func_800246AC */

typedef struct S_800246AC_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_800246AC_2;   /* arg1 in func_800246AC */

/* Advance the orbit angle and update the position when the object flags allow it. */
void func_800246AC(S_800246AC_0 *orbit, S_800246AC_2 *position, S_800246AC_1 *object) {
    s16 angle;
    s32 next_angle;
    s32 wrap_angle;

    angle = orbit->unk_08;
    next_angle = angle + 0x40;
    wrap_angle = next_angle;
    if (next_angle < 0) {
        wrap_angle = angle + 0x103F;
    }
    orbit->unk_08 = (s16) (next_angle - ((wrap_angle >> 0xC) << 0xC));
    func_800478B8(object);
    if (object->unk_14 & 0x6000) {
        func_8003DB94(object, &D_800DEB28, 0);
        position->unk_02 = (s16) (orbit->unk_00 + ((s32) ((func_800644B8(orbit->unk_08) >> 4) * 0x1C) >> 8));
        position->unk_06 = (s16) (orbit->unk_02 + ((s32) ((func_80064584(orbit->unk_08) >> 4) * 0x1C) >> 8));
    }
}
