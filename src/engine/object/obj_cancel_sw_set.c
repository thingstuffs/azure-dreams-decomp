/* Sprite display cancellation flags and per-node transform, draw and update dispatch. */
#include "slus/gp_shared_8099c.h"
#include "engine/object.h"
#include "sdk/libgpu.h"
#include "sdk/libgpu_packets.h"
#include "sdk/libgte.h"
#include "engine/graphics/sprite_scratch.h"
#include "slus/data.h"
#include "shared/object_node.h"
#include "shared/game_work.h"
#include "shared/gpu_packets.h"
#include "engine/window/cursor_body.h"
#include "shared/sprite_part_command.h"

/* Shared display-cancellation state; retail initializes it to zero. */
s32 object_render_cancel_switch = 0;


/* obj_disp23_cancel_sw_set: sets the display cancellation switch and returns it. */

/* Stores the supplied object_render_cancel_switch and returns the stored value. */
s32 obj_disp23_cancel_sw_set(s32 cancel_switch)
{
    object_render_cancel_switch = cancel_switch;
    return cancel_switch;
}



#define U8_AT(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PTR_AT(p, o) (*(u8 **)((u8 *)(p) + (o)))


/*
 * Composes each linked object transform with its parent and the render rotation, then projects
 * flipped sprite rectangles and queues those with a corner in the screen margin. Applies
 * texture-page, CLUT, and draw-flag overrides, invokes each node callback after saving the
 * primitive cursor, and restores the matrix stack.
 */
s32 draw_linked_sprite_nodes(WindowRenderPrefix *first_node, ObjectPosition *first_transform, SpriteFrameState *first_context) {
    SpriteLinkedScratch *scratch;
    ObjectPosition *transform;
    SpriteFrameState *context;
    Rec_D_80081FDC *object;
    SpritePartCommand *part;
    u8 *sprite;
    POLY_FT4 *primitive;
    GpuContext *render_state;
    GameWork *work;
    ObjectNodeHeader *next_node;
    void *matrix;
    void *translation;
    void *work_matrix;
    WindowRenderPrefix *node;
    void (*callback)(void *);
    s32 left_u;
    s32 top_v;
    s32 coord;
    s32 third_visible;
    s32 corner_visible;
    s32 context_flags;
    u8 *prim_cursor;
    s32 sum_u;
    s32 sum_v;
    s32 bottom_v_bits;
    s32 uv_word;
    s32 visible;
    s32 clut_base;
    s32 visible_corners;
    u16 clut_value;
    s32 tpage_base;
    u16 tpage_value;
    u16 draw_flags;
    s32 render_disabled;

    node = first_node;
    transform = first_transform;
    context = first_context;

    render_disabled = object_render_cancel_switch;
    work = &g_game_work;
    scratch = LINKED_SPRITE_SCRATCH;
    if (render_disabled != 0) {
        return 0;
    }

    matrix = &scratch->matrix.rotation_row0_xy;
    translation = &scratch->translation.vx;
    work_matrix = &scratch->work_matrix.m[0][0];

    render_state = g_game_work.draw_buffer;
    prim_cursor = render_state->packetCursor;
    scratch->ordering_table = render_state->orderTag;
    scratch->input.vz = 0x1000;
    scratch->translation.vz = 0;
    scratch->vertices[3].vz = 0;
    scratch->vertices[2].vz = 0;
    scratch->vertices[1].vz = 0;
    scratch->vertices[0].vz = 0;
    scratch->packet_cursor = prim_cursor;
    PushMatrix();

    while (1) {
        object = node->model;
        callback = node->draw_callback;
        scratch->ordering_depth = object->unk_60;
        context_flags = context->flags;
        part = context->source;
        scratch->context_flags = context_flags;
        scratch->input.vx = object->unk_20;
        scratch->input.vy = object->unk_24;
        scratch->input.vz = object->unk_28;

        if (PTR_AT(object, 0x4) == 0) {
            scratch->translation.vx = transform->x.w.i;
            scratch->translation.vy = transform->y.w.i;
            scratch->translation.vz = transform->z.w.i;
            TransMatrix(matrix, translation);
            RotMatrix(&object->unk_08, matrix);
            ScaleMatrix(matrix, &scratch->input);

            object->unk_40 = scratch->matrix.rotation_row0_xy;
            object->unk_44 = scratch->matrix.rotation_row0_z_row1_x;
            object->unk_48 = scratch->matrix.rotation_row1_yz;
            object->unk_4C = scratch->matrix.rotation_row2_xy;
            object->unk_50 = scratch->matrix.rotation_row2_z_pad;
            object->unk_54 = scratch->matrix.translation_x;
            object->unk_58 = scratch->matrix.translation_y;
            object->unk_5C = scratch->matrix.translation_z;

            scratch->translation.vx = object->unk_10;
            scratch->translation.vy = object->unk_14;
            scratch->translation.vz = object->unk_18;
            TransMatrix(work_matrix, translation);
            RotMatrix(object_render_rotation_angles, work_matrix);
            CompMatrix(matrix, work_matrix, matrix);
            SetRotMatrix(matrix);
            SetTransMatrix(matrix);
        } else {
            TransMatrix(matrix, &object->unk_30);
            RotMatrix(&object->unk_08, matrix);
            ScaleMatrix(matrix, &scratch->input);
            CompMatrix(PTR_AT(object, 0x4) + 0x40, matrix, matrix);

            object->unk_40 = scratch->matrix.rotation_row0_xy;
            object->unk_44 = scratch->matrix.rotation_row0_z_row1_x;
            object->unk_48 = scratch->matrix.rotation_row1_yz;
            object->unk_4C = scratch->matrix.rotation_row2_xy;
            object->unk_50 = scratch->matrix.rotation_row2_z_pad;
            object->unk_54 = scratch->matrix.translation_x;
            object->unk_58 = scratch->matrix.translation_y;
            object->unk_5C = scratch->matrix.translation_z;

            scratch->translation.vx = object->unk_10;
            scratch->translation.vy = object->unk_14;
            scratch->translation.vz = object->unk_18;
            TransMatrix(work_matrix, &scratch->translation);
            RotMatrix(object_render_rotation_angles, work_matrix);
            CompMatrix(matrix, work_matrix, matrix);
            SetRotMatrix(matrix);
            SetTransMatrix(matrix);
        }

        if (part != 0) {
            sprite = &part->code;
sprite_loop:
            primitive = scratch->packet_cursor;
            scratch->packet_cursor = primitive + 1;

            coord = *(volatile u8 *)(sprite + 0x7);
            left_u = U8_AT(sprite, 0x7);
            top_v = U8_AT(sprite, 0x8);
            scratch->uv_u_start = (u8)coord;
            coord = U8_AT(sprite, 0x8);
            scratch->uv_v_start = coord;
            scratch->uv_u_extent = U8_AT(sprite, 0x9);
            scratch->uv_v_extent = U8_AT(sprite, 0xA);
            if ((left_u + U8_AT(sprite, 0x9)) >= 0x100) {
                scratch->uv_u_extent -= 1;
            }
            if ((top_v + U8_AT(sprite, 0xA)) >= 0x100) {
                scratch->uv_v_extent -= 1;
            }

            if ((part->flags ^ scratch->context_flags) & 1) {
                coord = -((s32)(U8_AT(sprite, 1) << 24) >> 23);
                scratch->vertices[2].vx = coord;
                scratch->vertices[0].vx = coord;
                coord -= (u16)scratch->uv_u_extent;
            } else {
                coord = (s32)(U8_AT(sprite, 1) << 24) >> 23;
                scratch->vertices[2].vx = coord;
                scratch->vertices[0].vx = coord;
                coord += (u16)scratch->uv_u_extent;
            }
            scratch->vertices[3].vx = coord;
            scratch->vertices[1].vx = coord;

            if ((part->flags ^ scratch->context_flags) & 2) {
                coord = -((s32)(U8_AT(sprite, 2) << 24) >> 23);
                scratch->vertices[1].vy = coord;
                scratch->vertices[0].vy = coord;
                coord -= (u16)scratch->uv_v_extent;
                scratch->vertices[3].vy = coord;
                scratch->vertices[2].vy = coord;
            } else {
                coord = (s32)(U8_AT(sprite, 2) << 24) >> 23;
                scratch->vertices[1].vy = coord;
                scratch->vertices[0].vy = coord;
                coord += (u16)scratch->uv_v_extent;
                scratch->vertices[3].vy = coord;
                scratch->vertices[2].vy = coord;
            }

            RotTransPers4(&scratch->vertices[0], &scratch->vertices[1],
                          &scratch->vertices[2], &scratch->vertices[3],
                          (s32 *)&scratch->projected_vertices[0], (s32 *)&scratch->projected_vertices[1],
                          (s32 *)&scratch->projected_vertices[2], (s32 *)&scratch->projected_vertices[3],
                          &scratch->depth_cue, &scratch->gte_flag);

            visible = 0;
            if ((u16)(scratch->projected_vertices[0].x + 0x20) < 0x181U) {
                visible = (u16)(scratch->projected_vertices[0].y + 0x20) < 0x121U;
            }
            corner_visible = 0;
            if ((u16)(scratch->projected_vertices[1].x + 0x20) < 0x181U) {
                corner_visible = (u16)(scratch->projected_vertices[1].y + 0x20) < 0x121U;
            }
            third_visible = 0;
            visible |= corner_visible;
            if ((u16)(scratch->projected_vertices[2].x + 0x20) < 0x181U) {
                third_visible = (u16)(scratch->projected_vertices[2].y + 0x20) < 0x121U;
            }
            corner_visible = 0;
            visible_corners = visible | third_visible;
            if ((u16)(scratch->projected_vertices[3].x + 0x20) < 0x181U) {
                corner_visible = (u16)(scratch->projected_vertices[3].y + 0x20) < 0x121U;
            }

            if ((visible_corners | corner_visible) != 0) {
                s32 projected_xy0;
                s32 projected_xy1;
                s32 projected_xy2;
                s32 projected_xy3;
                /* BYTES: the GTE writes this named projected XY pair as one packet word. */
                projected_xy0 = *(s32 *)&scratch->projected_vertices[0];
                S32_AT(primitive, 0x8) = projected_xy0;
                /* BYTES: the GTE writes this named projected XY pair as one packet word. */
                projected_xy1 = *(s32 *)&scratch->projected_vertices[1];
                S32_AT(primitive, 0x10) = projected_xy1;
                /* BYTES: the GTE writes this named projected XY pair as one packet word. */
                projected_xy2 = *(s32 *)&scratch->projected_vertices[2];
                S32_AT(primitive, 0x18) = projected_xy2;
                /* BYTES: the GTE writes this named projected XY pair as one packet word. */
                projected_xy3 = *(s32 *)&scratch->projected_vertices[3];
                S32_AT(primitive, 0x20) = projected_xy3;
                U8_AT(primitive, 0x3) = 9;
                context->flags &= 0x7FFF;

                sum_u = scratch->uv_u_extent + scratch->uv_u_start;
                scratch->uv_u_extent = sum_u;
                if (sum_u & 0x100) {
                    scratch->uv_u_extent = sum_u - 1;
                }
                sum_v = scratch->uv_v_extent + scratch->uv_v_start;
                scratch->uv_v_extent = sum_v;
                if (sum_v & 0x100) {
                    scratch->uv_v_extent = sum_v - 1;
                }

                bottom_v_bits = scratch->uv_v_extent;
                uv_word = scratch->uv_v_start;
                bottom_v_bits <<= 8;
                scratch->uv_v_extent = bottom_v_bits;
                uv_word <<= 8;
                scratch->uv_v_start = uv_word;
                clut_base = context->clut;
                uv_word += scratch->uv_u_start;
                clut_value = clut_base;
                if (clut_base == 0) {
                    clut_value = U16_AT(sprite, 0x5);
                }
                uv_word += (s32)clut_value << 16;
                S32_AT(primitive, 0xC) = uv_word;

                U16_AT(primitive, 0x14) = (u16)scratch->uv_v_start + (u16)scratch->uv_u_extent;
                tpage_base = context->tpage_abr;
                if (tpage_base != 0) {
                    tpage_value = tpage_base + (U16_AT(sprite, 0x3) & 0xFF9F);
                } else {
                    tpage_value = U16_AT(sprite, 0x3);
                }
                primitive->tpage = tpage_value;
                visible = primitive->x0;
                U16_AT(primitive, 0x1C) = (u16)scratch->uv_v_extent + (u16)scratch->uv_u_start;
                sum_u = (u16)scratch->uv_v_extent;
                clut_base = (u16)scratch->uv_u_extent;
                coord = primitive->x3;
                sum_u += clut_base;
                U16_AT(primitive, 0x24) = sum_u;

                if (coord < visible) {
                    primitive->u1 -= 1;
                    primitive->u3 -= 1;
                }
                if (primitive->y0 > primitive->y3) {
                    primitive->v2 -= 1;
                    primitive->v3 -= 1;
                }
                if (scratch->input.vx >= 0x1800) {
                    primitive->u1 -= 1;
                    primitive->u3 -= 1;
                }
                if (scratch->input.vy >= 0x1800) {
                    primitive->v2 -= 1;
                    primitive->v3 -= 1;
                }

                clut_base = U8_AT(sprite, 0x0);
                context->color.c.code = clut_base;
                draw_flags = scratch->context_flags;
                if (draw_flags & 8) {
                    if (draw_flags & 4) {
                        context->color.c.code = clut_base | 2;
                    } else {
                        context->color.c.code = (u8)clut_base & 0xFD;
                    }
                }
                if (scratch->context_flags & 0x10) {
                    context->color.c.code &= 0xFE;
                } else {
                    context->color.c.code |= 1;
                }

                S32_AT(primitive, 0x4) = context->color.word;
                AddPrim(&scratch->ordering_table[scratch->ordering_depth], primitive);
            } else {
                context->flags |= 0x8000;
            }

            if ((s8)part->flags >= 0) {
                part++;
                sprite += 0xC;
                if (part != 0) {
                    goto sprite_loop;
                }
            }
        }

        work->draw_buffer->packetCursor = scratch->packet_cursor;
        if (callback != 0) {
            callback(node);
        }
        scratch->packet_cursor = work->draw_buffer->packetCursor;

        next_node = NODE_HEADER(node)->chain_next;
        node = NODE_BODY(next_node);
        if (next_node == 0) {
            break;
        }
        transform = next_node->position;
        context = next_node->sprite;
    }

    PopMatrix();
    work->draw_buffer->packetCursor = scratch->packet_cursor;
    return 0;
}
