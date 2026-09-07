#include "common.h"

extern s32 func_800AB1C0(void);
extern void func_800AD594(s32, s32);
extern void func_800A4ACC(s32);
extern s32 func_800AD9B4(s32, s32);
extern s32 D_80171728;

void func_80172B30(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    register void *entity ASM_REG("$17") = arg0;
    register s32 value ASM_REG("$18") = arg2;
    register s32 actor ASM_REG("$16") = arg3;

    if (func_800AB1C0() != 0) {
        func_800AD594(actor, 4);
        func_800A4ACC(actor);
        if ((func_800AD9B4(value, actor) << 16) > 0) {
            *(s32 **)((u8 *)entity + 0x8C) = &D_80171728;
            *(s32 *)((u8 *)entity + 0x90) = 0;
        }
    }
}
