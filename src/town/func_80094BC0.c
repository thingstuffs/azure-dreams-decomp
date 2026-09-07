#include "common.h"
#include "m2c_compat.h"

s32 func_80033B2C();                         /* extern */
M2C_UNK func_80094088();     /* extern */
M2C_UNK func_800942B0();     /* extern */
M2C_UNK func_80094378();     /* extern */
M2C_UNK func_80094414();     /* extern */
M2C_UNK func_80094474();     /* extern */
M2C_UNK func_800944BC();     /* extern */
M2C_UNK func_8009451C();     /* extern */
M2C_UNK func_80094C1C();                      /* extern */
M2C_UNK func_80095094();                      /* extern */
s32 func_8009567C(void *);            /* extern */
s32 func_80095840();               /* extern */
s16 func_80095978();               /* extern */
M2C_UNK func_80095A94();      /* extern */
M2C_UNK func_80095C80();                      /* extern */
extern u8 D_80083160[];
extern M2C_UNK D_800CFCB4;
extern M2C_UNK D_800CFCEF;
extern M2C_UNK D_800FE488;

typedef struct S_80092320_0 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80092320_0;   /* arg1 in func_80092320 */

typedef struct S_80092320_1 {
    u8 unk_00;
} S_80092320_1;   /* &D_800CFCEF in func_80092320 */

typedef struct S_80092320_2 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_80092320_2;   /* state in func_80092320 */

typedef struct S_80092320_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80092320_3;   /* arg0 in func_80092320 */

void func_80092320(S_80092320_3 *arg0, S_80092320_0 *arg1, M2C_UNK arg2) {
    u8 *state = D_80083160;
    s16 temp_v0;
    s32 temp_v0_3;
    u16 temp_v0_2;

    func_80095C80(arg1);
    func_80094C1C(arg0);
    func_80095094(arg1);
    temp_v0 = func_80095978(arg1, &D_800FE488);
    if ((temp_v0 - arg1->unk_0A) >= 4) {
        if (((S_80092320_1 *)(&D_800CFCEF))->unk_00 == 0) {
            func_80094378(arg0, arg1, arg2);
            goto block_end;
        }
        goto block_6;
    }
    if (((S_80092320_1 *)(&D_800CFCEF))->unk_00 == 0) {
        func_80095A94(arg1, temp_v0, &D_800FE488);
    }
block_6:
    if (((S_80092320_2 *)state)->unk_10 & 0x10) {
        func_800942B0(arg0, arg1, arg2);
        goto block_end;
    }
    temp_v0_2 = arg0->unk_0A - 1;
    arg0->unk_0A = temp_v0_2;
    if ((s16) temp_v0_2 < 0) {
        func_80094414(arg0, arg1, arg2);
        goto block_end;
    }
    if (((S_80092320_2 *)state)->unk_10 & 0x40) {
        temp_v0_3 = func_80095840(arg0, &D_800CFCB4);
        if (temp_v0_3 != 0) {
            if (temp_v0_3 == 2) {
                func_8009451C(arg0, arg1, arg2);
                goto block_end;
            }
            func_800944BC(arg0, arg1, arg2);
            goto block_end;
        }
        if (func_80033B2C(0xA4) != 0) {
            func_80094088(arg0, arg1, arg2);
            goto block_end;
        }
    } else if (func_8009567C(&D_800CFCB4) <= 0) {
        func_80094474(arg0, arg1, arg2);
    }
block_end:
    return;
}

/* MECHANISM: A held D_80083160 base supplies s4 and the exact 0x28 frame/save contract.
   Shared D_800CFCEF addressing and a signed s16 timer test reproduce the body operations.
   Correct one-argument func_8009567C ABI removes the dead a1 word and its displacement cascade. */
