#include "modules/dungeon_ovl_7ce800.h"
#include "common.h"
/* The root-pointer member at D_80083150 + 0x10. */
typedef struct { u8 *root; } RenderRootSlot;

typedef struct S_807B0B3C_0_pre {
    u8 * unk_00;
    u8 pad_04[0x4];
} S_807B0B3C_0_pre;   /* the 0x8 bytes before initial in func_800F833C, addressed as initial[-1] */

typedef struct S_807B0B3C_0 {
    u8 pad_00[0x6];
    u16 unk_06;
} S_807B0B3C_0;   /* initial in func_800F833C */

typedef struct S_807B0B3C_1 {
    union { u16 u; s16 s; } unk_00;   /* accessed as both */
    union { s16 s; u16 u; } unk_02;   /* accessed as both */
    u16 unk_04;
    s16 unk_06;
    union { u16 u16; u8 u8; } unk_08;   /* accessed as both */
} S_807B0B3C_1;   /* effect in func_800F833C */

typedef struct S_807B0B3C_2 {
    u16 unk_00;
    u16 unk_02;
    u8 pad_04[0x4];
    u16 unk_08;
} S_807B0B3C_2;   /* a3p in func_800F833C */

typedef struct S_807B0B3C_3 {
    union { u16 v; s16 n; } unk_00;   /* accessed as both */
    union { u16 v; s16 n; } unk_02;   /* accessed as both */
    u16 unk_04;
} S_807B0B3C_3;   /* a0p in func_800F833C */

typedef struct S_807B0B3C_4 {
    u8 pad_00[0x4];
    s16 unk_04;
    u8 pad_06[0x6];
    u16 unk_0C;
} S_807B0B3C_4;   /* (u8 *)a2v in func_800F833C */

typedef struct S_807B0B3C_5 {
    u16 unk_00;
    u16 unk_02;
    s16 unk_04;
    u8 pad_06[0x2];
    u16 unk_08;
} S_807B0B3C_5;   /* (u8 *)a2p in func_800F833C */

typedef struct S_807B0B3C_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u16 unk_04;
} S_807B0B3C_6;   /* (u8 *)v1 in func_800F833C */

typedef struct S_807B0B3C_7 {
    u32 unk_00;
    s32 unk_04;
    s32 unk_08;
    union { struct { s8 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x1]; s8 v; } at01; struct { u8 pad[0x2]; s16 v; } at02; } unk_0C;   /* overlapping accesses */
    s32 unk_10;
    s32 unk_14;
    union { struct { s8 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x1]; s8 v; } at01; struct { u8 pad[0x2]; s16 v; } at02; } unk_18;   /* overlapping accesses */
    s32 unk_1C;
    s32 unk_20;
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x2];
    s32 unk_28;
    s32 unk_2C;
    s8 unk_30;
    s8 unk_31;
} S_807B0B3C_7;   /* prim in func_800F833C */

typedef struct S_807B0B3C_8 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
} S_807B0B3C_8;   /* verts in func_800F833C */

typedef struct S_807B0B3C_9 {
    u8 pad_00[0xB0];
    u32 unk_B0;
} S_807B0B3C_9;   /* rootp in func_800F833C */

typedef struct S_807B0B3C_10 {
    u8 pad_00[0xB0];
    u32 unk_B0;
} S_807B0B3C_10;   /* entryp in func_800F833C */

typedef struct S_807B0B3C_11 {
    s8 unk_00;
    s8 unk_01;
    s8 unk_02;
} S_807B0B3C_11;   /* a1p in func_800F833C */

typedef struct S_807B0B3C_12 {
    union { u32 u; s32 s; } unk_00;   /* accessed as both */
    union { u32 u; s32 s; } unk_04;   /* accessed as both */
    union { u32 u; s32 s; } unk_08;   /* accessed as both */
    union { u32 u; s32 s; } unk_0C;   /* accessed as both */
} S_807B0B3C_12;   /* colors in func_800F833C */

typedef struct S_807B0B3C_13 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_807B0B3C_13;   /* dst in func_800F833C */

typedef struct S_807B0B3C_14 {
    u16 unk_00;
    u16 unk_02;
    u8 pad_04[0x4];
    u16 unk_08;
    u16 unk_0A;
    u8 pad_0C[0x4];
    u16 unk_10;
    u8 pad_12[0x6];
    u16 unk_18;
} S_807B0B3C_14;   /* scratch in func_800F833C */

typedef struct S_807B0B3C_15 {
    u8 pad_00[0xB0];
    u32 unk_B0;
} S_807B0B3C_15;   /* (u8 *)offset in func_800F833C */

typedef struct {
    s32 projection_flag;
} StackLocals;

extern s32 func_80065420(void *, void *, void *, void *);
extern s16 func_80066460(s32, s32, s32, s32);
extern s16 func_8006649C(s32, s32);
extern void func_80066640(void *, s32);
extern void func_80066708(void *);
extern void func_8006671C(u8 *primitive);
extern void func_80067F20(void *, s32, s32, s32, s32);
extern u8 D_80083150[];

/* Builds and queues textured and shaded quads for an effect and advances to the next object. */
s32 func_800F833C(void *object, s32 caller_a1, void *caller_a2) {
    u8 *scratch;
    u8 *colors;
    u8 *verts;
    u8 *effect;
    s16 saved_a1 = caller_a1;
    void *saved_a2 = caller_a2;
    StackLocals stack;
    u32 draw_value;
    s32 vertex_index;
    s32 frame_remainder;
    s32 pair_addr;
    s32 depth;
    s32 bucket_offset;
    s32 gray;
    void *prim_arg;
    s32 tex_coord;
    s32 tex_left;
    u8 *world_vertex;
    u8 *screen_vertex;
    u8 *prim;
    u8 *shaded_prim;
    u8 *draw_prim;
    u8 *next_object;
    u16 component;
    u16 component_2;
    u16 component_3;
    u16 component_4;
    u16 component_5;
    s32 coord;
    u8 **global_slot;
    u8 *render_state_m;
    u8 *bucket_ptr_m;

    scratch = (u8 *)0x1F800000;
    colors = scratch;
    verts = scratch;
    colors = (u8 *)((u32)colors | 0x40);
    verts = (u8 *)((u32)verts | 0x80);
    do {
        global_slot = (u8 **)(D_80083150 + 0x10);
        effect = (u8 *)object;
        if ((((S_807B0B3C_0 *)object)->unk_06 >> 10) & 1) {
            u8 *vertex_pair;
            u8 *vertex_ptr;
            s32 coord_half;

            for (vertex_index = 0; vertex_index < 2; vertex_index++) {
                vertex_pair = scratch + vertex_index * 0x10;
                bucket_ptr_m = (u8 *)(vertex_index * 2);
                coord_half = ((S_807B0B3C_1 *)effect)->unk_00.u;
                stack.projection_flag = (s32)bucket_ptr_m;
                ((S_807B0B3C_2 *)vertex_pair)->unk_08 = coord_half;
                ((S_807B0B3C_2 *)vertex_pair)->unk_00 = coord_half;
                vertex_ptr = vertex_pair + 8;
                bucket_ptr_m = (u8 *)(((S_807B0B3C_1 *)effect)->unk_02.s);
                if (vertex_index < 2) {
                    coord_half = (s32)bucket_ptr_m - 0x20;
                    ((S_807B0B3C_3 *)vertex_ptr)->unk_02.v = coord_half;
                } else {
                    coord_half = (s32)bucket_ptr_m + 0x20;
                    ((S_807B0B3C_3 *)vertex_ptr)->unk_02.v = coord_half;
                }
                pair_addr = stack.projection_flag;
                coord_half = ((S_807B0B3C_3 *)vertex_ptr)->unk_02.v;
                pair_addr <<= 3;
                ((S_807B0B3C_2 *)vertex_pair)->unk_02 = coord_half;
                draw_value = (u32)(((S_807B0B3C_1 *)effect)->unk_04);
                pair_addr += (u32)scratch;
                ((S_807B0B3C_4 *)((u8 *)pair_addr))->unk_0C = (s32)draw_value;
                coord_half = ((S_807B0B3C_1 *)effect)->unk_08.u16;
                frame_remainder = (s16)coord_half;
                frame_remainder %= 5;
                draw_value += frame_remainder;
                draw_value -= 0x36;
                ((S_807B0B3C_4 *)((u8 *)pair_addr))->unk_04 = (s32)draw_value;
            }
        } else {
            u8 *vertex_ptr;
            s32 second_pair;
            s32 pairs_end;

            pair_addr = (s32)scratch;
            second_pair = (s32)scratch + 0x10;
            pairs_end = (s32)scratch + 0x20;
    build_x_pairs:
            bucket_ptr_m = (u8 *)(((S_807B0B3C_1 *)effect)->unk_00.s);
            vertex_ptr = (u8 *)pair_addr + 8;
            if (pair_addr < second_pair) {
                caller_a1 = (s32)bucket_ptr_m - 0x20;
                ((S_807B0B3C_5 *)((u8 *)pair_addr))->unk_08 = caller_a1;
            } else {
                caller_a1 = (s32)bucket_ptr_m + 0x20;
                ((S_807B0B3C_5 *)((u8 *)pair_addr))->unk_08 = caller_a1;
            }
            caller_a1 = ((S_807B0B3C_3 *)vertex_ptr)->unk_00.v;
            ((S_807B0B3C_5 *)((u8 *)pair_addr))->unk_00 = caller_a1;
            caller_a1 = ((S_807B0B3C_1 *)effect)->unk_02.u;
            bucket_ptr_m = (u8 *)((s32)((u32)8 + (u32)pair_addr));
            ((S_807B0B3C_6 *)((u8 *)(s32)bucket_ptr_m))->unk_02 = caller_a1;
            ((S_807B0B3C_5 *)((u8 *)pair_addr))->unk_02 = caller_a1;
            draw_value = (u32)(((S_807B0B3C_1 *)effect)->unk_04);
            ((S_807B0B3C_6 *)((u8 *)(s32)bucket_ptr_m))->unk_04 = (s32)draw_value;
            caller_a1 = ((S_807B0B3C_1 *)effect)->unk_08.u16;
            frame_remainder = (s16)caller_a1;
            frame_remainder %= 5;
            draw_value += frame_remainder;
            draw_value -= 0x36;
            ((S_807B0B3C_5 *)((u8 *)pair_addr))->unk_04 = draw_value;
            pair_addr += 0x10;
            if (pair_addr < pairs_end) goto build_x_pairs;
        }

        depth = 0;

        for (vertex_index = 0; vertex_index < 4; vertex_index++) {
            s32 vertex_depth = func_80065420(scratch + vertex_index * 8, verts + vertex_index * 4, &stack.projection_flag, &stack.projection_flag);
            bucket_ptr_m = (u8 *)(depth - 8);
            depth = (s32)bucket_ptr_m + vertex_depth;
        }

        {
            s32 rounded_depth;

            rounded_depth = depth;
            depth = (rounded_depth / 4);
        }

        {
            u8 *render_state;

            render_state = ((RenderRootSlot *)global_slot)->root;
            prim = *(u8 **)(render_state + 0x8D0);
            prim_arg = (void *)prim;
            *(u8 **)(render_state + 0x8D0) = prim + 0x34;
        }
        gray = 0xA0A0A0;
        ((S_807B0B3C_7 *)prim)->unk_1C = 0;
        ((S_807B0B3C_7 *)prim)->unk_04 = 0;
        ((S_807B0B3C_7 *)prim)->unk_28 = gray;
        ((S_807B0B3C_7 *)prim)->unk_10 = gray;
        func_8006671C(prim_arg);
        func_80066640(prim, 1);
        ((S_807B0B3C_7 *)prim)->unk_18.at02.v = func_80066460(0, 1, 0x280, 0x100);
        {
            u16 clut;

            clut = func_8006649C(0x90, 0x1F7);
            tex_left = ((S_807B0B3C_8 *)verts)->unk_00;
            ((S_807B0B3C_7 *)prim)->unk_0C.at02.v = clut;
            ((S_807B0B3C_7 *)prim)->unk_08 = tex_left;
        }
        ((S_807B0B3C_7 *)prim)->unk_14 = ((S_807B0B3C_8 *)verts)->unk_04;
        ((S_807B0B3C_7 *)prim)->unk_20 = ((S_807B0B3C_8 *)verts)->unk_08;
        ((S_807B0B3C_7 *)prim)->unk_2C = ((S_807B0B3C_8 *)verts)->unk_0C;

        draw_value = ((S_807B0B3C_1 *)effect)->unk_08.u16;
        draw_value &= 7;
        tex_coord = (draw_value & 3) << 5;
        tex_left = tex_coord - 0x80;
        tex_coord -= 0x61;
        draw_value >>= 2;
        draw_value <<= 5;
        ((S_807B0B3C_7 *)prim)->unk_30 = tex_coord;
        ((S_807B0B3C_7 *)prim)->unk_24 = tex_coord;
        tex_coord = draw_value - 0x40;
        draw_value -= 0x21;
        ((S_807B0B3C_7 *)prim)->unk_31 = tex_coord;
        ((S_807B0B3C_7 *)prim)->unk_18.at01.v = tex_coord;
        ((S_807B0B3C_7 *)prim)->unk_18.at00.v = tex_left;
        ((S_807B0B3C_7 *)prim)->unk_0C.at00.v = tex_left;
        ((S_807B0B3C_7 *)prim)->unk_25 = draw_value;
        ((S_807B0B3C_7 *)prim)->unk_0C.at01.v = draw_value;

        if ((u32)depth < 0x1E0U) {
            s32 textured_offset;

            {
                u32 prim_tag;
                u32 bucket_tag;

                textured_offset = depth * 4;
                prim_tag = ((S_807B0B3C_7 *)prim)->unk_00;
                render_state_m = (u8 *)((u32)textured_offset + (u32)((RenderRootSlot *)global_slot)->root);
                prim_tag &= 0xFF000000U;

                bucket_tag = ((S_807B0B3C_9 *)render_state_m)->unk_B0;

                ((S_807B0B3C_7 *)prim)->unk_00 = prim_tag | (bucket_tag & 0xFFFFFFU);
            }
            {
                u8 *render_state;
                u8 *bucket_ptr;

                render_state = ((RenderRootSlot *)global_slot)->root;

                bucket_ptr = (u8 *)((u32)textured_offset + (u32)render_state);
                ((S_807B0B3C_10 *)bucket_ptr)->unk_B0 =
                    (((S_807B0B3C_10 *)bucket_ptr)->unk_B0 & 0xFF000000U) |
                    ((u32)prim & 0xFFFFFFU);
            }
        }

        {
            u8 *vertex_ptr;
            u8 *color_ptr;

            for (vertex_index = 3; vertex_index >= 0; vertex_index--) {
                vertex_ptr = scratch + vertex_index * 8;
                color_ptr = colors + vertex_index * 4;
                coord = ((S_807B0B3C_1 *)effect)->unk_00.s;
                if (vertex_index < 2) {
                    ((S_807B0B3C_3 *)vertex_ptr)->unk_00.n = coord - 0x20;
                } else {
                    ((S_807B0B3C_3 *)vertex_ptr)->unk_00.n = coord + 0x20;
                }
                coord = ((S_807B0B3C_1 *)effect)->unk_02.s;
                if (vertex_index & 1) {
                    ((S_807B0B3C_3 *)vertex_ptr)->unk_02.n = coord + 0x20;
                } else {
                    ((S_807B0B3C_3 *)vertex_ptr)->unk_02.n = coord - 0x20;
                }
                ((S_807B0B3C_3 *)vertex_ptr)->unk_04 = ((S_807B0B3C_1 *)effect)->unk_04;
                tex_coord = (((S_807B0B3C_1 *)effect)->unk_08.u8 & 3) * 8;
                ((S_807B0B3C_11 *)color_ptr)->unk_02 = tex_coord;
                ((S_807B0B3C_11 *)color_ptr)->unk_01 = tex_coord;
                ((S_807B0B3C_11 *)color_ptr)->unk_00 = tex_coord;
            }
        }

        coord = ((S_807B0B3C_1 *)effect)->unk_06;
        switch (coord) {
        case 0:
            ((S_807B0B3C_12 *)colors)->unk_08.u = 0x808080;
            ((S_807B0B3C_12 *)colors)->unk_00.u = 0x808080;
            component = (*(u16 *)((u8 *)effect + 2));
            {
                u8 *vertex_ptr;

                vertex_ptr = scratch + 0x10;
                ((S_807B0B3C_13 *)vertex_ptr)->unk_02 = component;
            }
            ((S_807B0B3C_14 *)scratch)->unk_02 = component;
            break;
        case 0x400:
            component_2 = ((S_807B0B3C_1 *)effect)->unk_00.u;
            ((S_807B0B3C_12 *)colors)->unk_0C.u = 0x808080;
            ((S_807B0B3C_12 *)colors)->unk_08.u = 0x808080;
            ((S_807B0B3C_14 *)scratch)->unk_18 = component_2;
            ((S_807B0B3C_14 *)scratch)->unk_10 = component_2;
            break;
        case 0x800:
            ((S_807B0B3C_12 *)colors)->unk_0C.u = 0x808080;
            ((S_807B0B3C_12 *)colors)->unk_04.u = 0x808080;
            component_3 = (*(u16 *)((u8 *)effect + 2));
            {
                u8 *vertex_ptr;

                vertex_ptr = scratch + 0x18;
                (*(u16 *)((u8 *)vertex_ptr + 2)) = component_3;
            }
            ((S_807B0B3C_14 *)scratch)->unk_0A = component_3;
            break;
        case 0xC00:
            component_4 = ((S_807B0B3C_1 *)effect)->unk_00.u;
            ((S_807B0B3C_12 *)colors)->unk_04.u = 0x808080;
            ((S_807B0B3C_12 *)colors)->unk_00.u = 0x808080;
            ((S_807B0B3C_14 *)scratch)->unk_08 = component_4;
            ((S_807B0B3C_14 *)scratch)->unk_00 = component_4;
            break;
        }
        for (vertex_index = 3; vertex_index >= 0; vertex_index--) {
            func_80065420(scratch + vertex_index * 8, verts + vertex_index * 4, &stack.projection_flag, &stack.projection_flag);
        }

        if ((u32)depth < 0x1E0U) {
            s32 blend_mode;
            s32 page_x;
            s32 page_y;

            {
                u8 *render_state;

                render_state = ((RenderRootSlot *)global_slot)->root;
                shaded_prim = *(u8 **)(render_state + 0x8D0);
                {
                    s32 first_color;

                    first_color = ((S_807B0B3C_12 *)colors)->unk_00.s;
                    *(u8 **)(render_state + 0x8D0) = shaded_prim + 0x24;
                    ((S_807B0B3C_7 *)shaded_prim)->unk_04 = first_color;
                }
            }
            ((S_807B0B3C_7 *)shaded_prim)->unk_0C.at00u.v = ((S_807B0B3C_12 *)colors)->unk_04.s;
            ((S_807B0B3C_7 *)shaded_prim)->unk_14 = ((S_807B0B3C_12 *)colors)->unk_08.s;
            ((S_807B0B3C_7 *)shaded_prim)->unk_1C = ((S_807B0B3C_12 *)colors)->unk_0C.s;
            func_80066708(shaded_prim);
            func_80066640(shaded_prim, 1);
            {
                s32 vertex;
                u32 prim_tag;
                u32 bucket_tag;

                vertex = ((S_807B0B3C_8 *)verts)->unk_00;
                prim_tag = ((S_807B0B3C_7 *)shaded_prim)->unk_00;

                ((S_807B0B3C_7 *)shaded_prim)->unk_08 = vertex;
                vertex = ((S_807B0B3C_8 *)verts)->unk_04;
                bucket_offset = depth * 4;
                ((S_807B0B3C_7 *)shaded_prim)->unk_10 = vertex;
                vertex = ((S_807B0B3C_8 *)verts)->unk_08;
                draw_value = 0;
                ((S_807B0B3C_7 *)shaded_prim)->unk_18.at00u.v = vertex;
                vertex = ((S_807B0B3C_8 *)verts)->unk_0C;
                blend_mode = 1;
                ((S_807B0B3C_7 *)shaded_prim)->unk_20 = vertex;
                prim_tag &= 0xFF000000U;

                render_state_m = (u8 *)((u32)bucket_offset + (u32)((RenderRootSlot *)global_slot)->root);
                bucket_tag = ((S_807B0B3C_9 *)render_state_m)->unk_B0;

                ((S_807B0B3C_7 *)shaded_prim)->unk_00 = prim_tag | (bucket_tag & 0xFFFFFFU);
            }
            {
                u32 bucket_tag;
                u8 *bucket;

                bucket = (u8 *)((u32)bucket_offset + (u32)((RenderRootSlot *)global_slot)->root);
                bucket_tag = ((S_807B0B3C_10 *)bucket)->unk_B0 & 0xFF000000U;
                bucket_tag |= (u32)shaded_prim & 0xFFFFFFU;

                (*(u32 *)((u8 *)bucket + 0xB0)) = bucket_tag;
                bucket_ptr_m = ((RenderRootSlot *)global_slot)->root;
                page_x = draw_value;
                draw_prim = *(u8 **)(bucket_ptr_m + 0x8D0);
                page_y = draw_value;
                *(u8 **)(bucket_ptr_m + 0x8D0) = draw_prim + 0xC;
            }
            component_5 = func_80066460(draw_value, blend_mode, page_x, page_y);
            {
                s32 zero;
                void *draw_mode_arg;

                draw_mode_arg = (void *)draw_prim;
                zero = 0;
                func_80067F20(draw_mode_arg, zero, zero, component_5, 0);
            }

            {
                u32 prim_tag;
                u32 bucket_tag;

                prim_tag = ((S_807B0B3C_7 *)draw_prim)->unk_00;
                render_state_m = (u8 *)((u32)bucket_offset + (u32)((RenderRootSlot *)global_slot)->root);
                prim_tag &= 0xFF000000U;

                bucket_tag = ((S_807B0B3C_10 *)render_state_m)->unk_B0;

                ((S_807B0B3C_7 *)draw_prim)->unk_00 = prim_tag | (bucket_tag & 0xFFFFFFU);
            }
            {
                u8 *render_state;

                render_state = ((RenderRootSlot *)global_slot)->root;

                bucket_offset += (s32)render_state;
                ((S_807B0B3C_15 *)((u8 *)bucket_offset))->unk_B0 =
                    (((S_807B0B3C_15 *)((u8 *)bucket_offset))->unk_B0 & 0xFF000000U) |
                    ((u32)draw_prim & 0xFFFFFFU);
            }
        }

        draw_value = (u32) ((S_807B0B3C_0_pre *)object)[-1].unk_00;
        if (draw_value == 0) break;
        draw_value += 0x20;
        object = (u8 *)draw_value;
    } while (1);
    {
        s32 zero_result = 0;

        return zero_result;
    }
}
