#include "common.h"

typedef struct S_func_80174228_0 {
    u8 pad_00[4];
    union { s16 s16; u16 u16; } unk_04;
    u8 unk_06;
    u8 pad_07[0x21];
    void *unk_28;
    void *unk_2C;
    s16 unk_30;
    s16 unk_32;
    s16 unk_34;
    u8 pad_36[0xA];
    s16 unk_40;
    s16 unk_42;
    u8 pad_44[4];
    u16 unk_48[24];
    s16 unk_78;
    s16 unk_7A;
    union { s32 s32; u16 u16; } unk_7C;
} S_func_80174228_0;

typedef struct S_func_80174228_1 {
    u16 unk_00;
    s16 unk_02;
    s16 unk_04;
    u8 pad_06[2];
} S_func_80174228_1;

typedef struct S_func_80174228_2 {
    void *unk_00;
    u8 pad_04[0xC4];
    u16 unk_C8;
} S_func_80174228_2;

typedef struct S_func_80174228_3 {
    u8 pad_00[0xA];
    s16 unk_0A;
    u8 pad_0C[2];
    u16 unk_0E;
    u8 pad_10[8];
    s16 unk_18;
} S_func_80174228_3;

typedef struct S_func_80174228_4 {
    u8 pad_00[0xB0];
    u32 unk_B0[520];
    void *unk_8D0;
} S_func_80174228_4;

typedef struct S_func_80174228_5 {
    u32 unk_00;
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 pad_07[1];
    s16 unk_08;
    s16 unk_0A;
    s8 unk_0C;
    u8 unk_0D;
    u8 pad_0E[2];
    s16 unk_10;
    s16 unk_12;
    s8 unk_14;
    u8 unk_15;
    s16 unk_16;
    s16 unk_18;
    s16 unk_1A;
    s8 unk_1C;
    u8 unk_1D;
    u8 pad_1E[2];
    s16 unk_20;
    s16 unk_22;
    s8 unk_24;
    u8 unk_25;
    u8 pad_26[2];
} S_func_80174228_5;

typedef struct S_func_80174228_6 {
    s16 unk_00;
} S_func_80174228_6;

typedef struct S_func_80174228_7 {
    u8 pad_00[0x48];
    s16 unk_48;
} S_func_80174228_7;

typedef struct S_func_80174228_8 {
    u8 pad_00[0x58];
    s16 unk_58;
} S_func_80174228_8;

typedef struct S_func_80174228_9 {
    void *unk_00;
} S_func_80174228_9;

typedef struct S_func_80174228_10 {
    u32 unk_00;
} S_func_80174228_10;

#define TMP ((S_func_80174228_0 *)storage)->unk_7C.s32
#define OUTX ((S_func_80174228_0 *)storage)->unk_78
#define OUTY ((S_func_80174228_0 *)storage)->unk_7A

extern s32 func_80065420();
extern s16 func_80066460();
extern void func_80066640();
extern void func_800666F4(void *);
extern void func_800DBA90();

extern u8 D_80083160[0x8D4];
extern u8 D_8017087C[];

/* Render linked items as shaded textured strips using projected bounds and a mirrored height profile. */
s32 func_80174228(u8 *item_data)
{
    u8 storage[0x80];
    s32 depth;
    s32 biased_depth;
    s32 prev_depth;
    s32 next_depth;
    s32 extends_right;
    u8 *vertices;
    s32 right_bound;
    s32 ot_offset;
    u8 *vertex_base;
    u8 *setup_source;
    s32 min_xy;
    s32 max_xy;
    s32 i;
    s32 *scratch_ptr;
    s32 screen_width;
    s32 strip_offset;
    s32 tex_coord;
    register s32 far_z ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register s32 near_z ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    u8 *next_node;
    register s32 left_coord ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s32 right_x ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s32 top_y;
    register s32 bottom_y;
    register s32 half_width;
    register s32 left_x;
    u32 addr_mask;
    register u32 tag_mask ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    register S_func_80174228_1 *init_vertex ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    u8 *vertex;
    S_func_80174228_5 *prim;
    u8 shade;
    u8 tex_height;
    S_func_80174228_4 *context;
    S_func_80174228_4 *context2;
    S_func_80174228_6 *profile_dst;
    S_func_80174228_7 *profile_mirror;
    u32 mirror_addr;
    S_func_80174228_8 *profile_base;
    s32 brightness;
    s32 shade_bias;
    s32 profile_raw;
    s32 vertex_depth;
    s32 screen_coord;
    u32 coord_bits;
    u16 profile_peak;
    s32 half_height;
    register S_func_80174228_3 *item ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 render_term ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    S_func_80174228_2 *render_state;
    register S_func_80174228_0 *profile_storage ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register u8 *transform ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */

    render_state = (S_func_80174228_2 *)D_80083160;
    __builtin_memcpy(storage, D_8017087C, 8);
    depth = 0;
    vertices = storage + 8;

    do {
        item = (S_func_80174228_3 *)item_data;
        vertex_base = vertices;
        i = 3;
        far_z = -0xA0;
        near_z = 0x10;
        ((S_func_80174228_0 *)storage)->unk_7C.s32 = 0x40;
        half_width = ((S_func_80174228_0 *)storage)->unk_7C.u16;
        init_vertex = (S_func_80174228_1 *)(vertex_base + 0x18);
        left_x = -half_width;
        do {
            init_vertex->unk_00 = half_width;
            if (i < 2) {
                init_vertex->unk_00 = left_x;
            }
            init_vertex->unk_02 = 0;
            if (i & 1) {
                init_vertex->unk_04 = far_z;
            } else {
                init_vertex->unk_04 = near_z;
            }
            i--;
            init_vertex--;
        } while (i >= 0);

        transform = storage + 0x28;
        ASM_KEEP_NV(transform);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        min_xy &= 0xFFFF;
        max_xy &= 0xFFFF;
        i = 3;
        setup_source = (u8 *)render_state;
        render_term = ((S_func_80174228_2 *)setup_source)->unk_C8;
        ASM_USE_NV(render_term);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        ((S_func_80174228_0 *)storage)->unk_32 = 0;
        ((S_func_80174228_0 *)storage)->unk_30 = 0;
        setup_source = vertices;
        scratch_ptr = &TMP;
        vertex = setup_source + 0x18;
        ((S_func_80174228_0 *)storage)->unk_28 = setup_source;
        ((S_func_80174228_0 *)storage)->unk_2C = setup_source;
        ((S_func_80174228_0 *)storage)->unk_34 = -render_term;
        __builtin_memcpy(storage + 0x38, item, 8);
        ((S_func_80174228_0 *)storage)->unk_40 = 4;
        ((S_func_80174228_0 *)storage)->unk_42 = 0;
        func_800DBA90(transform, left_x, near_z, far_z);

        min_xy |= 0x75300000;
        min_xy &= 0xFFFF0000;
        min_xy |= 0x7530;
        max_xy |= 0x8AD00000;
        max_xy &= 0xFFFF0000;
        max_xy |= 0x8AD0;

        do {
            vertex_depth = func_80065420(vertex, &OUTX, scratch_ptr, scratch_ptr);
            prev_depth = depth;
            screen_coord = OUTX;
            biased_depth = prev_depth - 8;
            ASM_USE2_NV(screen_coord, biased_depth);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            next_depth = biased_depth + vertex_depth;
            extends_right = (s16)max_xy < screen_coord;
            depth = next_depth;
            coord_bits = (u16)OUTX;
            if (extends_right) {
                max_xy &= 0xFFFF0000;
                coord_bits |= max_xy;
                max_xy = coord_bits;
            } else if (screen_coord < (s16)min_xy) {
                min_xy &= 0xFFFF0000;
                coord_bits |= min_xy;
                min_xy = coord_bits;
            }
            screen_coord = OUTY;
            coord_bits = (u16)OUTY;
            if ((max_xy >> 16) < screen_coord) {
                max_xy &= 0xFFFF;
                max_xy = max_xy | (coord_bits << 16);
            } else if (screen_coord < (min_xy >> 16)) {
                min_xy &= 0xFFFF;
                min_xy = min_xy | (coord_bits << 16);
            }
            i--;
            vertex -= 8;
        } while (i >= 0);

        i = 1;
        depth >>= 2;
        profile_peak = item->unk_0E;
        ASM_KEEP_MEMDEP_NV(profile_peak, profile_dst, storage[0]);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        profile_dst = (S_func_80174228_6 *)(storage + 0x60);
        ((S_func_80174228_0 *)storage)->unk_48[11] = profile_peak;
        do {
            mirror_addr = (0xB - i) * 2;
            mirror_addr += (u32)storage;
            profile_mirror = (S_func_80174228_7 *)mirror_addr;
            profile_raw = ((S_func_80174228_0 *)storage)->unk_48[0xC - i];
            i++;
            half_height = (profile_raw << 16) >> 17;
            profile_dst->unk_00 = half_height;
            profile_mirror->unk_48 = half_height;
            profile_dst++;
        } while (i < 0xC);

        if ((u32)depth < 0x1E0U) {
            i = 0;
            do {
                context = render_state->unk_00;
                prim = context->unk_8D0;
                context->unk_8D0 = (u8 *)prim + 0x28;

                profile_base = (S_func_80174228_8 *)(storage + i * 2 - 0x10);
                ASM_USE(profile_base);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                render_term = 0xB;
                render_term -= i;
                brightness = profile_base->unk_58;
                if (render_term < 0) {
                    render_term = -render_term;
                }
                brightness -= render_term;
                shade_bias = item->unk_18;
                brightness *= 2;
                shade_bias *= 4;
                shade_bias += 0x5C;
                brightness += shade_bias;
                TMP = brightness;
                if (brightness < 0) {
                    TMP = 0;
                }
                shade = TMP;
                prim->unk_06 = shade;
                prim->unk_05 = shade;
                prim->unk_04 = shade;
                func_800666F4(prim);
                func_80066640(prim, 1);
                prim->unk_16 = func_80066460(2, 1, 0x340, 0x100);

                render_term = i * ((S_func_80174228_0 *)storage)->unk_04.s16;
                left_coord = render_term / 23;
                prim->unk_14 = left_coord;
                prim->unk_0C = left_coord;
                tex_coord = left_coord;
                tex_coord += ((((S_func_80174228_0 *)storage)->unk_04.u16 << 16) >> 16) / 23;
                prim->unk_1D = 0;
                prim->unk_0D = 0;
                prim->unk_24 = tex_coord;
                prim->unk_1C = tex_coord;

                tex_height = ((S_func_80174228_0 *)storage)->unk_06;
                ASM_USE(tex_height);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                prim->unk_25 = tex_height;
                tex_coord = prim->unk_0D + 2;
                if (tex_height >= 2) {
                    tex_coord = prim->unk_0D + prim->unk_25;
                }
                right_bound = (s16)max_xy;
                screen_width = right_bound - (s16)min_xy;
                prim->unk_25 = tex_coord;
                prim->unk_15 = tex_coord;

                strip_offset = (screen_width * i) / 23;
                TMP = strip_offset;
                if (i < 0xB) {
                    TMP = strip_offset + item->unk_0A;
                    if ((screen_width >> 1) < TMP) {
                        TMP = screen_width >> 1;
                    }
                } else if (i >= 0xC) {
                    TMP = strip_offset - item->unk_0A;
                    if (TMP < (screen_width >> 1)) {
                        TMP = screen_width >> 1;
                    }
                }

                left_coord = (u16)TMP + min_xy;
                prim->unk_10 = left_coord;
                prim->unk_08 = left_coord;
                right_x = left_coord + screen_width / 23;
                prim->unk_20 = right_x;
                prim->unk_18 = right_x;

                profile_storage = (S_func_80174228_0 *)storage;
                top_y = profile_storage->unk_48[i] + (min_xy >> 16);
                prim->unk_1A = top_y;
                prim->unk_0A = top_y;
                bottom_y = profile_storage->unk_48[i] + (max_xy >> 16);
                prim->unk_22 = bottom_y;
                prim->unk_12 = bottom_y;

                ot_offset = depth * 4;
                tag_mask = 0xFF000000;
                addr_mask = 0x00FFFFFF;
                context = render_state->unk_00;
                prim->unk_00 = (prim->unk_00 & tag_mask) |
                    (((S_func_80174228_10 *)((u8 *)context + (0xB0 + ot_offset)))->unk_00 & addr_mask);
                context2 = render_state->unk_00;
                ((S_func_80174228_10 *)((u8 *)context2 + (0xB0 + ot_offset)))->unk_00 =
                    (((S_func_80174228_10 *)((u8 *)context2 + (0xB0 + ot_offset)))->unk_00 & tag_mask) |
                    ((u32)prim & addr_mask);

                i++;
            } while (i < 0x17);
        }

        next_node = ((S_func_80174228_9 *)(item_data - 8))->unk_00;
        if (next_node == 0) {
            break;
        }
        item_data = next_node + 0x20;
    } while (1);
    return 0;
}
