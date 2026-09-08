#include "common.h"

typedef struct {
    s32 field0;
    s32 field4;
    s32 field8;
    s32 fieldC;
    s32 field10;
    s32 field14;
} S_8081C8DC;

extern void func_800478B8(void *arg0, void *arg1);
extern s32 D_800814A0;

/* Advances the position and propagates flags from the processed result. */
void func_800268DC(void *object_data, S_8081C8DC *motion, S_8081C8DC *result)
{
    s32 delta_y;
    s32 delta_z;

    delta_y = motion->field10;
    delta_z = motion->field14;
    motion->field0 += motion->fieldC;
    motion->field4 += delta_y;
    motion->field8 += delta_z;
    func_800478B8(result, motion);
    if (*(u16 *)((u8 *)result + 0x14) & 0x6000) {
        *(u16 *)((u8 *)object_data - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
