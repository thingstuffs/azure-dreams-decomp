#include "common.h"

typedef struct {
    u8 pad[0x8D0];
    u8 *field_8D0;
} Context;

typedef struct {
    u8 pad[8];
    u32 field_8;
} Input0;

typedef struct {
    u8 pad0[2];
    u16 field_2;
    u8 pad4[2];
    u16 field_6;
    u8 pad8[2];
    u16 field_A;
} Input1;

typedef struct {
    u8 pad0[4];
    u16 x;
    u16 y;
    u16 z;
    u8 pad0A[0x12];
    u8 *volatile next;
    u8 pad20[4];
    u32 *ot;
    u8 pad28[0xA8];
    u8 padD0[0x30];
    u32 index;
} Scratch;

extern u32 func_80065420(void *, void *, void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, s32, s32);
extern void func_80170984(void) __attribute__((noreturn));
extern Context *D_80083160;

s32 func_80AEF12C(Input0 *arg0_in, Input1 *arg1_in) {
    u8 *obj = (u8 *)arg0_in;
    u8 *input = (u8 *)arg1_in;

    {
    u8 *global_addr = (u8 *)&D_80083160;
    register u32 low_mask ASM_REG("$18") = 0x00FFFFFF;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    Context *state = D_80083160;
    u32 high_mask = 0xFF000000;
    register Scratch *scratch ASM_REG("$17") = (Scratch *)0x1F800000;   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    register u32 byte4 ASM_REG("$3");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register u32 byte5 ASM_REG("$6");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    register u32 byte6 ASM_REG("$7");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    s32 zero_arg;
    register s32 one_arg ASM_REG("$5");   /* MATCH pin: retail schedule: same instructions, different order without it */
    u32 temp_arg0;
    u8 *prim;
    u32 value;
    u8 *initial_next;
    void *previous;

    ASM_KEEP(obj);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    ASM_KEEP(global_addr);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    ASM_KEEP(high_mask);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    ASM_KEEP(scratch);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */

    initial_next = state->field_8D0;
    scratch->ot = (u32 *)((u8 *)state + 0xB0);
    scratch->next = initial_next;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    scratch->x = *(volatile u16 *)(input + 2);
    prim = scratch->next;
    scratch->y = *(u16 *)(input + 6);
    scratch->z = *(u16 *)(input + 0xA);
    scratch->next = prim + 0xC;
    {
        void *setup_arg = &scratch->x;
        scratch->index = func_80065420(setup_arg, prim + 8,
                                       (u8 *)scratch + 0xD0,
                                       (u8 *)scratch + 0xD4);
    }

    if (scratch->index < 0x1E0U) {
        s32 command;

        zero_arg = 0;
        one_arg = 1;
        ASM_KEEP_NV(zero_arg);   /* MATCH pin: keeps a statement from moving across a call/branch */
        temp_arg0 = *(u32 *)(obj + 8);
        *(s8 *)(prim + 3) = 2;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
        command = 0x6A;
        *(s32 *)(prim + 4) = temp_arg0;
        byte4 = *(volatile u8 *)(prim + 4);
        ASM_KEEP(byte4);   /* MATCH pin: keeps a statement from moving across a call/branch */
        byte5 = *(volatile u8 *)(prim + 5);
        ASM_KEEP(byte5);   /* MATCH pin: retail register colouring depends on it */
        byte6 = *(volatile u8 *)(prim + 6);
        ASM_KEEP(byte6);   /* MATCH pin: keeps a statement from moving across a call/branch */
        byte5 = zero_arg;
        ASM_KEEP(byte5);   /* MATCH pin: retail register colouring depends on it */
        *(s8 *)(prim + 7) = command;

        *(u32 *)prim = (*(u32 *)prim & high_mask) |
            (scratch->ot[scratch->index] & low_mask);
        {
            register u32 ot_word ASM_REG("$3");   /* MATCH pin: keeps a statement from moving across a call/branch */
            ot_word = scratch->ot[scratch->index];
            scratch->ot[scratch->index] =
                (ot_word & high_mask) | ((u32)prim & low_mask);
        }

        prim = scratch->next;
        *(u8 **)((u8 *)scratch + 0x1C) = prim + 0xC;
        value = func_80066460(zero_arg, one_arg, byte5, zero_arg);
        {
        void *draw_prim = prim;

        one_arg = 0;
        func_80067F20(draw_prim, one_arg, one_arg, value & 0xFFFF, 0);
        }

        *(u32 *)prim = (*(u32 *)prim & high_mask) |
            (scratch->ot[scratch->index] & low_mask);
        {
            u32 ot_word2;
            ot_word2 = scratch->ot[scratch->index];
            prim = (u8 *)((u32)prim & low_mask);
            scratch->ot[scratch->index] =
                (ot_word2 & high_mask) | (u32)prim;
        }
    }

    previous = *(void **)(obj - 8);
    if (previous != 0) {
        obj = (u8 *)previous + 0x20;
        input = *(u8 **)((u8 *)previous + 8);
        ASM_KEEP(obj);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        ASM_KEEP(input);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        {
            register u32 tail_base ASM_REG("$17");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
            register u32 tail_arg ASM_REG("$4");   /* MATCH pin: load-bearing for the whole function shape */
#ifdef NON_MATCHING
            tail_base = (u32)scratch;
#endif
            ASM_KEEP_NV(tail_base);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
            tail_arg = tail_base + 4;
            ASM_TAILSLOT_PIN_TIED(tail_arg);   /* MATCH pin: retail delay-slot contents depend on it */
        }
        func_80170984();
    }
    (*(Context **)global_addr)->field_8D0 = scratch->next;
    {
        register s32 hard_zero ASM_REG("$0");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
#ifdef NON_MATCHING
        hard_zero = 0;
#endif
        return hard_zero;
    }
    }
}
