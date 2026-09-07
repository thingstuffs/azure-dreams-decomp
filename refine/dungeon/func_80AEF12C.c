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

/* Projects a point and queues a semitransparent pixel and its drawing mode. */
s32 func_80AEF12C(Input0 *object_data, Input1 *position_data) {
    u8 *object_bytes = (u8 *)object_data;
    u8 *position_bytes = (u8 *)position_data;

    {
        u8 *context_addr = (u8 *)&D_80083160;
        register u32 address_mask ASM_REG("$18") = 0x00FFFFFF;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        Context *context = D_80083160;
        u32 length_mask = 0xFF000000;
        register Scratch *scratch ASM_REG("$17") = (Scratch *)0x1F800000;   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        register u32 red ASM_REG("$3");   /* MATCH pin: keeps a statement from moving across a call/branch */
        register u32 green ASM_REG("$6");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        register u32 blue ASM_REG("$7");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        s32 zero_arg;
        register s32 mode_flag ASM_REG("$5");   /* MATCH pin: retail schedule: same instructions, different order without it */
        u32 color;
        u8 *prim;
        u32 texture_page;
        u8 *packet_start;
        void *linked_object;

        ASM_KEEP(object_bytes);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
        ASM_KEEP(context_addr);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        ASM_KEEP(length_mask);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        ASM_KEEP(scratch);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */

        packet_start = context->field_8D0;
        scratch->ot = (u32 *)((u8 *)context + 0xB0);
        scratch->next = packet_start;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
        scratch->x = *(volatile u16 *)(position_bytes + 2);
        prim = scratch->next;
        scratch->y = *(u16 *)(position_bytes + 6);
        scratch->z = *(u16 *)(position_bytes + 0xA);
        scratch->next = prim + 0xC;
        {
            void *position = &scratch->x;
            scratch->index = func_80065420(position, prim + 8,
                                           (u8 *)scratch + 0xD0,
                                           (u8 *)scratch + 0xD4);
        }

        if (scratch->index < 0x1E0U) {
            s32 pixel_command;

            zero_arg = 0;
            mode_flag = 1;
            ASM_KEEP_NV(zero_arg);   /* MATCH pin: keeps a statement from moving across a call/branch */
            color = *(u32 *)(object_bytes + 8);
            *(s8 *)(prim + 3) = 2;
            ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
            pixel_command = 0x6A;
            *(s32 *)(prim + 4) = color;
            red = *(volatile u8 *)(prim + 4);
            ASM_KEEP(red);   /* MATCH pin: keeps a statement from moving across a call/branch */
            green = *(volatile u8 *)(prim + 5);
            ASM_KEEP(green);   /* MATCH pin: retail register colouring depends on it */
            blue = *(volatile u8 *)(prim + 6);
            ASM_KEEP(blue);   /* MATCH pin: keeps a statement from moving across a call/branch */
            green = zero_arg;
            ASM_KEEP(green);   /* MATCH pin: retail register colouring depends on it */
            *(s8 *)(prim + 7) = pixel_command;

            *(u32 *)prim = (*(u32 *)prim & length_mask) |
                (scratch->ot[scratch->index] & address_mask);
            {
                register u32 pixel_ot_tag ASM_REG("$3");   /* MATCH pin: keeps a statement from moving across a call/branch */
                pixel_ot_tag = scratch->ot[scratch->index];
                scratch->ot[scratch->index] =
                    (pixel_ot_tag & length_mask) | ((u32)prim & address_mask);
            }

            prim = scratch->next;
            *(u8 **)((u8 *)scratch + 0x1C) = prim + 0xC;
            texture_page = func_80066460(zero_arg, mode_flag, green, zero_arg);
            {
                void *mode_prim = prim;

                mode_flag = 0;
                func_80067F20(mode_prim, mode_flag, mode_flag, texture_page & 0xFFFF, 0);
            }

            *(u32 *)prim = (*(u32 *)prim & length_mask) |
                (scratch->ot[scratch->index] & address_mask);
            {
                u32 mode_ot_tag;
                mode_ot_tag = scratch->ot[scratch->index];
                prim = (u8 *)((u32)prim & address_mask);
                scratch->ot[scratch->index] =
                    (mode_ot_tag & length_mask) | (u32)prim;
            }
        }

        linked_object = *(void **)(object_bytes - 8);
        if (linked_object != 0) {
            object_bytes = (u8 *)linked_object + 0x20;
            position_bytes = *(u8 **)((u8 *)linked_object + 8);
            ASM_KEEP(object_bytes);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
            ASM_KEEP(position_bytes);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            {
                register u32 scratch_addr ASM_REG("$17");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
                register u32 position_addr ASM_REG("$4");   /* MATCH pin: load-bearing for the whole function shape */
#ifdef NON_MATCHING
                scratch_addr = (u32)scratch;
#endif
                ASM_KEEP_NV(scratch_addr);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
                position_addr = scratch_addr + 4;
                ASM_TAILSLOT_PIN_TIED(position_addr);   /* MATCH pin: retail delay-slot contents depend on it */
            }
            func_80170984();
        }
        (*(Context **)context_addr)->field_8D0 = scratch->next;
        {
            register s32 return_zero ASM_REG("$0");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
#ifdef NON_MATCHING
            return_zero = 0;
#endif
            return return_zero;
        }
    }
}
