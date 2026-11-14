/* One native TU; source order follows the complete ledger cohort. */
#include "dungeon/effect/screen/transform_shade_and_queue_model_quads.h"
#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/game_work.h"
#include "dungeon/effect/screen.h"
#include "sdk/libgpu.h"
#include "sdk/libgte.h"
#include "shared/sprite_frame_state.h"
#include "sdk/libgte_matrix.h"
#include "sdk/libgpu_packets.h"
#include "engine/graphics/sprite_scratch.h"
#include "dungeon/effect/sprite/render_rotated_effect_quads.h"

typedef struct S_800C9088_4 S_800C9088_4;

typedef struct S_800C9088_0 {
    u8 pad_00[0x8];
    S_800C9088_4 *unk_08;
    CVECTOR base_color; /* the colour NormalColorCol shades each vertex normal with */
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
} S_800C9088_0;   /* object in transform_shade_and_queue_model_quads */



struct S_800C9088_4 {
    u8 * unk_00;
    SVECTOR *unk_04;
    SVECTOR *unk_08;
};   /* descriptor in transform_shade_and_queue_model_quads */

/* Transform, shade, and enqueue visible textured quads for the model. */
void transform_shade_and_queue_model_quads(void *parent_matrix, void *translation_arg, void *model_arg, s16 depth_bias)
{
    S_800C9088_0 *model = model_arg;
    ObjectPosition *translation = translation_arg;
    SpriteQuadScratch *scratch;
    u8 *indices;
    SVECTOR *positions;
    SVECTOR *normals;
    POLY_GT4 *packet;
    CVECTOR *base_color;
    GpuContext *state;
    GpuContext **state_table = (GpuContext **)&g_game_work;
    S_800C9088_4 *descriptor;
    SVECTOR *vertex0;
    SVECTOR *vertex1;
    SVECTOR *vertex2;
    SVECTOR *vertex3;
    s32 vertex_xy;
    u32 vertex_index;
    u32 last_index;
    s32 vertex2_xy;
    s32 vertex3_xy;
    u32 z_index;
    u16 vertex_z;
    u16 vertex3_z;
    SVECTOR *vertex2_pos;
    SVECTOR *vertex3_pos;
    s32 depth;
    s32 winding;
    volatile s32 *winding_slot;
    s32 flags;
    u16 scale_x;
    MATRIX saved_transform;
    s32 screen_xy0, screen_xy1, screen_xy2;


    PushMatrix();

    scale_x = model->unk_1C;
    scratch = (SpriteQuadScratch *)0x1F800000;
    scratch->input.vx = scale_x;
    scratch->input.vy = model->unk_1E;
    scratch->input.vz = model->unk_20;
    scratch->translation.vx = translation->x.w.i;
    scratch->translation.vy = translation->y.w.i;
    scratch->translation.vz = translation->z.w.i;

    ReadRotMatrix(&saved_transform);

    scratch->matrix.m[2][2] = 0x1000;
    scratch->matrix.m[1][1] = 0x1000;
    scratch->matrix.m[0][0] = 0x1000;
    scratch->matrix.m[2][1] = 0;
    scratch->matrix.m[2][0] = 0;
    scratch->matrix.m[1][2] = 0;
    scratch->matrix.m[1][0] = 0;
    scratch->matrix.m[0][2] = 0;
    scratch->matrix.m[0][1] = 0;

    RotMatrixX(model->unk_16, &scratch->matrix);
    RotMatrixZ(model->unk_1A, &scratch->matrix);
    RotMatrixY(model->unk_18, &scratch->matrix);

    if (model->unk_14 & 1) {
        scratch->input.vx = -scratch->input.vx;
    }
    if (model->unk_14 & 2) {
        scratch->input.vy = -scratch->input.vy;
    }

    ScaleMatrix(&scratch->matrix, &scratch->input);
    TransMatrix(&scratch->matrix, &scratch->translation);
    CompMatrix(&scratch->matrix, parent_matrix, &scratch->local_matrix);
    CompMatrix(&saved_transform, &scratch->local_matrix, &scratch->matrix);
    SetTransMatrix(&scratch->matrix);
    SetRotMatrix(&scratch->matrix);

    state = state_table[0];
    base_color = &model->base_color;
    scratch->ordering_table = (u32 *)&state->orderTag;
    packet = state->packetCursor;
    model->unk_14 |= 0x8000;

    descriptor = model->unk_08;
    indices = descriptor->unk_00;
    positions = descriptor->unk_04;
    normals = descriptor->unk_08;

    for (;;) {
    /* BYTES: retail copies the packed vertex XY word with one lw/sw */
    vertex_xy = *(s32 *)&positions[((u16 *)indices)[0]].vx;
    vertex_index = (*(u16 *)(indices + 2));
    *(s32 *)&scratch->vertices[0].vx = vertex_xy;
    /* BYTES: retail copies the packed vertex XY word with one lw/sw */
    vertex_xy = *(s32 *)&positions[vertex_index].vx;
    vertex2_pos = (SVECTOR *)(*(u16 *)(indices + 4) * 8 + (unsigned long)positions);
    *(s32 *)&scratch->vertices[1].vx = vertex_xy;
    last_index = (*(u16 *)(indices + 6));
    /* BYTES: retail copies the packed vertex XY word with one lw/sw */
    vertex2_xy = *(s32 *)&vertex2_pos->vx;
    vertex3_pos = (SVECTOR *)(last_index * 8 + (unsigned long)positions);
    *(s32 *)&scratch->vertices[2].vx = vertex2_xy;
    z_index = ((u16 *)indices)[0];
    /* BYTES: retail copies the packed vertex XY word with one lw/sw */
    vertex3_xy = *(s32 *)&vertex3_pos->vx;

    vertex_z = positions[z_index].vz;
    scratch->vertices[0].vz = vertex_z;

    vertex_z = positions[*(u16 *)(indices + 2)].vz;
    vertex0 = &scratch->vertices[0];
    scratch->vertices[1].vz = vertex_z;

    z_index = (*(u16 *)(indices + 4));
    vertex1 = &scratch->vertices[1];
    vertex_z = positions[z_index].vz;
    vertex2 = &scratch->vertices[2];
    scratch->vertices[2].vz = vertex_z;

    z_index = (*(u16 *)(indices + 6));
    vertex3 = &scratch->vertices[3];
    *(s32 *)&scratch->vertices[3].vx = vertex3_xy;
    vertex3_z = positions[z_index].vz;

    scratch->vertices[3].vz = vertex3_z;
    depth = RotAverage4(vertex0, vertex1,
                          vertex2, vertex3,
                          (s32 *)&packet->x0, (s32 *)&packet->x1,
                          (s32 *)&packet->x2, (s32 *)&packet->x3,
                          &scratch->depth_cue, &scratch->gte_flag);
    scratch->sort_depth = depth;

    flags = model->unk_14 & 3;
    switch (flags) {
    case 0:
        /* BYTES: retail copies the packed screen XY word with one lw/sw */
        screen_xy0 = *(s32 *)&packet->x0;
        /* BYTES: retail copies the packed screen XY word with one lw/sw */
        screen_xy1 = *(s32 *)&packet->x1;
        /* BYTES: retail copies the packed screen XY word with one lw/sw */
        screen_xy2 = *(s32 *)&packet->x2;
        break;
    case 1:
        /* BYTES: retail copies the packed screen XY word with one lw/sw */
        screen_xy0 = *(s32 *)&packet->x1;
        /* BYTES: retail copies the packed screen XY word with one lw/sw */
        screen_xy1 = *(s32 *)&packet->x0;
        /* BYTES: retail copies the packed screen XY word with one lw/sw */
        screen_xy2 = *(s32 *)&packet->x2;
        break;
    case 2:
        /* BYTES: retail copies the packed screen XY word with one lw/sw */
        screen_xy0 = *(s32 *)&packet->x2;
        /* BYTES: retail copies the packed screen XY word with one lw/sw */
        screen_xy1 = *(s32 *)&packet->x1;
        /* BYTES: retail copies the packed screen XY word with one lw/sw */
        screen_xy2 = *(s32 *)&packet->x0;
        break;
    default:
        /* BYTES: retail copies the packed screen XY word with one lw/sw */
        screen_xy0 = *(s32 *)&packet->x2;
        /* BYTES: retail copies the packed screen XY word with one lw/sw */
        screen_xy1 = *(s32 *)&packet->x0;
        /* BYTES: retail copies the packed screen XY word with one lw/sw */
        screen_xy2 = *(s32 *)&packet->x1;
        break;
    }
    winding = NormalClip(screen_xy0, screen_xy1, screen_xy2);
    /* retail stores the NormalClip result in its scratch slot and reads the slot back for the test */
    winding_slot = &scratch->winding;
    *winding_slot = winding;
    if (*winding_slot > 0) {
        scratch->sort_depth -= depth_bias;
        if (scratch->sort_depth < 0x1E0) {
            NormalColorCol(&normals[*(u16 *)(indices + 0x10)],
                          base_color, (CVECTOR *)&packet->r0);
            NormalColorCol(&normals[*(u16 *)(indices + 0x12)],
                          base_color, (CVECTOR *)&packet->r1);
            NormalColorCol(&normals[*(u16 *)(indices + 0x14)],
                          base_color, (CVECTOR *)&packet->r2);
            NormalColorCol(&normals[*(u16 *)(indices + 0x16)],
                          base_color, (CVECTOR *)&packet->r3);

            /* BYTES: retail stores the u/v pair with the CLUT or texture-page halfword as one sw; member stores compile to two sb and an sh */
            *(s32 *)&packet->u0 = (*(s32 *)(indices + 8));
            packet->clut += model->unk_12;
            /* BYTES: retail stores the u/v pair with the CLUT or texture-page halfword as one sw; member stores compile to two sb and an sh */
            *(s32 *)&packet->u1 = (*(s32 *)(indices + 0xC));
            if (model->unk_10 != 0) {
                packet->tpage = (packet->tpage & 0xFF9F) + model->unk_10;
            }
            /* BYTES: retail writes the packet u/v byte pair with one sh of the combined value; storing u and v separately compiles to two sb */
            *(u16 *)&packet->u2 = (*(u16 *)(indices + 0x1A));
            /* BYTES: retail writes the packet u/v byte pair with one sh of the combined value; storing u and v separately compiles to two sb */
            *(u16 *)&packet->u3 = (*(u16 *)(indices + 0x1C));

            SetPolyGT4(packet);
            flags = model->unk_14;
            if (flags & 8) {
                if (flags & 4) {
                    packet->code |= 2;
                }
            }
            AddPrim(scratch->ordering_table + scratch->sort_depth,
                          packet);
            packet++;
            model->unk_14 &= 0x7FFF;
        }
    }

    if (indices[0x1E] == 1 && ((s8 *)indices)[0x1F] < 0) {
        break;
    }
    indices += 0x20;
    }

    PopMatrix();
    state_table[0]->packetCursor = packet;
}
#include "m2c_compat.h"

typedef struct S_800C95C0_0 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_800C95C0_0;   /* arg1 in queue_linked_visible_rectangle_copies */

typedef struct S_800C95C0_1_pre {
    u8 * unk_00;
    u8 pad_04[0x4];
} S_800C95C0_1_pre;   /* the 0x8 bytes before state in queue_linked_visible_rectangle_copies, addressed as state[-1] */

struct S_Rect;

/* Updates each linked state from its input values and delta using scratchpad memory. */
s32 queue_linked_visible_rectangle_copies(void *initial_state, void *input_values, SpriteFrameState *initial_delta) {
    void *state = initial_state;
    SpriteFrameState *delta = initial_delta;
    SpriteQuadScratch *scratch = (SpriteQuadScratch *)0x1F800000;
    u8 *next_node;

    for (;;) {
        scratch->position.vx = ((S_800C95C0_0 *)input_values)->unk_02;
        scratch->position.vy = (*(u16 *)((u8 *)input_values + 6));
        scratch->position.vz = (*(u16 *)((u8 *)input_values + 0xA));
        scratch->sort_depth =
            RotTransPers(&scratch->position, (s32 *)&scratch->screen_origin,
                          &scratch->depth_cue, &scratch->gte_flag) -
            delta->depth_bias;
        queue_visible_rectangle_copy(state, scratch);
        next_node = ((S_800C95C0_1_pre *)state)[-1].unk_00;
        if (next_node == NULL)
            break;
        state = next_node + 0x20;
        input_values = *(u8 **)(next_node + 8);
        delta = *(u8 **)(next_node + 0xC);
    }
    return 0;
}

struct S_Rect;

/* Processes linked entries with position values staged in scratchpad memory. */
s32 queue_linked_rectangles_at_position(void *entry_data, void *position) {
    register u8 *data = entry_data;
    register SpriteQuadScratch *scratch = (SpriteQuadScratch *)0x1F800000;
    register u8 *next_node;
    s32 offset;

    for (;;) {
        offset = (s32)((u32)*(u16 *)data << 16) >> 17;
        scratch->screen_origin.x = *(u16 *)((u8 *)position + 2) - offset;
        scratch->screen_origin.y = *(u16 *)((u8 *)position + 6);
        scratch->sort_depth = *(s16 *)((u8 *)position + 10);
        queue_visible_rectangle_copy(data, scratch);
        next_node = *(u8 **)(data - 8);
        if (next_node == 0) {
            break;
        }
        data = next_node + 0x20;
        position = *(u8 **)(next_node + 8);
    }
    return 0;
}

typedef struct {
    char pad0[0x8D0];
    u8 *field_8D0;
} Ctx;

typedef struct S_Rect {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} S_Rect;


typedef struct {
    u16 x;
    s16 y;
    u16 w;
    u16 h;
} S_Stack;

extern u8 resident_globals_page[];
extern void func_80066890(u8 *dst, S_Stack *rect, s32 x, s32 y);

/* Queue a rectangle copy when both source and destination fit on screen. */
void queue_visible_rectangle_copy(S_Rect *copy_rect, SpriteQuadScratch *source) {
    S_Stack source_rect;
    s16 source_y, width, source_x, height;
    s32 dest_y, second_buffer, dest_x, buffer_y;
    u8 *packet;
    u8 *cursor;
    Ctx **active_ctx;

    active_ctx = (Ctx **)((u8 *)&resident_globals_page + 0x3160);
    cursor = (*(Ctx **)((u8 *)&resident_globals_page + 0x3160))->field_8D0;
    second_buffer = *(Ctx **)((u8 *)&resident_globals_page + 0x3160) != (Ctx *)upper_draw_context;
    if (source->sort_depth < 480) {
        source_x = source->screen_origin.x;
        source_y = source->screen_origin.y;
        dest_x = source_x + copy_rect->w;
        dest_y = source_y + copy_rect->h;
        if (dest_x >= 0) {
            width = copy_rect->x;
            if (((dest_x + width) < 320) && (dest_y >= 0)) {
                height = copy_rect->y;
                if (((dest_y + height) < 224) && (source_x >= 0) && ((source_x + width) < 320) && (source_y >= 0)
                    && ((source_y + height) < 224)) {
                    source_rect.x = source->screen_origin.x;
                    buffer_y = (s16)source->screen_origin.y;
                    if ((s16)second_buffer) {
                        buffer_y += 224;
                    }
                    source_rect.y = buffer_y;
                    source_rect.w = copy_rect->x;
                    source_rect.h = copy_rect->y;
                    func_80066890(cursor, &source_rect, source_x + copy_rect->w, (s16)buffer_y + copy_rect->h);
                    packet = cursor;
                    cursor += 24;
                    AddPrim((u8 *)(*(Ctx **)((u8 *)&resident_globals_page + 0x3160)) + ((source->sort_depth * 4) + 0xB0), packet);
                }
            }
        }
    }
    (*active_ctx)->field_8D0 = cursor;
}
