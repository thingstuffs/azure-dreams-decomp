#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_800A9E70_arg0.h"

#define M2C_BREAK() ((void)0)
#define M2C_SYNC() ((void)0)

extern void func_80047784(void *, u8, s32);
extern void func_800A4ACC(void *);
extern s16 D_80083228[8];
extern u8 D_801739E0[];



void func_8016DAC0(Rec_func_800A9E70_arg0 *arg0, void *arg1, void *arg2, Rec_D_800E3D7C *arg3) {
    s32 temp_v1;
    u32 temp_v0;
    u8 *temp_a1;

    arg3->unk_71.as_u8 = (s8) (arg3->unk_71.as_u8 & 0x7F);
    temp_v1 = arg0->unk_AC;
    arg0->unk_9A.as_s8 = 0x18;
    arg0->unk_8C = 0;
    arg0->unk_9B.as_s8 = 0;
    if (temp_v1 != 1) {
        if ((s32) temp_v1 < 2) {
            if (temp_v1 == 0) {
                goto table_0;
            }
            goto done;
        } else {
            if (temp_v1 == 2) {
                goto table_2;
            }
            if (temp_v1 == 3) {
                goto table_3;
            }
            goto done;
        }
    }
    goto table_1;

table_0:
    temp_a1 = (u8 *)0x80170000;
    ASM_KEEP(temp_a1);   /* MATCH pin: load-bearing for the whole function shape */
    temp_a1 += 0x39E0;
    goto dispatch;
table_1:
    temp_a1 = (u8 *)0x80170000;
    ASM_KEEP(temp_a1);   /* MATCH pin: load-bearing for the whole function shape */
    temp_a1 += 0x39E8;
    goto dispatch;
table_2:
    temp_a1 = (u8 *)0x80170000;
    ASM_KEEP(temp_a1);   /* MATCH pin: load-bearing for the whole function shape */
    temp_a1 += 0x39F0;
    goto dispatch;
table_3:
    temp_a1 = (u8 *)0x80170000;
    ASM_KEEP(temp_a1);   /* MATCH pin: load-bearing for the whole function shape */
    temp_a1 += 0x39F8;

dispatch:
    *(volatile void **)((u8 *)arg2 + 0x2C) = temp_a1;
    temp_v0 = (((D_80083228[0] + arg3->unk_2A.as_s16 + 0x100) >> 9) & 7);
    temp_v0 = temp_v0 + (u32)temp_a1;
    func_80047784(arg2, *(u8 *)temp_v0, 0);

done:
    func_800A4ACC(arg3);
    arg3->unk_6D.as_u8 = (u8) (arg3->unk_6D.as_u8 - 1);
}
