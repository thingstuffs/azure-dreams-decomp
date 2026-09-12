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

/* Projects a position and links its render packets into the ordering table. */
s32 FUNC_80AE9000_BODY(Input0 *render_data, Input1 *position_data) {
    u8 *render_bytes = (u8 *)render_data;
    u8 *position_bytes = (u8 *)position_data;
    u8 *context_addr = D_80083160;
    register u32 addr_mask ASM_REG("$18") = 0x00FFFFFF;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    Context *state = *(Context **)D_80083160;
    u32 length_mask = 0xFF000000;
    register Scratch *scratch ASM_REG("$17") = (Scratch *)0x1F800000;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register u32 red ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    u8 green;
    register u32 blue ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register s32 pinned_zero ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register s32 pinned_one ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    u8 *packet;
    u32 draw_mode;
    u8 *packet_start;
    void *linked_node;

    ASM_KEEP(render_bytes);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(context_addr);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(length_mask);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(scratch);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

    packet_start = state->field_8D0;
    scratch->ot = (u32 *)((u8 *)state + 0xB0);
    scratch->next = packet_start;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    scratch->x = *(volatile u16 *)(position_bytes + 2);
    packet = scratch->next;
    scratch->y = *(u16 *)(position_bytes + 6);
    scratch->z = *(u16 *)(position_bytes + 0xA);
    scratch->next = packet + 0xC;
    {
        void *position = &scratch->x;
        scratch->index = func_80065420(position, packet + 8,
                                       (u8 *)scratch + 0xD0,
                                       (u8 *)scratch + 0xD4);
    }

    if (scratch->index < 0x1E0U) {
        s32 packet_code;

        pinned_zero = 0;
        pinned_one = 1;
        packet_start = *(u32 *)(render_bytes + 8);
        *(s8 *)(packet + 3) = 2;
        packet_code = 0x6A;
        *(s32 *)(packet + 4) = packet_start;
        red = *(volatile u8 *)(packet + 4);
        ASM_KEEP(red);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        green = *(volatile u8 *)(packet + 5);
           /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        blue = *(volatile u8 *)(packet + 6);
        ASM_KEEP(blue);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        green = pinned_zero;
        *(s8 *)(packet + 7) = packet_code;

        *(u32 *)packet = (*(u32 *)packet & length_mask) |
            (scratch->ot[scratch->index] & addr_mask);
        {
            register u32 ot_tag ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
            ot_tag = scratch->ot[scratch->index];
            scratch->ot[scratch->index] =
                (ot_tag & length_mask) | ((u32)packet & addr_mask);
        }

        packet = scratch->next;
        *(u8 **)((u8 *)scratch + 0x1C) = packet + 0xC;
        draw_mode = func_80066460(0, 1, green, 0);
        func_80067F20(packet, 0, 0, draw_mode & 0xFFFF, 0);

        *(u32 *)packet = (*(u32 *)packet & length_mask) |
            (scratch->ot[scratch->index] & addr_mask);
        {
            u32 ot_tag;
            ot_tag = scratch->ot[scratch->index];
            packet = (u8 *)((u32)packet & addr_mask);
            scratch->ot[scratch->index] =
                (ot_tag & length_mask) | (u32)packet;
        }
    }

    linked_node = *(void **)(render_bytes - 8);
    if (linked_node != 0) {
        render_bytes = (u8 *)linked_node + 0x20;
        position_bytes = *(u8 **)((u8 *)linked_node + 8);
        ASM_KEEP(render_bytes);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(position_bytes);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        {
            register u32 scratch_addr ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            register u32 position_addr ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
#ifdef NON_MATCHING
            scratch_addr = (u32)scratch;
#endif
            ASM_KEEP_NV(scratch_addr);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            position_addr = scratch_addr + 4;
            ASM_TAILSLOT_PIN(position_addr);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        }
        func_8014C8FC();
    }
    (*(Context **)context_addr)->field_8D0 = scratch->next;
    {
        register s32 return_zero ASM_REG("$0");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
#ifdef NON_MATCHING
        return_zero = 0;
#endif
        return return_zero;
    }
}
