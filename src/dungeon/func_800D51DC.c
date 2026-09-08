#include "common.h"

typedef struct S_800DA93C_0 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_800DA93C_0;   /* base->unk0 in func_800DA93C */

typedef struct S_800DA93C_1_pre {
    s32 unk_00;
    u8 pad_04[0x4];
} S_800DA93C_1_pre;   /* the 0x8 bytes before walker in func_800DA93C, addressed as walker[-1] */

typedef struct S_800DA93C_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u16 unk_04;
    u16 unk_06;
} S_800DA93C_1;   /* walker in func_800DA93C */

typedef struct S_800DA93C_2 {
    u32 unk_00;
    s32 unk_04;
    u8 pad_08[0x4];
    s8 unk_0C;
    s8 unk_0D;
    u16 unk_0E;
    u8 pad_10[0x4];
    s8 unk_14;
    s8 unk_15;
    u16 unk_16;
    u8 pad_18[0x4];
    s8 unk_1C;
    s8 unk_1D;
    u8 pad_1E[0x6];
    s8 unk_24;
    s8 unk_25;
} S_800DA93C_2;   /* record in func_800DA93C */

typedef struct S_800DA93C_3 {
    u8 pad_00[0xB0];
    u32 unk_B0;
} S_800DA93C_3;   /* (u8 *)((u32)work + (u32)base->unk0) in func_800DA93C */

typedef struct S_800DA93C_4 {
    u8 pad_00[0xB0];
    u32 unk_B0;
} S_800DA93C_4;   /* (u8 *)work in func_800DA93C */


typedef struct {
    void *unk0;
    u8 pad[0x1F8];
    s32 unk1FC;
} S_800A1600_D80083160;


extern S_800A1600_D80083160 D_80083160;
extern s32 func_80065420();
extern void func_80066640();
extern void func_800666F4();

/* Build textured quad packets from a linked list and insert them into the ordering table. */
s32 func_800DA93C(void *first_quad) {
    void *quad_data;
    void *packet;
    S_800A1600_D80083160 *render_state;
    s32 scratch;
    s32 depth;
    register s32 link_addr;
    s32 tile_index;
    s32 u_offset;
    s8 u_left;
    s8 u_right;
    s32 v_offset;
    s8 v_top;
    s8 v_bottom;
    u32 addr_mask;
    u32 tag_mask;

    quad_data = first_quad;
    render_state = &D_80083160;
    addr_mask = 0x00FFFFFF;
    tag_mask = 0xFF000000;

    do {
        packet = ((S_800DA93C_0 *)(render_state->unk0))->unk_8D0;
        ((S_800DA93C_0 *)(render_state->unk0))->unk_8D0 = (u8 *)packet + 0x28;

        depth = func_80065420((u8 *)quad_data + 0x28,
                           (u8 *)packet + 8, &scratch, &scratch);
        depth += func_80065420((u8 *)quad_data + 0x30,
                            (u8 *)packet + 0x10, &scratch, &scratch);
        depth += func_80065420((u8 *)quad_data + 0x38,
                            (u8 *)packet + 0x18, &scratch, &scratch);
        depth += func_80065420((u8 *)quad_data + 0x40,
                            (u8 *)packet + 0x20, &scratch, &scratch);
        depth = (depth >> 2) - 8;

        if ((u32)depth < 0x1E0U) {
            scratch = 0xFF - ((S_800DA93C_1 *)quad_data)->unk_02;
            ((S_800DA93C_2 *)packet)->unk_04 = (*(s32 *)((u8 *)quad_data + 0x10));
            func_800666F4(packet);
            func_80066640(packet, 1);

            ((S_800DA93C_2 *)packet)->unk_16 = ((S_800DA93C_1 *)quad_data)->unk_04;
            ((S_800DA93C_2 *)packet)->unk_0E = ((S_800DA93C_1 *)quad_data)->unk_06;

            tile_index = (s16)(((S_800DA93C_1 *)quad_data)->unk_02 % 8);
            scratch = tile_index;

            u_offset = (tile_index % 4) << 5;
            u_left = u_offset - 0x80;
            u_right = u_offset - 0x61;
            ((S_800DA93C_2 *)packet)->unk_14 = u_left;
            ((S_800DA93C_2 *)packet)->unk_0C = u_left;
            ((S_800DA93C_2 *)packet)->unk_24 = u_right;
            ((S_800DA93C_2 *)packet)->unk_1C = u_right;

            v_offset = (scratch / 4) << 5;
            v_top = v_offset + 0x40;
            v_bottom = v_offset + 0x5F;
            ((S_800DA93C_2 *)packet)->unk_1D = v_top;
            ((S_800DA93C_2 *)packet)->unk_0D = v_top;
            ((S_800DA93C_2 *)packet)->unk_25 = v_bottom;
            ((S_800DA93C_2 *)packet)->unk_15 = v_bottom;

            link_addr = depth << 2;
            ((S_800DA93C_2 *)packet)->unk_00 =
                (((S_800DA93C_2 *)packet)->unk_00 & tag_mask) |
                (((S_800DA93C_3 *)((u8 *)((u32)link_addr + (u32)render_state->unk0)))->unk_B0 & addr_mask);
            link_addr += (s32)render_state->unk0;
            ((S_800DA93C_4 *)((u8 *)link_addr))->unk_B0 =
                (((S_800DA93C_4 *)((u8 *)link_addr))->unk_B0 & tag_mask) |
                ((u32)packet & addr_mask);
        }

        link_addr = ((S_800DA93C_1_pre *)quad_data)[-1].unk_00;
        quad_data = (void *)(link_addr + 0x20);
    } while (link_addr != 0);

    return 0;
}
