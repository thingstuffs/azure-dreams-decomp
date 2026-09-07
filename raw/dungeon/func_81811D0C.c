#include "common.h"

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

void func_80026D0C(void *arg0, s32 arg1) {
    s32 temp_a2;
    s32 temp_v0;
    s32 temp_v1;
    void *temp_a1;
    void *temp_v1_2;

    temp_v1 = ((arg1 % 72) % 9) * 0xB;
    FIELD(FIELD(FIELD(arg0, void *, 0xC), void *, 4), s16, 8) =
        (s16)(temp_v1 - 0x2B);
    temp_a2 = ((arg1 % 72) / 9) * 0x10;
    FIELD(FIELD(FIELD(arg0, void *, 0xC), void *, 4), s16, 0xA) =
        (s16)(temp_a2 + 0xF);
    temp_a1 = FIELD(arg0, void *, 0x10);
    temp_v0 = FIELD(FIELD(temp_a1, void *, 0), u8, 0xA);
    temp_a1 = FIELD(temp_a1, void *, 4);
    temp_v0 = (u32)temp_v0 >> 1;
    temp_v0 -= 0x29;
    FIELD(temp_a1, s16, 8) = (s16)(temp_v1 + temp_v0);
    temp_v1_2 = FIELD(arg0, void *, 0x10);
    FIELD(FIELD(temp_v1_2, void *, 4), s16, 0xA) =
        (s16)(temp_a2 + ((FIELD(FIELD(temp_v1_2, void *, 0), u8, 0xB) >> 1) + 0xF));
}
