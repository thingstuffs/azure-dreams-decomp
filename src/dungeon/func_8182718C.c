#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

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



extern int D_800814A0[];
extern u8 D_80045340[];
extern void func_80024A7C(void) __attribute__((noreturn));

/* Advance a timed two-state action and propagate target status flags. */
void func_8182718C(void *state_data, void *unused, Rec_D_80082E80 *target) {
    s16 state;
    u16 timer;
    u16 ticks_left;
    S_8182718C_1 *linked_data;

    linked_data = ((S_8182718C_0 *)state_data)->unk_00;
    linked_data->unk_52 = (s16) (linked_data->unk_52 | 0x8000);
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
        u16 old_state;
        u16 interval;

        ticks_left = ((S_8182718C_0 *)state_data)->unk_48 - 1;
        ((S_8182718C_0 *)state_data)->unk_48 = ticks_left;
        if ((ticks_left << 0x10) <= 0) {
            func_8004491C(state_data - 0x20, D_80045340);
            old_state = ((S_8182718C_0 *)state_data)->unk_4C.u;
            interval = ((S_8182718C_0 *)state_data)->unk_4E;
            ((S_8182718C_0 *)state_data)->unk_48 = interval;
            ((S_8182718C_0 *)state_data)->unk_4C.u = (u16) (old_state + 1);
            func_80024A7C();
        }
        goto done;
    }

one_state:
    {
        timer = ((S_8182718C_0 *)state_data)->unk_48;
        ((S_8182718C_0 *)state_data)->unk_48 = (u16) (timer - 1);
        if ((timer << 0x10) <= 0) {
            func_800478B8(target);
            ((S_8182718C_0 *)state_data)->unk_48 = (u16) ((S_8182718C_0 *)state_data)->unk_4E;
        }
        if (target->unk_14.at00_u16.v & 0x6000) {
            ((S_8182718C_0_pre *)state_data)[-1].unk_00 = (u16) (((S_8182718C_0_pre *)state_data)[-1].unk_00 | 0x8000);
            D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
        }
    }

done:
    ;
}
