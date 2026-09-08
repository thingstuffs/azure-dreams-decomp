#include "common.h"

typedef struct S_80173E94_0 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_80173E94_0;   /* state in func_80173E94 */

typedef struct S_80173E94_1 {
    volatile u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u8 pad_06[0x12];
    u8 * unk_18;
    u8 pad_1C[0x4];
    union { u8 * p; u32 * p2; } unk_20;   /* accessed as both */
    u8 pad_24[0x9C];
    u32 unk_C0;
} S_80173E94_1;   /* scratch in func_80173E94 */

typedef struct S_80173E94_2 {
    u8 pad_00[0x2];
    volatile u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80173E94_2;   /* input in func_80173E94 */

typedef struct S_80173E94_3 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_00;   /* overlapping accesses */
    union { struct { u32 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; struct { u8 pad[0x3]; u8 v; } at03; } unk_04;   /* overlapping accesses */
} S_80173E94_3;   /* packet in func_80173E94 */

typedef struct S_80173E94_4_pre {
    void * unk_00;
    u8 pad_04[0x4];
} S_80173E94_4_pre;   /* the 0x8 bytes before node in func_80173E94, addressed as node[-1] */

typedef struct S_80173E94_4 {
    u8 pad_00[0x8];
    volatile u32 unk_08;
    u8 pad_0C[0x26];
    s16 unk_32;
} S_80173E94_4;   /* node in func_80173E94 */

typedef struct S_80173E94_5 {
    u8 pad_00[0x8];
    u8 * unk_08;
} S_80173E94_5;   /* previous in func_80173E94 */

typedef struct S_80173E94_6 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_80173E94_6;   /* final_state in func_80173E94 */



extern u8 D_80083160[];

extern s32 func_80065420(void *, void *, void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, s32, s32);

/* Append shaded point and draw-mode packets for the linked nodes to the ordering table. */
s32 func_80173E94(void *node_arg, void *vertex_arg)
{
    u8 **state_ptr;
    u8 *scratch;
    register u8 *state;
    register u8 *final_state;
    register u8 *packet_end;
    register u8 *packet;
    u8 *node;
    u8 *vertex;
    void *previous;
    u32 depth_index;
    u16 vertex_x;
    register u32 addr_mask ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u32 tag_mask;

    node = node_arg;
    vertex = vertex_arg;
    state_ptr = (u8 **)D_80083160;
    addr_mask = 0x00FFFFFF;
    state = *(u8 **)D_80083160;
    tag_mask = 0xFF000000;
    scratch = (u8 *)0x1F800000;
    ASM_KEEP(state_ptr);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(tag_mask);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(scratch);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    *(u8 * volatile *)(scratch + 0x18) = ((S_80173E94_0 *)state)->unk_8D0;
    ((S_80173E94_1 *)scratch)->unk_20.p = state + 0xB0;

loop:
    vertex_x = ((S_80173E94_2 *)vertex)->unk_02;
    packet = *(u8 * volatile *)(scratch + 0x18);
    ((S_80173E94_1 *)scratch)->unk_00 = vertex_x;
    ((S_80173E94_1 *)scratch)->unk_02 = ((S_80173E94_2 *)vertex)->unk_06;
    ((S_80173E94_1 *)scratch)->unk_04 = ((S_80173E94_2 *)vertex)->unk_0A;
    *(u8 * volatile *)(scratch + 0x18) = packet + 0xC;

    depth_index = func_80065420(scratch, packet + 8, scratch + 0x90,
                         scratch + 0x94);
    ((S_80173E94_1 *)scratch)->unk_C0 = depth_index;

    if (depth_index < 0x1E0) {
        s32 shade_or_page;
        register s32 pixel_mode ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        register s32 blend_mode ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        s32 page_x;
        s32 tile_code;

        ((S_80173E94_3 *)packet)->unk_04.at00.v = ((S_80173E94_4 *)node)->unk_08;
        shade_or_page = ((S_80173E94_3 *)packet)->unk_04.at00u.v * ((S_80173E94_4 *)node)->unk_32;
        if (shade_or_page < 0) {
            shade_or_page += 0xFF;
        }
        ((S_80173E94_3 *)packet)->unk_04.at00u.v = shade_or_page >> 8;

        shade_or_page = ((S_80173E94_3 *)packet)->unk_04.at01.v * ((S_80173E94_4 *)node)->unk_32;
        if (shade_or_page < 0) {
            shade_or_page += 0xFF;
        }
        ((S_80173E94_3 *)packet)->unk_04.at01.v = shade_or_page >> 8;

        shade_or_page = ((S_80173E94_3 *)packet)->unk_04.at02.v * ((S_80173E94_4 *)node)->unk_32;
        if (shade_or_page < 0) {
            shade_or_page += 0xFF;
        }
        pixel_mode = 0;
        blend_mode = 1;
        ((S_80173E94_3 *)packet)->unk_04.at02.v = shade_or_page >> 8;
        ((S_80173E94_3 *)packet)->unk_00.at03.v = 2;
        tile_code = 0x6A;
        ASM_SET(page_x);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        page_x = pixel_mode;
        ((S_80173E94_3 *)packet)->unk_04.at03.v = tile_code;

        ((S_80173E94_3 *)packet)->unk_00.at00.v =
            (((S_80173E94_3 *)packet)->unk_00.at00.v & tag_mask) |
            ((*(u32 *)((u8 *)(((S_80173E94_1 *)scratch)->unk_20.p2) + ((S_80173E94_1 *)scratch)->unk_C0 * 4)) & addr_mask);
        {
            register u32 *ot_entry ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            register u32 ot_tag ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            u32 packet_addr;

            ot_entry = (u32 *)(((S_80173E94_1 *)scratch)->unk_C0 << 2);
            ot_entry = (u32 *)((u32)ot_entry +
                            (u32)((S_80173E94_1 *)scratch)->unk_20.p2);
            ot_tag = *ot_entry;
            packet_addr = (u32)packet & addr_mask;
            ot_tag = (ot_tag & tag_mask) | packet_addr;
            *ot_entry = ot_tag;
        }

        packet = *(u8 * volatile *)(scratch + 0x18);
        ((S_80173E94_1 *)scratch)->unk_18 = packet + 0xC;
        shade_or_page = func_80066460(pixel_mode, blend_mode, page_x, pixel_mode);
        func_80067F20(packet, 0, 0, (u16)shade_or_page, 0);

        ((S_80173E94_3 *)packet)->unk_00.at00.v =
            (((S_80173E94_3 *)packet)->unk_00.at00.v & tag_mask) |
            ((*(u32 *)((u8 *)(((S_80173E94_1 *)scratch)->unk_20.p2) + ((S_80173E94_1 *)scratch)->unk_C0 * 4)) & addr_mask);
        packet = (u8 *)((u32)packet & addr_mask);
        (*(u32 *)((u8 *)(((S_80173E94_1 *)scratch)->unk_20.p2) + ((S_80173E94_1 *)scratch)->unk_C0 * 4)) =
            ((*(u32 *)((u8 *)(((S_80173E94_1 *)scratch)->unk_20.p2) + ((S_80173E94_1 *)scratch)->unk_C0 * 4)) & tag_mask) |
            (u32)packet;
    }

    previous = ((S_80173E94_4_pre *)node)[-1].unk_00;
    node = (u8 *)previous + 0x20;
    if (previous != 0) {
        vertex = ((S_80173E94_5 *)previous)->unk_08;
        ASM_KEEP(node);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        goto loop;
    }

    final_state = *state_ptr;
    packet_end = ((S_80173E94_1 *)scratch)->unk_18;
    ((S_80173E94_6 *)final_state)->unk_8D0 = packet_end;
    return 0;
}
