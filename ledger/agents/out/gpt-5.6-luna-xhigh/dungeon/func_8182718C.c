#include "common.h"
#include "m2c_compat.h"

typedef struct S_8182718C_0_pre {
    u16 status_flags;
} S_8182718C_0_pre;   /* the 0x2 bytes before arg0 in func_8182718C, addressed as arg0[-1] */

typedef struct S_8182718C_0 {
    void * linked_state;
    u8 pad_04[0x44];
    u16 countdown;
    u8 pad_4A[0x2];
    union { s16 s; u16 u; } mode;   /* accessed as both */
    u16 reload_count;
} S_8182718C_0;   /* arg0 in func_8182718C */

typedef struct S_8182718C_1 {
    u8 pad_00[0x52];
    u16 status_flags;
} S_8182718C_1;   /* linked_state in func_8182718C */

typedef struct S_8182718C_2 {
    u8 pad_00[0x14];
    u16 input_flags;
} S_8182718C_2;   /* arg2 in func_8182718C */


extern int D_800814A0[];
extern u8 D_80045340[];
extern void func_80024A7C(void) __attribute__((noreturn));

/* Updates the linked state flags and advances the mode-specific countdown. */
void func_8182718C(void *state_record, void *unused_arg, S_8182718C_2 *input_state) {
    s16 mode;
    u16 countdown_before_decrement;
    u16 countdown_after_decrement;
    S_8182718C_1 *linked_state;

    linked_state = ((S_8182718C_0 *)state_record)->linked_state;
    linked_state->status_flags = (s16) (linked_state->status_flags | 0x8000);
    mode = ((S_8182718C_0 *)state_record)->mode.s;
    if (mode == 0) {
        goto zero_state;
    }
    if (mode == 1) {
        goto one_state;
    }
    func_80024A7C();

zero_state:
    {
        u16 mode_before_increment;
        u16 reload_count;

        countdown_after_decrement = ((S_8182718C_0 *)state_record)->countdown - 1;
        ((S_8182718C_0 *)state_record)->countdown = countdown_after_decrement;
        if ((countdown_after_decrement << 0x10) <= 0) {
            func_8004491C(state_record - 0x20, D_80045340);
            mode_before_increment = ((S_8182718C_0 *)state_record)->mode.u;
            reload_count = ((S_8182718C_0 *)state_record)->reload_count;
            ((S_8182718C_0 *)state_record)->countdown = reload_count;
            ((S_8182718C_0 *)state_record)->mode.u = (u16) (mode_before_increment + 1);
            func_80024A7C();
        }
        goto done;
    }

one_state:
    {
        countdown_before_decrement = ((S_8182718C_0 *)state_record)->countdown;
        ((S_8182718C_0 *)state_record)->countdown = (u16) (countdown_before_decrement - 1);
        if ((countdown_before_decrement << 0x10) <= 0) {
            func_800478B8(input_state);
            ((S_8182718C_0 *)state_record)->countdown = (u16) ((S_8182718C_0 *)state_record)->reload_count;
        }
        if (input_state->input_flags & 0x6000) {
            ((S_8182718C_0_pre *)state_record)[-1].status_flags = (u16) (((S_8182718C_0_pre *)state_record)[-1].status_flags | 0x8000);
            D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
        }
    }

done:
    ;
}
