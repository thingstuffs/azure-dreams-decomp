#include "common.h"

typedef struct {
    u8 pad00[0x38];
    s32 unk38[3];
    u8 pad44[0x54 - 0x44];
    s32 unk54;
    s32 unk58[7];
    s32 unk74;
} Unk818110CC;

extern s32 func_80049004(s32 *arg0, s32 arg1, s32 arg2);
extern s32 func_80048FBC(s32 *arg0, s32 arg1);
extern void func_800491CC(s32 arg0, s32 *arg1, s32 arg2);
extern s32 D_8002E5E8[3];

s32 func_800260CC(Unk818110CC *arg0, s32 arg1)
{
    s32 result = 0;
    s32 *field58 = arg0->unk58;
    s32 value;

    value = func_80049004(field58, arg1, 6);
    arg0->unk54 = value;
    if (value != 0) {
        value = func_80048FBC(field58, 6);
        arg0->unk74 = value;
        if (value != 0) {
            arg0->unk38[0] = D_8002E5E8[0];
            arg0->unk38[1] = D_8002E5E8[1];
            arg0->unk38[2] = D_8002E5E8[2];
            func_800491CC(arg0->unk54, arg0->unk38, 13);
            result = 1;
        }
    }
    return result;
}
