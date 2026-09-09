#include "common.h"

typedef struct S_800248EC_0 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_800248EC_0;   /* ctx in func_800248EC */

typedef struct S_800248EC_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800248EC_1;   /* input in func_800248EC */

typedef struct S_800248EC_2 {
    u8 pad_00[0x3];
    u8 unk_03;
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_04;   /* overlapping accesses */
} S_800248EC_2;   /* packet in func_800248EC */

typedef struct S_800248EC_3_pre {
    void * unk_00;
    u8 pad_04[0x4];
} S_800248EC_3_pre;   /* the 0x8 bytes before cur in func_800248EC, addressed as cur[-1] */

typedef struct S_800248EC_3 {
    u8 pad_00[0x8];
    u32 unk_08;
    u8 pad_0C[0x26];
    s16 unk_32;
} S_800248EC_3;   /* cur in func_800248EC */

typedef struct S_800248EC_4 {
    u8 pad_00[0x8];
    void * unk_08;
} S_800248EC_4;   /* next in func_800248EC */

typedef struct S_800248EC_5 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_800248EC_5;   /* final_ctx in func_800248EC */



typedef struct {
    u16 x;
    u16 y;
    u16 z;
    u8 pad06[0x12];
    u8 *cursor;
    u8 pad1C[4];
    u32 *ot;
    u8 pad24[0x6C];
    u32 xy;
    u32 depth;
    u8 pad98[0x28];
    u32 index;
} Scratch800248EC;

typedef struct {
    u32 tag;
    u8 r;
    u8 g;
    u8 b;
    u8 code;
    u32 data;
} Packet800248EC;

extern u8 D_80083160[];
extern u32 func_80065420(void *, void *, void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, s32, s32);

/* Projects linked points and queues shaded tiles with draw-mode packets. */
s32 func_800248EC(void *first_point, void *first_position)
{
    void *point = first_point;
    void *position = first_position;
    u8 *render_state = D_80083160;
    register u32 addr_mask ASM_REG("$18") = 0x00FFFFFF;
    u8 *render_ctx = *(u8 **)D_80083160;
    u8 *packet_start;
    u32 tag_mask = 0xFF000000;
    Scratch800248EC *scratch =
        (Scratch800248EC *)0x1F800000;
    Packet800248EC *tile;
    Packet800248EC *draw_mode;
    u8 *final_render_ctx;
    s32 color_value;
    s32 draw_page;
    void *next_node;
    register s32 tex_depth ASM_REG("$4");
    register s32 blend_mode ASM_REG("$5");
    register s32 page_x ASM_REG("$6");
    u32 tile_code;


    packet_start = ((S_800248EC_0 *)render_ctx)->unk_8D0;
    scratch->ot = (u32 *)(render_ctx + 0xB0);
    scratch->cursor = packet_start;

    for (;;) {
        tile = *(Packet800248EC *volatile *)&scratch->cursor;
        scratch->x = ((S_800248EC_1 *)position)->unk_02;
        scratch->y = ((S_800248EC_1 *)position)->unk_06;
        scratch->z = ((S_800248EC_1 *)position)->unk_0A;
        scratch->cursor = (u8 *)tile + 0xC;
        scratch->index = func_80065420(scratch, (u8 *)tile + 8,
                                      &scratch->xy, &scratch->depth);

        if (scratch->index < 0x1E0U) {
            ((S_800248EC_2 *)tile)->unk_04.at00.v = ((S_800248EC_3 *)point)->unk_08;

            color_value = (s32)tile->r * ((S_800248EC_3 *)point)->unk_32;
            if (color_value < 0) {
                color_value += 0x7F;
            }
            tile->r = color_value >> 7;

            color_value = (s32)tile->g * ((S_800248EC_3 *)point)->unk_32;
            if (color_value < 0) {
                color_value += 0x7F;
            }
            tile->g = color_value >> 7;

            color_value = (s32)tile->b * ((S_800248EC_3 *)point)->unk_32;
            if (color_value < 0) {
                color_value += 0x7F;
            }
            tile->b = color_value >> 7;

            tex_depth = 0;
            blend_mode = 1;
            ((S_800248EC_2 *)tile)->unk_03 = 2;
            ASM_KEEP(tex_depth);
            tile_code = 0x6A;
            ASM_KEEP(tile_code);
            page_x = tex_depth;
            ((S_800248EC_2 *)tile)->unk_04.at03.v = tile_code;
            tile->tag = (tile->tag & tag_mask) |
                          (scratch->ot[scratch->index] & addr_mask);
            {
                u32 ot_tag = scratch->ot[scratch->index];
                register u32 tile_addr ASM_REG("$2") =
                    (u32)tile & addr_mask;

                scratch->ot[scratch->index] =
                    (ot_tag & tag_mask) | tile_addr;
                ASM_KEEP(tile_addr);
            }

            draw_mode = (Packet800248EC *)scratch->cursor;
            scratch->cursor = (u8 *)draw_mode + 0xC;
            draw_page = func_80066460(tex_depth, blend_mode, page_x, tex_depth);
            func_80067F20(draw_mode, 0, 0, (u16)draw_page, 0);

            draw_mode->tag = (draw_mode->tag & tag_mask) |
                           (scratch->ot[scratch->index] & addr_mask);
            scratch->ot[scratch->index] =
                (scratch->ot[scratch->index] & tag_mask) |
                ((u32)draw_mode & addr_mask);
        }

        next_node = ((S_800248EC_3_pre *)point)[-1].unk_00;
        if (next_node != 0) {
            point = (u8 *)next_node + 0x20;
            position = ((S_800248EC_4 *)next_node)->unk_08;
            continue;
        }

        break;
    }

    final_render_ctx = *(u8 **)render_state;
    ((S_800248EC_5 *)final_render_ctx)->unk_8D0 = scratch->cursor;
    return 0;
}
