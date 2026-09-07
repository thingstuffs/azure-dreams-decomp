#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B2FAC_0 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_800B2FAC_0;   /* arg2 in func_800B2FAC */

typedef struct S_800B2FAC_1_pre {
    u16 unk_00;
} S_800B2FAC_1_pre;   /* the 0x2 bytes before arg3 in func_800B2FAC, addressed as arg3[-1] */

typedef struct S_800B2FAC_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_800B2FAC_1;   /* arg3 in func_800B2FAC */


M2C_UNK func_8009A028();                      /* extern */
M2C_UNK func_8009A3D0();             /* extern */
M2C_UNK func_800A2DB8();                      /* extern */
M2C_UNK func_800A32A4();                      /* extern */
extern M2C_UNK D_800814A0;
extern M2C_UNK D_80083460;

void func_800B2FAC(void *arg0, void *arg1, void *arg2, void *arg3) {
    M2C_UNK var_a2;
    s32 flags;
    u8 var_a0;
    u8 var_a1;
    s32 *global;

    if (((S_800B2FAC_0 *)arg2)->unk_14 & 0xE000) {
        global = &D_80083460;
        if (global[4] == (arg3 - 0x20)) {
            global[4] = global[4] & 0x7FFFFFFF;
        }
        func_800A2DB8(arg3);
        func_800A32A4(arg3);
        flags = ((S_800B2FAC_1 *)arg3)->unk_1C;
        var_a0 = ((S_800B2FAC_0 *)arg2)->unk_24;
        var_a1 = ((S_800B2FAC_0 *)arg2)->unk_25;
        var_a2 = 0x3000;
        if (flags & 0x2000) {
            var_a2 = 0x300;
        }
        func_8009A3D0(var_a0, var_a1, var_a2);
        func_8009A028(arg3);
        (*(u16 *)((u8 *)arg3 + -2)) = (u16) (((S_800B2FAC_1_pre *)arg3)[-1].unk_00 | 0x8000);
        D_800814A0 = D_800814A0 | 0x8000;
    }
}

/* MECHANISM: Four-argument ABI holds arg2/arg3 in s1/s0 and yields the retail 0x20 frame/save order.
   A named D_80083460 base forces cdk's split lui/addiu plus the 0x10 field displacement.
   Cached flag/byte locals expose retail load scheduling; a direct D_800814A0 update removes the extra address word. */
