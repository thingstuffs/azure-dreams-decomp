#include "shared/gpu_packets.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/game_work.h"
#include "dungeon/effect/shade.h"
#include "sdk/libc.h"
#include "sdk/libgpu.h"
#include "sdk/libgte.h"

#include "sdk/libgte_matrix.h"
#include "sdk/libgpu_packets.h"
#include "dungeon/effect/shaded_quad_scratch.h"

   /* *global in project_depth_sliced_quads */

/* Project depth-sliced quads and link visible packets into the ordering table. */
void project_depth_sliced_quads(void *geometry, ObjectPosition *position, SpriteFrameState *render_state, s16 depth_bias)
{
    ShadedQuadScratch *scratch = (ShadedQuadScratch *)0x1F800000;
    u8 **render_context = (u8 **)((u8 *)(&g_game_work));
    POLY_F4 *packet;
    s32 ot_index;
    s32 depth_span;
    s32 abs_depth_span;
    s32 abs_depth_span_2;
    s32 coord_index;
    u32 address_mask;
    u32 length_mask;
    u16 depth_edges[4];
    MATRIX matrix;

    scratch->ordering_table = (u32 *)(*render_context + 0xB0);
    scratch->local_matrix.t[0] = position->x.w.i;
    scratch->local_matrix.t[1] = position->y.w.i;
    scratch->local_matrix.t[2] = position->z.w.i;
    render_state->flags |= 0x8000;

    PushMatrix();

    scratch->scale.vz = 0x2000;
    scratch->scale.vy = 0x2000;
    scratch->scale.vx = 0x2000;
    scratch->angles.vx = render_state->angle_x;
    scratch->angles.vz = render_state->angle_z;
    scratch->angles.vy = render_state->angle_y;
    RotMatrix(&scratch->angles, &scratch->local_matrix);
    ReadRotMatrix(&matrix);
    CompMatrix(&matrix, &scratch->local_matrix, &scratch->composed_matrix);
    ScaleMatrix(&scratch->composed_matrix, &scratch->scale);
    SetTransMatrix(&scratch->composed_matrix);
    SetRotMatrix(&scratch->composed_matrix);

    scratch->render_flags = render_state->flags;
    for (coord_index = 0; coord_index < 4; coord_index++) {
        depth_edges[coord_index] = (*(u16 *)((u8 *)geometry + 0x54 + coord_index * 2));
    }

    abs_depth_span = abs(((s16)depth_edges[0]) - ((s16)depth_edges[2]));
    if (abs_depth_span >= 0x11) {
        address_mask = 0x00FFFFFF;
        length_mask = 0xFF000000;
        do {
            scratch->vertices[0].vx = (*(u16 *)((u8 *)geometry + 0x44));
            scratch->vertices[1].vx = (*(u16 *)((u8 *)geometry + 0x46));
            scratch->vertices[2].vx = (*(u16 *)((u8 *)geometry + 0x48));
            scratch->vertices[3].vx = (*(u16 *)((u8 *)geometry + 0x4A));
            scratch->vertices[0].vy = (*(u16 *)((u8 *)geometry + 0x4C));
            scratch->vertices[1].vy = (*(u16 *)((u8 *)geometry + 0x4E));
            scratch->vertices[2].vy = (*(u16 *)((u8 *)geometry + 0x50));
            scratch->vertices[3].vy = (*(u16 *)((u8 *)geometry + 0x52));
            scratch->vertices[0].vz = depth_edges[2] - 0x10;
            scratch->vertices[1].vz = depth_edges[3] - 0x10;
            scratch->vertices[2].vz = depth_edges[2];
            scratch->vertices[3].vz = depth_edges[3];
            depth_edges[2] -= 0x10;
            depth_edges[3] -= 0x10;

            packet = ((GpuContext *)(*render_context))->packetCursor;
            ((GpuContext *)(*render_context))->packetCursor = packet + 1;
            ot_index = RotAverage4(&scratch->vertices[0], &scratch->vertices[1],
                                     &scratch->vertices[2], &scratch->vertices[3],
                                     (s32 *)&packet->x0, (s32 *)&packet->x1,
                                     (s32 *)&packet->x2, (s32 *)&packet->x3,
                                     &scratch->depth_cue, &scratch->gte_flag) - depth_bias - 6;
            scratch->ot_index = ot_index;

            if ((u32)ot_index < 0x1E0) {
                if ((((u16)(packet->x0 + 0x20) < 0x181) &&
                     ((u16)(packet->y0 + 0x20) < 0x121)) |
                    (((u16)(packet->x1 + 0x20) < 0x181) &&
                     ((u16)(packet->y1 + 0x20) < 0x121)) |
                    (((u16)(packet->x2 + 0x20) < 0x181) &&
                     ((u16)(packet->y2 + 0x20) < 0x121)) |
                    (((u16)(packet->x3 + 0x20) < 0x181) &&
                     ((u16)(packet->y3 + 0x20) < 0x121))) {
                    render_state->flags &= 0x7FFF;
                    /* BYTES: retail copies the colour word (red, green, blue and code) with one sw; member stores compile to four sb */
                    *(u32 *)&packet->red = render_state->color.word;
                    SetPolyF4(packet);

                    packet->tag = (packet->tag & length_mask) |
                        (scratch->ordering_table[scratch->ot_index] & address_mask);
                    scratch->ordering_table[scratch->ot_index] =
                        (scratch->ordering_table[scratch->ot_index] & length_mask) |
                        ((u32)packet & address_mask);
                }
            }
            abs_depth_span_2 = abs(((s16)depth_edges[0]) - ((s16)depth_edges[2]));
        } while (abs_depth_span_2 >= 0x11);
    }

    if ((s16)depth_edges[0] != (s16)depth_edges[2]) {
        scratch->vertices[0].vx = (*(u16 *)((u8 *)geometry + 0x44));
        scratch->vertices[1].vx = (*(u16 *)((u8 *)geometry + 0x46));
        scratch->vertices[2].vx = (*(u16 *)((u8 *)geometry + 0x48));
        scratch->vertices[3].vx = (*(u16 *)((u8 *)geometry + 0x4A));
        scratch->vertices[0].vy = (*(u16 *)((u8 *)geometry + 0x4C));
        scratch->vertices[1].vy = (*(u16 *)((u8 *)geometry + 0x4E));
        scratch->vertices[2].vy = (*(u16 *)((u8 *)geometry + 0x50));
        scratch->vertices[3].vy = (*(u16 *)((u8 *)geometry + 0x52));
        scratch->vertices[0].vz = depth_edges[0];
        scratch->vertices[1].vz = depth_edges[1];
        scratch->vertices[2].vz = depth_edges[2];
        scratch->vertices[3].vz = depth_edges[3];

        packet = ((GpuContext *)(*render_context))->packetCursor;
        ((GpuContext *)(*render_context))->packetCursor = packet + 1;
        ot_index = RotAverage4(&scratch->vertices[0], &scratch->vertices[1],
                                 &scratch->vertices[2], &scratch->vertices[3],
                                 (s32 *)&packet->x0, (s32 *)&packet->x1,
                                 (s32 *)&packet->x2, (s32 *)&packet->x3,
                                 &scratch->depth_cue, &scratch->gte_flag) - depth_bias - 6;
        scratch->ot_index = ot_index;

        if ((u32)ot_index < 0x1E0) {
            if ((((u16)(packet->x0 + 0x20) < 0x181) &&
                 ((u16)(packet->y0 + 0x20) < 0x121)) |
                (((u16)(packet->x1 + 0x20) < 0x181) &&
                 ((u16)(packet->y1 + 0x20) < 0x121)) |
                (((u16)(packet->x2 + 0x20) < 0x181) &&
                 ((u16)(packet->y2 + 0x20) < 0x121)) |
                (((u16)(packet->x3 + 0x20) < 0x181) &&
                 ((u16)(packet->y3 + 0x20) < 0x121))) {
                render_state->flags &= 0x7FFF;
                /* BYTES: retail copies the colour word (red, green, blue and code) with one sw; member stores compile to four sb */
                *(u32 *)&packet->red = render_state->color.word;
                SetPolyF4(packet);

                packet->tag = (packet->tag & 0xFF000000) |
                    (scratch->ordering_table[scratch->ot_index] & 0x00FFFFFF);
                scratch->ordering_table[scratch->ot_index] =
                    (scratch->ordering_table[scratch->ot_index] & 0xFF000000) |
                    ((u32)packet & 0x00FFFFFF);
            }
        }
    }

    PopMatrix();
}
