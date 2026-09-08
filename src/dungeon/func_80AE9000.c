/* cfail-repair: extent span with the matched DUNGEON packet idiom */
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
extern void func_8014C8FC(void) __attribute__((noreturn));
extern u8 D_80083160[];

#ifdef __mips__
static const u32 func_80AE9000_extent_prefix[41]
    __asm__("func_80AE9000")
    __attribute__((used, section(".text.func_80AE9000"), aligned(4))) = {
    0x8014D158, 0x8014D320, 0x8014DB54, 0x8014DB54,
    0x8014DB54, 0x8014DB80, 0x8014DB00, 0x8014DB00,
    0x8014DB00, 0x8014DAAC, 0x8014DAE4, 0x8014DB80,
    0x8014DB80, 0x8014DB44, 0x8014F020, 0x8014F070,
    0x8014F0E4, 0x8014F158, 0x8014F1D0, 0x00000000,
    0x8014F29C, 0x8014F4CC, 0x8014F514, 0x8014F744,
    0x8014F7CC, 0x00000000, 0x8014F34C, 0x8014F344,
    0x8014F33C, 0x8014F354, 0x8014F2F8, 0x8014F2F0,
    0x8014F2E8, 0x00000001, 0x00010001, 0x00010000,
    0x0001FFFF, 0x0000FFFF, 0xFFFFFFFF, 0xFFFF0000,
    0xFFFF0001,
};
__asm__(".globl func_80AE9000\n"
        ".size func_80AE9000, 644");
#define FUNC_80AE9000_BODY func_80AE90A4
#else
#define FUNC_80AE9000_BODY func_80AE9000
#endif

s32 FUNC_80AE9000_BODY(Input0 *arg0_in, Input1 *arg1_in) {
    u8 *obj = (u8 *)arg0_in;
    u8 *input = (u8 *)arg1_in;
    u8 *global_addr = D_80083160;
    register u32 low_mask ASM_REG("$18") = 0x00FFFFFF;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    Context *state = *(Context **)D_80083160;
    u32 high_mask = 0xFF000000;
    register Scratch *scratch ASM_REG("$17") = (Scratch *)0x1F800000;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register u32 byte4 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    register u32 byte5 ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register u32 byte6 ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register s32 zero_arg ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register s32 one_arg ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register u32 temp_arg0 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    u8 *prim;
    u32 value;
    u8 *initial_next;
    void *previous;

    ASM_KEEP(obj);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(global_addr);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(high_mask);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(scratch);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

    initial_next = state->field_8D0;
    scratch->ot = (u32 *)((u8 *)state + 0xB0);
    scratch->next = initial_next;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
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
        temp_arg0 = *(u32 *)(obj + 8);
        *(s8 *)(prim + 3) = 2;
        command = 0x6A;
        *(s32 *)(prim + 4) = temp_arg0;
        byte4 = *(volatile u8 *)(prim + 4);
        ASM_KEEP(byte4);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        byte5 = *(volatile u8 *)(prim + 5);
        ASM_KEEP(byte5);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        byte6 = *(volatile u8 *)(prim + 6);
        ASM_KEEP(byte6);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        byte5 = zero_arg;
        *(s8 *)(prim + 7) = command;

        *(u32 *)prim = (*(u32 *)prim & high_mask) |
            (scratch->ot[scratch->index] & low_mask);
        {
            register u32 ot_word ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
            ot_word = scratch->ot[scratch->index];
            scratch->ot[scratch->index] =
                (ot_word & high_mask) | ((u32)prim & low_mask);
        }

        prim = scratch->next;
        *(u8 **)((u8 *)scratch + 0x1C) = prim + 0xC;
        value = func_80066460(0, 1, byte5, 0);
        func_80067F20(prim, 0, 0, value & 0xFFFF, 0);

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
        ASM_KEEP(obj);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(input);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        {
            register u32 tail_base ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            register u32 tail_arg ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
#ifdef NON_MATCHING
            tail_base = (u32)scratch;
#endif
            ASM_KEEP_NV(tail_base);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            tail_arg = tail_base + 4;
            ASM_TAILSLOT_PIN(tail_arg);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        }
        func_8014C8FC();
    }
    (*(Context **)global_addr)->field_8D0 = scratch->next;
    {
        register s32 hard_zero ASM_REG("$0");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
#ifdef NON_MATCHING
        hard_zero = 0;
#endif
        return hard_zero;
    }
}
