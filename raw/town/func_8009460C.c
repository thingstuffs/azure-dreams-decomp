#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 func_80094220(void *, void *, s32);
extern void func_80094984(void *, void *, s32);
extern void func_80095C80(void *);
extern s32 D_800D00E8;
extern s32 D_800D00F0;
extern s32 D_800D00F8;
extern s16 D_800D0454[];

void func_80091D6C(void *arg0, void *arg1, s32 arg2) {
    s16 temp_v0;
    s32 temp_s3;

    func_80095C80(arg1);
    if (FIELD(arg0, s16, 0xA) >= 15) {
        temp_s3 = (s32)((u32)(FIELD(arg0, s16, 0x34) +
                   D_800D0454[21 - FIELD(arg0, s16, 0xA)]) << 16);
        goto selector_join;
    } else {
        temp_s3 = (s32)((u32)FIELD(arg0, s16, 0x34) << 16);
    }

selector_join:
    if (FIELD(arg0, s16, 0xA) == 19)
        func_80094984(&D_800D00E8, arg0, arg2);
    if (FIELD(arg0, s16, 0xA) == 15)
        func_80094984(&D_800D00F0, arg0, arg2);
    if (FIELD(arg0, s16, 0xA) == 12)
        func_80094984(&D_800D00F8, arg0, arg2);
    temp_v0 = (u16)FIELD(arg0, s16, 0xA) - 1;
    FIELD(arg0, s16, 0xA) = temp_v0;
    if ((s32)((u32)(u16)temp_v0 << 16) <= 0) {
        FIELD(arg1, s32, 0xC) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0x14) = 0;
        func_80094220(arg0, arg1, arg2);
        return;
    }
    FIELD(arg1, s32, 0x14) = temp_s3 - FIELD(arg1, s32, 8);
}
