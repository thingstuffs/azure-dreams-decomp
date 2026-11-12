#include "shared/gpu_packets.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/game_work.h"
#include "dungeon/effect/mesh.h"
#include "sdk/libgpu.h"
#include "sdk/libgte.h"
#include "sdk/libgpu_packets.h"
#include "engine/graphics/sprite_scratch.h"

typedef void (*Callback)(s32, void *, void *, void *);

   /* global_page->table[0] in transform_sprite_parts_to_quads */

typedef struct S_800D07C8_4 {
    u8 unk_00;
} S_800D07C8_4;

   /* table[0] in transform_sprite_parts_to_quads */

/* Transform sprite parts into textured quads, queue visible quads, and invoke part callbacks. */
void transform_sprite_parts_to_quads(s32 context, ObjectPosition *position, SpriteFrameState *sprite, s16 depth_bias) {
    MATRIX matrix;
    SpriteQuadScratch *scratch = (SpriteQuadScratch *)0x1F800000;
    u8 *part_uv;
    u8 *part;
    POLY_GT4 *packet;
    s16 vertex_x;
    s16 vertex_y;
    s32 first_three_visible;
    s32 first_pair_visible;
    s32 color;
    s32 u_end;
    s32 v_end;
    s32 vertex_2_visible;
    s32 vertex_0_visible;
    s32 vertex_1_visible;
    s32 vertex_3_visible;
    u32 depth;
    u16 sprite_flags;
    u8 part_command;
    u8 draw_command;
    u8 **table = ((u8 * *)(&g_game_work));
    Callback callback;

    scratch->ordering_table = (u32 *)(table[0] + 0xB0);
    scratch->local_matrix.t[0] = position->x.w.i;
    scratch->local_matrix.t[1] = position->y.w.i;
    scratch->local_matrix.t[2] = position->z.w.i;
    scratch->vertices[3].vz = 0;
    scratch->vertices[2].vz = 0;
    scratch->vertices[1].vz = 0;
    scratch->vertices[0].vz = 0;
    packet = ((GpuContext *)(table[0]))->packetCursor;
    sprite->flags |= 0x8000;
    PushMatrix();
    scratch->extent_x = sprite->offset_x;
    scratch->extent_y = sprite->offset_y;
    scratch->input.vx = sprite->scale_x * 2;
    scratch->input.vy = sprite->scale_y * 2;
    scratch->input.vz = 0;
    scratch->angles.vx = sprite->angle_x;
    scratch->angles.vz = sprite->angle_z;
    scratch->angles.vy = sprite->angle_y;
    RotMatrix(&scratch->angles, &scratch->local_matrix);
    ReadRotMatrix(&matrix);
    CompMatrix(&matrix, &scratch->local_matrix, &scratch->matrix);
    ScaleMatrix(&scratch->matrix, &scratch->input);
    SetTransMatrix(&scratch->matrix);
    SetRotMatrix(&scratch->matrix);

    part = *(u8 * *)&sprite->source;
    scratch->sprite_flags = sprite->flags;
    for (;;) {
        part_uv = part + 8;
        if (!(((S_800D07C8_4 *)part)->unk_00 & 0x20)) {
            scratch->uv_u_start = (*(part_uv + 0));
            scratch->uv_v_start = (*(part_uv + 1));
            scratch->uv_u_extent = (*(part_uv + 2));
            scratch->uv_v_extent = (*(part_uv + 3));
            if ((((S_800D07C8_4 *)part)->unk_00 ^ scratch->sprite_flags) & 1) {
                vertex_x = (0 - (s8)(*(part_uv + -6))) - scratch->extent_x;
                scratch->vertices[2].vx = vertex_x;
                scratch->vertices[0].vx = vertex_x;
                vertex_x -= scratch->uv_u_extent;
                scratch->vertices[3].vx = vertex_x;
                scratch->vertices[1].vx = vertex_x;
            } else {
                vertex_x = (s8)(*(part_uv + -6)) - scratch->extent_x;
                scratch->vertices[2].vx = vertex_x;
                scratch->vertices[0].vx = vertex_x;
                vertex_x = vertex_x + scratch->uv_u_extent;
                scratch->vertices[3].vx = vertex_x;
                scratch->vertices[1].vx = vertex_x;
            }
            if ((((S_800D07C8_4 *)part)->unk_00 ^ scratch->sprite_flags) & 2) {
                vertex_y = (0 - (s8)(*(part_uv + -5))) - scratch->extent_y;
                scratch->vertices[1].vy = vertex_y;
                scratch->vertices[0].vy = vertex_y;
                vertex_y -= scratch->uv_v_extent;
                scratch->vertices[3].vy = vertex_y;
                scratch->vertices[2].vy = vertex_y;
            } else {
                vertex_y = (s8)(*(part_uv + -5)) - scratch->extent_y;
                scratch->vertices[1].vy = vertex_y;
                scratch->vertices[0].vy = vertex_y;
                vertex_y = vertex_y + scratch->uv_v_extent;
                scratch->vertices[3].vy = vertex_y;
                scratch->vertices[2].vy = vertex_y;
            }

            depth = (RotAverage4(&scratch->vertices[0], &scratch->vertices[1],
                                   &scratch->vertices[2], &scratch->vertices[3],
                                   (s32 *)&packet->x0, (s32 *)&packet->x1,
                                   (s32 *)&packet->x2, (s32 *)&packet->x3,
                                   &scratch->depth_cue, &scratch->gte_flag) - depth_bias) - 6;
            scratch->sort_depth = depth;
            if (depth < 0x1E0U) {
                vertex_0_visible = 0;
                if ((u32)((packet->x0 + 0x20) & 0xFFFF) < 0x181U) {
                    u32 screen_y;
                    screen_y = (u32)((packet->y0 + 0x20) & 0xFFFF);
                    vertex_0_visible = screen_y < 0x121U;
                }
                vertex_1_visible = 0;
                if ((u32)((packet->x1 + 0x20) & 0xFFFF) < 0x181U) {
                    u32 screen_y;
                    screen_y = (u32)((packet->y1 + 0x20) & 0xFFFF);
                    vertex_1_visible = screen_y < 0x121U;
                }
                vertex_2_visible = 0;
                first_pair_visible = vertex_0_visible | vertex_1_visible;
                if ((u32)((packet->x2 + 0x20) & 0xFFFF) < 0x181U) {
                    u32 screen_y;
                    screen_y = (u32)((packet->y2 + 0x20) & 0xFFFF);
                    vertex_2_visible = screen_y < 0x121U;
                }
                vertex_3_visible = 0;
                first_three_visible = first_pair_visible | vertex_2_visible;
                if ((u32)((packet->x3 + 0x20) & 0xFFFF) < 0x181U) {
                    u32 screen_y;
                    screen_y = (u32)((packet->y3 + 0x20) & 0xFFFF);
                    vertex_3_visible = screen_y < 0x121U;
                }
                if ((first_three_visible | vertex_3_visible) != 0) {
                    sprite->flags &= 0x7FFF;
                    u_end = scratch->uv_u_extent + scratch->uv_u_start;
                    scratch->uv_u_extent = u_end;
                    if (u_end & 0x100) {
                        scratch->uv_u_extent = u_end - 1;
                    }
                    v_end = scratch->uv_v_extent + scratch->uv_v_start;
                    scratch->uv_v_extent = v_end;
                    if (v_end & 0x100) {
                        scratch->uv_v_extent = v_end - 1;
                    }
                    scratch->uv_v_start <<= 8;
                    scratch->uv_v_extent <<= 8;
                    if (scratch->sprite_flags & 0x100) {
                        packet->clut = sprite->clut;
                    } else {
                        packet->clut = sprite->clut + (*(u16 *)(part_uv
                            + -2));
                    }
                    /* BYTES: retail writes the packet u/v byte pair with one sh of the combined value; storing u and v separately compiles to two sb */
                    *(s16 *)&packet->u0 = scratch->uv_v_start
                        + scratch->uv_u_start;
                    /* BYTES: retail writes the packet u/v byte pair with one sh of the combined value; storing u and v separately compiles to two sb */
                    *(s16 *)&packet->u1 = scratch->uv_v_start
                        + scratch->uv_u_extent;
                    {
                        s32 tpage_base = sprite->tpage_abr;
                        s32 tpage;
                        if (tpage_base != 0) {
                            tpage = tpage_base + ((*(u16 *)(part_uv + -4)) & 0xFF9F);
                        } else {
                            tpage = (*(u16 *)(part_uv + -4));
                        }
                        packet->tpage = tpage;
                    }
                    /* BYTES: retail writes the packet u/v byte pair with one sh of the combined value; storing u and v separately compiles to two sb */
                    *(s16 *)&packet->u2 = scratch->uv_v_extent
                        + scratch->uv_u_start;
                    /* BYTES: retail writes the packet u/v byte pair with one sh of the combined value; storing u and v separately compiles to two sb */
                    *(s16 *)&packet->u3 = scratch->uv_v_extent
                        + scratch->uv_u_extent;
                    if ((s16)packet->x0 > (s16)packet->x3) {
                        packet->u1--;
                        packet->u3--;
                    }
                    if ((s16)packet->y0 > (s16)packet->y3) {
                        packet->v2--;
                        packet->v3--;
                    }
                    color = sprite->color.word;
                    /* BYTES: retail stores each vertex colour word (red, green, blue and the code or pad byte) with one sw; member stores compile to four sb */
                    *(s32 *)&packet->r3 = 0;
                    /* BYTES: retail stores each vertex colour word (red, green, blue and the code or pad byte) with one sw; member stores compile to four sb */
                    *(s32 *)&packet->r2 = 0;
                    ((GpuLinkTag *)&packet->tag)->len = 0xC;
                    /* BYTES: retail stores each vertex colour word (red, green, blue and the code or pad byte) with one sw; member stores compile to four sb */
                    *(s32 *)&packet->r1 = color;
                    /* BYTES: retail stores each vertex colour word (red, green, blue and the code or pad byte) with one sw; member stores compile to four sb */
                    *(s32 *)&packet->r0 = color;
                    part_command = (*(part_uv + -7));
                    packet->code = part_command;
                    sprite_flags = scratch->sprite_flags;
                    if (sprite_flags & 8) {
                        draw_command = sprite_flags & 4;
                        if (draw_command == 0) {
                            draw_command = part_command & 0xFD;
                        } else {
                            draw_command = part_command | 2;
                        }
                        packet->code = draw_command;
                    }
                    AddPrim(scratch->ordering_table + scratch->sort_depth,
                        packet);
                    packet++;
                                }
            }
        } else {
            callback = (*(Callback *)(part_uv + 0));
            if (callback != 0) {
                callback(context, position, sprite, part);
            }
        }

        if ((s8)((S_800D07C8_4 *)part)->unk_00 >= 0) {
            part += 0xC;
        } else {
            break;
        }
    }
    PopMatrix();
    ((GpuContext *)(table[0]))->packetCursor = packet;
}
