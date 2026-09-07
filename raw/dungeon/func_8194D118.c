#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 func_80024700();
extern u32 func_800644B8();
extern s32 D_800814A0;

void func_80024918(void *arg0) {
    s16 temp_v0;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_y;
    void *temp_v1;

    temp_v1 = FIELD(arg0, void *, 0);
    FIELD(temp_v1, u16, 0x1A) = FIELD(temp_v1, u16, 0x1A) + 1;
    FIELD(arg0, s16, 0x78) = func_800644B8(FIELD(arg0, s16, 0x74) << 8) >> 6;
    temp_a1 = FIELD(arg0, s32, 0x44);
    FIELD(arg0, s32, 0x34) += FIELD(arg0, s32, 0x40);
    temp_y = FIELD(arg0, s32, 0x38);
    temp_a2 = FIELD(arg0, s32, 0x48);
    FIELD(arg0, s32, 0x38) = temp_y + temp_a1;
    FIELD(arg0, s32, 0x3C) += temp_a2;
    func_80024700(arg0, temp_a1, temp_a2);
    temp_v0 = (s16)FIELD(arg0, s16, 0x74) + 1;
    FIELD(arg0, s16, 0x74) = temp_v0;
    if (temp_v0 >= 9) {
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
