#include "common.h"

typedef struct S_800A2B5C_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
} S_800A2B5C_0;   /* state in func_800A2B5C */



extern u16 func_800A2B28();
extern u8 D_80083460[0x14];

s16 func_800A2B5C(s32 arg0) {
    u8 *state = D_80083460;
    s32 current = ((S_800A2B5C_0 *)state)->unk_0C;

    if (current == arg0) {
        goto call;
    }
    if (current != 0) {
        return 1;
    }
    if (((S_800A2B5C_0 *)state)->unk_10 != 0) {
        return 1;
    }
    if (((S_800A2B5C_0 *)state)->unk_0A != 0) {
        return 1;
    }
    if (((S_800A2B5C_0 *)state)->unk_02 & 8) {
        return 1;
    }
    ((S_800A2B5C_0 *)state)->unk_0C = arg0;
call:
    return func_800A2B28();
}
