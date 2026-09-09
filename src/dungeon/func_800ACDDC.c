#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_800A9E70_arg0.h"


extern s32 func_800A2BDC(void *arg0);
extern void func_800ACB98(void *arg0, s32 arg1, s32 arg2, void *arg3);
extern void func_800ACD74(void *arg0, s32 arg1, s32 arg2, void *arg3);

extern s16 D_800DCE68;
extern u8 D_80083460[0x14];




typedef struct S_800B253C_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x4];
    s16 unk_08;
    u8 pad_0A[0x2];
    void * unk_0C;
    s32 unk_10;
} S_800B253C_2;   /* state in func_800B253C */

void func_800B253C(Rec_func_800A9E70_arg0 *arg0, s32 arg1, s32 arg2, Rec_D_800E3D7C *arg3) {
    u8 *state;
    void *held;
    s32 flags14;
    s32 nextState;

    if ((arg3->unk_1C.as_s32 & 0x2000) || (arg3->unk_14.as_s32 & 0x4000)) {
        if ((u32)(arg0->unk_9A.as_u8 - 0x13) >= 2U) {
            if (arg3->unk_6D.as_s8 == 0) {
                if (D_800DCE68 == 0) {
                    if ((func_800A2BDC(arg3) << 0x10) != 0) {
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
                        if (arg3->unk_1C.as_s32 & 0x400000) {
                            arg0->unk_8C = 0;
                            flags14 = arg3->unk_14.as_s32;
                            arg3->unk_1C.as_s32 &= 0xFFBFFFFF;
                            if (flags14 & 0x20000000) {
                                arg3->unk_14.as_s32 = flags14 | 0x400000;
                                arg0->unk_AD = 0;
                                func_800ACB98(arg0, arg1, arg2, arg3);
                                return;
                            }
                            arg3->unk_14.as_s32 = flags14 & 0xFFBFFFFF;
                            nextState = flags14 & 0x4000;
                            if (!nextState) {
                                nextState = 2;
                            } else {
                                nextState = 1;
                            }
                            arg0->unk_9A.as_u8 = nextState;
                            goto block_17;
                        }
                        if (arg3->unk_1C.as_s32 & 0x02000000) {
                            arg0->unk_8C = 0;
                            arg3->unk_71.as_u8 = 0;
                            arg3->unk_1C.as_s32 &= 0xFDFFFFFF;
                            if (arg3->unk_14.as_s32 & 0x20000000) {
                                func_800ACD74(arg0, arg1, arg2, arg3);
                                return;
                            }
                            arg0->unk_9A.as_u8 = 0;
                        block_17:
                            arg0->unk_9B.as_u8 = 0;
                        }
                    }
                }
            }
        }
    }
}
