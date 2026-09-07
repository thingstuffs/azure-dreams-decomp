#include "common.h"
#include "m2c_compat.h"

typedef struct S_8017208C_0 {
    u8 pad_00[0x3];
    u8 unk_03;
    u8 pad_04[0x18];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x41];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
    u8 pad_72[0x12];
    s8 unk_84;
    s8 unk_85;
} S_8017208C_0;   /* arg3 in func_8017208C */

typedef struct S_8017208C_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    s8 unk_9A;
    s8 unk_9B;
    u8 pad_9C[0x10];
    u8 unk_AC;
} S_8017208C_1;   /* arg0 in func_8017208C */


M2C_UNK func_80047784();         /* extern */
M2C_UNK func_8009C93C(); /* extern */
s32 func_800A2B5C();                          /* extern */
M2C_UNK func_800C7930(); /* extern */
M2C_UNK func_80172154();                            /* extern */
M2C_UNK func_80172180();                            /* extern */
extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_80174038[];

void func_8017208C(void *arg0, M2C_UNK arg1, void *arg2, void *arg3) {
    ((S_8017208C_0 *)arg3)->unk_71 = (u8) (((S_8017208C_0 *)arg3)->unk_71 & 0x7F);
    if (!(D_80083462 & 0x2000) && ((func_800A2B5C(arg3) << 0x10) == 0) && (func_800C7930(arg3 - 0x20, arg1, 8, 0x300), ((func_800A2B5C(arg3) << 0x10) == 0))) {
        ((S_8017208C_1 *)arg0)->unk_8C = 0;
        ((S_8017208C_1 *)arg0)->unk_9B = 0;
        if (((S_8017208C_1 *)arg0)->unk_98 & 0x8000) {
            ((S_8017208C_1 *)arg0)->unk_9A = 0x17;
            if (((S_8017208C_0 *)arg3)->unk_1C & 0x1000) {
                ((S_8017208C_1 *)arg0)->unk_98 = (u16) (((S_8017208C_1 *)arg0)->unk_98 | 0x4000);
            } else {
                ((S_8017208C_1 *)arg0)->unk_98 = (u16) (((S_8017208C_1 *)arg0)->unk_98 & 0xBFFF);
            }
            ((S_8017208C_1 *)arg0)->unk_AC = (u8) ((S_8017208C_0 *)arg3)->unk_03;
            ((S_8017208C_0 *)arg3)->unk_03 = 0xFFU;
            ((S_8017208C_0 *)arg3)->unk_84 = 0x7E;
        } else {
            ((S_8017208C_1 *)arg0)->unk_9A = 0x11;
            ((S_8017208C_0 *)arg3)->unk_84 = 0x7C;
        }
        ((S_8017208C_0 *)arg3)->unk_85 = 8;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
        (*(u8 **)((u8 *)arg2 + 0x2C)) = D_80174038;
        func_80047784(arg2, D_80174038[((D_80083228 + ((S_8017208C_0 *)arg3)->unk_2A + 0x100) >> 9) & 7], 0);
        ((S_8017208C_0 *)arg3)->unk_6D = (u8) (((S_8017208C_0 *)arg3)->unk_6D - 1);
        func_8009C93C(arg3, arg2, ((S_8017208C_0 *)arg3)->unk_2A, 1, 0);
        if (!(((S_8017208C_1 *)arg0)->unk_98 & 0x8000)) {
            ((S_8017208C_0 *)arg3)->unk_1C = (s32) (((S_8017208C_0 *)arg3)->unk_1C & 0xFEFFFFFF);
        }
    }
}

/* MECHANISM: Retail's 0x80172154/0x80172180 targets are local CFG joins, not callees.
   A u8 path result carries 0x7E/0x7C into the shared arg3+0x84 store.
   The held argument roles naturally produce the 0x30 frame and s1/s0/s3/s2 saves. */
