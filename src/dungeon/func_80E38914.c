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

/* Updates object state and flags according to the state handler result. */
s32 func_80172114(void *object, M2C_UNK state_input_a, M2C_UNK state_input_b) {
    M2C_UNK saved_input_a;
    M2C_UNK saved_input_b;
    void *saved_object;
    register s32 call_result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 state;

    saved_input_a = state_input_a;
    saved_input_b = state_input_b;
    saved_object = object;
    call_result = func_800ADDA0(saved_input_a, saved_input_b, saved_object, 2, 4, saved_object + 0x9C);
    ASM_KEEP(saved_input_a);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(saved_input_b);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
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
    ((S_80172114_0 *)saved_object)->unk_9A = 0xE;
    func_800A9A0C(saved_object);
    return 0;

state_two:
    func_801716A4(saved_object, saved_input_a, saved_input_b, saved_object);
    return 0;

state_one:
    ((S_80172114_0 *)saved_object)->unk_71 =
        (u8) (((S_80172114_0 *)saved_object)->unk_71 & 0x7F);
    if ((func_800A2BDC(saved_object) << 0x10) != 0) {
        goto clear_field;
    }

common_update:
    ((S_80172114_0 *)saved_object)->unk_71 =
        (u8) (((S_80172114_0 *)saved_object)->unk_71 & 0x7F);
    if ((D_80083462 & 8) == 0) {
        return 1;
    }

clear_field:
    call_result = 0;
    ((S_80172114_0 *)saved_object)->unk_46 =
        (u16) (((S_80172114_0 *)saved_object)->unk_46 & 0x7FFF);

negative_return:
    return call_result;
}
