/* One native TU; source order follows the complete ledger cohort. */
#include "dungeon/effect/screen/transform_shade_and_queue_model_quads.h"
#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/game_work.h"
#include "dungeon/effect/screen.h"
#include "sdk/libgpu.h"
#include "sdk/libgte.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "sdk/libgte_matrix.h"
#include "sdk/libgpu_packets.h"
#include "engine/graphics/sprite_scratch.h"
#include "dungeon/effect/sprite/render_rotated_effect_quads.h"

/* One 32-byte face contains four position and normal indices and the
 * texture coordinates copied to the projected POLY_GT4. */
typedef struct ShadedModelQuad {
    u16 vertices[4];
    u32 uv0_clut;
    u32 uv1_tpage;
    u16 normals[4];
    u8 pad18[2];
    u16 uv2;
    u16 uv3;
    u8 type;
    s8 end;
} ShadedModelQuad;

/* Transform, shade, and enqueue visible textured quads for the model. */
void transform_shade_and_queue_model_quads(void *parent_matrix, ObjectPosition *translation, SpriteFrameState *sprite, s16 depth_bias)
{
    SpriteQuadScratch *scratch;
    ShadedModelQuad *face;
    u8 *indices;
    SVECTOR *positions;
    SVECTOR *normals;
    POLY_GT4 *packet;
    CVECTOR *base_color;
    GpuContext *state;
    GameWork *work = &g_game_work;
    ShadedModel *descriptor;
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

    scale_x = sprite->scale_x;
    scratch = SPRITE_SCRATCH;
    scratch->input.vx = scale_x;
    scratch->input.vy = sprite->scale_y;
    scratch->input.vz = sprite->offset_x;
    scratch->translation.vx = translation->x.w.i;
    scratch->translation.vy = translation->y.w.i;
    scratch->translation.vz = translation->z.w.i;

    ReadRotMatrix(&saved_transform);

    scratch->matrix_50.m[2][2] = 0x1000;
    scratch->matrix_50.m[1][1] = 0x1000;
    scratch->matrix_50.m[0][0] = 0x1000;
    scratch->matrix_50.m[2][1] = 0;
    scratch->matrix_50.m[2][0] = 0;
    scratch->matrix_50.m[1][2] = 0;
    scratch->matrix_50.m[1][0] = 0;
    scratch->matrix_50.m[0][2] = 0;
    scratch->matrix_50.m[0][1] = 0;

    RotMatrixX(sprite->angle_x, &scratch->matrix_50);
    RotMatrixZ(sprite->angle_z, &scratch->matrix_50);
    RotMatrixY(sprite->angle_y, &scratch->matrix_50);

    if (sprite->flags & 1) {
        scratch->input.vx = -scratch->input.vx;
    }
    if (sprite->flags & 2) {
        scratch->input.vy = -scratch->input.vy;
    }

    ScaleMatrix(&scratch->matrix_50, &scratch->input);
    TransMatrix(&scratch->matrix_50, &scratch->translation);
    CompMatrix(&scratch->matrix_50, parent_matrix, &scratch->matrix_D0);
    CompMatrix(&saved_transform, &scratch->matrix_D0, &scratch->matrix_50);
    SetTransMatrix(&scratch->matrix_50);
    SetRotMatrix(&scratch->matrix_50);

    state = work->draw_buffer;
    base_color = (CVECTOR *)&sprite->color;
    scratch->ordering_table = (u32 *)&state->orderTag;
    packet = state->packetCursor;
    sprite->flags |= 0x8000;

    descriptor = sprite->source;
    face = descriptor->quads;
    positions = descriptor->positions;
    normals = descriptor->normals;

    for (;;) {
    /* BYTES: retail copies the packed vertex XY word with one lw/sw */
    indices = (u8 *)face->vertices;
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

    flags = sprite->flags & 3;
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
            NormalColorCol(&normals[face->normals[0]],
                          base_color, (CVECTOR *)&packet->r0);
            NormalColorCol(&normals[face->normals[1]],
                          base_color, (CVECTOR *)&packet->r1);
            NormalColorCol(&normals[face->normals[2]],
                          base_color, (CVECTOR *)&packet->r2);
            NormalColorCol(&normals[face->normals[3]],
                          base_color, (CVECTOR *)&packet->r3);

            /* BYTES: retail stores the u/v pair with the CLUT or texture-page halfword as one sw; member stores compile to two sb and an sh */
            *(s32 *)&packet->u0 = face->uv0_clut;
            packet->clut += sprite->clut;
            /* BYTES: retail stores the u/v pair with the CLUT or texture-page halfword as one sw; member stores compile to two sb and an sh */
            *(s32 *)&packet->u1 = face->uv1_tpage;
            if (sprite->tpage_abr != 0) {
                packet->tpage = (packet->tpage & 0xFF9F) + sprite->tpage_abr;
            }
            /* BYTES: retail writes the packet u/v byte pair with one sh of the combined value; storing u and v separately compiles to two sb */
            *(u16 *)&packet->u2 = face->uv2;
            /* BYTES: retail writes the packet u/v byte pair with one sh of the combined value; storing u and v separately compiles to two sb */
            *(u16 *)&packet->u3 = face->uv3;

            SetPolyGT4(packet);
            flags = sprite->flags;
            if (flags & 8) {
                if (flags & 4) {
                    packet->code |= 2;
                }
            }
            AddPrim(scratch->ordering_table + scratch->sort_depth,
                          packet);
            packet++;
            sprite->flags &= 0x7FFF;
        }
    }

    if (face->type == 1 && face->end < 0) {
        break;
    }
    face++;
    }

    PopMatrix();
    {
        GpuContext *output = work->draw_buffer;
        output->packetCursor = packet;
    }
}
#include "m2c_compat.h"

/* Updates each linked state from its input values and delta using scratchpad memory. */
s32 queue_linked_visible_rectangle_copies(RectangleCopy *initial_state, ObjectPosition *input_values, SpriteFrameState *initial_delta) {
    RectangleCopy *state = initial_state;
    ObjectPosition *position = input_values;
    SpriteFrameState *delta = initial_delta;
    SpriteQuadScratch *scratch = SPRITE_SCRATCH;
    ObjectNodeHeader *next_node;

    for (;;) {
        scratch->position.vx = position->x.w.i;
        scratch->position.vy = position->y.w.i;
        scratch->position.vz = position->z.w.i;
        scratch->sort_depth =
            RotTransPers(&scratch->position, (s32 *)&scratch->screen_origin,
                          &scratch->depth_cue, &scratch->gte_flag) -
            delta->depth_bias;
        queue_visible_rectangle_copy(state, scratch);
        next_node = NODE_HEADER(state)->chain_next;
        if (next_node == NULL)
            break;
        state = NODE_BODY(next_node);
        position = next_node->position;
        delta = next_node->sprite;
    }
    return 0;
}

struct RectangleCopy;

/* Processes linked entries with position values staged in scratchpad memory. */
s32 queue_linked_rectangles_at_position(void *entry_data, void *initial_position) {
    ObjectPosition *position = initial_position;
    register RectangleCopy *data = entry_data;
    register SpriteQuadScratch *scratch = SPRITE_SCRATCH;
    register ObjectNodeHeader *next_node;
    s32 offset;

    for (;;) {
        offset = data->width >> 1;
        scratch->screen_origin.x = position->x.w.i - offset;
        scratch->screen_origin.y = position->y.w.i;
        scratch->sort_depth = position->z.w.i;
        queue_visible_rectangle_copy(data, scratch);
        next_node = NODE_HEADER(data)->chain_next;
        if (next_node == 0) {
            break;
        }
        data = NODE_BODY(next_node);
        position = next_node->position;
    }
    return 0;
}

typedef struct {
    char pad0[0x8D0];
    u8 *field_8D0;
} Ctx;



typedef struct {
    u16 x;
    s16 y;
    u16 w;
    u16 h;
} S_Stack;

extern u8 resident_globals_page[];
extern void func_80066890(u8 *dst, S_Stack *rect, s32 x, s32 y);

/* Queue a rectangle copy when both source and destination fit on screen. */
void queue_visible_rectangle_copy(RectangleCopy *copy_rect, SpriteQuadScratch *source) {
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
        dest_x = source_x + copy_rect->delta_x;
        dest_y = source_y + copy_rect->delta_y;
        if (dest_x >= 0) {
            width = copy_rect->width;
            if (((dest_x + width) < 320) && (dest_y >= 0)) {
                height = copy_rect->height;
                if (((dest_y + height) < 224) && (source_x >= 0) && ((source_x + width) < 320) && (source_y >= 0)
                    && ((source_y + height) < 224)) {
                    source_rect.x = source->screen_origin.x;
                    buffer_y = (s16)source->screen_origin.y;
                    if ((s16)second_buffer) {
                        buffer_y += 224;
                    }
                    source_rect.y = buffer_y;
                    source_rect.w = copy_rect->width;
                    source_rect.h = copy_rect->height;
                    func_80066890(cursor, &source_rect, source_x + copy_rect->delta_x, (s16)buffer_y + copy_rect->delta_y);
                    packet = cursor;
                    cursor += 24;
                    AddPrim((u8 *)(*(Ctx **)((u8 *)&resident_globals_page + 0x3160)) + ((source->sort_depth * 4) + 0xB0), packet);
                }
            }
        }
    }
    (*active_ctx)->field_8D0 = cursor;
}
