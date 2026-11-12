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
#include "sdk/libgpu_packets.h"
#include "dungeon/effect/shaded_quad_scratch.h"

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

#include "sdk/libgte_matrix.h"

/* Transform a textured quad and add it to the ordering table if visible. */
void draw_gouraud_textured_ribbon_quad(S_801663AC_4 *quad, ObjectPosition *position, SpriteFrameState *render_state, s16 depth_bias)
{
    ShadedQuadScratch *scratch = (ShadedQuadScratch *)0x1F800000;
    POLY_GT4 *packet;
    u8 *texture;
    s32 ot_index;
    u16 render_flags;
    u8 tex_flags;
    MATRIX view_matrix;

    scratch->ordering_table = (u32 *)(*(u8 **)&g_game_work.draw_buffer + 0xB0);
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
    ReadRotMatrix(&view_matrix);
    CompMatrix(&view_matrix, &scratch->local_matrix, &scratch->composed_matrix);
    ScaleMatrix(&scratch->composed_matrix, &scratch->scale);
    SetTransMatrix(&scratch->composed_matrix);
    SetRotMatrix(&scratch->composed_matrix);

    texture = ((S_801663AC_2 *)render_state)->unk_08;
    scratch->render_flags = render_state->flags;
    scratch->uv_u_start = texture[8];
    scratch->uv_v_start = texture[9];
    (*(s32 *)((u8 *)scratch + 0x14)) = texture[0xA];
    scratch->uv_v_extent = texture[0xB];
    packet = ((GpuContext *)(*(u8 **)&g_game_work.draw_buffer))->packetCursor;
    ((GpuContext *)(*(u8 **)&g_game_work.draw_buffer))->packetCursor = packet + 1;

    scratch->vertices[0].vx = quad->unk_74;
    scratch->vertices[1].vx = quad->unk_7A;
    scratch->vertices[2].vx = quad->unk_80;
    scratch->vertices[3].vx = quad->unk_86;
    scratch->vertices[0].vy = quad->unk_76;
    scratch->vertices[1].vy = quad->unk_7C;
    scratch->vertices[2].vy = quad->unk_82;
    scratch->vertices[3].vy = quad->unk_88;
    scratch->vertices[0].vz = quad->unk_78;
    scratch->vertices[1].vz = quad->unk_7E;
    scratch->vertices[2].vz = quad->unk_84;
    scratch->vertices[3].vz = quad->unk_8A;

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

            scratch->uv_u_extent += scratch->uv_u_start;
            if (scratch->uv_u_extent & 0x100) {
                scratch->uv_u_extent--;
            }
            scratch->uv_v_extent += scratch->uv_v_start;
            if (scratch->uv_v_extent & 0x100) {
                scratch->uv_v_extent--;
            }
            scratch->uv_v_start <<= 8;
            scratch->uv_v_extent <<= 8;

            if (render_state->clut) {
                if (scratch->render_flags & 0x100) {
                    packet->clut = render_state->clut;
                } else {
                    packet->clut = render_state->clut +
                                              ((ObjectPosition *)texture)->y.unsigned_parts.integer;
                }
            } else {
                packet->clut = ((ObjectPosition *)texture)->y.unsigned_parts.integer;
            }

            /* BYTES: retail writes the packet u/v byte pair with one sh of the combined value; storing u and v separately compiles to two sb */
            *(u16 *)&packet->u0 = scratch->uv_v_start +
                                      scratch->uv_u_start;
            /* BYTES: retail writes the packet u/v byte pair with one sh of the combined value; storing u and v separately compiles to two sb */
            *(u16 *)&packet->u1 = scratch->uv_v_start +
                                       scratch->uv_u_extent;

            if (render_state->tpage_abr) {
                packet->tpage = render_state->tpage_abr +
                                           (((ObjectPosition *)texture)->y.w.frac & 0xFF9F);
            } else {
                packet->tpage = ((ObjectPosition *)texture)->y.w.frac;
            }

            /* BYTES: retail writes the packet u/v byte pair with one sh of the combined value; storing u and v separately compiles to two sb */
            *(u16 *)&packet->u2 = scratch->uv_v_extent +
                                       scratch->uv_u_start;
            /* BYTES: retail writes the packet u/v byte pair with one sh of the combined value; storing u and v separately compiles to two sb */
            *(u16 *)&packet->u3 = scratch->uv_v_extent +
                                       scratch->uv_u_extent;

            if ((s16)packet->x0 > (s16)packet->x3) {
                packet->u1--;
                packet->u3--;
            }
            if ((s16)packet->y0 > (s16)packet->y3) {
                packet->v2--;
                packet->v3--;
            }

            /* BYTES: retail copies each vertex colour word (red, green, blue and the code or pad byte) with one sw; member stores compile to four sb */
            *(u32 *)&packet->r0 = quad->unk_00;
            /* BYTES: retail copies each vertex colour word (red, green, blue and the code or pad byte) with one sw; member stores compile to four sb */
            *(u32 *)&packet->r1 = quad->unk_04;
            /* BYTES: retail copies each vertex colour word (red, green, blue and the code or pad byte) with one sw; member stores compile to four sb */
            *(u32 *)&packet->r2 = quad->unk_08;
            /* BYTES: retail copies each vertex colour word (red, green, blue and the code or pad byte) with one sw; member stores compile to four sb */
            *(u32 *)&packet->r3 = quad->unk_0C;

            SetPolyGT4(packet);

            tex_flags = texture[1];
            render_state->color.c.code = tex_flags;
            render_flags = scratch->render_flags;
            if (render_flags & 8) {
                render_state->color.c.code = (render_flags & 4) ?
                    (tex_flags | 2) : (tex_flags & 0xFD);
            }

            packet->code |= render_state->color.c.code;
            packet->tag = (packet->tag & 0xFF000000) |
                (scratch->ordering_table[scratch->ot_index] & 0x00FFFFFF);

            scratch->ordering_table[scratch->ot_index] =
                (scratch->ordering_table[scratch->ot_index] & 0xFF000000) |
                ((u32)packet & 0x00FFFFFF);
        }
    }

    PopMatrix();
}

