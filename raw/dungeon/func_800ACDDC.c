#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern s32 func_800A2BDC(void *arg0);
extern void func_800ACB98(void *arg0, s32 arg1, s32 arg2, void *arg3);
extern void func_800ACD74(void *arg0, s32 arg1, s32 arg2, void *arg3);
extern void func_800B2728(void);
extern void func_800B272C(void);

extern s16 D_800DCE68;
extern u8 D_80083460[0x14];

void func_800B253C(void *arg0, s32 arg1, s32 arg2, void *arg3) {
    u8 *state;
    void *held;
    s32 flags14;

    if ((FIELD(arg3, s32, 0x1C) & 0x2000) || (FIELD(arg3, s32, 0x14) & 0x4000)) {
        if ((u32)(FIELD(arg0, u8, 0x9A) - 0x13) >= 2U) {
            if (FIELD(arg3, s8, 0x6D) == 0) {
                if (D_800DCE68 == 0) {
                    if ((func_800A2BDC(arg3) << 0x10) != 0) {
                        func_800B272C();
                        return;
                    }
                    goto block_16;
                }
                state = D_80083460;
                held = FIELD(state, void *, 0xC);
                if (held != arg3) {
                    if ((FIELD(state, s32, 0x10) == 0) && (held == 0) &&
                        (FIELD(state, s16, 8) == 0) &&
                        !(FIELD(state, u16, 2) & 0x2008) &&
                        (FIELD(arg3, u8, 0x43) == 0xFD)) {
                        FIELD(state, void *, 0xC) = arg3;
                        goto block_15;
                    }
                } else {
                block_15:
                    if (FIELD(arg3, u8, 0x43) == 0xFD) {
                    block_16:
                        if (FIELD(arg3, s32, 0x1C) & 0x400000) {
                            FIELD(arg0, s32, 0x8C) = 0;
                            flags14 = FIELD(arg3, s32, 0x14);
                            FIELD(arg3, s32, 0x1C) &= 0xFFBFFFFF;
                            if (flags14 & 0x20000000) {
                                FIELD(arg3, s32, 0x14) = flags14 | 0x400000;
                                FIELD(arg0, u8, 0xAD) = 0;
                                func_800ACB98(arg0, arg1, arg2, arg3);
                                func_800B272C();
                                return;
                            }
                            FIELD(arg3, s32, 0x14) = flags14 & 0xFFBFFFFF;
                            FIELD(arg0, u8, 0x9A) = (flags14 & 0x4000) ? 1 : 2;
                            func_800B2728();
                            return;
                        }
                        if (FIELD(arg3, s32, 0x1C) & 0x02000000) {
                            FIELD(arg0, s32, 0x8C) = 0;
                            FIELD(arg3, u8, 0x71) = 0;
                            FIELD(arg3, s32, 0x1C) &= 0xFDFFFFFF;
                            if (FIELD(arg3, s32, 0x14) & 0x20000000) {
                                func_800ACD74(arg0, arg1, arg2, arg3);
                                func_800B272C();
                                return;
                            }
                            FIELD(arg0, u8, 0x9A) = 0;
                            FIELD(arg0, u8, 0x9B) = 0;
                        }
                    }
                }
            }
        }
    }
}
