#include "common.h"

typedef s32 M2C_UNK;

#ifndef NULL
#define NULL 0
#endif

typedef struct S_801749EC_0 {
    u8 pad_00[0x6];
    s16 unk_06;
} S_801749EC_0;   /* arg0 in func_801749EC */

typedef struct S_801749EC_1_pre {
    u16 unk_00;
} S_801749EC_1_pre;   /* the 0x2 bytes before state in func_801749EC, addressed as state[-1] */

typedef struct S_801749EC_1 {
    u8 pad_00[0x6];
    u16 unk_06;
    s16 unk_08;
    u8 pad_0A[0x2];
    u16 unk_0C;
} S_801749EC_1;   /* state in func_801749EC */

typedef struct S_801749EC_2_pre {
    u16 unk_00;
} S_801749EC_2_pre;   /* the 0x2 bytes before temp_v1_2 in func_801749EC, addressed as temp_v1_2[-1] */

typedef struct S_801749EC_2 {
    s16 unk_00;
} S_801749EC_2;   /* temp_v1_2 in func_801749EC */

typedef struct S_801749EC_3 {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
} S_801749EC_3;   /* temp_s2 in func_801749EC */

typedef struct S_801749EC_4 {
    s16 unk_00;
    u16 unk_02;
} S_801749EC_4;   /* temp_v1_3 in func_801749EC */

typedef struct S_801749EC_5 {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
} S_801749EC_5;   /* temp_s2_2 in func_801749EC */

typedef struct S_801749EC_6 {
    u8 pad_00[0x1A];
    s16 unk_1A;
    s16 unk_1C;
    u8 pad_1E[0x46];
    u16 unk_64;
    u16 unk_66;
    u16 unk_68;
    u16 unk_6A;
    u16 unk_6C;
    u16 unk_6E;
} S_801749EC_6;   /* temp_s1_3 in func_801749EC */

typedef struct S_801749EC_7 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_801749EC_7;   /* temp_v0_12 in func_801749EC */

typedef struct S_801749EC_8 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
} S_801749EC_8;   /* temp_a0 in func_801749EC */

typedef struct S_801749EC_9 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_801749EC_9;   /* temp_v1_4 in func_801749EC */

typedef struct S_801749EC_10 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_801749EC_10;   /* object_origin in func_801749EC */

typedef struct S_801749EC_11 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_801749EC_11;   /* color in func_801749EC */

typedef struct S_801749EC_12 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
} S_801749EC_12;   /* temp_v0_13 in func_801749EC */

typedef struct S_801749EC_13 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
} S_801749EC_13;   /* temp_a0_4 in func_801749EC */

typedef struct S_801749EC_14 {
    u8 pad_00[0x1A];
    s16 unk_1A;
    s16 unk_1C;
    u8 pad_1E[0x46];
    u16 unk_64;
    u16 unk_66;
    u16 unk_68;
    u16 unk_6A;
    u16 unk_6C;
    u16 unk_6E;
} S_801749EC_14;   /* temp_s1_4 in func_801749EC */

typedef struct S_801749EC_15 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_801749EC_15;   /* temp_v0_14 in func_801749EC */

typedef struct S_801749EC_16 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
} S_801749EC_16;   /* temp_a0_5 in func_801749EC */

typedef struct S_801749EC_17 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_801749EC_17;   /* temp_v1_5 in func_801749EC */

typedef struct S_801749EC_18 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_801749EC_18;   /* temp_a0_6 in func_801749EC */

typedef struct S_801749EC_19 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
} S_801749EC_19;   /* temp_v0_15 in func_801749EC */

typedef struct S_801749EC_20 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
} S_801749EC_20;   /* temp_s4 in func_801749EC */

typedef struct S_801749EC_21 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
} S_801749EC_21;   /* temp_v0_16 in func_801749EC */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

void *func_8003FC64(s32);
void func_8004491C(void *, void *);
s32 func_800644B8(s32);
s32 func_80064584(s32);
extern M2C_UNK D_800814A0;
extern M2C_UNK D_80174954;
extern M2C_UNK D_801749A8;

/* Build an animated spherical wireframe and advance its lifetime. */
void func_801749EC(void *effect, void *origin, void *tint) {
    s16 ring_angles[10];
    s16 vertices[10][6][3];
    s16 *volatile opening_angles;
    s16 *volatile closing_angles;
    register void *object_origin;
    M2C_UNK *line_data;
    s16 *angle_or_vertices;
    s16 *closing_angle;
    s16 next_angle_index;
    s16 next_meridian;
    s16 next_ring;
    s16 remaining_ticks;
    s16 opening_angle;
    s16 next_opening_ring;
    s16 next_opening_sector;
    s16 closing_angle_value;
    s16 next_closing_ring;
    s16 next_closing_sector;
    s16 prev_angle_index;
    s16 phase;
    s16 meridian;
    s16 ring_sector;
    register s16 sector ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s16 segment ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s16 ring;
    s16 ring_index;
    s16 next_segment;
    s16 next_ring_sector;
    s32 sector_offset;
    s32 segment_index;
    s32 opening_azimuth;
    s32 closing_azimuth;
    s32 opening_sector_radius;
    s32 closing_sector_radius;
    s32 vertex_base_or_offset;
    s32 radius;
    s32 vertex_offset;
    register s32 signed_ring_index;
    s32 ring_index_shifted;
    u16 closing_progress;
    u16 opening_progress;
    u16 old_phase;
    void *meridian_render;
    void *segment_start;
    void *ring_render;
    register void *ring_color ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register void *meridian_line ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    register void *ring_line ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    void *opening_vertex;
    void *closing_vertex;
    void *sector_or_ring_start;
    register void *color ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    void *meridian_object;
    void *segment_end;
    void *ring_object;
    void *next_vertex;
    void *current_vertex;
    void *opening_angle_slot;
    void *closing_angle_slot;
    void *meridian_origin;
    void *ring_origin;
    register M2C_UNK *ring_data;

    (void)&effect;
    object_origin = origin;
    phase = ((S_801749EC_0 *)effect)->unk_06;
    if (phase != 1) {
        meridian = 0;
        if (phase < 2) {
            if (phase == 0) {
                register s32 scale ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                s16 *angle_base;
                s32 angle_limit;
                register s32 state ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                scale = 0x1E;
                ring_index = 1;
                state = (s32) *(void *volatile *)&effect;
                angle_base = ring_angles;
                angle_limit = 0x400;
                ring_angles[0] = (0 - ((S_801749EC_1 *)state)->unk_0C) + 0x400;
                do {
                    opening_angle_slot = (void *)(((ring_index << 0x10) >> 0xF) + (s32)angle_base);
                    opening_angle = ((S_801749EC_2_pre *)opening_angle_slot)[-1].unk_00 + 0xCC;
                    ((S_801749EC_2 *)opening_angle_slot)->unk_00 = opening_angle;
                    if (opening_angle >= 0x401) {
                        ((S_801749EC_2 *)opening_angle_slot)->unk_00 = angle_limit;
                    }
                    next_angle_index = ring_index + 1;
                    ring_index = next_angle_index;
                } while (next_angle_index < 0xA);
                ring_index = 0;
                state = (s32) ring_angles;
                opening_angles = (void *) state;
                radius = scale;
                do {
                    sector = 0;
                    ring_index_shifted = ring_index << 0x10;
                    signed_ring_index = ring_index_shifted >> 0x10;
                    state = (s32) opening_angles;
                    {
                        s32 scaled_outer;
                        scaled_outer = signed_ring_index << 1;
                        angle_or_vertices = (s16 *) (scaled_outer + state);
                    }
opening_sector_loop:
                    opening_sector_radius = sector << 0x10;
                    state = radius * func_800644B8(*angle_or_vertices);
                    opening_sector_radius >>= 0x10;
                    vertex_offset = (opening_sector_radius * 6) + (signed_ring_index * 0x24);
                    opening_vertex = (s8 *)vertices + vertex_offset;
                    {
                        register s32 coordinate ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                        coordinate = state >> 0xC;
                        ((S_801749EC_3 *)opening_vertex)->unk_04 = (s16) coordinate;
                    }
                    opening_azimuth = opening_sector_radius << 2;
                    state = radius * func_80064584(*angle_or_vertices);
                    opening_azimuth += opening_sector_radius;
                    opening_azimuth += opening_azimuth << 4;
                    opening_azimuth <<= 2;
                    opening_azimuth += opening_sector_radius;
                    opening_azimuth <<= 1;
                    opening_sector_radius = state >> 0xC;
                    state = (s16) opening_sector_radius * func_80064584(opening_azimuth);
                    {
                        register s32 coordinate ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                        coordinate = state >> 0xC;
                        ((S_801749EC_3 *)opening_vertex)->unk_00 = (s16) coordinate;
                    }
                    next_opening_sector = sector + 1;
                    sector = next_opening_sector;
                    state = (s16) opening_sector_radius * func_800644B8(opening_azimuth);
                    {
                        register s32 y_coordinate ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                        y_coordinate = state >> 0xC;
                        ((S_801749EC_3 *)opening_vertex)->unk_02 = (s16) y_coordinate;
                    }
                    if (next_opening_sector < 6) {
                        goto opening_sector_loop;
                    }
                    next_opening_ring = ring_index + 1;
                    ring_index = next_opening_ring;
                } while (next_opening_ring < 0xA);
                state = (s32) *(void *volatile *)&effect;
                opening_progress = ((S_801749EC_1 *)state)->unk_0C + 0x64;
                ((S_801749EC_1 *)state)->unk_0C = opening_progress;
                if ((s16) opening_progress >= 0x800) {
                    ((S_801749EC_1 *)state)->unk_0C = 0x800U;
                }
                meridian = 0;
                state = (s32) *(void *volatile *)&effect;
                if (((S_801749EC_1 *)state)->unk_08 < 0x16) {
                    old_phase = ((S_801749EC_1 *)state)->unk_06;
                    ((S_801749EC_1 *)state)->unk_0C = 0U;
                    ((S_801749EC_1 *)state)->unk_06 = old_phase + 1;
                    goto select_line_data;
                }
                goto select_line_data;
            }
            line_data = &D_801749A8;
            goto build_lines;
        }
        goto select_line_data;
    }
    {
    register s32 scale ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s16 *angle_base;
    s32 angle_limit;
    register s32 state ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    scale = 0x1E;
    ring_index = 8;
    state = (s32) *(void *volatile *)&effect;
    angle_base = ring_angles;
    angle_limit = -0x400;
    ring_angles[9] = (0 - ((S_801749EC_1 *)state)->unk_0C) + 0x400;
    do {
        closing_angle_slot = (void *)(((ring_index << 0x10) >> 0xF) + (s32)angle_base);
        closing_angle_value = ((S_801749EC_4 *)closing_angle_slot)->unk_02 - 0xCC;
        ((S_801749EC_4 *)closing_angle_slot)->unk_00 = closing_angle_value;
        if (closing_angle_value < -0x400) {
            ((S_801749EC_4 *)closing_angle_slot)->unk_00 = angle_limit;
        }
        prev_angle_index = ring_index - 1;
        ring_index = prev_angle_index;
    } while ((prev_angle_index << 0x10) != 0);
    ring_index = 0;
    state = (s32) ring_angles;
    closing_angles = (void *) state;
    radius = scale;
    do {
        sector = 0;
        ring_index_shifted = ring_index << 0x10;
        signed_ring_index = ring_index_shifted >> 0x10;
        state = (s32) closing_angles;
        {
            s32 scaled_outer;
            scaled_outer = signed_ring_index << 1;
            closing_angle = (s16 *) (scaled_outer + state);
        }
closing_sector_loop:
        closing_sector_radius = sector << 0x10;
        state = radius * func_800644B8(*closing_angle);
        closing_sector_radius >>= 0x10;
        vertex_offset = (closing_sector_radius * 6) + (signed_ring_index * 0x24);
        closing_vertex = (s8 *)vertices + vertex_offset;
        {
            register s32 coordinate ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            coordinate = state >> 0xC;
            ((S_801749EC_5 *)closing_vertex)->unk_04 = (s16) coordinate;
        }
        closing_azimuth = closing_sector_radius << 2;
        state = radius * func_80064584(*closing_angle);
        closing_azimuth += closing_sector_radius;
        closing_azimuth += closing_azimuth << 4;
        closing_azimuth <<= 2;
        closing_azimuth += closing_sector_radius;
        closing_azimuth <<= 1;
        closing_sector_radius = state >> 0xC;
        state = (s16) closing_sector_radius * func_80064584(closing_azimuth);
        {
            register s32 coordinate ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            coordinate = state >> 0xC;
            ((S_801749EC_5 *)closing_vertex)->unk_00 = (s16) coordinate;
        }
        next_closing_sector = sector + 1;
        sector = next_closing_sector;
        state = (s16) closing_sector_radius * func_800644B8(closing_azimuth);
        {
            register s32 y_coordinate ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            y_coordinate = state >> 0xC;
            ((S_801749EC_5 *)closing_vertex)->unk_02 = (s16) y_coordinate;
        }
        if (next_closing_sector < 6) {
            goto closing_sector_loop;
        }
        next_closing_ring = ring_index + 1;
        ring_index = next_closing_ring;
    } while (next_closing_ring < 0xA);
    state = (s32) *(void *volatile *)&effect;
    closing_progress = ((S_801749EC_1 *)state)->unk_0C + 0x64;
    ((S_801749EC_1 *)state)->unk_0C = closing_progress;
    if ((s16) closing_progress >= 0x800) {
        ((S_801749EC_1 *)state)->unk_0C = 0x800U;
    }
    meridian = 0;
    }
select_line_data:
    line_data = &D_801749A8;
build_lines:
    vertex_base_or_offset = (s32)vertices;
    ASM_USE_NV(vertex_base_or_offset);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    segment = 0;
    do {
        {
            s32 sector_shifted;
            sector_shifted = meridian << 0x10;
            sector_or_ring_start = (void *) (sector_shifted >> 0x10);
        }
meridian_segment_loop:
        meridian_object = func_8003FC64(0x212);
        if (meridian_object == NULL) {
            goto next_meridian_segment;
        }
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
        meridian_line = meridian_object + 0x20;
        ((S_801749EC_6 *)meridian_line)->unk_1A = 1;
        ((S_801749EC_6 *)meridian_line)->unk_1C = 1;
        ((S_801749EC_7 *)meridian_object)->unk_10 = line_data;
        func_8004491C(meridian_object, &D_80174954);
        meridian_render = ((S_801749EC_7 *)meridian_object)->unk_0C;
        ((S_801749EC_8 *)meridian_render)->unk_10 = 0x20;
        ((S_801749EC_8 *)meridian_render)->unk_14 = (u16) (((S_801749EC_8 *)meridian_render)->unk_14 | 0xC);
        meridian_origin = ((S_801749EC_7 *)meridian_object)->unk_08;
        ((S_801749EC_9 *)meridian_origin)->unk_00 = (s32) ((S_801749EC_10 *)object_origin)->unk_00;
        ((S_801749EC_9 *)meridian_origin)->unk_04 = (s32) ((S_801749EC_10 *)object_origin)->unk_04;
        ((S_801749EC_9 *)meridian_origin)->unk_08 = (s32) ((S_801749EC_10 *)object_origin)->unk_08;
        meridian_render = ((S_801749EC_7 *)meridian_object)->unk_0C;
        (*(s16 *)((u8 *)meridian_render + 0x1E)) = 0x1000;
        (*(s16 *)((u8 *)meridian_render + 0x1C)) = 0x1000;
        color = *(void *volatile *)&tint;
        ((S_801749EC_8 *)meridian_render)->unk_0C = (u8) ((S_801749EC_11 *)color)->unk_0C;
        ((S_801749EC_8 *)meridian_render)->unk_0D = (u8) ((S_801749EC_11 *)color)->unk_0D;
        ((S_801749EC_8 *)meridian_render)->unk_0E = (u8) ((S_801749EC_11 *)color)->unk_0E;
        segment_index = segment << 0x10;
        segment_index >>= 0x10;
        sector_offset = (s32) sector_or_ring_start * 6;
        segment_end = (s8 *)vertices + (sector_offset + ((segment_index + 1) * 0x24));
        ((S_801749EC_6 *)meridian_line)->unk_64 = (u16) ((S_801749EC_12 *)segment_end)->unk_00;
        ((S_801749EC_6 *)meridian_line)->unk_66 = (u16) ((S_801749EC_12 *)segment_end)->unk_02;
        ((S_801749EC_6 *)meridian_line)->unk_68 = (u16) ((S_801749EC_12 *)segment_end)->unk_04;
        segment_start = (s8 *)vertices + (sector_offset + (segment_index * 0x24));
        ((S_801749EC_6 *)meridian_line)->unk_6A = (u16) ((S_801749EC_13 *)segment_start)->unk_00;
        ((S_801749EC_6 *)meridian_line)->unk_6C = (u16) ((S_801749EC_13 *)segment_start)->unk_02;
        ((S_801749EC_6 *)meridian_line)->unk_6E = (u16) ((S_801749EC_13 *)segment_start)->unk_04;
next_meridian_segment:
        next_segment = segment + 1;
        segment = next_segment;
        if (next_segment < 9) {
            goto meridian_segment_loop;
        }
        segment = 0;
        next_meridian = meridian + 1;
        meridian = next_meridian;
    } while (next_meridian < 6);
    ring = 1;
    ring_data = &D_801749A8;
    angle_or_vertices = (s16 *)vertices;
ring_loop:
    ring_sector = 0;
    {
        s32 signed_outer;
        s32 scaled_outer;
        signed_outer = ring;
        scaled_outer = (signed_outer << 3) + signed_outer;
        vertex_base_or_offset = scaled_outer << 2;
    }
    sector_or_ring_start = (s8 *)angle_or_vertices + vertex_base_or_offset;
ring_sector_loop:
    ring_object = func_8003FC64(0x212);
    if (ring_object == NULL) {
        goto advance_ring_sector;
    }
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    ring_line = ring_object + 0x20;
    ((S_801749EC_14 *)ring_line)->unk_1A = 1;
    ((S_801749EC_14 *)ring_line)->unk_1C = 1;
    ((S_801749EC_15 *)ring_object)->unk_10 = ring_data;
    func_8004491C(ring_object, &D_80174954);
    ring_render = ((S_801749EC_15 *)ring_object)->unk_0C;
    {
        u16 object_flags;
        register s32 object_width ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        object_flags = ((S_801749EC_16 *)ring_render)->unk_14;
        object_width = 0x20;
        ((S_801749EC_16 *)ring_render)->unk_10 = object_width;
        object_flags |= 0xC;
        ((S_801749EC_16 *)ring_render)->unk_14 = object_flags;
    }
    ring_origin = ((S_801749EC_15 *)ring_object)->unk_08;
    ((S_801749EC_17 *)ring_origin)->unk_00 = (s32) ((S_801749EC_10 *)object_origin)->unk_00;
    ((S_801749EC_17 *)ring_origin)->unk_04 = (s32) ((S_801749EC_10 *)object_origin)->unk_04;
    ((S_801749EC_17 *)ring_origin)->unk_08 = (s32) ((S_801749EC_10 *)object_origin)->unk_08;
    ring_color = ((S_801749EC_15 *)ring_object)->unk_0C;
    (*(s16 *)((u8 *)ring_color + 0x1E)) = 0x1000;
    (*(s16 *)((u8 *)ring_color + 0x1C)) = 0x1000;
    color = *(void *volatile *)&tint;
    ((S_801749EC_18 *)ring_color)->unk_0C = (u8) ((S_801749EC_11 *)color)->unk_0C;
    ((S_801749EC_18 *)ring_color)->unk_0D = (u8) ((S_801749EC_11 *)color)->unk_0D;
    ((S_801749EC_18 *)ring_color)->unk_0E = (u8) ((S_801749EC_11 *)color)->unk_0E;
    if (ring_sector != 5) {
        next_vertex = (s8 *)angle_or_vertices + (((ring_sector + 1) * 6) + vertex_base_or_offset);
        ((S_801749EC_14 *)ring_line)->unk_64 = (u16) ((S_801749EC_19 *)next_vertex)->unk_00;
        ((S_801749EC_14 *)ring_line)->unk_66 = (u16) ((S_801749EC_19 *)next_vertex)->unk_02;
        ((S_801749EC_14 *)ring_line)->unk_68 = (u16) ((S_801749EC_19 *)next_vertex)->unk_04;
        goto set_ring_start;
    }
    ((S_801749EC_14 *)ring_line)->unk_64 = (u16) ((S_801749EC_20 *)sector_or_ring_start)->unk_00;
    ((S_801749EC_14 *)ring_line)->unk_66 = (u16) ((S_801749EC_20 *)sector_or_ring_start)->unk_02;
    ((S_801749EC_14 *)ring_line)->unk_68 = (u16) ((S_801749EC_20 *)sector_or_ring_start)->unk_04;
set_ring_start:
    current_vertex = (s8 *)angle_or_vertices + ((ring_sector * 6) + vertex_base_or_offset);
    ((S_801749EC_14 *)ring_line)->unk_6A = (u16) ((S_801749EC_21 *)current_vertex)->unk_00;
    ((S_801749EC_14 *)ring_line)->unk_6C = (u16) ((S_801749EC_21 *)current_vertex)->unk_02;
    ((S_801749EC_14 *)ring_line)->unk_6E = (u16) ((S_801749EC_21 *)current_vertex)->unk_04;
advance_ring_sector:
    next_ring_sector = ring_sector + 1;
    ring_sector = next_ring_sector;
    if (next_ring_sector < 6) {
        goto ring_sector_loop;
    }
    next_ring = ring + 1;
    ring = next_ring;
    if (next_ring < 9) {
        goto ring_loop;
    }
    {
        register void *state ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        state = *(void *volatile *)&effect;
        remaining_ticks = (u16) ((S_801749EC_1 *)state)->unk_08 - 1;
        ((S_801749EC_1 *)state)->unk_08 = remaining_ticks;
        if ((remaining_ticks << 0x10) <= 0) {
            (*(u16 *)((u8 *)state + -2)) = (u16) (((S_801749EC_1_pre *)state)[-1].unk_00 | 0x8000);
            D_800814A0 = D_800814A0 | 0x8000;
        }
        return;
    }
}
