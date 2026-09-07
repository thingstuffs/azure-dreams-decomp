#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern void func_80021F18() __attribute__((noreturn));
extern void func_80022084() __attribute__((noreturn));
extern s32 func_800A2A18(void *, void *);
extern u32 D_80012D5C;
extern u8 D_800243F0[];
extern s32 D_80024438[];
extern s32 D_80024444[];

void func_80021E88(void *arg0, void *arg1, void *arg2) {
    s16 state;
    s32 value;
    s32 transition_value;
    register s32 one ASM_REG("$4");
    register s32 transition ASM_REG("$19");
    u16 flags;
    void *object;

    object = FIELD(arg0, void *, 4);
    transition = 0;
    if (FIELD(object, s16, 0x18) == 0) {
        FIELD(arg0, s16, 0) = 0;
    }
    if (D_80012D5C >= 100U) {
        if (func_800A2A18(D_800243F0, arg1) != 0) {
            transition = 1;
            ASM_TAILSLOT_PIN(transition);
            func_80021F18();
        }
        FIELD(arg2, s32, 8) = D_80024438[FIELD(arg0, s16, 0x54)];
    }

    one = 1;
    state = FIELD(arg0, s16, 0);
    if (state == one) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        return func_80022084(one);
    }
    ASM_SCHED_BARRIER();
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_3;
    }
    return func_80022084(one);

state_0:
    FIELD(arg1, s32, 8) += 0xFFF80000;
    if (FIELD(arg1, s32, 8) > 0) {
        goto done;
    }
    FIELD(arg1, s32, 8) = 0;
    FIELD(arg2, s32, 0xC) = 0x808080;
    FIELD(arg0, s16, 0) = one;
    func_80022084(one);

state_1:
    transition_value = transition;
    ASM_KEEP(transition_value);
    if (transition_value) {
        if (FIELD(FIELD(arg0, void *, 4), s16, 0x22) == 3) {
            FIELD(object, u16, 0x20) |= 1;
            FIELD(arg2, s32, 8) = D_80024444[FIELD(arg0, s16, 0x54)];
            FIELD(object, s16, 0x22) = FIELD(arg0, u16, 0x54);
        }
    }
    one = 3;
    if (FIELD(object, s16, 0x22) == one) {
        goto done;
    }
    if (FIELD(FIELD(arg0, void *, 4), s16, 0x22) == FIELD(arg0, s16, 0x54)) {
        FIELD(arg0, s16, 0) = one;
        func_80022084(one);
    }
    FIELD(arg0, s16, 0) = 2;
    func_80022084(one);

state_2:
    FIELD(arg1, s32, 8) += 0x80000;
    if (FIELD(arg1, s32, 8) > 0x3FFFFF) {
        FIELD(arg1, s32, 8) = 0x400000;
        func_80022084(0x80000);
    }
    goto done;

state_3:
    flags = FIELD(object, u16, 0x20);
    if (flags & 1) {
        FIELD(object, u16, 0x20) = flags | 1;
        FIELD(arg2, s32, 8) = D_80024444[FIELD(arg0, s16, 0x54)];
    }

done:
    return;
}
