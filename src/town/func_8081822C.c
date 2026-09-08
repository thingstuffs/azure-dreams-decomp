#include "common.h"

typedef struct S_8002222C_0 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_8002222C_0;   /* arena in func_8002222C */

typedef struct S_8002222C_1_pre {
    s32 unk_00;
    u8 pad_04[0x4];
} S_8002222C_1_pre;   /* the 0x8 bytes before var_s3 in func_8002222C, addressed as var_s3[-1] */

typedef struct S_8002222C_1 {
    u8 pad_00[0x18];
    s32 unk_18;
    s32 unk_1C;
} S_8002222C_1;   /* var_s3 in func_8002222C */

typedef struct S_8002222C_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
} S_8002222C_2;   /* temp_s0 in func_8002222C */

typedef struct S_8002222C_3 {
    s32 unk_00;
    s32 unk_04;
} S_8002222C_3;   /* scratch in func_8002222C */

typedef struct S_8002222C_4 {
    u16 unk_00;
    u16 unk_02;
} S_8002222C_4;   /* scratch100 in func_8002222C */

typedef struct S_8002222C_5 {
    u8 pad_00[0xB0];
    s32 unk_B0;
} S_8002222C_5;   /* temp_a1_2 + temp_v0 in func_8002222C */

typedef struct S_8002222C_6 {
    u8 pad_00[0xB0];
    s32 unk_B0;
} S_8002222C_6;   /* temp_a0 in func_8002222C */

typedef struct S_8002222C_7 {
    s32 unk_00;
} S_8002222C_7;   /* temp_s1 in func_8002222C */

typedef struct S_8002222C_8 {
    u8 pad_00[0xB0];
    s32 unk_B0;
} S_8002222C_8;   /* temp_a1_2 in func_8002222C */



extern void func_80065770(void *, void *, void *, void *, void *, s32);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_80066640(void *, s32);
extern void func_800667D0(void *);
extern void func_80067F20(void *, s32, s32, s32, s32);
extern u8 D_80083160[];
extern u8 D_1F800000[];

/* Build line and draw-mode packets for each entry and link them into the ordering table. */
s32 func_8002222C(void *first_entry) {
    u8 *line_packet;
    u8 *mode_packet;
    s32 bucket_or_next;
    s32 bucket_addr;
    s32 packet_word;
    s32 link_word;
    s32 texture_page;
    u8 *entry;
    u8 **arena_ptr;
    register u8 *depths ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *transform_work;
    register u8 *scratch_base ASM_REG("$30");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    u8 *screen_xy;
    u32 addr_mask;
    u32 count_mask;
    register s32 result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */

    entry = first_entry;
    arena_ptr = (u8 **)D_80083160;
    scratch_base = (u8 *)0x1F800000;
    ASM_KEEP_NV(scratch_base);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    screen_xy = scratch_base;
    depths = screen_xy;
    ASM_KEEP_NV(depths);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    depths = (u8 *)((u32)depths | 0x100);
    transform_work = screen_xy;
    ASM_KEEP_NV(transform_work);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    transform_work = (u8 *)((u32)transform_work | 0x180);
    addr_mask = 0xFFFFFF;
    count_mask = 0xFF000000;
    do {
        func_80065770(entry + 8, screen_xy, depths, transform_work,
                     transform_work, 2);
        {
            u8 *arena;
            s32 page_depth;
            s32 page_blend;
            s32 page_x;
            s32 page_y;
            u8 *packet_end;
            arena = *arena_ptr;
            ASM_KEEP(arena);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            page_depth = 0;
            ASM_KEEP(page_depth);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            line_packet = ((S_8002222C_0 *)arena)->unk_8D0;
            ASM_KEEP(line_packet);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            page_blend = page_depth;
            ASM_KEEP(page_blend);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            ((S_8002222C_0 *)arena)->unk_8D0 = line_packet + 0x14;
            arena = *arena_ptr;
            ASM_KEEP(arena);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            page_x = page_depth;
            ASM_KEEP(page_x);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            mode_packet = ((S_8002222C_0 *)arena)->unk_8D0;
            ASM_KEEP(mode_packet);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            page_y = page_depth;
            ASM_KEEP(page_y);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            packet_end = mode_packet + 0xC;
            ASM_KEEP(packet_end);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            ((S_8002222C_0 *)arena)->unk_8D0 = packet_end;
            texture_page = func_80066460(page_depth, page_blend, page_x, page_y);
        }
        {
            u8 *mode_dest;
            s32 draw_flags;
            mode_dest = mode_packet;
            ASM_KEEP(mode_dest);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            draw_flags = 0;
            ASM_KEEP(draw_flags);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            func_80067F20(mode_dest, draw_flags, draw_flags, texture_page & 0xFFFF, 0);
        }
        packet_word = ((S_8002222C_1 *)entry)->unk_18;
        ((S_8002222C_2 *)line_packet)->unk_04 = packet_word;
        packet_word = ((S_8002222C_1 *)entry)->unk_1C;
        ((S_8002222C_2 *)line_packet)->unk_0C = packet_word;
        func_800667D0(line_packet);
        func_80066640(line_packet, 1);
        packet_word = ((S_8002222C_3 *)screen_xy)->unk_00;
        ((S_8002222C_2 *)line_packet)->unk_08 = packet_word;
        packet_word = ((S_8002222C_3 *)screen_xy)->unk_04;
        ((S_8002222C_2 *)line_packet)->unk_10 = packet_word;
        {
            register s32 depth_offset ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            s32 min_depth;
            register u32 first_depth ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            first_depth = ((S_8002222C_4 *)depths)->unk_00;
            depth_offset = first_depth << 0x10;
            min_depth = ((S_8002222C_4 *)depths)->unk_02 << 0x10;
            if (depth_offset < min_depth) {
                min_depth = depth_offset >> 0x13;
            } else {
                min_depth >>= 0x13;
            }
            depth_offset = min_depth * 4;
            ASM_KEEP(depth_offset);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            bucket_addr = depth_offset;
        }
        packet_word = (s32)*arena_ptr;
        link_word = ((S_8002222C_2 *)line_packet)->unk_00;
        packet_word = ((S_8002222C_5 *)(bucket_addr + packet_word))->unk_B0;
        link_word &= count_mask;
        packet_word &= addr_mask;
        link_word |= packet_word;
        ((S_8002222C_2 *)line_packet)->unk_00 = link_word;
        {
            register s32 arena_addr ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            arena_addr = (s32)*arena_ptr;
            bucket_or_next = bucket_addr + arena_addr;
        }
        packet_word = ((S_8002222C_6 *)bucket_or_next)->unk_B0;
        link_word = (u32)line_packet & addr_mask;
        packet_word &= count_mask;
        packet_word |= link_word;
        ((S_8002222C_6 *)bucket_or_next)->unk_B0 = packet_word;
        packet_word = (s32)*arena_ptr;
        link_word = ((S_8002222C_7 *)mode_packet)->unk_00;
        packet_word = ((S_8002222C_5 *)(bucket_addr + packet_word))->unk_B0;
        link_word &= count_mask;
        packet_word &= addr_mask;
        link_word |= packet_word;
        ((S_8002222C_7 *)mode_packet)->unk_00 = link_word;
        bucket_addr += (s32)*arena_ptr;
        packet_word = ((S_8002222C_8 *)bucket_addr)->unk_B0;
        link_word = (u32)mode_packet & addr_mask;
        packet_word &= count_mask;
        packet_word |= link_word;
        ((S_8002222C_8 *)bucket_addr)->unk_B0 = packet_word;
        bucket_or_next = ((S_8002222C_1_pre *)entry)[-1].unk_00;
        entry = bucket_or_next + 0x20;
    } while (bucket_or_next != 0);
    result = 0;
    return result;
}
