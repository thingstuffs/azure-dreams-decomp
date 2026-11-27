#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_moving_views.h"
#include "dungeon/effect/sprite.h"
#include "dungeon/effect/projected_quad_scratch.h"
#include "sdk/libgpu.h"
#include "sdk/libgte.h"


typedef struct S_func_818BC9CC_3 {
    struct {
        u8 pad_00[3];
        u8 unk_03;
    } unk_00;
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 unk_07;
    u16 unk_08;
    u16 unk_0A;
    u8 unk_0C;
    u8 unk_0D;
    u16 unk_0E;
    u8 unk_10;
    u8 unk_11;
    u8 unk_12;
    u8 pad_13[0x1];
    u16 unk_14;
    u16 unk_16;
    u8 unk_18;
    u8 unk_19;
    u16 unk_1A;
    u8 unk_1C;
    u8 unk_1D;
    u8 unk_1E;
    u8 pad_1F[0x1];
    u16 unk_20;
    u16 unk_22;
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x2];
    u8 unk_28;
    u8 unk_29;
    u8 unk_2A;
    u8 pad_2B[0x1];
    u16 unk_2C;
    u16 unk_2E;
    u8 unk_30;
    u8 unk_31;
} S_func_818BC9CC_3;

typedef struct S_func_818BC9CC_4 {
    u32 unk_00;
} S_func_818BC9CC_4;


typedef struct { unsigned addr : 24; unsigned len : 8; } PacketTag;

static inline u32 *projected_ordering_entry(ProjectedQuadScratch *scratch)
{
    /* BYTES: Compute the scaled depth before adding the ordering-table base. Pointer indexing changes which temporary holds the loaded table base. */
    return (u32 *)((scratch->ot_index << 2) + (unsigned long)scratch->ordering_table);
}

/* Draw four shaded textured quads around the given position. */
s32 draw_four_shaded_quads(OffsetColorEffectBody *effect, MovingPosition *position)
{
    ProjectedQuadScratch *scratch;
    S_func_818BC9CC_3 *packet;
    S_func_818BC9CC_4 *draw_mode;
    S_func_818BC9CC_4 *draw_mode_2;
    GpuContext *render_ctx;
    GpuContext *full_ctx;
    GpuContext *tile_ctx;
    GameWork *render_state;
    s32 page_depth;
    s32 page_blend;
    s32 page_x;
    u32 y_extent;
    u32 x_extent;
    u32 depth;
    s32 quad_index;
    u32 far_z;
    u32 z_extent;
    u32 far_y;
    s32 angle;
    u16 texture_v;
    u16 coord;
    u8 intensity;
    s16 tile_window[4];
    s16 full_window[4];

    render_state = &g_game_work;
    scratch = PROJECTED_QUAD_SCRATCH;
    angle = render_state->view.camera_rotation.parts.viewAngle;
    scratch->ordering_table = &g_game_work.draw_buffer->orderTag[GPU_ORDER_DEPTH_BASE];
    x_extent = (u32)((rcos(angle) >> 4) * (s16)effect->extent) >> 8;
    y_extent = (u32)((rsin(angle) >> 4) * (s16)effect->extent) >> 8;
    texture_v = (effect->elapsed_ticks.s16 % 4) << 3;

    quad_index = 0;

    do {
        render_ctx = render_state->draw_buffer;
        packet = render_ctx->packetCursor;
        render_ctx->packetCursor = (u8 *)packet + 0x34;

        packet->unk_00.unk_03 = 0x0C;
        packet->unk_07 = 0x3E;
        packet->unk_1A = GetTPage(0, 1, 0x280, 0x100);
        packet->unk_0E = effect->clut;
        packet->unk_0C = 0;
        packet->unk_0D = (u8)texture_v;
        packet->unk_18 = 0x3F;
        packet->unk_19 = (u8)texture_v;
        packet->unk_24 = 0x3F;
        packet->unk_25 = texture_v + 0x3F;
        packet->unk_31 = texture_v + 0x3F;
        packet->unk_30 = 0;
        packet->unk_04 = effect->brightness;
        packet->unk_05 = effect->brightness;
        intensity = effect->brightness;
        packet->unk_10 = 0;
        packet->unk_11 = 0;
        packet->unk_12 = 0;
        packet->unk_1C = 0;
        packet->unk_1D = 0;
        packet->unk_1E = 0;
        packet->unk_28 = 0;
        packet->unk_29 = 0;
        packet->unk_2A = 0;
        packet->unk_06 = intensity;

        switch (quad_index) {
        case 0:
            coord = position->x;
            scratch->vertices[2].vx = coord;
            scratch->vertices[0].vx = coord;
            coord = position->x + x_extent;
            scratch->vertices[3].vx = coord;
            scratch->vertices[1].vx = coord;
            coord = position->y;
            scratch->vertices[2].vy = coord;
            scratch->vertices[0].vy = coord;
            coord = position->y - y_extent;
            scratch->vertices[3].vy = coord;
            scratch->vertices[1].vy = coord;
            coord = position->z;
            scratch->vertices[1].vz = coord;
            scratch->vertices[0].vz = coord;
            far_z = position->z;
            z_extent = effect->extent;
            far_z = far_z + z_extent;
            scratch->vertices[3].vz = far_z;
            scratch->vertices[2].vz = far_z;
            break;
        case 1:
            coord = position->x;
            scratch->vertices[2].vx = coord;
            scratch->vertices[0].vx = coord;
            coord = position->x - x_extent;
            scratch->vertices[3].vx = coord;
            scratch->vertices[1].vx = coord;
            coord = position->y;
            scratch->vertices[2].vy = coord;
            scratch->vertices[0].vy = coord;
            coord = position->y + y_extent;
            scratch->vertices[3].vy = coord;
            scratch->vertices[1].vy = coord;
            coord = position->z;
            scratch->vertices[1].vz = coord;
            scratch->vertices[0].vz = coord;
            far_z = position->z;
            far_z = far_z + effect->extent;
            scratch->vertices[3].vz = far_z;
            scratch->vertices[2].vz = far_z;
            break;
        case 2:
            coord = position->x;
            scratch->vertices[2].vx = coord;
            scratch->vertices[0].vx = coord;
            coord = position->x + x_extent;
            scratch->vertices[3].vx = coord;
            scratch->vertices[1].vx = coord;
            coord = position->y;
            scratch->vertices[2].vy = coord;
            scratch->vertices[0].vy = coord;
            far_y = (u32)position->y - y_extent;
            scratch->vertices[3].vy = far_y;
            scratch->vertices[1].vy = far_y;
            coord = position->z;
            scratch->vertices[1].vz = coord;
            scratch->vertices[0].vz = coord;
            far_z = position->z;
            far_z -= effect->extent;
            scratch->vertices[3].vz = far_z;
            scratch->vertices[2].vz = far_z;
            break;
        case 3:
            coord = position->x;
            scratch->vertices[2].vx = coord;
            scratch->vertices[0].vx = coord;
            coord = position->x - x_extent;
            scratch->vertices[3].vx = coord;
            scratch->vertices[1].vx = coord;
            coord = position->y;
            scratch->vertices[2].vy = coord;
            scratch->vertices[0].vy = coord;
            far_y = (u32)position->y + y_extent;
            scratch->vertices[3].vy = far_y;
            scratch->vertices[1].vy = far_y;
            coord = position->z;
            scratch->vertices[1].vz = coord;
            scratch->vertices[0].vz = coord;
            far_z = position->z;
            far_z -= effect->extent;
            scratch->vertices[3].vz = far_z;
            scratch->vertices[2].vz = far_z;
            break;
        }

        {
            void *vertex0 = &scratch->vertices[0];
            void *vertex1 = &scratch->vertices[1];
            void *vertex2 = &scratch->vertices[2];
            void *vertex3 = &scratch->vertices[3];

            depth = RotAverage4(vertex0, vertex1, vertex2, vertex3,
                              (s32 *)&scratch->screen[0].x, (s32 *)&scratch->screen[1].x,
                              (s32 *)&scratch->screen[2].x, (s32 *)&scratch->screen[3].x,
                              &scratch->depth_cue, &scratch->gte_flag);
        }
        scratch->ot_index = depth;
        packet->unk_08 = scratch->screen[0].x;
        packet->unk_0A = scratch->screen[0].y;
        packet->unk_14 = scratch->screen[1].x;
        packet->unk_16 = scratch->screen[1].y;
        packet->unk_20 = scratch->screen[2].x;
        packet->unk_22 = scratch->screen[2].y;
        packet->unk_2C = scratch->screen[3].x;
        packet->unk_2E = scratch->screen[3].y;

        if (scratch->ot_index < 0x1E0U) {
            full_window[1] = 0;
            full_window[0] = 0;
            full_ctx = render_state->draw_buffer;
            full_window[3] = 0xFF;
            full_window[2] = 0xFF;
            draw_mode = full_ctx->packetCursor;
            full_ctx->packetCursor = (u8 *)draw_mode + 0x0C;
            SetDrawMode(draw_mode, 0, 0, GetTPage(0, 1, 0x280, 0x100), full_window);
            page_depth = 0;

            page_blend = 1;
            page_x = 0x280;

            {
                u32 *ot;

                ot = projected_ordering_entry(scratch);
                ((PacketTag *)draw_mode)->addr = ((PacketTag *)ot)->addr;
            }
            {
                u32 *ot;

                ot = projected_ordering_entry(scratch);
                ((PacketTag *)ot)->addr = (u32)draw_mode;
            }
            {
                u32 *ot;

                ot = projected_ordering_entry(scratch);
                ((PacketTag *)packet)->addr = ((PacketTag *)ot)->addr;
            }
            {
                u32 *ot;

                ot = projected_ordering_entry(scratch);
                ((PacketTag *)ot)->addr = (u32)packet;
            }

            tile_window[0] = 0;
            tile_window[1] = 0x80;
            tile_ctx = render_state->draw_buffer;
            tile_window[3] = 0x40;
            tile_window[2] = 0x40;
            draw_mode_2 = tile_ctx->packetCursor;
            tile_ctx->packetCursor = (u8 *)draw_mode_2 + 0x0C;
            SetDrawMode(draw_mode_2, 0, 0, GetTPage(page_depth, page_blend, page_x, 0x100), tile_window);

            {
                u32 *ot;

                ot = projected_ordering_entry(scratch);
                ((PacketTag *)draw_mode_2)->addr = ((PacketTag *)ot)->addr;
            }
            {
                u32 *ot;

                ot = projected_ordering_entry(scratch);
                ((PacketTag *)ot)->addr = (u32)draw_mode_2;
            }
        }
        quad_index++;
    } while (quad_index < 4);

    return 0;
}
