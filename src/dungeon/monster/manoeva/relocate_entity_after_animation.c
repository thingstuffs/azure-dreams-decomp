#include "shared/entity.h"
#include "shared/gpu_packets.h"
#include "common.h"
#include "slus/data.h"
#include "shared/game_work.h"
#include "records/Rec_func_800D6DC0_arg2.h"
#include "dungeon/monster/manoeva.h"
#include "sdk/libgpu.h"
#include "sdk/libgte.h"
#include "sdk/libgpu_packets.h"
#include "engine/graphics/sprite_scratch.h"


typedef struct {
    s8 flag;
    u8 pad;
    s8 x;
    s8 y;
    u16 f4;
    u16 f6;
    u8 f8;
    u8 f9;
    u8 fA;
    u8 fB;
} Texture;

/* Projects textured sprite quads and queues visible packets for depth-sorted drawing. */
void project_depth_sorted_sprite_quads(ManoevaTerrainEffectBody *sprite, ObjectPosition *position, Rec_func_800D6DC0_arg2 *render,
    s16 depth_bias)
{
    GameWork *render_globals = &g_game_work;
    SpriteQuadScratch *scratch = (SpriteQuadScratch *)0x1F800000;
    GpuContext *state;
    MATRIX *matrix;
    POLY_FT4 *packet;
    Texture *texture;
    s32 scaled_coord;
    s32 view_angle;
    s32 angle_offset;
    s32 visible_0;
    s32 visible_1;
    s32 visible_2;
    s32 visible_3;
    s32 visible_01;
    s32 visible_012;

    if (sprite->unk_1C.s == 0) {
        return;
    }

    state = render_globals->draw_buffer;
    scratch->local_matrix.t[2] = 0;
    scratch->vertices[3].vz = 0;
    scratch->vertices[2].vz = 0;
    scratch->vertices[1].vz = 0;
    scratch->vertices[0].vz = 0;
    scratch->ordering_table = (u32 *)&state->orderTag;
    scratch->position.vx = position->x.unsigned_parts.integer;
    scratch->position.vy = position->y.unsigned_parts.integer;
    scratch->position.vz = position->z.unsigned_parts.integer;
    packet = state->packetCursor;
    scratch->sort_depth = RotTransPers(
        &scratch->position, (s32 *)&scratch->screen_origin, &scratch->depth_cue, &scratch->gte_flag);

    render->unk_14 |= 0x8000;
    {
        u32 depth = scratch->sort_depth;
        u32 sort_depth;
        u32 biased_depth;
        sort_depth = (biased_depth = depth - 6, biased_depth - (s16)depth_bias);
        matrix = &sprite_projection_matrix;
        matrix->t[2] = depth * 4;
        scratch->sort_depth = sort_depth;
    }

    if (scratch->sort_depth < 0x1E0U) {
        PushMatrix();
        scratch->screen_origin.x -= 0xA0;
        scratch->screen_origin.y -= 0x78;
        scratch->input.vx = render_globals->view.camera_rotation.parts.camera_rotation_x;
        scratch->input.vy = render_globals->view.camera_rotation.parts.camera_rotation_y;
        scratch->input.vz = render_globals->view.camera_rotation.parts.viewAngle;

        scratch->angles.vx = render->unk_16;
        scratch->angles.vz =
            ((u16)(render_globals->view.view_rotation_offset.parts.view_rotation_offset_z)) +
            (render->unk_1A - scratch->input.vy);
        view_angle = ((u16)scratch->input.vz + 0x100) & 0x1FF;
        angle_offset = render->unk_18 - 0x100;
        scratch->angles.vy = view_angle + angle_offset;

        scratch->extent_x = scratch->local_matrix.t[0] =
            render->unk_20;
        scratch->extent_y = scratch->local_matrix.t[1] =
            render->unk_22;
        RotMatrix(&scratch->angles, &scratch->local_matrix);

        scratch->input.vx = render->unk_1C;
        scratch->input.vy = render->unk_1E;
        scratch->input.vz = 0x1000;
        ScaleMatrix(&scratch->local_matrix, &scratch->input);
        CompMatrix(matrix, &scratch->local_matrix, &scratch->matrix);
        SetTransMatrix(&scratch->matrix);
        SetRotMatrix(&scratch->matrix);

        texture = (Texture *)render->unk_08;
        scratch->sprite_flags = render->unk_14;

        for (;;) {
            scratch->uv_u_start = texture->f8;
            scratch->uv_v_start = texture->f9;
            scratch->uv_u_extent = texture->fA;
            scratch->uv_v_extent = texture->fB;

            scaled_coord = (texture->x -
                     (s16)scratch->extent_x) *
                    sprite->unk_22;
            scratch->vertices[0].vx = scaled_coord >> 12;
            scaled_coord = (texture->x -
                     (s16)scratch->extent_x) *
                    sprite->unk_2A;
            scratch->vertices[2].vx = scaled_coord >> 12;
            scaled_coord = (scratch->vertices[0].vx +
                     scratch->uv_u_extent) *
                    sprite->unk_28;
            scratch->vertices[1].vx = scaled_coord >> 12;
            scaled_coord = (scratch->vertices[0].vx +
                     scratch->uv_u_extent) *
                    sprite->unk_30;
            scratch->vertices[3].vx = scaled_coord >> 12;

            scaled_coord = (texture->y -
                     (s16)scratch->extent_y) *
                    sprite->unk_24;
            scratch->vertices[0].vy = scaled_coord >> 12;
            scaled_coord = (texture->y -
                     (s16)scratch->extent_y) *
                    sprite->unk_28;
            scratch->vertices[1].vy = scaled_coord >> 12;
            scaled_coord = (scratch->vertices[0].vy +
                     scratch->uv_v_extent) *
                    sprite->unk_2C;
            scratch->vertices[2].vy = scaled_coord >> 12;
            {
                SVECTOR *vertex_1 = &scratch->vertices[1];
                SVECTOR *vertex_2 = &scratch->vertices[2];
                SVECTOR *vertex_3 = &scratch->vertices[3];
                s32 *screen_0;
                s32 bottom_y;

                bottom_y = scratch->vertices[0].vy +
                                scratch->uv_v_extent;
                screen_0 = (s32 *)&scratch->projected_vertices[0];
                scratch->vertices[3].vy = (bottom_y * sprite->unk_30) >> 12;

                RotTransPers4(&scratch->vertices[0], vertex_1,
                              vertex_2, vertex_3,
                              screen_0, (s32 *)&scratch->projected_vertices[1],
                              (s32 *)&scratch->projected_vertices[2], (s32 *)&scratch->projected_vertices[3],
                              &scratch->depth_cue, &scratch->gte_flag);
            }

            packet->x0 =
                scratch->projected_vertices[0].x + scratch->screen_origin.x;
            packet->y0 =
                scratch->projected_vertices[0].y + scratch->screen_origin.y;
            packet->x1 =
                scratch->projected_vertices[1].x + scratch->screen_origin.x;
            packet->y1 =
                scratch->projected_vertices[1].y + scratch->screen_origin.y;
            packet->x2 =
                scratch->projected_vertices[2].x + scratch->screen_origin.x;
            packet->y2 =
                scratch->projected_vertices[2].y + scratch->screen_origin.y;
            packet->x3 =
                scratch->projected_vertices[3].x + scratch->screen_origin.x;
            packet->y3 =
                scratch->projected_vertices[3].y + scratch->screen_origin.y;

            visible_0 = 0;
            if ((u16)(packet->x0 + 0x20) < 0x181U) {
                visible_0 =
                    (u16)(packet->y0 + 0x20) < 0x121U;
            }
            visible_1 = 0;
            if ((u16)(packet->x1 + 0x20) < 0x181U) {
                visible_1 =
                    (u16)(packet->y1 + 0x20) < 0x121U;
            }
            visible_01 = visible_0 | visible_1;
            visible_2 = 0;
            if ((u16)(packet->x2 + 0x20) < 0x181U) {
                visible_2 =
                    (u16)(packet->y2 + 0x20) < 0x121U;
            }
            visible_012 = visible_01 | visible_2;
            visible_3 = 0;
            if ((u16)(packet->x3 + 0x20) < 0x181U) {
                visible_3 =
                    (u16)(packet->y3 + 0x20) < 0x121U;
            }

            if ((visible_012 | visible_3) != 0) {
                scratch->uv_u_extent += scratch->uv_u_start;
                scratch->uv_v_extent =
                    (scratch->uv_v_start +
                     scratch->uv_v_extent) << 8;
                scratch->uv_v_start <<= 8;

                packet->clut =
                    render->unk_12 + texture->f6;
                /* BYTES: retail writes the packet u/v byte pair with one sh of the combined value; storing u and v separately compiles to two sb */
                *(u16 *)&packet->u0 = scratch->uv_v_start + scratch->uv_u_start;
                /* BYTES: retail writes the packet u/v byte pair with one sh of the combined value; storing u and v separately compiles to two sb */
                *(u16 *)&packet->u1 = scratch->uv_v_start + scratch->uv_u_extent;
                if (render->unk_10 != 0) {
                    packet->tpage =
                        render->unk_10 +
                        (texture->f4 & 0xFF9F);
                } else {
                    packet->tpage = texture->f4;
                }
                /* BYTES: retail writes the packet u/v byte pair with one sh of the combined value; storing u and v separately compiles to two sb */
                *(u16 *)&packet->u2 = scratch->uv_v_extent + scratch->uv_u_start;
                /* BYTES: retail writes the packet u/v byte pair with one sh of the combined value; storing u and v separately compiles to two sb */
                *(u16 *)&packet->u3 = scratch->uv_v_extent + scratch->uv_u_extent;

                if (packet->u1 == 0) {
                    packet->u1--;
                    packet->u3--;
                }
                if (packet->v2 == 0) {
                    packet->v2--;
                    packet->v3--;
                }

                /* BYTES: retail stores the sprite colour word (r0, g0, b0 and code) with one sw; member stores compile to four sb */
                *(u32 *)&packet->r0 = render->unk_0C;
                SetPolyFT4(packet);
                if (scratch->sprite_flags & 8) {
                    packet->code |= 2;
                }

                AddPrim(scratch->ordering_table + scratch->sort_depth,
                              packet);
                packet++;
            }

            if (texture->flag < 0) {
                break;
            }
            texture++;
        }

        PopMatrix();
    }

    ((GpuContext *)render_globals->draw_buffer)->packetCursor = packet;
}
