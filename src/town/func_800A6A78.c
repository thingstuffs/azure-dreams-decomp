#include "common.h"

typedef struct S_800A41D8_0 {
    u8 pad_00[0x8];
    u16 unk_08;
    u8 pad_0A[0xC];
    u16 unk_16;
} S_800A41D8_0;   /* arg0 in func_800A41D8 */

typedef struct S_800A41D8_1 {
    u8 pad_00[0x8];
    union { s32 n; volatile s32 v; } unk_08;   /* accessed as both */
    union { s32 n; volatile s32 v; } unk_0C;   /* accessed as both */
    s32 unk_10;
    union { s32 n; volatile s32 v; } unk_14;   /* accessed as both */
    u8 pad_18[0x8];
    s32 unk_20;
    u8 pad_24[0x50];
    u16 unk_74;
    u8 pad_76[0x6];
    u16 unk_7C;
    u8 pad_7E[0x6];
    u16 unk_84;
    u8 pad_86[0x6];
    u16 unk_8C;
    u8 pad_8E[0x2];
    s32 unk_90;
    u8 pad_94[0x5C];
    union { struct { u16 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x2]; u16 v; } at02; } unk_F0;   /* overlapping accesses */
    union { struct { u16 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x2]; u16 v; } at02; } unk_F4;   /* overlapping accesses */
    union { struct { u16 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x2]; u16 v; } at02; } unk_F8;   /* overlapping accesses */
    union { struct { u16 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x2]; u16 v; } at02; } unk_FC;   /* overlapping accesses */
    u8 pad_100[0x18];
    s32 unk_118;
} S_800A41D8_1;   /* state in func_800A41D8 */

typedef struct S_800A41D8_2 {
    u8 pad_00[0x4];
    s8 unk_04;
    s8 unk_05;
    s8 unk_06;
    u8 pad_07[0x1];
    s32 unk_08;
    u8 pad_0C[0x4];
    s16 unk_10;
    s16 unk_12;
    u8 pad_14[0x4];
    s32 unk_18;
    u8 pad_1C[0x4];
    s16 unk_20;
    s16 unk_22;
    u8 pad_24[0x8];
    s8 unk_2C;
    u8 pad_2D[0xB];
    s32 unk_38;
    u8 pad_3C[0xC];
    s32 unk_48;
} S_800A41D8_2;   /* var_s3 in func_800A41D8 */

typedef struct S_800A41D8_3 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
    u8 pad_0C[0xC];
    s16 unk_18;
    s16 unk_1A;
} S_800A41D8_3;   /* temp_a0 in func_800A41D8 */

typedef struct S_800A41D8_4 {
    u8 pad_00[0x5];
    s8 unk_05;
    s8 unk_06;
} S_800A41D8_4;   /* temp_v0_7 in func_800A41D8 */

typedef struct S_800A41D8_5_pre {
    u8 unk_00;
    u8 pad_01[0xC];
    u8 unk_0D;
    u8 pad_0E[0x8];
    u8 unk_16;
    u8 pad_17[0x6];
    u8 unk_1D;
} S_800A41D8_5_pre;   /* the 0x1E bytes before var_s0 in func_800A41D8, addressed as var_s0[-1] */

typedef struct S_800A41D8_5 {
    u8 unk_00;
} S_800A41D8_5;   /* var_s0 in func_800A41D8 */

typedef struct S_800A41D8_6 {
    u8 pad_00[0xF];
    u8 unk_0F;
} S_800A41D8_6;   /* arg1 in func_800A41D8 */

typedef struct S_800A41D8_7 {
    s16 unk_00;
    u16 unk_02;
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 unk_07;
} S_800A41D8_7;   /* var_s2 in func_800A41D8 */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_80065610();
extern s32 func_80066460();
extern void func_8006658C();
extern void func_800666F4();
extern void func_80067F20();

/* Projects and draws visible textured strips, returning the next free primitive. */
void *func_800A41D8(void *origin, void *render_flags, void *draw_state, void *prim_buffer, u16 texture_index) {
    s32 buckets[2];
    u16 texture_id;
    u16 base_shade;
    u16 screen_y;
    s16 strip_shade;
    register s32 strip_offset ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s16 shade;
    register s32 uv_top ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 uv_value;
    s32 bucket_offset;
    s32 bucket;
    register s32 uv_left ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 uv_height ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 coord_value;
    s32 bottom_x;
    s32 top_y;
    s32 bottom_y;
    s32 third_visible;
    s32 first_three_visible;
    s32 first_pair_visible;
    s32 corner_visible;
    u16 origin_x;
    u16 uv_bottom;
    u16 uv_right;
    register s32 right_u ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u16 bottom_right_uv;
    u16 right_x;
    u16 left_x;
    u32 bucket_index;
    void *right_quad;
    void *draw_mode;
    void *right_colors;
    void *buffer_end;
    register void *packet_cursor ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    void *state;
    register void *entry_cursor ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register void *next_prim ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    s32 half_index;
    s32 texture_entry;
    s32 strip_index;
    s32 *bucket_list;
    s32 *bucket_slot;
    s32 bucket_addr;
    s32 visible_count;

    state = draw_state;
    next_prim = prim_buffer;
    visible_count = 0;
    strip_index = 0;
    texture_id = texture_index;
    bucket_list = buckets;
    ASM_KEEP(state);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    origin_x = ((S_800A41D8_0 *)origin)->unk_08;
    left_x = origin_x - 0x6200;
    right_x = origin_x - 0x5400;
    base_shade = ((S_800A41D8_0 *)origin)->unk_16;
    ((S_800A41D8_1 *)state)->unk_7C = left_x;
    ((S_800A41D8_1 *)state)->unk_74 = left_x;
    ((S_800A41D8_1 *)state)->unk_8C = right_x;
    ((S_800A41D8_1 *)state)->unk_84 = right_x;
    do {
        ((S_800A41D8_1 *)state)->unk_74 = (u16) (((S_800A41D8_1 *)state)->unk_74 + 0xE00);
        ((S_800A41D8_1 *)state)->unk_7C = (u16) (((S_800A41D8_1 *)state)->unk_7C + 0xE00);
        ((S_800A41D8_1 *)state)->unk_84 = (u16) (((S_800A41D8_1 *)state)->unk_84 + 0xE00);
        ((S_800A41D8_1 *)state)->unk_8C = (u16) (((S_800A41D8_1 *)state)->unk_8C + 0xE00);
        if (func_80065610(state + 0x70, state + 0x78, state + 0x80, state + 0x88, state + 0xF0, state + 0xF4, state + 0xF8, state + 0xFC, state + 0x90, state + 0xC0, state + 0x94) > 0) {
            first_pair_visible = 0;
            if ((u32) ((((S_800A41D8_1 *)state)->unk_F0.at00.v + 0x20) & 0xFFFF) < 0x181U) {
                screen_y = ((S_800A41D8_1 *)state)->unk_F0.at02.v + 0x20;
                first_pair_visible = screen_y < 0x121U;
            }
            corner_visible = 0;
            if ((u32) ((((S_800A41D8_1 *)state)->unk_F4.at00.v + 0x20) & 0xFFFF) < 0x181U) {
                screen_y = ((S_800A41D8_1 *)state)->unk_F4.at02.v + 0x20;
                corner_visible = screen_y < 0x121U;
            }
            third_visible = 0;
            first_pair_visible |= corner_visible;
            if ((u32) ((((S_800A41D8_1 *)state)->unk_F8.at00.v + 0x20) & 0xFFFF) < 0x181U) {
                screen_y = ((S_800A41D8_1 *)state)->unk_F8.at02.v + 0x20;
                third_visible = screen_y < 0x121U;
            }
            corner_visible = 0;
            first_three_visible = first_pair_visible | third_visible;
            if ((u32) ((((S_800A41D8_1 *)state)->unk_FC.at00.v + 0x20) & 0xFFFF) < 0x181U) {
                screen_y = ((S_800A41D8_1 *)state)->unk_FC.at02.v + 0x20;
                corner_visible = screen_y < 0x121U;
            }
            if ((first_three_visible | corner_visible) != 0) {
                right_quad = next_prim + 0x28;
                ((S_800A41D8_2 *)next_prim)->unk_08 = ((S_800A41D8_1 *)state)->unk_F0.at00u.v;
                ((S_800A41D8_2 *)next_prim)->unk_18 = ((S_800A41D8_1 *)state)->unk_F8.at00u.v;
                ((S_800A41D8_2 *)next_prim)->unk_38 = ((S_800A41D8_1 *)state)->unk_F4.at00u.v;
                ((S_800A41D8_2 *)next_prim)->unk_48 = ((S_800A41D8_1 *)state)->unk_FC.at00u.v;
                coord_value = (s32) ((s16) ((S_800A41D8_1 *)state)->unk_F0.at00.v + (s16) ((S_800A41D8_1 *)state)->unk_F4.at00.v) >> 1;
                ((S_800A41D8_3 *)right_quad)->unk_08 = (s16) coord_value;
                ((S_800A41D8_2 *)next_prim)->unk_10 = (s16) coord_value;
                bottom_x = (s32) ((s16) ((S_800A41D8_1 *)state)->unk_F8.at00.v + (s16) ((S_800A41D8_1 *)state)->unk_FC.at00.v) >> 1;
                ((S_800A41D8_3 *)right_quad)->unk_18 = (s16) bottom_x;
                ((S_800A41D8_2 *)next_prim)->unk_20 = (s16) bottom_x;
                top_y = (s32) ((s16) ((S_800A41D8_1 *)state)->unk_F0.at02.v + (s16) ((S_800A41D8_1 *)state)->unk_F4.at02.v) >> 1;
                ((S_800A41D8_3 *)right_quad)->unk_0A = (s16) top_y;
                ((S_800A41D8_2 *)next_prim)->unk_12 = (s16) top_y;
                bottom_y = (s32) ((s16) ((S_800A41D8_1 *)state)->unk_F8.at02.v + (s16) ((S_800A41D8_1 *)state)->unk_FC.at02.v) >> 1;
                ((S_800A41D8_3 *)right_quad)->unk_1A = (s16) bottom_y;
                ((S_800A41D8_2 *)next_prim)->unk_22 = (s16) bottom_y;
                strip_offset = (s16) ((S_800A41D8_1 *)state)->unk_74 % 3584;
                ((S_800A41D8_1 *)state)->unk_90 = (s32) strip_offset;
                if (strip_offset < 0) {
                    strip_offset += 0xFF;
                }
                coord_value = strip_offset >> 8;
                ((S_800A41D8_1 *)state)->unk_90 = coord_value;
                strip_shade = (base_shade + (strip_index * 0xE)) - 0x40;
                shade = 0x80;
                if (strip_shade < 0x81) {
                    shade = strip_shade;
                    if (strip_shade < 0) {
                        shade = 0;
                    }
                }
                half_index = 0;
                packet_cursor = next_prim + 0x25;
                right_colors = next_prim + 0x28;
                ((S_800A41D8_2 *)next_prim)->unk_06 = (s8) shade;
                ((S_800A41D8_4 *)right_colors)->unk_06 = (s8) shade;
                ((S_800A41D8_2 *)next_prim)->unk_05 = (s8) shade;
                ((S_800A41D8_4 *)right_colors)->unk_05 = (s8) shade;
                ((S_800A41D8_2 *)next_prim)->unk_04 = (s8) shade;
                ((S_800A41D8_2 *)next_prim)->unk_2C = (s8) shade;
                texture_entry = ((S_800A41D8_1 *)state)->unk_118 + ((((strip_index & 1) * 2) + ((s32) (texture_id << 0x10) >> 0xE)) * 0xC);
                entry_cursor = texture_entry + 4;
                do {
                    func_800666F4(next_prim);
                    ((S_800A41D8_5_pre *)packet_cursor)[-1].unk_00 = (u8) (((S_800A41D8_5_pre *)packet_cursor)[-1].unk_00 | (((S_800A41D8_6 *)render_flags)->unk_0F & 2));
                    ((S_800A41D8_1 *)state)->unk_08.n = (s32) ((S_800A41D8_7 *)entry_cursor)->unk_04;
                    ((S_800A41D8_1 *)state)->unk_0C.n = (s32) ((S_800A41D8_7 *)entry_cursor)->unk_05;
                    uv_left = ((S_800A41D8_1 *)state)->unk_08.v;
                    uv_top = ((S_800A41D8_1 *)state)->unk_0C.v;
                    ((S_800A41D8_1 *)state)->unk_10 = (s32) ((S_800A41D8_7 *)entry_cursor)->unk_06;
                    uv_value = uv_top;
                    ((S_800A41D8_1 *)state)->unk_14.n = (s32) ((S_800A41D8_7 *)entry_cursor)->unk_07;
                    uv_top <<= 8;
                    ((S_800A41D8_1 *)state)->unk_0C.n = uv_top;
                    uv_height = ((S_800A41D8_1 *)state)->unk_14.v;
                    uv_value += uv_height;
                    uv_value <<= 8;
                    ((S_800A41D8_1 *)state)->unk_14.n = uv_value;
                    ((S_800A41D8_1 *)state)->unk_10 = (s32) (((S_800A41D8_1 *)state)->unk_10 + uv_left);
                    uv_value = uv_left;
                    ASM_KEEP_NV(uv_value);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                    (*(s32 *)((u8 *)packet_cursor + -0x19)) = (s32) ((uv_top + uv_value) | (((S_800A41D8_7 *)entry_cursor)->unk_02 << 0x10));
                    (*(s32 *)((u8 *)packet_cursor + -0x11)) = (s32) ((((S_800A41D8_1 *)state)->unk_0C.n + ((S_800A41D8_1 *)state)->unk_10) | (((S_800A41D8_7 *)entry_cursor)->unk_00 << 0x10));
                    (*(s16 *)((u8 *)packet_cursor + -9)) = (s16) ((u16) ((S_800A41D8_1 *)state)->unk_14.n + (u16) ((S_800A41D8_1 *)state)->unk_08.n);
                    right_u = ((S_800A41D8_5_pre *)packet_cursor)[-1].unk_0D;
                    uv_bottom = (u16) ((S_800A41D8_1 *)state)->unk_14.n;
                    uv_right = (u16) ((S_800A41D8_1 *)state)->unk_10;
                    bottom_right_uv = uv_bottom + uv_right;
                    do {
                        right_u -= 1;
                    } while (0);
                    (*(s16 *)((u8 *)packet_cursor + -1)) = (s16) bottom_right_uv;
                    do {
                        ((S_800A41D8_5_pre *)packet_cursor)[-1].unk_0D = (u8) right_u;
                    } while (0);
                    ((S_800A41D8_5_pre *)packet_cursor)[-1].unk_1D = (u8) (((S_800A41D8_5_pre *)packet_cursor)[-1].unk_1D - 1);
                    ((S_800A41D8_5_pre *)packet_cursor)[-1].unk_16 = (u8) (((S_800A41D8_5_pre *)packet_cursor)[-1].unk_16 - 1);
                    ((S_800A41D8_5 *)packet_cursor)->unk_00 = (u8) (((S_800A41D8_5 *)packet_cursor)->unk_00 - 1);
                    func_8006658C(((S_800A41D8_1 *)state)->unk_20 + (((u32) ((s32) (0 - ((texture_entry - ((S_800A41D8_1 *)state)->unk_118) * 0x55555555)) >> 2) / 12U) * 4), next_prim);
                    bucket_index = (u32) ((s32) (0 - ((texture_entry - ((S_800A41D8_1 *)state)->unk_118) * 0x55555555)) >> 2) / 12U;
                    entry_cursor += 0xC;
                    packet_cursor += 0x28;
                    next_prim += 0x28;
                    bucket_offset = half_index * 4;
                    half_index += 1;
                    bucket_slot = (s32 *)(bucket_offset + (s32) bucket_list);
                    texture_entry += 0xC;
                    bucket_addr = ((S_800A41D8_1 *)state)->unk_20;
                    bucket_addr += bucket_index * 4;
                    *bucket_slot = bucket_addr;
                } while (half_index < 2);
                packet_cursor = next_prim;
                half_index = 0;
                entry_cursor = bucket_list;
                do {
                    func_80067F20(packet_cursor, 1, 0, func_80066460(0, 0, 0x140, 0) & 0xFFFF, 0);
                    draw_mode = packet_cursor;
                    packet_cursor += 0xC;
                    bucket = *(s32 *)entry_cursor;
                    entry_cursor += 4;
                    half_index += 1;
                    func_8006658C(bucket, draw_mode);
                } while (half_index < 2);
                next_prim = packet_cursor;
                visible_count += 1;
            }
        }
        strip_index += 1;
    } while (strip_index < 0xE);
    buffer_end = 0;
    if (visible_count != 0) {
        buffer_end = next_prim;
    }
    return buffer_end;
}
