#include "common.h"

typedef struct {
    s32 value;
    s32 pad[2];
} GlobalFlags;

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern GlobalFlags D_800814A0;

void func_80170DC4(void *arg0, s32 arg1, void *arg2) {
    s32 temp_lo;
    u16 temp_v1;

    temp_v1 = FIELD(arg0, u16, 0x96) - 1;
    temp_lo = (s32) ((s32) (temp_v1 << 16) >> 9) / FIELD(arg0, s16, 0x9E);
    FIELD(arg0, u16, 0x96) = temp_v1;
    FIELD(arg2, s8, 0xC) = (s8) temp_lo;
    FIELD(arg2, s8, 0xE) = (s8) temp_lo;
    FIELD(arg2, s8, 0xD) = (s8) temp_lo;
    if ((s16) FIELD(arg0, u16, 0x96) <= 0) {
        FIELD(arg0, u16, -2) = FIELD(arg0, u16, -2) | 0x8000;
        D_800814A0.value = D_800814A0.value | 0x8000;
    }
}
