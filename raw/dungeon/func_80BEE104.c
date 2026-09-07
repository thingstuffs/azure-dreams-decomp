#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern s32 rand(void);
extern s32 func_80064584(s32);
extern s32 func_800644B8(s32);
extern void func_8003DB94(void *, void *, s32);
extern s32 func_801739E0(void);

extern u8 D_80045340;
extern u8 D_800DEC70[];
extern u8 D_80173738;

void func_80173904(
    s32 arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4, u16 arg5)
{
    register s32 product ASM_REG("$7");
    register s32 dispatch_result ASM_REG("$2");
    register s32 factor ASM_REG("$3");
    register s32 normalized ASM_REG("$16");
    register s32 work ASM_REG("$19");
    register s32 held_arg4 ASM_REG("$21");
    register void *held_arg1;
    register u16 held_arg5 ASM_REG("$23");
    void *display;
    register void *state ASM_REG("$17");
    void *object;
    register void *transform ASM_REG("$20");
    void *texture;
    register void *call_a0 ASM_REG("$4");
    register void *call_a1 ASM_REG("$5");
    register s32 call_a2 ASM_REG("$6");

    (void)arg0;
    (void)arg2;
    (void)arg3;
    held_arg4 = arg4;
    held_arg1 = arg1;
    call_a0 = (void *)0x212;
    held_arg5 = arg5;
    ASM_KEEP_NV(held_arg4);
    ASM_KEEP_NV(held_arg1);
    ASM_KEEP_NV(held_arg1);
    ASM_KEEP_NV(held_arg5);
    object = func_8003FC64((s32)call_a0);
    if (object != NULL) {
        work = held_arg4;
        ASM_KEEP(work);
        call_a0 = object;
        call_a1 = &D_80045340;
        ASM_KEEP_NV(call_a0);
        ASM_KEEP_NV(call_a1);
        state = (u8 *)object + 0x20;
        ASM_KEEP_NV(state);
        FIELD(state, s16, 0x1A) = 0x14;
        FIELD(state, s16, 0x20) = 0x14;
        FIELD(state, s16, 0x1E) = (s16)held_arg4;
        FIELD(object, void *, 0x10) = &D_80173738;
        func_8004491C(call_a0, call_a1);

        display = FIELD(object, void *, 0xC);
        FIELD(display, s16, 0x10) = 0x60;
        FIELD(display, u16, 0x14) |= 0xC;
        if (rand() & 1) {
            FIELD(display, u16, 0x14) |= 1;
        }

        transform = FIELD(object, void *, 8);
        FIELD(state, s32, 0x40) = FIELD(held_arg1, s32, 0);
        dispatch_result = FIELD(held_arg1, s32, 4);
        ASM_KEEP_NV(dispatch_result);
        FIELD(state, s32, 0x44) = dispatch_result;
        dispatch_result = held_arg4 << 16;
        ASM_TAILSLOT_PIN(dispatch_result);
        dispatch_result = func_801739E0();
        do {
            work = dispatch_result;
            ASM_KEEP_NV(dispatch_result);
            dispatch_result = (s16)dispatch_result;
            if (dispatch_result < 0x1001) {
                break;
            }
            dispatch_result = work - 0x1000;
        } while (1);

        normalized = (s16)work;
        dispatch_result = func_80064584(normalized);
        factor = FIELD(state, s16, 0x20);
        product = factor * dispatch_result;
        dispatch_result = FIELD(state, s32, 0x40);
        factor = product << 4;
        dispatch_result += factor;
        FIELD(transform, s32, 0) = dispatch_result;
        dispatch_result = func_800644B8(normalized);
        factor = FIELD(state, s16, 0x20);
        product = factor * dispatch_result;
        texture = D_800DEC70;
        dispatch_result = FIELD(state, s32, 0x44);
        factor = product << 4;
        dispatch_result += factor;
        FIELD(transform, s32, 4) = dispatch_result;
        FIELD(transform, u16, 0xA) = FIELD(held_arg1, u16, 0xA) + held_arg5;

        display = FIELD(object, void *, 0xC);
        FIELD(display, s16, 0x1E) = 0x1000;
        FIELD(display, s16, 0x1C) = 0x1000;
        ASM_SCHED_BARRIER();
        dispatch_result = 0x40;
        ASM_KEEP(dispatch_result);
        FIELD(display, u8, 0xC) = dispatch_result;
        ASM_SCHED_BARRIER();
        factor = dispatch_result;
        ASM_KEEP_NV(factor);
        FIELD(display, u8, 0xE) = dispatch_result;
        dispatch_result = 0xC0;
        FIELD(display, u8, 0xD) = dispatch_result;
        FIELD(state, u8, 0) = factor;
        dispatch_result = FIELD(display, u8, 0xD);
        ASM_SCHED_BARRIER();
        call_a2 = 0;
        ASM_KEEP_NV(call_a2);
        FIELD(state, u8, 1) = dispatch_result;
        dispatch_result = FIELD(display, u8, 0xE);
        ASM_SCHED_BARRIER();
        call_a0 = display;
        ASM_KEEP_NV(call_a0);
        FIELD(state, u8, 2) = dispatch_result;
        func_8003DB94(call_a0, texture, call_a2);
        FIELD(display, s16, 0x12) = 0x7DCF;
        FIELD(display, u16, 0x14) |= 0x100;
    }
}

extern s32 func_801739E0(void) __attribute__((noreturn));
