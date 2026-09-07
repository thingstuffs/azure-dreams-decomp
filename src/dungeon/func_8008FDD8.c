#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_8008ACDC_arg0.h"

typedef struct S_80095538_3 {
    void * unk_00;
} S_80095538_3;   /* &D_80082EB0 in func_80095538 */

typedef struct S_80095538_4 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_80095538_4;   /* ((S_80095538_3 *)(&D_80082EB0))->unk_00 in func_80095538 */


typedef struct S_80095538_0 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x5C];
    s32 unk_64;
    s32 unk_68;
} S_80095538_0;   /* var_s1 in func_80095538; pointer addresses record offset 0x18 */

typedef struct S_80095538_1 {
    union { s32 s; void * u; } unk_00;   /* accessed as both */
    s32 unk_04;
} S_80095538_1;   /* &D_80082EB0 in func_80095538 */



M2C_UNK func_8008D388();    /* extern */
M2C_UNK func_800982A8();              /* extern */
M2C_UNK func_80098614();              /* extern */
s32 func_80098920(); /* extern */
s32 func_8009FADC();                             /* extern */
extern M2C_UNK D_80082EB0;

s32 func_80095538(Rec_func_8008ACDC_arg0 *arg0, s16 arg1, s16 arg2) {
    s32 temp_s3;
    s32 temp_s4;
    register s32 var_s5 ASM_REG("$21");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 var_v0;
    u8 temp_v0;
    void *var_s1;
    void *var_a1;
    void *var_a1_2;

    var_s1 = arg0;
    temp_s3 = ((S_80095538_0 *)((u8 *)var_s1 - 0x18))->unk_00;
    temp_s4 = ((S_80095538_0 *)((u8 *)var_s1 - 0x18))->unk_04;
    var_s5 = 1;
    ((S_80095538_1 *)(&D_80082EB0))->unk_00.s = func_8009FADC(arg1);
    if (arg2 != 0) {
        ((S_80095538_1 *)(&D_80082EB0))->unk_04 = func_8009FADC(arg2);
    } else {
        ((S_80095538_1 *)(&D_80082EB0))->unk_04 = 0;
    }
    temp_v0 = ((S_80095538_4 *)(((S_80095538_3 *)(&D_80082EB0))->unk_00))->unk_01;
    switch (temp_v0) {
    case 15:
    case 16:
        var_a1 = NULL;
        if (((S_80095538_1 *)(&D_80082EB0))->unk_00.u != ((S_80095538_0 *)((u8 *)var_s1 - 0x18))->unk_64) {
            var_a1 = ((S_80095538_1 *)(&D_80082EB0))->unk_00.u;
        }
        func_800982A8(var_s1, var_a1);
        var_v0 = var_s5 << 0x10;
        goto return_lbl;
    case 17:
        var_a1_2 = NULL;
        if (((S_80095538_1 *)(&D_80082EB0))->unk_00.u != ((S_80095538_0 *)((u8 *)var_s1 - 0x18))->unk_68) {
            var_a1_2 = ((S_80095538_1 *)(&D_80082EB0))->unk_00.u;
        }
        func_80098614(var_s1, var_a1_2);
        var_v0 = var_s5 << 0x10;
        goto return_lbl;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
        var_s5 = func_80098920(var_s1, ((S_80095538_1 *)(&D_80082EB0))->unk_00.u, 3, 0);
        goto block_13;
    case 18:
        arg0->unk_BC = (void *) ((S_80095538_1 *)(&D_80082EB0))->unk_00.u;
        func_8008D388(arg0, temp_s3, temp_s4, var_s1);
        goto block_13;
    case 19:
    case 20:
    case 21:
    default:
        goto block_13;
    }
block_13:
    var_v0 = var_s5 << 0x10;
return_lbl:
    return var_v0 >> 0x10;
}

/* MECHANISM: Separate arg0 lifetimes hold the original in s6 and the working base in s1.
   A guarded s5 pin with ASM_KEEP_NV restores the retail save/color order without a sched barrier.
   The direct D_80082EB0 base and one shared post-switch shift remove the +1-word CFG cascade. */
