#include "common.h"
#include "m2c_compat.h"

typedef struct S_8182718C_0_pre {
    u16 flags;
} S_8182718C_0_pre;   /* the 0x2 bytes before effect in func_8182718C, addressed as effect[-1] */

typedef struct S_8182718C_0 {
    void *linked_entity;
    u8 pad_04[0x44];
    u16 timer;
    u8 pad_4A[0x2];
    union { s16 s; u16 u; } state;   /* accessed as both */
    u16 timer_reload;
} S_8182718C_0;   /* effect in func_8182718C */

typedef struct S_8182718C_1 {
    u8 pad_00[0x52];
    u16 flags;
} S_8182718C_1;   /* linked_entity in func_8182718C */

typedef struct S_8182718C_2 {
    u8 pad_00[0x14];
    u16 flags;
} S_8182718C_2;   /* target in func_8182718C */


extern int D_800814A0[];
extern u8 D_80045340[];
extern void func_80024A7C(void) __attribute__((noreturn));

// Advances a two-state timed effect and propagates its active flag.
void func_8182718C(void *effect, void *unused, S_8182718C_2 *target) {
    s16 state;
    u16 previous_timer;
    u16 decremented_timer;
    S_8182718C_1 *linked_entity;

    linked_entity = ((S_8182718C_0 *)effect)->linked_entity;
    linked_entity->flags = (s16) (linked_entity->flags | 0x8000);
    state = ((S_8182718C_0 *)effect)->state.s;
    if (state == 0) {
        goto zero_state;
    }
    if (state == 1) {
        goto one_state;
    }
    func_80024A7C();

zero_state:
    {
        u16 previous_state;
        u16 reload_value;

        decremented_timer = ((S_8182718C_0 *)effect)->timer - 1;
        ((S_8182718C_0 *)effect)->timer = decremented_timer;
        if ((decremented_timer << 0x10) <= 0) {
            func_8004491C(effect - 0x20, D_80045340);
            previous_state = ((S_8182718C_0 *)effect)->state.u;
            reload_value = ((S_8182718C_0 *)effect)->timer_reload;
            ((S_8182718C_0 *)effect)->timer = reload_value;
            ((S_8182718C_0 *)effect)->state.u = (u16) (previous_state + 1);
            func_80024A7C();
        }
        goto done;
    }

one_state:
    {
        previous_timer = ((S_8182718C_0 *)effect)->timer;
        ((S_8182718C_0 *)effect)->timer = (u16) (previous_timer - 1);
        if ((previous_timer << 0x10) <= 0) {
            func_800478B8(target);
            ((S_8182718C_0 *)effect)->timer = (u16) ((S_8182718C_0 *)effect)->timer_reload;
        }
        if (target->flags & 0x6000) {
            ((S_8182718C_0_pre *)effect)[-1].flags = (u16) (((S_8182718C_0_pre *)effect)[-1].flags | 0x8000);
            D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
        }
    }

done:
    ;
}
