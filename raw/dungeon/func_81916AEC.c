#include "common.h"

typedef s32 unk32;

typedef struct Copy6 {
    s32 word[6];
} Copy6;

#ifndef NULL
#define NULL 0
#endif

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void *func_8003FC64(s32);
extern void func_8003DB94(void *, void *, s32);
extern void func_8004491C(void *, void *);

extern unk32 D_800241E4;
extern unk32 D_80045340;
extern unk32 D_800DEC70;

void *func_800242EC(s32 arg0, void *arg1, void *arg2)
{
    void *temp_s0;
    void *temp_v0;
    void *temp_v1;
    Copy6 *temp_v1_2;
    register void *var_v0 ASM_REG("$2");

    temp_v0 = func_8003FC64(0x212);
    var_v0 = NULL;
    if (temp_v0 != NULL) {
        temp_v1 = (u8 *)temp_v0 + 0x20;
        FIELD(temp_v0, unk32 *, 0x10) = &D_800241E4;
        FIELD(temp_v0, s32, 0x20) = arg0;
        FIELD(temp_v1, s16, 4) = 0;
        FIELD(temp_v1, s16, 6) = 8;
        FIELD(temp_v1, s16, 8) = 8;
        FIELD(temp_v1, u16, 0xA) = FIELD(arg2, u16, 0x2A);
        temp_s0 = FIELD(temp_v0, void *, 0xC);
        FIELD(temp_s0, s8, 0xD) = 0x30;
        FIELD(temp_s0, s8, 0xC) = 0x30;
        FIELD(temp_s0, u8, 0xE) = 0xC0;
        FIELD(temp_s0, s16, 0x12) = 0x7DCF;
        FIELD(temp_s0, u16, 0x14) |= 0xC;
        FIELD(temp_s0, u16, 0x10) |= 0x20;
        FIELD(temp_s0, u16, 0x14) |= 0x100;
        func_8003DB94(temp_s0, &D_800DEC70, 0);
        FIELD(temp_s0, s16, 0x1E) = 0x1000;
        FIELD(temp_s0, s16, 0x1C) = 0x1000;
        func_8004491C(temp_v0, &D_80045340);
        temp_v1_2 = FIELD(temp_v0, Copy6 *, 8);
        var_v0 = temp_v0;
        *temp_v1_2 = *(Copy6 *)arg1;
        ASM_KEEP(var_v0);
    }
    return var_v0;
}
