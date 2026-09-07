#include "common.h"

#define FIELD(ptr, type, off) (*(type *)((s8 *)(ptr) + (off)))

extern s32 D_800814A0[3];

void func_80024A30(void *arg0) {
    void *temp_v0;
    s16 temp_v1;
    u16 temp_a0;
    s32 value;

    temp_v0 = FIELD(arg0, void *, 4);
    temp_v1 = FIELD(arg0, s16, 0);
    temp_a0 = *(volatile u16 *)arg0;

    switch (temp_v1) {
    case 0:
        if (FIELD(temp_v0, u16, 0xC) & 2) {
            FIELD(arg0, u16, 0) = temp_a0 + 1;
        }
        break;

    case 1:
        value = FIELD(arg0, s32, 8) + 0xFFF7F7F8U;
        FIELD(arg0, s32, 8) = value;
        if (value <= 0x80808) {
            FIELD(arg0, u16, -2) |= 0x8000;
            D_800814A0[0] |= 0x8000;
        }
        break;
    }

    ASM_KEEP(arg0);
}
