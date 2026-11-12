#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_moving_views.h"
#include "dungeon/effect/sprite.h"
#include "sdk/libgpu.h"
#include "sdk/libgte.h"
#include "sdk/libgte_matrix.h"
#include "shared/dungeon_effect_state.h"
#include "sdk/libgpu_packets.h"
#include "engine/graphics/sprite_scratch.h"

/* Scratchpad slots of the cylinder renderer: the ordering-table base, the RotAverage4 corner inputs, depth and
 * GTE flag outputs, the averaged depth it returns and the four screen points it writes. */
typedef struct CylinderQuadScratch {
    u8 pad_00[0x18];
    u32 *ordering_table; /* the current draw context's ordering-table base (GpuContext.orderTag) */
    u8 pad_1C[0x48];
    SVECTOR vertices[4]; /* RotAverage4 inputs: the quad corners */
    s32 depth_cue; /* RotAverage4 depth-cue output */
    s32 gte_flag; /* RotAverage4 GTE flag output */
    u8 pad_8C[0x28];
    u32 sort_depth; /* RotAverage4 result: the ordering-table index of the quad */
    u8 pad_B8[0x20];
    SpriteScratchScreenPoint projected_vertices[4]; /* RotAverage4 screen outputs */
} CylinderQuadScratch;

/* Draws a shaded, textured cylindrical wall using 16 quads. */
s32 draw_shaded_textured_cylinder(B22_81893474_EffectState *unused_data, MovingPosition *center, s32 unused_value, s16 rotation,
                  s32 height, s16 radius, u8 blend_mode, u8 brightness)
{
    CylinderQuadScratch *scratch = (CylinderQuadScratch *)0x1F800000;
    s32 edge_z;
    s16 segment;
    GameWork *game = &g_game_work;

    scratch->ordering_table = (u32 *)&((GpuContext *)game->draw_buffer)->orderTag;
    edge_z = center->z - height + 1;
    scratch->vertices[1].vz = edge_z;
    scratch->vertices[0].vz = edge_z;
    edge_z = center->z;
    scratch->vertices[2].vz = edge_z;
    scratch->vertices[3].vz = edge_z;

    for (segment = 0; segment < 16; segment++) {
        register POLY_GT4 *prim;
        GpuContext *context;
        s32 next_angle;
        s32 angle_offset;
        s32 raw_angle;
        s32 biased_angle;
        s32 angle;

        context = game->draw_buffer;
        prim = context->packetCursor;

        context->packetCursor = prim + 1;
        ((GpuLinkTag *)&prim->tag)->len = 12;
        prim->code = 0x3C;

        if (blend_mode == 4) {
            prim->tpage = GetTPage(0, 0, 0x280, 0x100);
        } else {
            prim->code = 0x3E;
            prim->tpage =
                GetTPage(0, blend_mode, 0x280, 0x100);
        }

        prim->clut = 0x7E00;
        {
            register s32 texture_u_max = 0x3F;

            prim->u0 = 0;
            prim->v0 = 0x80;
            prim->u1 = texture_u_max;
            prim->v1 = 0x80;
            prim->u2 = 0;
            prim->u3 = texture_u_max;
        }
        prim->r0 = 0;
        prim->g0 = 0;
        prim->b0 = 0;
        prim->r1 = 0;
        prim->g1 = 0;
        prim->b1 = 0;
        prim->r2 = brightness;
        prim->g2 = brightness;
        prim->b2 = brightness;
        prim->r3 = brightness;
        prim->g3 = brightness;
        prim->b3 = brightness;

        angle_offset = (s16)segment * 0x100;
        raw_angle = angle_offset + rotation;
        biased_angle = raw_angle;
        prim->v2 = 0xBF;
        prim->v3 = 0xBF;
        if (raw_angle < 0) {
            biased_angle = raw_angle + 0xFFF;
        }
        angle_offset = (biased_angle >> 12) << 12;
        angle = raw_angle - angle_offset;

        scratch->vertices[2].vx = center->x +
            ((rsin(angle) >> 4) * radius >> 8);
        scratch->vertices[0].vx = scratch->vertices[2].vx;

        scratch->vertices[3].vx = center->x +
            ((rsin((((((s16)segment + 1) % 16) * 0x100 + rotation) % 0x1000)) >> 4) * radius >> 8);
        scratch->vertices[1].vx = scratch->vertices[3].vx;

        scratch->vertices[2].vy = center->y +
            ((rcos(angle) >> 4) * radius >> 8);
        scratch->vertices[0].vy = scratch->vertices[2].vy;

        scratch->vertices[3].vy = center->y +
            ((rcos((((((s16)segment + 1) % 16) * 0x100 + rotation) % 0x1000)) >> 4) * radius >> 8);
        scratch->vertices[1].vy = scratch->vertices[3].vy;

        scratch->sort_depth = RotAverage4(
            &scratch->vertices[0], &scratch->vertices[1], &scratch->vertices[2], &scratch->vertices[3],
            (s32 *)&scratch->projected_vertices[0], (s32 *)&scratch->projected_vertices[1], (s32 *)&scratch->projected_vertices[2], (s32 *)&scratch->projected_vertices[3],
            &scratch->depth_cue, &scratch->gte_flag);

        prim->x0 = scratch->projected_vertices[0].x;
        prim->y0 = scratch->projected_vertices[0].y;
        prim->x1 = scratch->projected_vertices[1].x;
        prim->y1 = scratch->projected_vertices[1].y;
        prim->x2 = scratch->projected_vertices[2].x;
        prim->y2 = scratch->projected_vertices[2].y;
        prim->x3 = scratch->projected_vertices[3].x;
        prim->y3 = scratch->projected_vertices[3].y;

        {
            u32 depth = scratch->sort_depth;

            if (depth < 0x1E0U) {
                ((GpuLinkTag *)&prim->tag)->addr = scratch->ordering_table[depth];
                ((GpuLinkTag *)(scratch->ordering_table + scratch->sort_depth))->addr = (u32)prim;
            }
        }
    }

    return 0;
}
