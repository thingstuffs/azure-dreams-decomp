#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern s32 func_80033D08();
extern s32 func_80095388();
extern s32 func_8009539C();
extern s32 func_8009C5BC();
extern s16 func_800C2AE8();

extern s32 D_800814A0[3];
extern u8 D_8009C5D8[];

void func_8009C4E8(void *arg0, void *arg1, void *arg2) {
    s16 value;
    u16 timer;

    timer = FIELD(arg0, u16, 0x6C) - 1;
    FIELD(arg0, u16, 0x6C) = timer;
    if ((s16)(timer) < 0) {
        func_80033D08();
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
        func_8009C5BC();
        return;
    }

    func_80095388(arg1);
    func_8009539C(arg1);
    value = func_800C2AE8(arg1);
    if (FIELD(arg1, s16, 0xA) > value) {
        FIELD(arg1, s16, 0xA) = value;
        FIELD(arg1, s32, 0xC) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg2, s8, 0xE) = 0x40;
        FIELD(arg2, s8, 0xD) = 0x40;
        FIELD(arg2, s8, 0xC) = 0x40;
        FIELD(arg2, s16, 0x10) = 0x20;
        FIELD(arg2, u16, 0x14) |= 0x1C;
        FIELD(arg0, void *, 0x50) = D_8009C5D8;
    }
}
