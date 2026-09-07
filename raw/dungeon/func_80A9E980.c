#include "common.h"

typedef struct {
    u8 pad[0x1A];
    u16 field_1A;
    u16 field_1C;
    u16 field_1E;
} Object;

extern s32 D_800814A0[3];

void func_80174180(u16 *arg0, s32 arg1, Object *arg2) {
    u16 angle;
    u16 height;

    angle = arg2->field_1A + 0x320;
    height = arg2->field_1E + 0x200;
    do { arg2->field_1E = height; } while (0);
    arg2->field_1C = height;
    arg2->field_1A = angle;
    if (height >= 0x2000) {
        arg0[-1] |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
