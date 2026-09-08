#include "common.h"

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))
#define TMP FIELD(storage, s32, 0x7C)
#define OUTX FIELD(storage, s16, 0x78)
#define OUTY FIELD(storage, s16, 0x7A)

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
    register u8 *init_vertex ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    u8 *vertex;
    u8 *prim;
    u8 shade;
    u8 tex_height;
    u8 *context;
    u8 *context2;
    u8 *profile_dst;
    u8 *profile_mirror;
    u32 mirror_addr;
    s16 *profile_base;
    s32 brightness;
    s32 shade_bias;
    s32 profile_raw;
    s32 vertex_depth;
    s32 screen_coord;
    u32 coord_bits;
    u16 profile_peak;
    s32 half_height;
    register u8 *item ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 render_term ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    u8 *render_state;
    register u8 *profile_storage ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register u8 *transform ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */

    render_state = D_80083160;
    __builtin_memcpy(storage, D_8017087C, 8);
    depth = 0;
    vertices = storage + 8;

    do {
        item = item_data;
        vertex_base = vertices;
        i = 3;
        far_z = -0xA0;
        near_z = 0x10;
        FIELD(storage, s32, 0x7C) = 0x40;
        half_width = FIELD(storage, u16, 0x7C);
        init_vertex = vertex_base + 0x18;
        left_x = -half_width;
        do {
            FIELD(init_vertex, u16, 0) = half_width;
            if (i < 2) {
                FIELD(init_vertex, u16, 0) = left_x;
            }
            FIELD(init_vertex, s16, 2) = 0;
            if (i & 1) {
                FIELD(init_vertex, s16, 4) = far_z;
            } else {
                FIELD(init_vertex, s16, 4) = near_z;
            }
            i--;
            init_vertex -= 8;
        } while (i >= 0);

        transform = storage + 0x28;
        ASM_KEEP_NV(transform);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        min_xy &= 0xFFFF;
        max_xy &= 0xFFFF;
        i = 3;
        setup_source = render_state;
        render_term = FIELD(setup_source, u16, 0xC8);
        ASM_USE_NV(render_term);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        FIELD(storage, s16, 0x32) = 0;
        FIELD(storage, s16, 0x30) = 0;
        setup_source = vertices;
        scratch_ptr = &TMP;
        vertex = setup_source + 0x18;
        FIELD(storage, u8 *, 0x28) = setup_source;
        FIELD(storage, u8 *, 0x2C) = setup_source;
        FIELD(storage, s16, 0x34) = -render_term;
        __builtin_memcpy(storage + 0x38, item, 8);
        FIELD(storage, s16, 0x40) = 4;
        FIELD(storage, s16, 0x42) = 0;
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
        profile_peak = FIELD(item, u16, 0xE);
        ASM_KEEP_MEMDEP_NV(profile_peak, profile_dst, storage[0]);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        profile_dst = storage + 0x60;
        FIELD(storage, u16, 0x5E) = profile_peak;
        do {
            mirror_addr = (0xB - i) * 2;
            mirror_addr += (u32)storage;
            profile_mirror = (u8 *)mirror_addr;
            profile_raw = FIELD(storage, u16, 0x48 + (0xC - i) * 2);
            i++;
            half_height = (profile_raw << 16) >> 17;
            FIELD(profile_dst, s16, 0) = half_height;
            FIELD(profile_mirror, s16, 0x48) = half_height;
            profile_dst += 2;
        } while (i < 0xC);

        if ((u32)depth < 0x1E0U) {
            i = 0;
            do {
                context = FIELD(render_state, u8 *, 0);
                prim = FIELD(context, u8 *, 0x8D0);
                FIELD(context, u8 *, 0x8D0) = prim + 0x28;

                profile_base = (s16 *)(storage + i * 2 - 0x10);
                ASM_USE(profile_base);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                render_term = 0xB;
                render_term -= i;
                brightness = FIELD(profile_base, s16, 0x58);
                if (render_term < 0) {
                    render_term = -render_term;
                }
                brightness -= render_term;
                shade_bias = FIELD(item, s16, 0x18);
                brightness *= 2;
                shade_bias *= 4;
                shade_bias += 0x5C;
                brightness += shade_bias;
                TMP = brightness;
                if (brightness < 0) {
                    TMP = 0;
                }
                shade = TMP;
                FIELD(prim, u8, 6) = shade;
                FIELD(prim, u8, 5) = shade;
                FIELD(prim, u8, 4) = shade;
                func_800666F4(prim);
                func_80066640(prim, 1);
                FIELD(prim, s16, 0x16) = func_80066460(2, 1, 0x340, 0x100);

                render_term = i * FIELD(storage, s16, 4);
                left_coord = render_term / 23;
                FIELD(prim, s8, 0x14) = left_coord;
                FIELD(prim, s8, 0xC) = left_coord;
                tex_coord = left_coord;
                tex_coord += ((FIELD(storage, u16, 4) << 16) >> 16) / 23;
                FIELD(prim, u8, 0x1D) = 0;
                FIELD(prim, u8, 0xD) = 0;
                FIELD(prim, s8, 0x24) = tex_coord;
                FIELD(prim, s8, 0x1C) = tex_coord;

                tex_height = FIELD(storage, u8, 6);
                ASM_USE(tex_height);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                FIELD(prim, u8, 0x25) = tex_height;
                tex_coord = FIELD(prim, u8, 0xD) + 2;
                if (tex_height >= 2) {
                    tex_coord = FIELD(prim, u8, 0xD) + FIELD(prim, u8, 0x25);
                }
                right_bound = (s16)max_xy;
                screen_width = right_bound - (s16)min_xy;
                FIELD(prim, u8, 0x25) = tex_coord;
                FIELD(prim, u8, 0x15) = tex_coord;

                strip_offset = (screen_width * i) / 23;
                TMP = strip_offset;
                if (i < 0xB) {
                    TMP = strip_offset + FIELD(item, s16, 0xA);
                    if ((screen_width >> 1) < TMP) {
                        TMP = screen_width >> 1;
                    }
                } else if (i >= 0xC) {
                    TMP = strip_offset - FIELD(item, s16, 0xA);
                    if (TMP < (screen_width >> 1)) {
                        TMP = screen_width >> 1;
                    }
                }

                left_coord = (u16)TMP + min_xy;
                FIELD(prim, s16, 0x10) = left_coord;
                FIELD(prim, s16, 8) = left_coord;
                right_x = left_coord + screen_width / 23;
                FIELD(prim, s16, 0x20) = right_x;
                FIELD(prim, s16, 0x18) = right_x;

                profile_storage = storage;
                top_y = FIELD(profile_storage, u16, 0x48 + i * 2) + (min_xy >> 16);
                FIELD(prim, s16, 0x1A) = top_y;
                FIELD(prim, s16, 0xA) = top_y;
                bottom_y = FIELD(profile_storage, u16, 0x48 + i * 2) + (max_xy >> 16);
                FIELD(prim, s16, 0x22) = bottom_y;
                FIELD(prim, s16, 0x12) = bottom_y;

                ot_offset = depth * 4;
                tag_mask = 0xFF000000;
                addr_mask = 0x00FFFFFF;
                context = FIELD(render_state, u8 *, 0);
                FIELD(prim, u32, 0) = (FIELD(prim, u32, 0) & tag_mask) |
                    (FIELD(context, u32, 0xB0 + ot_offset) & addr_mask);
                context2 = FIELD(render_state, u8 *, 0);
                FIELD(context2, u32, 0xB0 + ot_offset) =
                    (FIELD(context2, u32, 0xB0 + ot_offset) & tag_mask) |
                    ((u32)prim & addr_mask);

                i++;
            } while (i < 0x17);
        }

        next_node = FIELD(item_data, u8 *, -8);
        if (next_node == 0) {
            break;
        }
        item_data = next_node + 0x20;
    } while (1);
    return 0;
}
