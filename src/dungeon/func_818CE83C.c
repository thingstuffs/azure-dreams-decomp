/* func_8002403C (dungeon, foff 0x18EE83C, 592 B) -- true base 0x8002403C by bank law
 * (bank 0x18EA800 -> 0x80020000, delta 0x7E735800, same delta as the proven region
 * leaf_18efb74_truebase_80025374 in this bank).  The retail `j 0x80024094` at word 132
 * is this function's OWN loop head (word 22): reorg steals `move a0,s1` from the target
 * thread into the j delay slot and retargets the jump one word past the label.  Written
 * as an ordinary loop it needs no fake extern callee, no census entry and no maspsx
 * name table: gcc emits `j $Lloop` itself and the word links to 0x08009025 at the true base.
 * Stock 2.7.2-cdk -O2 -G0, as_flags container default --fill-shadowed-return-delay.
 * Landing route (codegen_nudges §7.45): rowbase record for [0x18EE83C,0x18EEA8C) delta
 * 0x7E735800 -> rowbase.py promote -> rowbase_rename_reverify.py --execute (TU then
 * defines func_8002403C) -> overlay_land_function.
 */
#include "common.h"


extern u8 D_80083160[];

extern s32 func_80065420(void *, void *, void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, s32, s32);


typedef struct S_8002403C_0 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_8002403C_0;   /* state in func_8002403C */

typedef struct S_8002403C_1 {
    volatile u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u8 pad_06[0x12];
    u8 * unk_18;
    u8 pad_1C[0x4];
    union { u8 * p; u32 * p2; } unk_20;   /* accessed as both */
    u8 pad_24[0x9C];
    u32 unk_C0;
} S_8002403C_1;   /* scratch in func_8002403C */

typedef struct S_8002403C_2 {
    u8 pad_00[0x2];
    volatile u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8002403C_2;   /* input in func_8002403C */

typedef struct S_8002403C_3 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_00;   /* overlapping accesses */
    union { struct { u32 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; struct { u8 pad[0x3]; u8 v; } at03; } unk_04;   /* overlapping accesses */
} S_8002403C_3;   /* packet in func_8002403C */

typedef struct S_8002403C_4_pre {
    void * unk_00;
    u8 pad_04[0x4];
} S_8002403C_4_pre;   /* the 0x8 bytes before node in func_8002403C, addressed as node[-1] */

typedef struct S_8002403C_4 {
    u8 pad_00[0x8];
    volatile u32 unk_08;
    u8 pad_0C[0x26];
    s16 unk_32;
} S_8002403C_4;   /* node in func_8002403C */

typedef struct S_8002403C_5 {
    u8 pad_00[0x8];
    u8 * unk_08;
} S_8002403C_5;   /* previous in func_8002403C */

typedef struct S_8002403C_6 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_8002403C_6;   /* final_state in func_8002403C */

/* Project linked nodes and enqueue shaded point primitives with their draw modes. */
s32 func_8002403C(void *start_node, void *start_coords)
{
    register u8 **state_ptr;
    register u8 *scratch;
    register u8 *render_state;
    register u8 *final_state;
    register u8 *packet_end;
    register u8 *packet;
    register u8 *node;
    register u8 *coords;
    register void *prev_entry;
    u32 depth_index;
    u16 coord_x;
    register u32 addr_mask ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register u32 length_mask;

    node = start_node;
    coords = start_coords;
    state_ptr = (u8 **)D_80083160;
    addr_mask = 0x00FFFFFF;
    render_state = *(u8 **)D_80083160;
    length_mask = 0xFF000000;
    scratch = (u8 *)0x1F800000;

    *(u8 * volatile *)(scratch + 0x18) = ((S_8002403C_0 *)render_state)->unk_8D0;
    ((S_8002403C_1 *)scratch)->unk_20.p = render_state + 0xB0;

    for (;;) {
        coord_x = ((S_8002403C_2 *)coords)->unk_02;
        packet = *(u8 * volatile *)(scratch + 0x18);
        ((S_8002403C_1 *)scratch)->unk_00 = coord_x;
        ((S_8002403C_1 *)scratch)->unk_02 = ((S_8002403C_2 *)coords)->unk_06;
        ((S_8002403C_1 *)scratch)->unk_04 = ((S_8002403C_2 *)coords)->unk_0A;
        *(u8 * volatile *)(scratch + 0x18) = packet + 0xC;

        depth_index = func_80065420(scratch, packet + 8, scratch + 0x90,
                             scratch + 0x94);
        ((S_8002403C_1 *)scratch)->unk_C0 = depth_index;

        if (depth_index < 0x1E0) {
            register s32 color_or_tpage;
            s32 texture_depth;
            register s32 blend_mode ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            register s32 page_x;
            s32 opcode;

            ((S_8002403C_3 *)packet)->unk_04.at00.v = ((S_8002403C_4 *)node)->unk_08;
            color_or_tpage = ((S_8002403C_3 *)packet)->unk_04.at00u.v * ((S_8002403C_4 *)node)->unk_32;
            if (color_or_tpage < 0) {
                color_or_tpage += 0xFF;
            }
            ((S_8002403C_3 *)packet)->unk_04.at00u.v = color_or_tpage >> 8;

            color_or_tpage = ((S_8002403C_3 *)packet)->unk_04.at01.v * ((S_8002403C_4 *)node)->unk_32;
            if (color_or_tpage < 0) {
                color_or_tpage += 0xFF;
            }
            ((S_8002403C_3 *)packet)->unk_04.at01.v = color_or_tpage >> 8;

            color_or_tpage = ((S_8002403C_3 *)packet)->unk_04.at02.v * ((S_8002403C_4 *)node)->unk_32;
            if (color_or_tpage < 0) {
                color_or_tpage += 0xFF;
                texture_depth = 0;
            } else {
                texture_depth = 0;
            }
            blend_mode = 1;
            ((S_8002403C_3 *)packet)->unk_04.at02.v = color_or_tpage >> 8;
            ((S_8002403C_3 *)packet)->unk_00.at03.v = 2;
            opcode = 0x6A;
            ASM_SET(page_x);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            page_x = texture_depth;
            ASM_KEEP_DEP_NV(page_x, opcode);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            ((S_8002403C_3 *)packet)->unk_04.at03.v = opcode;

            ((S_8002403C_3 *)packet)->unk_00.at00.v =
                (((S_8002403C_3 *)packet)->unk_00.at00.v & length_mask) |
                ((*(u32 *)((u8 *)(((S_8002403C_1 *)scratch)->unk_20.p2) + (((S_8002403C_1 *)scratch)->unk_C0 * 4))) & addr_mask);
            {
                register u32 *ot_entry ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                register u32 ot_tag ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                u32 packet_addr;

                ot_entry = (u32 *)(((S_8002403C_1 *)scratch)->unk_C0 << 2);
                ot_entry = (u32 *)((u32)ot_entry +
                                (u32)((S_8002403C_1 *)scratch)->unk_20.p2);
                ot_tag = *ot_entry;
                packet_addr = (u32)packet & addr_mask;
                ot_tag = (ot_tag & length_mask) | packet_addr;
                *ot_entry = ot_tag;
            }

            packet = *(u8 * volatile *)(scratch + 0x18);
            ((S_8002403C_1 *)scratch)->unk_18 = packet + 0xC;
            color_or_tpage = func_80066460(texture_depth, blend_mode, page_x, texture_depth);
            func_80067F20(packet, 0, 0, (u16)color_or_tpage, 0);

            ((S_8002403C_3 *)packet)->unk_00.at00.v =
                (((S_8002403C_3 *)packet)->unk_00.at00.v & length_mask) |
                ((*(u32 *)((u8 *)(((S_8002403C_1 *)scratch)->unk_20.p2) + (((S_8002403C_1 *)scratch)->unk_C0 * 4))) & addr_mask);
            packet = (u8 *)((u32)packet & addr_mask);
            (*(u32 *)((u8 *)(((S_8002403C_1 *)scratch)->unk_20.p2) + (((S_8002403C_1 *)scratch)->unk_C0 * 4))) =
                ((*(u32 *)((u8 *)(((S_8002403C_1 *)scratch)->unk_20.p2) + (((S_8002403C_1 *)scratch)->unk_C0 * 4))) & length_mask) |
                (u32)packet;
        }

        prev_entry = ((S_8002403C_4_pre *)node)[-1].unk_00;
        node = (u8 *)prev_entry + 0x20;
        if (prev_entry == 0) {
            break;
        }
        coords = ((S_8002403C_5 *)prev_entry)->unk_08;
    }

    final_state = *state_ptr;
    packet_end = ((S_8002403C_1 *)scratch)->unk_18;
    ((S_8002403C_6 *)final_state)->unk_8D0 = packet_end;
    return 0;
}
