#include "common.h"


extern s32 func_800A2BDC(void *arg0);
extern void func_800ACB98(void *arg0, s32 arg1, s32 arg2, void *arg3);
extern void func_800ACD74(void *arg0, s32 arg1, s32 arg2, void *arg3);
extern void func_800B2728(void);
extern void func_800B272C(void);

extern s16 D_800DCE68;
extern u8 D_80083460[0x14];


typedef struct S_800B253C_0 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0x23];
    u8 unk_43;
    u8 pad_44[0x29];
    s8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
} S_800B253C_0;   /* arg3 in func_800B253C */

typedef struct S_800B253C_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0x11];
    u8 unk_AD;
} S_800B253C_1;   /* arg0 in func_800B253C */

typedef struct S_800B253C_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x4];
    s16 unk_08;
    u8 pad_0A[0x2];
    void * unk_0C;
    s32 unk_10;
} S_800B253C_2;   /* state in func_800B253C */

void func_800B253C(S_800B253C_1 *arg0, s32 arg1, s32 arg2, S_800B253C_0 *arg3) {
    u8 *state;
    void *held;
    s32 flags14;

    if ((arg3->unk_1C & 0x2000) || (arg3->unk_14 & 0x4000)) {
        if ((u32)(arg0->unk_9A - 0x13) >= 2U) {
            if (arg3->unk_6D == 0) {
                if (D_800DCE68 == 0) {
                    if ((func_800A2BDC(arg3) << 0x10) != 0) {
                        func_800B272C();
                        return;
                    }
                    goto block_16;
                }
                state = D_80083460;
                held = ((S_800B253C_2 *)state)->unk_0C;
                if (held != arg3) {
                    if ((((S_800B253C_2 *)state)->unk_10 == 0) && (held == 0) &&
                        (((S_800B253C_2 *)state)->unk_08 == 0) &&
                        !(((S_800B253C_2 *)state)->unk_02 & 0x2008) &&
                        (arg3->unk_43 == 0xFD)) {
                        ((S_800B253C_2 *)state)->unk_0C = arg3;
                        goto block_15;
                    }
                } else {
                block_15:
                    if (arg3->unk_43 == 0xFD) {
                    block_16:
                        if (arg3->unk_1C & 0x400000) {
                            arg0->unk_8C = 0;
                            flags14 = arg3->unk_14;
                            arg3->unk_1C &= 0xFFBFFFFF;
                            if (flags14 & 0x20000000) {
                                arg3->unk_14 = flags14 | 0x400000;
                                arg0->unk_AD = 0;
                                func_800ACB98(arg0, arg1, arg2, arg3);
                                func_800B272C();
                                return;
                            }
                            arg3->unk_14 = flags14 & 0xFFBFFFFF;
                            arg0->unk_9A = (flags14 & 0x4000) ? 1 : 2;
                            func_800B2728();
                            return;
                        }
                        if (arg3->unk_1C & 0x02000000) {
                            arg0->unk_8C = 0;
                            arg3->unk_71 = 0;
                            arg3->unk_1C &= 0xFDFFFFFF;
                            if (arg3->unk_14 & 0x20000000) {
                                func_800ACD74(arg0, arg1, arg2, arg3);
                                func_800B272C();
                                return;
                            }
                            arg0->unk_9A = 0;
                            arg0->unk_9B = 0;
                        }
                    }
                }
            }
        }
    }
}
