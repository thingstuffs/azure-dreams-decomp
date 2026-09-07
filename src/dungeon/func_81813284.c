#include "common.h"

typedef struct {
    u8 pad00[0x4C];
    s32 unk4C;
    u8 pad50[0x6C - 0x50];
    s32 unk6C[3];
    u8 pad78[0x88 - 0x78];
    s32 unk88;
    s32 unk8C[7];
} Unk818110CC;

extern s32 func_80049004(s32 *arg0, s32 arg1, s32 arg2);
extern s32 func_80048FBC(s32 *arg0, s32 arg1);
extern void func_800491CC(s32 arg0, s32 *arg1, s32 arg2);
extern s32 D_8002E5E8[3];

s32 func_80028284(Unk818110CC *arg0, s32 arg1)
{
    s32 result = 0;
    s32 *field8C = arg0->unk8C;
    s32 value;

    value = func_80049004(field8C, arg1, 8);
    arg0->unk88 = value;
    if (value != 0) {
        value = func_80048FBC(field8C, 8);
        arg0->unk4C = value;
        if (value != 0) {
            arg0->unk6C[0] = D_8002E5E8[0];
            arg0->unk6C[1] = D_8002E5E8[1];
            arg0->unk6C[2] = D_8002E5E8[2];
            func_800491CC(arg0->unk88, arg0->unk6C, 15);
            result = 1;
        }
    }
    return result;
}
