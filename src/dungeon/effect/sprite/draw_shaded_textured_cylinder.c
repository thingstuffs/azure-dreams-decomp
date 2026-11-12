#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_moving_views.h"
#include "dungeon/effect/sprite.h"
#include "sdk/libgpu.h"
#include "sdk/libgte.h"
#include "sdk/libgte_matrix.h"
#include "shared/dungeon_effect_state.h"

typedef struct S_80024930_0 {
    u8 pad_00[0x18];
    union { void * p; u8 * p2; } unk_18;   /* accessed as both */
    u8 pad_1C[0x48];
    SVECTOR vertices[4]; /* RotAverage4 inputs: the quad corners */
    s32 depth_cue; /* RotAverage4 depth-cue output */
    s32 gte_flag; /* RotAverage4 GTE flag output */
    u8 pad_8C[0x28];
    u32 unk_B4;
    u8 pad_B8[0x20];
    u16 unk_D8;
    u16 unk_DA;
    u16 unk_DC;
    u16 unk_DE;
    u16 unk_E0;
    u16 unk_E2;
    u16 unk_E4;
    u16 unk_E6;
} S_80024930_0;   /* scratch in draw_shaded_textured_cylinder */

   /* arg1 in draw_shaded_textured_cylinder */

   /* *global_page in draw_shaded_textured_cylinder */

typedef struct S_80024930_3 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_00;   /* overlapping accesses */
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
} S_80024930_3;   /* prim in draw_shaded_textured_cylinder */

typedef struct S_80024930_4 {
    u32 unk_00;
} S_80024930_4;   /* (void *)offset in draw_shaded_textured_cylinder */


typedef struct TagWord { u32 addr:24; u32 len:8; } TagWord;

/* Draws a shaded, textured cylindrical wall using 16 quads. */
s32 draw_shaded_textured_cylinder(B22_81893474_EffectState *unused_data, MovingPosition *center, s32 unused_value, s16 rotation,
                  s32 height, s16 radius, u8 blend_mode, u8 brightness)
{
    S_80024930_0 *scratch = (S_80024930_0 *)0x1F800000;
    s32 edge_z;
    s16 segment;
    void **global_page = (void **)((u8 *)(&g_game_work));

    scratch->unk_18.p = (u8 *)(*global_page) + 0xB0;
    edge_z = center->z - height + 1;
    scratch->vertices[1].vz = edge_z;
    scratch->vertices[0].vz = edge_z;
    edge_z = center->z;
    scratch->vertices[2].vz = edge_z;
    scratch->vertices[3].vz = edge_z;

    for (segment = 0; segment < 16; segment++) {
        register u8 *prim;
        s32 next_angle;
        s32 angle_offset;
        s32 raw_angle;
        s32 biased_angle;
        s32 angle;

        prim = ((GpuContext *)(*global_page))->packetCursor;

        ((GpuContext *)(*global_page))->packetCursor = prim + 0x34;
        ((S_80024930_3 *)prim)->unk_00.at03.v = 12;
        ((S_80024930_3 *)prim)->unk_07 = 0x3C;

        if (blend_mode == 4) {
            ((S_80024930_3 *)prim)->unk_1A = GetTPage(0, 0, 0x280, 0x100);
        } else {
            ((S_80024930_3 *)prim)->unk_07 = 0x3E;
            ((S_80024930_3 *)prim)->unk_1A =
                GetTPage(0, blend_mode, 0x280, 0x100);
        }

        ((S_80024930_3 *)prim)->unk_0E = 0x7E00;
        {
            register s32 texture_u_max = 0x3F;

            ((S_80024930_3 *)prim)->unk_0C = 0;
            ((S_80024930_3 *)prim)->unk_0D = 0x80;
            ((S_80024930_3 *)prim)->unk_18 = texture_u_max;
            ((S_80024930_3 *)prim)->unk_19 = 0x80;
            ((S_80024930_3 *)prim)->unk_24 = 0;
            ((S_80024930_3 *)prim)->unk_30 = texture_u_max;
        }
        ((S_80024930_3 *)prim)->unk_04 = 0;
        ((S_80024930_3 *)prim)->unk_05 = 0;
        ((S_80024930_3 *)prim)->unk_06 = 0;
        ((S_80024930_3 *)prim)->unk_10 = 0;
        ((S_80024930_3 *)prim)->unk_11 = 0;
        ((S_80024930_3 *)prim)->unk_12 = 0;
        ((S_80024930_3 *)prim)->unk_1C = brightness;
        ((S_80024930_3 *)prim)->unk_1D = brightness;
        ((S_80024930_3 *)prim)->unk_1E = brightness;
        ((S_80024930_3 *)prim)->unk_28 = brightness;
        ((S_80024930_3 *)prim)->unk_29 = brightness;
        ((S_80024930_3 *)prim)->unk_2A = brightness;

        angle_offset = (s16)segment * 0x100;
        raw_angle = angle_offset + rotation;
        biased_angle = raw_angle;
        ((S_80024930_3 *)prim)->unk_25 = 0xBF;
        ((S_80024930_3 *)prim)->unk_31 = 0xBF;
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

        scratch->unk_B4 = RotAverage4(
            &scratch->vertices[0], &scratch->vertices[1], &scratch->vertices[2], &scratch->vertices[3],
            (s32 *)&scratch->unk_D8, (s32 *)&scratch->unk_DC, (s32 *)&scratch->unk_E0, (s32 *)&scratch->unk_E4,
            &scratch->depth_cue, &scratch->gte_flag);

        ((S_80024930_3 *)prim)->unk_08 = scratch->unk_D8;
        ((S_80024930_3 *)prim)->unk_0A = scratch->unk_DA;
        ((S_80024930_3 *)prim)->unk_14 = scratch->unk_DC;
        ((S_80024930_3 *)prim)->unk_16 = scratch->unk_DE;
        ((S_80024930_3 *)prim)->unk_20 = scratch->unk_E0;
        ((S_80024930_3 *)prim)->unk_22 = scratch->unk_E2;
        ((S_80024930_3 *)prim)->unk_2C = scratch->unk_E4;
        ((S_80024930_3 *)prim)->unk_2E = scratch->unk_E6;

        {
            u32 depth_or_mask = scratch->unk_B4;

            if (depth_or_mask < 0x1E0U) {
                u32 ot_entry_addr = depth_or_mask * 4;
                ot_entry_addr += (u32)scratch->unk_18.p2;
                ((TagWord *)prim)->addr = ((S_80024930_4 *)(void *)ot_entry_addr)->unk_00;
                ((TagWord *)(scratch->unk_18.p2 +
                    scratch->unk_B4 * 4))->addr = (u32)prim;
            }
        }
    }

    return 0;
}
