/* Troll-family effect renderer: draws an effect's motion vector as a chain of short flat lines. */
#include "common.h"
#include "shared/entity.h"
#include "shared/game_work.h"
#include "shared/sprite_frame_state.h"
#include "sdk/libc.h"
#include "sdk/libgte.h"
#include "sdk/libgpu.h"
#include "dungeon/monster/troll.h"
#include "dungeon/monster/troll/draw_segmented_motion_lines.h"

/* Project the effect's motion vector from its position in 16-unit segments
 * (at least one), queue one LINE_F2 packet per segment in the ordering
 * table, then queue a draw-mode packet. Sprite flags 8/4 select the
 * semi-transparency bit of both the sprite and the line color command. */
void draw_segmented_motion_lines(SegmentedLineState *state,
    ObjectPosition *position, SpriteFrameState *sprite, s32 depth_bias)
{
    void *draw_buffer_slot = &g_game_work.draw_buffer;
    GpuContext **context_ref = draw_buffer_slot;
    GpuContext *initial_context = *context_ref;
    SegmentedLineScratch *scratch = SEGMENTED_LINE_SCRATCH;
    SegmentedLinePacket *line;
    SegmentedLineDrawMode *draw_mode;
    GteMatrix matrix;
    s32 length, segments, index, next;
    s32 color;
    u16 draw_page;
    u16 saved_depth_bias = depth_bias;

    scratch->ordering_table.words = &initial_context->orderTag;
    scratch->rotation.t[0] = position->x.w.i;
    scratch->rotation.t[1] = position->y.w.i;
    scratch->rotation.t[2] = position->z.w.i;
    sprite->flags |= 0x8000;
    PushMatrix();
    scratch->scale.x = scratch->scale.y = scratch->scale.z = 0x2000;
    scratch->angles.vx = sprite->angle_x;
    scratch->angles.vz = sprite->angle_z;
    scratch->angles.vy = sprite->angle_y;
    RotMatrix(&scratch->angles, &scratch->rotation);
    ReadRotMatrix(&matrix);
    CompMatrix(&matrix, &scratch->rotation, &scratch->transform);
    ScaleMatrix(&scratch->transform, &scratch->scale);
    SetTransMatrix(&scratch->transform);
    SetRotMatrix(&scratch->transform);
    scratch->flags = sprite->flags;
    length = abs(state->vector_x.w.i) <= abs(state->vector_y.w.i)
        ? abs(state->vector_y.w.i) : abs(state->vector_x.w.i);
    segments = length / 16;
    if (segments == 0) segments = 1;
    for (index = 0; index < segments; index++) {
        line = (*context_ref)->packetCursor;
        (*context_ref)->packetCursor = line + 1;
        scratch->point[0].vx = scratch->point[2].vx = state->vector_x.w.i * index / segments;
        next = index + 1;
        scratch->point[1].vx = scratch->point[3].vx = state->vector_x.w.i * next / segments;
        scratch->point[0].vy = scratch->point[2].vy = state->vector_y.w.i * index / segments;
        scratch->point[1].vy = scratch->point[3].vy = state->vector_y.w.i * next / segments;
        scratch->point[0].vz = scratch->point[2].vz = state->vector_z.w.i * index / segments;
        scratch->point[1].vz = scratch->point[3].vz = state->vector_z.w.i * next / segments;
        scratch->depth = RotAverage4(&scratch->point[0], &scratch->point[1],
            &scratch->point[2], &scratch->point[3], &line->xy0, &line->xy1,
            &line->xy0, &line->xy1, &scratch->projection,
            &scratch->projection_flags) - (s16)saved_depth_bias - 6;
        if (scratch->flags & 8) {
            if (scratch->flags & 4) sprite->color.c.code |= 2;
            else sprite->color.c.code &= 0xFD;
        }
        color = sprite->color.word;
        line->tag.len = 3;
        line->color.word = color;
        line->color.c.code = 0x40;
        if (scratch->flags & 8) {
            if (scratch->flags & 4) line->color.c.code |= 2;
            else line->color.c.code &= 0xFD;
        }
        line->tag.addr = scratch->ordering_table.links[scratch->depth].addr;
        scratch->ordering_table.links[scratch->depth].addr = (u32)line;
    }
    draw_mode = (*context_ref)->packetCursor;
    (*context_ref)->packetCursor = draw_mode + 1;
    draw_page = GetTPage(0, 1, 0, 0);
    SetDrawMode(draw_mode, 0, 0, draw_page, 0);
    draw_mode->tag.addr = scratch->ordering_table.links[scratch->depth].addr;
    scratch->ordering_table.links[scratch->depth].addr = (u32)draw_mode;
    PopMatrix();
}
