/* Mandara effect phase updates and layered wavy-strip rendering. */
#include "common.h"
#include "shared/game_work.h"
#include "dungeon/effect/particle.h"
#include "dungeon/monster/mandara.h"
#include "sdk/libgpu.h"
#include "sdk/libgte.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 pad;
} Vertex;

typedef struct {
    s32 value;
} __attribute__((packed)) PackedS32;

typedef struct {
    s32 w0;
    s32 w1;
} __attribute__((packed)) PackedPair;

typedef struct {
    s16 screen[2];
    s32 outer;
} Scratch;

typedef struct {
    void *vertices;
    void *output;
    s16 pad08;
    s16 pad0A;
    s16 z;
    s16 pad0E;
    PackedPair v10;
    s16 count;
    s16 pad1A;
    s32 pad1C;
} Projection;

extern u8 D_8017089C[];
extern u8 upper_draw_context[];

/* Adds 80 and four times the layer index to the phase. */
static __inline__ s32 advance_phase(s32 phase, s32 layer)
{
    phase += 80;
    return phase + (layer << 2);
}

/*
 * Projects linked objects into four layers of wavy textured strips and queues them at their
 * average depth.
 */
typedef union {
    s32 word;
    struct { u16 x; u16 y; } parts;
} PackedScreenPoint;

s32 draw_layered_wavy_object_strips(void *object_data, void *unused, void *appearance)
{
    s16 bounds[4];
    PackedPair material;
    Vertex vertices[4];
    Projection projection;
    Scratch scratch;
    void *object;
    Projection *projection_ptr;
    s32 bottom_y;
    s32 first_y;
    s32 depth;
    Vertex *vertex_base;
    s32 row_count;
    s32 depth_offset;
    u8 *vertex_bytes;
    u8 *poly;
    s32 index_or_row;
    PackedScreenPoint min_xy;
    PackedScreenPoint max_xy;
    s32 depth_out_or_phase;
    s32 last_y;
    register s32 row_span;
    register s32 crop_y;
    GameWork *render_state;
    (void) unused;
    render_state = &g_game_work;
    material = *((PackedPair *) D_8017089C);
    depth = 0;
    vertex_base = vertices;
    for (;;) {
        s32 right_x;
        s32 left_x;
        s32 camera_z;
        s16 min_y;
        s16 max_y;
        s32 base_y;
        s16 height;
        s16 top_page;
        s32 top_page_index;
        s32 left_bound;
        s32 height_pixels;
        s32 top_bound;
        s32 bottom_bound;
        s32 top_copy;
        s32 crop_product;
        s32 bottom_page;
        void *next_object;
        scratch.outer = 48;
        right_x = (u16) scratch.outer;
        index_or_row = 3;
        bottom_bound = -160;
        object = object_data;
        height_pixels = 16;
        left_x = -right_x;

        do {
            vertex_base[index_or_row].x = right_x;
            if (index_or_row < 2) {
                vertex_base[index_or_row].x = left_x;
            }
            vertex_base[index_or_row].y = 0;
            if (index_or_row & 1) {
                vertex_base[index_or_row].z = bottom_bound;
            }
            else {
                vertex_base[index_or_row].z = height_pixels;
            }
            index_or_row--;
        } while (index_or_row >= 0);
        projection_ptr = &projection;
        camera_z = *(u16 *)&render_state->view.camera_rotation.parts.viewAngle;
        projection.pad0A = 0;
        projection.pad08 = 0;
        projection.vertices = vertex_base;
        projection.output = vertex_base;
        projection.z = -camera_z;
        projection.v10 = *((PackedPair *) (((u8 *) object) + 0xA2));
        projection.count = 4;
        projection.pad1A = 0;
        transform_rotated_vertices(projection_ptr);
        min_xy.parts.y = 0x7530;
        min_xy.parts.x = 0x7530;
        max_xy.parts.y = 0x8AD0;
        max_xy.parts.x = 0x8AD0;
        index_or_row = 3;
        depth_out_or_phase = (s32) (&scratch.outer);
        vertex_bytes = ((u8 *) vertex_base) + 24;
        do {
            s32 vertex_depth;
            s32 screen_x;
            u16 x_bits;
            s32 screen_y;
            u16 y_bits;
            vertex_depth = RotTransPers(vertex_bytes, scratch.screen, (void *) depth_out_or_phase,
                (void *) depth_out_or_phase);
            depth += vertex_depth - 8;
            x_bits = (u16) scratch.screen[0];
            screen_x = scratch.screen[0];
            if (((s16) max_xy.word) < screen_x) {
                max_xy.word &= 0xFFFF0000;
                max_xy.word = x_bits | max_xy.word;
            }
            else if (screen_x < ((s16) min_xy.word)) {
                min_xy.word &= 0xFFFF0000;
                min_xy.word = x_bits | min_xy.word;
            }
            screen_y = scratch.screen[1];
            y_bits = (u16) scratch.screen[1];
            if (((s16) (max_xy.word >> 16)) < screen_y) {
                max_xy.word &= 0xFFFF;
                max_xy.word |= y_bits << 16;
            }
            else if (screen_y < ((s16) (min_xy.word >> 16))) {
                min_xy.word &= 0xFFFF;
                min_xy.word |= y_bits << 16;
            }
            index_or_row--;
            vertex_bytes -= 8;
        }
        while (index_or_row >= 0);
        left_bound = (s16) min_xy.word;
        min_y = (s16) (min_xy.word >> 16);
        base_y = min_y;
        bounds[2] = (s16) (max_xy.word - min_xy.word);
        bounds[0] = left_bound;
        depth = depth >> 2;
        if ((*(u8 **)&render_state->draw_buffer) != upper_draw_context) {
            base_y += 0xE0;
        }
        max_y = (s16) (max_xy.word >> 16);
        height = max_y - min_y;
        bounds[1] = base_y;
        bounds[3] = height;
        if (((u32) depth) < 0x1E0U) {
            crop_y = (*((s16 *) (((u8 *) object) + 0x96))) - 0x34;
            if (crop_y < 0) {
                crop_y = 0;
            }
            height_pixels = (s16) height;
            crop_product = height_pixels * crop_y;
            crop_y = crop_product / 8;
            top_bound = (s16) base_y;
            bottom_bound = top_bound + height_pixels;
            top_copy = top_bound;
            last_y = bottom_bound;
            top_page = top_bound / 0xE0;
            top_page_index = top_page;
            if ((top_page_index != top_page) && (last_y != bottom_bound)) {
                bottom_page = 0;
            }
            bottom_page = bottom_bound / 0xE0;
            bottom_y = last_y;
            if (top_page_index != bottom_page) {
                last_y = bottom_page * 0xE0;
            }
            scratch.outer = 4;
            left_bound = 0x00FFFFFF;
            depth_offset = depth << 2;
            do {
                s32 layer;
                s32 phase_or_y;
                layer = scratch.outer;
                phase_or_y = (*((s16 *) (((u8 *) object) + 0x96))) + layer;
                depth_out_or_phase = phase_or_y << 7;
                if (!(layer & 1)) {
                    depth_out_or_phase += 0x800;
                }
                phase_or_y = bounds[1];
                index_or_row = phase_or_y + crop_y;
                first_y = index_or_row;
                if (last_y >= index_or_row) {
                    row_span = bottom_y - index_or_row;
                    row_count = row_span + 1;
                    do {
                        u8 *frame;
                        u8 *depth_bucket;
                        s32 texture_width;
                        s32 strip_y;
                        s32 texture_step;
                        s32 texture_top;
                        s32 texture_bottom;
                        s32 wave_x;
                        s32 poly_link;
                        s32 bucket_link;
                        depth_out_or_phase = advance_phase(depth_out_or_phase, scratch.outer);
                        frame = render_state->draw_buffer;
                        poly = *((u8 **) (frame + 0x8D0));
                        *((u8 **) (frame + 0x8D0)) = poly + 40;
                        *((s32 *) (poly + 4)) = *((s32 *) (((u8 *) appearance) + 0xC));
                        SetPolyFT4(poly);
                        SetSemiTrans(poly, 1);
                        *((s16 *) (poly + 0x16)) = (s16) GetTPage(2, ((u8 *) appearance)[0xC] != 0x80,
                            0x340, 0x100);
                        *((((u8 *) poly) + 0x14)) = 0;
                        *((((u8 *) poly) + 0x0C)) = 0;
                        texture_width = ((u8 *) (&material))[4];
                        *((s16 *) (poly + 8)) = (s16) row_span;
                        *((((u8 *) poly) + 0x24)) = texture_width;
                        *((((u8 *) poly) + 0x1C)) = texture_width;
                        if (((u32)row_span << 16) == 0) {
                            *((u16 *) (poly + 8)) = (u16) row_count;
                        }
                        texture_step = ((s16 *) (&material))[3] * (index_or_row - first_y);
                        texture_step = texture_step / (*((s16 *) (poly + 8)));
                        *((((u8 *) poly) + 0x1D)) = (u8) texture_step;
                        *((((u8 *) poly) + 0x0D)) = (u8) texture_step;
                        texture_step = ((s16 *) (&material))[3] / (*((s16 *) (poly + 8)));
                        texture_top = *((((u8 *) poly) + 0x0D));
                        *((((u8 *) poly) + 0x25)) = (u8) texture_step;
                        if (((u8) texture_step) >= 2) {
                            texture_bottom = texture_top + (*((((u8 *) poly) + 0x25)));
                        }
                        else {
                            texture_bottom = texture_top + 2;
                        }
                        *((((u8 *) poly) + 0x25)) = (u8) texture_bottom;
                        *((((u8 *) poly) + 0x15)) = (u8) texture_bottom;
                        wave_x = rsin(depth_out_or_phase);
                        wave_x = ((u16) bounds[0]) + (wave_x >> 9);
                        *((s16 *) (poly + 0x10)) = (s16) wave_x;
                        *((s16 *) (poly + 8)) = (s16) wave_x;
                        wave_x = wave_x + ((u16) bounds[2]);
                        *((s16 *) (poly + 0x20)) = (s16) wave_x;
                        *((s16 *) (poly + 0x18)) = (s16) wave_x;
                        strip_y = index_or_row - ((index_or_row / 0xE0) * 0xE0);
                        index_or_row++;
                        strip_y = strip_y - ((u16) scratch.outer);
                        *((s16 *) (poly + 0x1A)) = (s16) strip_y;
                        *((s16 *) (poly + 0x0A)) = (s16) strip_y;
                        strip_y += 2;
                        *((s16 *) (poly + 0x22)) = (s16) strip_y;
                        *((s16 *) (poly + 0x12)) = (s16) strip_y;
                        poly_link = *((s32 *) ((u8 *) (depth_offset + ((long)(*(u8 **)&render_state->draw_buffer))) + 0xB0));
                        *((s32 *) (poly + 0)) = ((*((s32 *) (poly + 0))) & 0xFF000000)
                        | (poly_link & left_bound);
                        depth_bucket = (u8 *) (depth_offset + ((long)(*(u8 **)&render_state->draw_buffer)));
                        bucket_link = *((s32 *) (depth_bucket + 0xB0));
                        *((s32 *) (depth_bucket + 0xB0)) =
                            (bucket_link & 0xFF000000) | (((s32) poly) & left_bound);
                    }
                    while (last_y >= index_or_row);
                }
            }
            while ((--scratch.outer) > 0);
        }
        next_object = *((void **) (((u8 *) object_data) - 8));
        if (next_object == 0) {
            break;
        }
        object_data = ((u8 *) next_object) + 0x20;
        appearance = *((void **) (((u8 *) next_object) + 0xC));
    }

    return 0;
}
