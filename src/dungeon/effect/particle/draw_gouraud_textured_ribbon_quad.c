#include "shared/gpu_packets.h"
#include "dungeon/effect/particle.h"
/* Rowbase phase-2 landing shape (docs/rowbase_lane_phase2.md): natural plain C
 * at the Beldo region true base 0x80174334 — the function defines its
 * TRUE-space name draw_gouraud_textured_ribbon_quad; the j->0x8017xxxx words are its own local
 * if/else joins (gap probe 5). No pins, no noreturn scaffolding. */
#include "common.h"
#include "shared/game_work.h"
#include "sdk/libgpu.h"
#include "sdk/libgte.h"

typedef struct S_801663AC_0 {
    u8 pad_00[0xC];
    union { s32 s32; u16 u16; } unk_0C;   /* accessed as both */
    union { s32 s32; u16 u16; } unk_10;   /* accessed as both */
    union { s32 s32; u16 u16; } unk_14;   /* accessed as both */
    union { s32 s32; u16 u16; } unk_18;   /* accessed as both */
    u8 pad_1C[0x8];
    u8 *unk_24;
    u16 unk_28;
    u8 pad_2A[0xA];
    s32 unk_34;
    s32 unk_38;
    s32 unk_3C;
    u8 pad_40[0x48];
    s32 unk_88;
    s32 unk_8C;
    s32 unk_90;
    u8 pad_94[0x10];
    u16 unk_A4;
    u16 unk_A6;
    u16 unk_A8;
    u8 pad_AA[0x6];
    u16 unk_B0;
    u16 unk_B2;
    u16 unk_B4;
    u8 pad_B6[0x2];
    u16 unk_B8;
    u16 unk_BA;
    u16 unk_BC;
    u8 pad_BE[0x2];
    u16 unk_C0;
    u16 unk_C2;
    u16 unk_C4;
    u8 pad_C6[0x2];
    u16 unk_C8;
    u16 unk_CA;
    u16 unk_CC;
    u8 pad_CE[0x32];
    s32 unk_100;
} S_801663AC_0;   /* scratch in draw_gouraud_textured_ribbon_quad */


typedef struct S_801663AC_2 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 pad_0C[0x3];
    u8 unk_0F;
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
} S_801663AC_2;   /* arg2 in draw_gouraud_textured_ribbon_quad */

   /* *(u8 **)D_80083160 in draw_gouraud_textured_ribbon_quad */

typedef struct S_801663AC_4 {
    u32 unk_00;
    u32 unk_04;
    u32 unk_08;
    u32 unk_0C;
    u8 pad_10[0x64];
    u16 unk_74;
    u16 unk_76;
    u16 unk_78;
    u16 unk_7A;
    u16 unk_7C;
    u16 unk_7E;
    u16 unk_80;
    u16 unk_82;
    u16 unk_84;
    u16 unk_86;
    u16 unk_88;
    u16 unk_8A;
} S_801663AC_4;   /* arg0 in draw_gouraud_textured_ribbon_quad */

typedef struct S_801663AC_5 {
    u32 unk_00;
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_04;   /* overlapping accesses */
    u16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
    u16 unk_0E;
    u32 unk_10;
    u16 unk_14;
    u16 unk_16;
    union { u16 u16; u8 u8; } unk_18;   /* accessed as both */
    u16 unk_1A;
    u32 unk_1C;
    u16 unk_20;
    u16 unk_22;
    union { struct { u16 v; } at00; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    u8 pad_26[0x2];
    u32 unk_28;
    u16 unk_2C;
    u16 unk_2E;
    union {
        struct { u16 v; } at00;
        struct { u8 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_30;   /* overlapping accesses */
} S_801663AC_5;   /* packet in draw_gouraud_textured_ribbon_quad */


typedef struct {
    s16 m[3][3];
    s16 pad;
    s32 t[3];
} MATRIX;

/* Transform a textured quad and add it to the ordering table if visible. */
void draw_gouraud_textured_ribbon_quad(void *quad, ObjectPosition *position, SpriteFrameState *render_state, s16 depth_bias)
{
    S_801663AC_0 *scratch = (S_801663AC_0 *)0x1F800000;
    u8 *packet;
    u8 *texture;
    s32 ot_index;
    u16 render_flags;
    u8 tex_flags;
    MATRIX view_matrix;

    scratch->unk_24 = *(u8 **)&g_game_work.draw_buffer + 0xB0;
    scratch->unk_88 = position->x.w.i;
    scratch->unk_8C = position->y.w.i;
    scratch->unk_90 = position->z.w.i;
    render_state->flags |= 0x8000;

    PushMatrix();

    scratch->unk_3C = 0x2000;
    scratch->unk_38 = 0x2000;
    scratch->unk_34 = 0x2000;
    scratch->unk_A4 = render_state->angle_x;
    scratch->unk_A8 = render_state->angle_z;
    scratch->unk_A6 = render_state->angle_y;
    RotMatrix((u8 *)scratch + 0xA4, (u8 *)scratch + 0x74);
    ReadRotMatrix(&view_matrix);
    CompMatrix(&view_matrix, (u8 *)scratch + 0x74, (u8 *)scratch + 0x54);
    ScaleMatrix((u8 *)scratch + 0x54, (u8 *)scratch + 0x34);
    SetTransMatrix((u8 *)scratch + 0x54);
    SetRotMatrix((u8 *)scratch + 0x54);

    texture = ((S_801663AC_2 *)render_state)->unk_08;
    scratch->unk_28 = render_state->flags;
    scratch->unk_0C.s32 = texture[8];
    scratch->unk_10.s32 = texture[9];
    (*(s32 *)((u8 *)scratch + 0x14)) = texture[0xA];
    scratch->unk_18.s32 = texture[0xB];
    packet = ((GpuContext *)(*(u8 **)&g_game_work.draw_buffer))->packetCursor;
    ((GpuContext *)(*(u8 **)&g_game_work.draw_buffer))->packetCursor = packet + 0x34;

    scratch->unk_B0 = ((S_801663AC_4 *)quad)->unk_74;
    scratch->unk_B8 = ((S_801663AC_4 *)quad)->unk_7A;
    scratch->unk_C0 = ((S_801663AC_4 *)quad)->unk_80;
    scratch->unk_C8 = ((S_801663AC_4 *)quad)->unk_86;
    scratch->unk_B2 = ((S_801663AC_4 *)quad)->unk_76;
    scratch->unk_BA = ((S_801663AC_4 *)quad)->unk_7C;
    scratch->unk_C2 = ((S_801663AC_4 *)quad)->unk_82;
    scratch->unk_CA = ((S_801663AC_4 *)quad)->unk_88;
    scratch->unk_B4 = ((S_801663AC_4 *)quad)->unk_78;
    scratch->unk_BC = ((S_801663AC_4 *)quad)->unk_7E;
    scratch->unk_C4 = ((S_801663AC_4 *)quad)->unk_84;
    scratch->unk_CC = ((S_801663AC_4 *)quad)->unk_8A;

    ot_index = RotAverage4((u8 *)scratch + 0xB0, (u8 *)scratch + 0xB8,
                             (u8 *)scratch + 0xC0, (u8 *)scratch + 0xC8,
                             packet + 8, packet + 0x14,
                             packet + 0x20, packet + 0x2C,
                             (u8 *)scratch + 0xD0, (u8 *)scratch + 0xD4) - depth_bias - 6;
    scratch->unk_100 = ot_index;

    if ((u32)ot_index < 0x1E0) {
        if ((((u16)(((S_801663AC_5 *)packet)->unk_08 + 0x20) < 0x181) &&
             ((u16)(((S_801663AC_5 *)packet)->unk_0A + 0x20) < 0x121)) |
            (((u16)(((S_801663AC_5 *)packet)->unk_14 + 0x20) < 0x181) &&
             ((u16)(((S_801663AC_5 *)packet)->unk_16 + 0x20) < 0x121)) |
            (((u16)(((S_801663AC_5 *)packet)->unk_20 + 0x20) < 0x181) &&
             ((u16)(((S_801663AC_5 *)packet)->unk_22 + 0x20) < 0x121)) |
            (((u16)(((S_801663AC_5 *)packet)->unk_2C + 0x20) < 0x181) &&
             ((u16)(((S_801663AC_5 *)packet)->unk_2E + 0x20) < 0x121))) {
            render_state->flags &= 0x7FFF;

            scratch->unk_14.s32 += scratch->unk_0C.s32;
            if (scratch->unk_14.s32 & 0x100) {
                scratch->unk_14.s32--;
            }
            scratch->unk_18.s32 += scratch->unk_10.s32;
            if (scratch->unk_18.s32 & 0x100) {
                scratch->unk_18.s32--;
            }
            scratch->unk_10.s32 <<= 8;
            scratch->unk_18.s32 <<= 8;

            if (render_state->clut) {
                if (scratch->unk_28 & 0x100) {
                    ((S_801663AC_5 *)packet)->unk_0E = render_state->clut;
                } else {
                    ((S_801663AC_5 *)packet)->unk_0E = render_state->clut +
                                              ((ObjectPosition *)texture)->y.unsigned_parts.integer;
                }
            } else {
                ((S_801663AC_5 *)packet)->unk_0E = ((ObjectPosition *)texture)->y.unsigned_parts.integer;
            }

            ((S_801663AC_5 *)packet)->unk_0C = scratch->unk_10.u16 +
                                      scratch->unk_0C.u16;
            ((S_801663AC_5 *)packet)->unk_18.u16 = scratch->unk_10.u16 +
                                       scratch->unk_14.u16;

            if (render_state->tpage_abr) {
                ((S_801663AC_5 *)packet)->unk_1A = render_state->tpage_abr +
                                           (((ObjectPosition *)texture)->y.w.frac & 0xFF9F);
            } else {
                ((S_801663AC_5 *)packet)->unk_1A = ((ObjectPosition *)texture)->y.w.frac;
            }

            ((S_801663AC_5 *)packet)->unk_24.at00.v = scratch->unk_18.u16 +
                                       scratch->unk_0C.u16;
            ((S_801663AC_5 *)packet)->unk_30.at00.v = scratch->unk_18.u16 +
                                       scratch->unk_14.u16;

            if ((s16)((S_801663AC_5 *)packet)->unk_08 > (s16)((S_801663AC_5 *)packet)->unk_2C) {
                ((S_801663AC_5 *)packet)->unk_18.u8--;
                ((S_801663AC_5 *)packet)->unk_30.at00u.v--;
            }
            if ((s16)((S_801663AC_5 *)packet)->unk_0A > (s16)((S_801663AC_5 *)packet)->unk_2E) {
                ((S_801663AC_5 *)packet)->unk_24.at01.v--;
                ((S_801663AC_5 *)packet)->unk_30.at01.v--;
            }

            ((S_801663AC_5 *)packet)->unk_04.at00.v = ((S_801663AC_4 *)quad)->unk_00;
            ((S_801663AC_5 *)packet)->unk_10 = ((S_801663AC_4 *)quad)->unk_04;
            ((S_801663AC_5 *)packet)->unk_1C = ((S_801663AC_4 *)quad)->unk_08;
            ((S_801663AC_5 *)packet)->unk_28 = ((S_801663AC_4 *)quad)->unk_0C;

            SetPolyGT4(packet);

            tex_flags = texture[1];
            render_state->color.c.code = tex_flags;
            render_flags = scratch->unk_28;
            if (render_flags & 8) {
                render_state->color.c.code = (render_flags & 4) ?
                    (tex_flags | 2) : (tex_flags & 0xFD);
            }

            ((S_801663AC_5 *)packet)->unk_04.at03.v |= render_state->color.c.code;
            ((S_801663AC_5 *)packet)->unk_00 = (((S_801663AC_5 *)packet)->unk_00 & 0xFF000000) |
                ((*(u32 *)((u8 *)(scratch->unk_24)
                    + scratch->unk_100 * 4)) & 0x00FFFFFF);

            (*(u32 *)((u8 *)(scratch->unk_24) + scratch->unk_100 * 4)) =
                ((*(u32 *)((u8 *)(scratch->unk_24)
                    + scratch->unk_100 * 4)) & 0xFF000000) |
                ((u32)packet & 0x00FFFFFF);
        }
    }

    PopMatrix();
}

