#include "common.h"

typedef struct {
    u8 unk0[0xC];
    s32 value;
} DungeonNode;

extern void func_800B8FC8(void *, u16 *, u16 *, s32, s32);

void func_80025FF4(void *arg0, void *arg1) {
    u16 local[6];
    s32 var_s1;
    s32 val;
    DungeonNode *temp_s0;
    s32 temp_s2;
    void *var_a0;
    u8 *base;
    s16 temp_a0;

    var_s1 = 0x40;
    local[1] = 0x100;
    val = var_s1;
    ASM_KEEP_NV(val);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    local[2] = val;
    local[3] = 0x80;
    local[5] = 0x13C;
    do {
        temp_a0 = var_s1 + 0x340;
        local[0] = temp_a0;
        temp_a0 += (s16)local[2] / 2;
        local[4] = temp_a0;
        if (var_s1 == 0) {
            base = (u8 *)arg0 - 0x14;
        } else {
            base = (u8 *)arg1 - 0x14;
        }
        temp_s0 = *(DungeonNode **)base;
        temp_s2 = temp_s0->value;
        temp_s0->value = 0x808080;
        var_a0 = arg1;
        if (var_s1 == 0) {
            var_a0 = arg0;
        }
        func_800B8FC8(var_a0, &local[0], &local[4], 1, 2);
        var_s1 -= 0x40;
        temp_s0->value = temp_s2;
    } while (var_s1 >= 0);
}
