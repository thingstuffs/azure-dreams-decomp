#include "common.h"

typedef s32 M2C_UNK;

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

extern M2C_UNK func_80047784();
extern s32 func_800990FC();
extern s32 func_80099194();
extern M2C_UNK func_80099290();
extern s32 func_80099734();
extern s32 func_800A2BDC();
extern M2C_UNK func_800A5720();

extern s16 D_80083228;
extern u8 D_80083460[12];
extern u8 D_80170838[16];
extern u8 D_80170848[16];
extern u8 D_80174880[9];

#line 1 "a"
void func_801722E0(void *arg0, void *arg1, void *arg2, void *arg3) {
    register void *call_arg ASM_REG("$4");
    register s32 pass_value ASM_REG("$5");
    register s32 saved_value ASM_REG("$16");
    s32 result;
    u8 *state = D_80083460;

    FIELD(arg3, u8, 0x71) = (u8)(FIELD(arg3, u8, 0x71) & 0x7F);
    if (!(FIELD(state, u16, 2) & 0x2000) &&
        ((func_800A2BDC(arg3) << 0x10) == 0)) {
        u8 *table = D_80174880;

        FIELD(arg0, s8, 0x9A) = 0x17;
        FIELD(arg0, s32, 0x8C) = 0;
        FIELD(arg0, s8, 0x9B) = 0;
        FIELD(arg2, u8 *, 0x2C) = table;
        func_80047784(
            arg2,
            table[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        FIELD(arg3, u8, 0x6D) = (u8)(FIELD(arg3, u8, 0x6D) - 1);
        FIELD(state, u16, 0xA) = (u16)(FIELD(state, u16, 0xA) + 1);
        result = func_800990FC();
        call_arg = arg3;
        pass_value = result;
        saved_value = pass_value;
        func_80099290(func_80099194(
            D_80170848,
            func_80099734(FIELD(arg0, void *, 0xA8),
                func_80099194(D_80170838,
                    func_80099734(call_arg, pass_value)))));
        func_800A5720(saved_value);
    }
}
