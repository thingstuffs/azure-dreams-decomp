#include "common.h"
#include "m2c_compat.h"

typedef struct S_8182718C_0_pre {
    u16 unk_00;
} S_8182718C_0_pre;   /* the 0x2 bytes before arg0 in func_8182718C, addressed as arg0[-1] */

typedef struct S_8182718C_0 {
    void * unk_00;
    u8 pad_04[0x44];
    u16 unk_48;
    u8 pad_4A[0x2];
    union { s16 s; u16 u; } unk_4C;   /* accessed as both */
    u16 unk_4E;
} S_8182718C_0;   /* arg0 in func_8182718C */

typedef struct S_8182718C_1 {
    u8 pad_00[0x52];
    u16 unk_52;
} S_8182718C_1;   /* temp_v1 in func_8182718C */

typedef struct S_8182718C_2 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_8182718C_2;   /* arg2 in func_8182718C */


extern int D_800814A0[];
extern u8 D_80045340[];
extern void func_80024A7C(void) __attribute__((noreturn));

/* Advance a two-state countdown, trigger timed actions, and propagate target flags. */
void func_8182718C(void *state_data, void *unused, S_8182718C_2 *target) {
    s16 state;
    u16 timer_before_decrement;
    u16 timer_after_decrement;
    S_8182718C_1 *linked_object;

    linked_object = ((S_8182718C_0 *)state_data)->unk_00;
    linked_object->unk_52 = (s16) (linked_object->unk_52 | 0x8000);
    state = ((S_8182718C_0 *)state_data)->unk_4C.s;
    if (state == 0) {
        goto zero_state;
    }
    if (state == 1) {
        goto one_state;
    }
    func_80024A7C();

zero_state:
    {
        u16 state_before_transition;
        u16 reload_ticks;

        timer_after_decrement = ((S_8182718C_0 *)state_data)->unk_48 - 1;
        ((S_8182718C_0 *)state_data)->unk_48 = timer_after_decrement;
        if ((timer_after_decrement << 0x10) <= 0) {
            func_8004491C(state_data - 0x20, D_80045340);
            state_before_transition = ((S_8182718C_0 *)state_data)->unk_4C.u;
            reload_ticks = ((S_8182718C_0 *)state_data)->unk_4E;
            ((S_8182718C_0 *)state_data)->unk_48 = reload_ticks;
            ((S_8182718C_0 *)state_data)->unk_4C.u = (u16) (state_before_transition + 1);
            func_80024A7C();
        }
        goto done;
    }

one_state:
    {
        timer_before_decrement = ((S_8182718C_0 *)state_data)->unk_48;
        ((S_8182718C_0 *)state_data)->unk_48 = (u16) (timer_before_decrement - 1);
        if ((timer_before_decrement << 0x10) <= 0) {
            func_800478B8(target);
            ((S_8182718C_0 *)state_data)->unk_48 = (u16) ((S_8182718C_0 *)state_data)->unk_4E;
        }
        if (target->unk_14 & 0x6000) {
            ((S_8182718C_0_pre *)state_data)[-1].unk_00 = (u16) (((S_8182718C_0_pre *)state_data)[-1].unk_00 | 0x8000);
            D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
        }
    }

done:
    ;
}
