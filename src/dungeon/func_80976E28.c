#include "common.h"
#include "m2c_compat.h"

s32 func_800A2BDC();                          /* extern */
M2C_UNK func_800A9A0C();                      /* extern */
s32 func_800ADDA0(); /* extern */
M2C_UNK func_80171C34(); /* extern */
extern u16 D_80083462;

typedef struct S_80172628_0 {
    u8 pad_00[0x46];
    u16 unk_46;
    u8 pad_48[0x29];
    u8 unk_71;
    u8 pad_72[0x28];
    s8 unk_9A;
} S_80172628_0;   /* hold_arg0 in func_80172628 */

s32 func_80172628(void *arg0, M2C_UNK arg1, M2C_UNK arg2, s32 arg3) {
    s16 temp_v0;
    register s32 var_v0 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    M2C_UNK hold_arg1 = arg1;
    M2C_UNK hold_arg2 = arg2;
    register s32 hold_arg3 ASM_REG("$19") = arg3;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    void *hold_arg0 = arg0;

    var_v0 = func_800ADDA0(hold_arg1, hold_arg2, hold_arg0, 3, 6, hold_arg0 + 0x9C);
    var_v0 <<= 0x10;
    temp_v0 = var_v0 >> 0x10;
    {
    var_v0 = 0;
    if (temp_v0 < 0) {
        goto done;
    }
    if ((hold_arg3 << 0x10) != 0) {
        goto call_state;
    }
    ASM_KEEP(hold_arg3);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    if (temp_v0 == 1) {
        goto type_one;
    }
    if (temp_v0 >= 2) {
        goto type_ge_two;
    }
    if (temp_v0 == 0) {
        goto type_zero;
    }
    goto reset_state;

type_ge_two:
    if (temp_v0 == 2) {
        goto call_state;
    }
    goto reset_state;

type_zero:
    ((S_80172628_0 *)hold_arg0)->unk_9A = 0xE;
    func_800A9A0C(hold_arg0);
    var_v0 = 0;
    goto done;

call_state:
    func_80171C34(hold_arg0, hold_arg1, hold_arg2, hold_arg0);
    ASM_KEEP(hold_arg1);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(hold_arg2);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    var_v0 = 0;
    goto done;

type_one:
    ((S_80172628_0 *)hold_arg0)->unk_71 = (u8) (((S_80172628_0 *)hold_arg0)->unk_71 & 0x7F);
    if ((func_800A2BDC(hold_arg0) << 0x10) != 0) {
        goto clear_state;
    }
reset_state:
    ((S_80172628_0 *)hold_arg0)->unk_71 = (u8) (((S_80172628_0 *)hold_arg0)->unk_71 & 0x7F);
    if ((D_80083462 & 8) == 0) {
        var_v0 = 1;
        goto done;
    }
clear_state:
    var_v0 = 0;
    ((S_80172628_0 *)hold_arg0)->unk_46 = (u16) (((S_80172628_0 *)hold_arg0)->unk_46 & 0x7FFF);
done:
    return var_v0;
    }
}

/* MECHANISM: The 0x80172714/0x8017274c words are true-space local joins,
   so shared labels replace the seed's phantom calls and preserve retail block order.
   Guarded arg pins fix s1/s2/s3/s0; a v0 return local fills both zero delay slots. */
