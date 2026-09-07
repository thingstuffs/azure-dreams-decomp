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

void func_800268DC(void *arg0, S_8081C8DC *arg1, S_8081C8DC *arg2)
{
    s32 temp_a0;
    s32 temp_a2;

    temp_a0 = arg1->field10;
    temp_a2 = arg1->field14;
    arg1->field0 += arg1->fieldC;
    arg1->field4 += temp_a0;
    arg1->field8 += temp_a2;
    func_800478B8(arg2, arg1);
    if (*(u16 *)((u8 *)arg2 + 0x14) & 0x6000) {
        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
