#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern s32 func_80053DA8();
extern s32 func_800DC650();
extern u8 D_800E2924[];

void func_800DC724(void *arg0, s32 arg1)
{
    s32 temp_v0_2;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 var_v0;
    s32 var_v0_2;
    s32 temp_a2;
    s32 index;
    s32 target_x;
    u8 *table;
    void *holder;
    void *temp_a0;
    void *temp_v0;

    table = D_800E2924;
    index = FIELD(arg0, s32, 0x50);
    holder = FIELD(arg0, void *, 0x3C);
    temp_v0 = (index * 4) + table;
    target_x = FIELD(temp_v0, u16, 0);
    do { temp_a2 = FIELD(temp_v0, u16, 2); } while (0);
    do { temp_a0 = FIELD(holder, void *, 4); } while (0);
    FIELD(arg0, s32, 0x58) = 0;
    temp_v1 = (s16)target_x - FIELD(temp_a0, s16, 8);
    if (temp_v1 != 0) {
        do { FIELD(arg0, s32, 0x58) = 1; } while (0);
        arg1 = FIELD(temp_a0, s16, 8);
        var_v0 = temp_v1 + 3;
        if (temp_v1 <= 0) {
            var_v0 = temp_v1 - 3;
        }
        FIELD(temp_a0, s16, 8) = arg1 + (var_v0 >> 2);
    }
    temp_v1_2 = (s16)temp_a2 - FIELD(temp_a0, s16, 0xA);
    if (temp_v1_2 != 0) {
        FIELD(arg0, s32, 0x58) = 1;
        arg1 = FIELD(temp_a0, s16, 0xA);
        var_v0_2 = temp_v1_2 + 3;
        if (temp_v1_2 <= 0) {
            var_v0_2 = temp_v1_2 - 3;
        }
        FIELD(temp_a0, s16, 0xA) = arg1 + (var_v0_2 >> 2);
    }
    func_800DC650(arg0, arg1, temp_a2);
    if (FIELD(arg0, s32, 0x58) != 0) {
        return;
    }
    temp_v1_3 = FIELD(arg0, s32, 0x50);
    temp_v0_2 = FIELD(arg0, s32, 0x54);
    if (temp_v1_3 == temp_v0_2) {
        return;
    }
    if ((temp_v0_2 ^ temp_v1_3) & 2) {
        func_80053DA8(0x507);
    }
    FIELD(arg0, s32, 0x50) = FIELD(arg0, s32, 0x54);
}
