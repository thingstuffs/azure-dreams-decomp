#include "common.h"

extern s32 func_800AB1C0(M2C_UNK);
extern void func_800AD594(s32, s32);
extern void func_800A4ACC(s32);
extern s32 func_800AD9B4(s32, s32);
extern s32 D_80170E9C;

void func_801720DC(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    void *entity = arg0;
    s32 value = arg2;
    s32 actor = arg3;

    if (func_800AB1C0(arg0, arg1, arg2, arg3) != 0) {
        func_800AD594(actor, 3);
        func_800A4ACC(actor);
        if ((func_800AD9B4(value, actor) << 16) > 0) {
            *(s32 **)((u8 *)entity + 0x8C) = &D_80170E9C;
            *(s32 *)((u8 *)entity + 0x90) = 0;
        }
    }
}
