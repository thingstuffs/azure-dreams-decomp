#include "common.h"

typedef struct Position {
    s16 pad0;
    s16 x;
    s16 pad4;
    s16 y;
} Position;

extern void func_80053DA8(s32);
extern Position D_80083780;
extern u8 D_800C1EA4[];

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

void func_800C1F8C(void *arg0)
{
    register s32 temp_a0 ASM_REG("$4");
    register s32 temp_v0 ASM_REG("$2");
    register s32 temp_v1 ASM_REG("$3");

    temp_v0 = FIELD(arg0, s16, 4);
    temp_v1 = D_80083780.x;
    temp_a0 = D_80083780.y;
    temp_v0 -= temp_v1;
    if (temp_v0 < 0) {
        temp_v0 = -temp_v0;
    }
    temp_v0 <<= 16;

    temp_v1 = FIELD(arg0, s16, 6) - temp_a0;
    temp_a0 = temp_v1;
    if (temp_v1 < 0) {
        temp_a0 = -temp_a0;
    }

    if (FIELD(arg0, s16, 0xC) < (temp_v0 >> 16)) {
        goto trigger;
    }
    temp_v0 = (s16)temp_a0;
    if (FIELD(arg0, s16, 0xE) >= temp_v0) {
        return;
    }

trigger:
    func_80053DA8(FIELD(arg0, u16, 0x10) | 0x1000);
    FIELD(arg0, void *, 0) = D_800C1EA4;
}
