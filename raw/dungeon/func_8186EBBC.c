#include "common.h"

extern s32 rand(void);
extern s16 func_800BCB04(s32, s32, s32);
extern s16 D_80025308;
extern s32 D_800814A0[];

typedef struct {
    u16 unk0;
    u16 unk2;
    u16 unk4;
    u16 unk6;
    union {
        s32 unk8;
        struct {
            u16 unk8_lo;
            u16 unkA;
        } half;
    } value;
} UnkArg1;

void func_8186EBBC(u8 *arg0, UnkArg1 *arg1)
{
    u16 temp;

    D_80025308 = 1;
    if ((s16)arg1->value.half.unkA <
        func_800BCB04(arg1->unk2, arg1->unk6,
                      (s16)(arg1->value.half.unkA + 2))) {
        arg1->value.unk8 += 0x20000 + (rand() & 0xFFF);
    }

    temp = *(u16 *)(arg0 + 0x32) - 8;
    *(u16 *)(arg0 + 0x32) = temp;
    if ((s32)(temp << 16) <= 0) {
        *(u16 *)(arg0 - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
