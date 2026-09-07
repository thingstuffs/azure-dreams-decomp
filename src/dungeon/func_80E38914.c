#include "common.h"
#include "m2c_compat.h"

s32 func_800A2BDC();                          /* extern */
M2C_UNK func_800A9A0C();                      /* extern */
s32 func_800ADDA0(); /* extern */
M2C_UNK func_801716A4(); /* extern */
extern u16 D_80083462;

typedef struct S_80172114_0 {
    u8 pad_00[0x46];
    u16 unk_46;
    u8 pad_48[0x29];
    u8 unk_71;
    u8 pad_72[0x28];
    s8 unk_9A;
} S_80172114_0;   /* held_arg0 in func_80172114 */

s32 func_80172114(void *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    M2C_UNK held_arg1;
    M2C_UNK held_arg2;
    void *held_arg0;
    register s32 call_result ASM_REG("$2");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    s32 state;

    held_arg1 = arg1;
    held_arg2 = arg2;
    held_arg0 = arg0;
    call_result = func_800ADDA0(held_arg1, held_arg2, held_arg0, 2, 4, held_arg0 + 0x9C);
    ASM_KEEP(held_arg1);   /* MATCH pin: load-bearing for the whole function shape */
    ASM_KEEP(held_arg2);   /* MATCH pin: retail schedule: same instructions, different order without it */
    call_result <<= 16;
    state = call_result >> 16;
    call_result = 0;
    if (state < 0) {
        goto negative_return;
    }
    if (state == 1) {
        goto state_one;
    }
    if (state >= 2) {
        goto state_ge_two;
    }
    if (state == 0) {
        goto state_zero;
    }
    goto common_update;

state_ge_two:
    if (state == 2) {
        goto state_two;
    }

    goto common_update;

state_zero:
    ((S_80172114_0 *)held_arg0)->unk_9A = 0xE;
    func_800A9A0C(held_arg0);
    return 0;

state_two:
    func_801716A4(held_arg0, held_arg1, held_arg2, held_arg0);
    return 0;

state_one:
    ((S_80172114_0 *)held_arg0)->unk_71 =
        (u8) (((S_80172114_0 *)held_arg0)->unk_71 & 0x7F);
    if ((func_800A2BDC(held_arg0) << 0x10) != 0) {
        goto clear_field;
    }

common_update:
    ((S_80172114_0 *)held_arg0)->unk_71 =
        (u8) (((S_80172114_0 *)held_arg0)->unk_71 & 0x7F);
    if ((D_80083462 & 8) == 0) {
        return 1;
    }

clear_field:
    call_result = 0;
    ((S_80172114_0 *)held_arg0)->unk_46 =
        (u16) (((S_80172114_0 *)held_arg0)->unk_46 & 0x7FFF);

negative_return:
    return call_result;
}

/* MECHANISM: Fixed s1/s2/s0 argument roles reproduce the 0x28 prologue save order.
   The raw call result stays in v0, sign-extends into v1, then v0 becomes the zero edge value.
   Local true-space CFG labels merge the negative and clear-field paths at one epilogue. */
