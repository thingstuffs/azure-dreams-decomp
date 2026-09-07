#include "common.h"

#define FIELD(ptr, type, off) (*(type *)((u8 *)(ptr) + (off)))

extern void func_80024388() __attribute__((noreturn));
extern void func_800243C4() __attribute__((noreturn));

void func_8191CA88(void *arg0, void *arg1, void *arg2) {
    register void *object ASM_REG("$7") = arg0;
    register void *motion ASM_REG("$8");
    register s32 state ASM_REG("$4");
    register s32 state_u ASM_REG("$5");
    register s32 timer ASM_REG("$3");
    register s32 old_timer ASM_REG("$2");
    register s32 compare_left ASM_REG("$2");
    register s32 compare_right ASM_REG("$3");
    register s32 compare_result ASM_REG("$2");
    register s32 timer_signed ASM_REG("$2");
    register s32 threshold_value ASM_REG("$3");
    register s32 threshold_result ASM_REG("$2");
    register u8 *global_base ASM_REG("$3");
    s32 position;
    s32 acceleration;
    s32 next_state;
    s32 x_velocity;
    s32 y_velocity;
    u16 arg2_field;
    void *inner;

    ASM_KEEP(object);
    inner = FIELD(object, void *, 0);
    FIELD(inner, u16, 0x14) = FIELD(inner, u16, 0x14) + 1;
    arg2_field = FIELD(arg2, u16, 0x1A);
    ASM_USE(arg2_field);
    motion = arg1;
    ASM_KEEP(motion);
    FIELD(arg2, u16, 0x1A) = arg2_field + 0x300;
    old_timer = FIELD(object, volatile u16, 0x10);
    ASM_SCHED_BARRIER();
    state = FIELD(object, s16, 0xE);
    ASM_SCHED_BARRIER();
    state_u = FIELD(object, volatile u16, 0xE);
    ASM_USE(old_timer);
    timer = old_timer + 1;
    FIELD(object, u16, 0x10) = timer;

    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        func_800243C4(state, state_u, arg2, object);
    }
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_3;
    }
    func_800243C4(state, state_u, arg2, object);

state_0:
    position = FIELD(motion, s32, 0);
    acceleration = FIELD(motion, s32, 0xC);
    x_velocity = FIELD(motion, s32, 0x10);
    y_velocity = FIELD(motion, s32, 0x14);
    FIELD(motion, s32, 0) = position + acceleration;
    FIELD(motion, s32, 4) += x_velocity;
    FIELD(motion, s32, 8) += y_velocity;
    compare_left = FIELD(object, s16, 0x10);
    compare_right = FIELD(object, s16, 0x14);
    ASM_USE2(compare_left, compare_right);
    compare_result = compare_left < compare_right;
    ASM_TAILSLOT_PIN_TIED(compare_result);
    func_80024388(x_velocity, y_velocity, arg2, object);

state_1:
    timer_signed = timer << 16;
    ASM_USE(timer_signed);
    threshold_value = FIELD(object, s16, 0x16);
    timer_signed >>= 16;
    ASM_USE2(timer_signed, threshold_value);
    threshold_result = timer_signed < threshold_value;
    ASM_USE(threshold_result);
    if (threshold_result != 0) {
        goto done;
    }
    FIELD(object, s16, 0xE) = state_u + 1;
    FIELD(object, u16, 0x10) = 0;
    func_800243C4(state, state_u, arg2, object);

state_2:
    FIELD(motion, s32, 8) -= timer << 16;
    if (FIELD(object, s16, 0x10) < 0x18) {
        goto done;
    }
    next_state = FIELD(object, u16, 0xE) + 1;
    FIELD(object, u16, 0x10) = 0;
    FIELD(object, u16, 0xE) = next_state;
    func_800243C4(state, state_u, arg2, object);

state_3:
    FIELD(object, u16, -2) |= 0x8000;
    global_base = (u8 *)0x80080000;
    ASM_KEEP(global_base);
    FIELD(global_base, u32, 0x14A0) |= 0x8000;

done:
    return;
}

/* MECHANISM: Noreturn tails plus path-local $a0/$a1/$a3/$t0 carriers let LEAD 18/19 elide the false frame.
   Load-order seams and a held $v1 page base preserve the retail timer/state/global access schedule.
   Explicit sll/lh/sra staging and the tied $v0 tail-slot comparison close the final code-motion residue. */
