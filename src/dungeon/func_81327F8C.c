#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047784();         /* extern */
s32 func_8009A180();                     /* extern */
s8 func_8009FB34();                           /* extern */
M2C_UNK func_800A9A0C();                      /* extern */
M2C_UNK func_800AA258(); /* extern */
s32 func_800AA6B4(); /* extern */
M2C_UNK func_800AA888(); /* extern */
void func_8016FA60(void) __attribute__((noreturn));
M2C_UNK func_8016FA84();                            /* extern */
M2C_UNK func_8016FCE4(); /* extern */
s32 func_80170224(); /* extern */
M2C_UNK func_8017092C(); /* extern */
M2C_UNK func_80174320();     /* extern */
extern u16 D_80013714;
extern void *D_800814A8;
extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_80174A2C[];
extern u8 D_80174A64[];


typedef struct S_8016F78C_0 {
    u8 pad_00[0x90];
    s32 unk_90;
    u8 pad_94[0x4];
    u16 unk_98;
    union { u8 n; volatile u8 v; } unk_9A;   /* accessed as both */
} S_8016F78C_0;   /* arg0 in func_8016F78C */

typedef struct S_8016F78C_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x1C];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
} S_8016F78C_1;   /* arg3 in func_8016F78C */

typedef struct S_8016F78C_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    s8 unk_26;
    u8 pad_27[0x5];
    u8 * unk_2C;
} S_8016F78C_2;   /* arg2 in func_8016F78C */

typedef struct S_8016F78C_3 {
    u8 pad_00[0x58];
    s32 unk_58;
} S_8016F78C_3;   /* D_800814A8 in func_8016F78C */

void func_8016F78C(void *arg0, M2C_UNK arg1, void *arg2, void *arg3) {
    u8 stack_pad[8];
    u8 state;
    s32 state_id;

    if (D_80083462 & 0x1000) {
        ((S_8016F78C_0 *)arg0)->unk_9A.n = 0xEU;
        func_8016FA84();
        func_8016FA60();
        return;
    }
    if (!(D_80083462 & 0x2000)) {
        if (((S_8016F78C_1 *)arg3)->unk_1C & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            func_8016FA60();
            return;
        }
        state = ((S_8016F78C_0 *)arg0)->unk_9A.v;
        state_id = 0xE;
        if (state != state_id) {
            if (((S_8016F78C_2 *)arg2)->unk_2C != D_80174A2C) {
                (*(u8 **)((u8 *)arg2 + (0x2C))) = D_80174A2C;
                func_80047784(arg2, D_80174A2C[((D_80083228 + ((S_8016F78C_1 *)arg3)->unk_2A + 0x100) >> 9) & 7], 0);
            }
            ((S_8016F78C_0 *)arg0)->unk_9A.n = state_id;
        }
        ((S_8016F78C_0 *)arg0)->unk_98 = (u16) (((S_8016F78C_0 *)arg0)->unk_98 & 0xFFF3);
        if ((((S_8016F78C_1 *)arg3)->unk_64 == 0) || (func_800AA6B4(arg0, arg1, arg2, D_80174A64) == 0)) {
            if (((S_8016F78C_1 *)arg3)->unk_1C & 0x80000) {
                func_800AA888(arg0, arg1, arg2, arg3);
                func_8017092C(arg0, arg1, arg2, arg3);
                (*(u8 **)((u8 *)arg2 + (0x2C))) = D_80174A2C;
                func_80047784(arg2, D_80174A2C[((D_80083228 + ((S_8016F78C_1 *)arg3)->unk_2A + 0x100) >> 9) & 7], 0);
                ((S_8016F78C_0 *)arg0)->unk_90 = 0;
                func_8016FA60();
                return;
            }
            goto block_16;
        }
    } else {
block_16:
        ((S_8016F78C_2 *)arg2)->unk_26 = func_8009FB34(((S_8016F78C_2 *)arg2)->unk_24, ((S_8016F78C_2 *)arg2)->unk_25);
        if (((S_8016F78C_1 *)arg3)->unk_6D > 0) {
            if (((S_8016F78C_1 *)arg3)->unk_1C & 0x20) {
                func_800A9A0C(arg3);
                func_8016FA60();
                return;
            }
            if (!(((S_8016F78C_1 *)arg3)->unk_46 & 0x8000)) {
                if (!(D_80083462 & 0x2000) || ((func_8009A180(arg3, ((S_8016F78C_3 *)D_800814A8)->unk_58 + 0x20) << 0x10) == 0)) {
                    if (D_80013714 & 8) {
                        func_80174320(arg0, arg1, arg2);
                        ((S_8016F78C_1 *)arg3)->unk_71 = (u8) (((S_8016F78C_1 *)arg3)->unk_71 & 0x7F);
                        func_800A9A0C(arg3);
                        ((S_8016F78C_1 *)arg3)->unk_46 = (u16) (((S_8016F78C_1 *)arg3)->unk_46 & 0x7FFF);
                        func_8016FA60();
                        return;
                    }
                    if ((func_80170224(arg0, arg1, arg2, 0) << 0x10) != 0) {
                        ((S_8016F78C_1 *)arg3)->unk_46 = (u16) (((S_8016F78C_1 *)arg3)->unk_46 | 0x4000);
                        goto block_28;
                    }
                }
            } else {
block_28:
                ((S_8016F78C_1 *)arg3)->unk_46 = (u16) (((S_8016F78C_1 *)arg3)->unk_46 & 0x7FFF);
                ((S_8016F78C_1 *)arg3)->unk_71 = (u8) (((S_8016F78C_1 *)arg3)->unk_71 & 0x7F);
                func_800A9A0C(arg3);
                func_8016FCE4(arg0, arg1, arg2, arg3);
            }
        }
    }
}
