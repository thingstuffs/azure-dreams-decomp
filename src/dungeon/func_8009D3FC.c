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

/* Sets or reuses the requested value and calls func_800A2B28 when state permits. */
s16 func_800A2B5C(s32 requested_value) {
    u8 *state = D_80083460;
    s32 current_value = ((S_800A2B5C_0 *)state)->unk_0C;

    if (current_value == requested_value) {
        goto call;
    }
    if (current_value != 0) {
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
    ((S_800A2B5C_0 *)state)->unk_0C = requested_value;
call:
    return func_800A2B28();
}
