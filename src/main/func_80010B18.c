#include "common.h"

extern void *D_800282A4[3];
extern void *D_800791A4;

extern s32 func_80022138(void);
extern void *func_8004DA74(void *arg0, void *arg1, s32 arg2);

void func_80023B18(void *arg0) {
    void **temp;
    s32 idx;

    temp = *(void ***)((u8 *) arg0 + 0x260);
    idx = (func_80022138() >= 3);
    *(void **) temp = func_8004DA74((u8 *) arg0 + 8, D_800282A4[idx], 1);
    *(s16 *)((u8 *) temp[1] + 8) = 0xF0;
    *(s16 *)((u8 *) temp[1] + 0xA) = 0x91;

    temp = *(void ***)((u8 *) arg0 + 0x270);
    *(s16 *)((u8 *) temp[1] + 8) = 0x70;
    *(s16 *)((u8 *) temp[1] + 0xA) = 0x10;
    *(void **) temp = &D_800791A4;

    temp = *(void ***)((u8 *) arg0 + 0x278);
    *(void **) temp = (u8 *) arg0 + 0x134;
    *(s16 *)((u8 *) temp[1] + 8) = 0xAE;
    *(s16 *)((u8 *) temp[1] + 0xA) = 0x18;
}
