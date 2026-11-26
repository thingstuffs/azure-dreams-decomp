#include "shared/gpu_packets.h"
#include "dungeon/effect/projected_quad_scratch.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/entity.h"
#include "dungeon/monster/golem.h"
#include "sdk/libc.h"

   /* context in draw_randomized_shaded_polylines */

typedef struct S_80175A90_2 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_00;   /* overlapping accesses */
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 unk_07;
    u16 unk_08;
    u16 unk_0A;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u16 unk_12;
    u8 unk_14;
    u8 unk_15;
    u8 unk_16;
    u8 pad_17[0x1];
    u16 unk_18;
    u16 unk_1A;
    u32 unk_1C;
} S_80175A90_2;   /* prim in draw_randomized_shaded_polylines */

typedef struct S_80175A90_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80175A90_3;   /* arg0 in draw_randomized_shaded_polylines */

extern s32 func_80065530(void *, void *, void *, void *, void *, void *, void *, void *);

/*
 * Projects six jittered red three-point lines plus a center line between two positions, and queues
 * them by depth.
 */
void draw_randomized_shaded_polylines(S_80175A90_3 *start_pos, EntityRec *end_pos)
{
    GameWork *render_state = &g_game_work;
    ProjectedQuadScratch *scratch = PROJECTED_QUAD_SCRATCH;
    S_80175A90_2 *prim;
    s32 line_index = 0;
    s32 endpoint_red = 0xC0;
    u32 addr_mask = 0x00FFFFFF;
    u32 length_mask = 0xFF000000;

    GpuContext *initial_context = render_state->draw_buffer;

    scratch->ordering_table = &initial_context->orderTag[GPU_ORDER_DEPTH_BASE];

    do {
        GpuContext *context = render_state->draw_buffer;
        s32 offset;

        prim = context->packetCursor;
        context->packetCursor = (u8 *)prim + 0x20;

        prim->unk_07 = 0x58;
        prim->unk_00.at03.v = 7;
        prim->unk_1C = 0x55555555;
        prim->unk_07 |= 2;

        scratch->vertices[0].vx = start_pos->unk_02;
        scratch->vertices[0].vy = start_pos->unk_06;
        scratch->vertices[0].vz = start_pos->unk_0A;

        scratch->vertices[1].vx =
            (((s16)start_pos->unk_02) + end_pos->x.w.i) / 2;
        scratch->vertices[1].vy =
            (((s16)start_pos->unk_06) + end_pos->y.w.i) / 2;
        scratch->vertices[1].vz =
            (((s16)start_pos->unk_0A) + end_pos->z.w.i) / 2;

        scratch->vertices[2].vx = end_pos->x.w.i;
        scratch->vertices[2].vy = end_pos->y.w.i;
        scratch->vertices[2].vz = end_pos->z.w.i;

        offset = (rand() % 9) + 4;
        switch (line_index) {
        case 0:
            scratch->vertices[0].vx -= 2;
            scratch->vertices[1].vx += offset;
            scratch->vertices[2].vx -= offset;
            break;
        case 1:
            scratch->vertices[0].vy -= 2;
            scratch->vertices[1].vy += offset;
            scratch->vertices[2].vy -= offset;
            break;
        case 2:
            scratch->vertices[0].vz -= 2;
            scratch->vertices[1].vz += offset;
            scratch->vertices[2].vz -= offset;
            break;
        case 3:
            scratch->vertices[0].vx += 2;
            scratch->vertices[1].vx -= offset;
            scratch->vertices[2].vx += offset;
            break;
        case 4:
            scratch->vertices[0].vy += 2;
            scratch->vertices[1].vy -= offset;
            scratch->vertices[2].vy += offset;
            break;
        case 5:
            scratch->vertices[0].vz += 2;
            scratch->vertices[1].vz -= offset;
            scratch->vertices[2].vz += offset;
            break;
        case 6:
            break;
        }

        prim->unk_05 = 0x40;
        prim->unk_06 = 0x40;
        prim->unk_0C = 0x40;
        prim->unk_15 = 0x40;
        prim->unk_16 = 0x40;
        prim->unk_04 = endpoint_red;
        prim->unk_0D = 0;
        prim->unk_0E = 0;
        prim->unk_14 = endpoint_red;

        scratch->ot_index = func_80065530(
            &scratch->vertices[0], &scratch->vertices[1], &scratch->vertices[2],
            &scratch->screen[0].x, &scratch->screen[1].x, &scratch->screen[2].x,
            &scratch->depth_cue, &scratch->gte_flag);

        prim->unk_08 = scratch->screen[0].x;
        prim->unk_0A = scratch->screen[0].y;
        prim->unk_10 = scratch->screen[1].x;
        prim->unk_12 = scratch->screen[1].y;
        prim->unk_18 = scratch->screen[2].x;
        prim->unk_1A = scratch->screen[2].y;

        {
            u32 depth = scratch->ot_index;
            if (depth < 0x1E0) {
                prim->unk_00.at00.v =
                    (prim->unk_00.at00.v & length_mask) |
                    (scratch->ordering_table[depth] & addr_mask);
                scratch->ordering_table[scratch->ot_index] =
                    (scratch->ordering_table[scratch->ot_index] & length_mask) |
                    ((u32)prim & addr_mask);
            }
        }

        line_index++;
    } while (line_index < 7);
}
