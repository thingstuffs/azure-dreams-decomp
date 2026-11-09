/* Sprite display cancellation flags and per-node transform, draw and update dispatch. */
#include "slus/gp_shared_8099c.h"
#include "engine/object.h"
#include "sdk/libgpu.h"
#include "sdk/libgte.h"
#include "engine/graphics/sprite_scratch.h"
#include "slus/data.h"
#include "shared/object_node.h"

/* Shared display-cancellation state; retail initializes it to zero. */
s32 object_render_cancel_switch = 0;


/* obj_disp23_cancel_sw_set: sets the display cancellation switch and returns it. */
extern u8 *D_80083160[3];

/* Stores the supplied object_render_cancel_switch and returns the stored value. */
s32 obj_disp23_cancel_sw_set(s32 cancel_switch)
{
    object_render_cancel_switch = cancel_switch;
    return cancel_switch;
}



#define U8_AT(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define S8_AT(p, o) (*(s8 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PTR_AT(p, o) (*(u8 **)((u8 *)(p) + (o)))


/*
 * Composes each linked object transform with its parent and the render rotation, then projects
 * flipped sprite rectangles and queues those with a corner in the screen margin. Applies
 * texture-page, CLUT, and draw-flag overrides, invokes each node callback after saving the
 * primitive cursor, and restores the matrix stack.
 */
s32 draw_linked_sprite_nodes(u8 *first_node, u8 *first_transform, SpriteFrameState *first_context) {
    SpriteLinkedScratch *scratch;
    u8 *transform;
    SpriteFrameState *context;
    u8 *object;
    u8 *sprite_data;
    u8 *sprite;
    u8 *primitive;
    u8 *render_state;
    u8 **state_ptr;
    u8 *next_node;
    void *matrix;
    void *translation;
    void *work_matrix;
    u8 *node;
    void (*callback)(void *);
    s32 left_u;
    s32 top_v;
    s32 coord;
    s32 third_visible;
    s32 corner_visible;
    s32 context_flags;
    s32 prim_cursor;
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
    state_ptr = D_80083160;
    scratch = (SpriteLinkedScratch *)0x1F800000;
    if (render_disabled != 0) {
        return 0;
    }

    matrix = (void *)0x1F800054;
    translation = (void *)0x1F800044;
    work_matrix = (void *)0x1F8000C8;

    render_state = D_80083160[0];
    prim_cursor = S32_AT(render_state, 0x8D0);
    scratch->ordering_table = (u32)(render_state + 0x70);
    scratch->input_z = 0x1000;
    scratch->translation_z = 0;
    scratch->vertices[3].z = 0;
    scratch->vertices[2].z = 0;
    scratch->vertices[1].z = 0;
    scratch->vertices[0].z = 0;
    scratch->primitive_cursor = prim_cursor;
    PushMatrix();

    while (1) {
        object = PTR_AT(node, 0x0);
        callback = *(void (**)(void *))(node + 0x8);
        scratch->ordering_depth = S32_AT(object, 0x60);
        context_flags = context->flags;
        sprite_data = context->source;
        scratch->context_flags = context_flags;
        scratch->input_x = S32_AT(object, 0x20);
        scratch->input_y = S32_AT(object, 0x24);
        scratch->input_z = S32_AT(object, 0x28);

        if (PTR_AT(object, 0x4) == 0) {
            scratch->translation_x = S16_AT(transform, 0x2);
            scratch->translation_y = S16_AT(transform, 0x6);
            scratch->translation_z = S16_AT(transform, 0xA);
            TransMatrix(matrix, translation);
            RotMatrix(object + 0x8, matrix);
            ScaleMatrix(matrix, &scratch->input_x);

            S32_AT(object, 0x40) = scratch->matrix.rotation_row0_xy;
            S32_AT(object, 0x44) = scratch->matrix.rotation_row0_z_row1_x;
            S32_AT(object, 0x48) = scratch->matrix.rotation_row1_yz;
            S32_AT(object, 0x4C) = scratch->matrix.rotation_row2_xy;
            S32_AT(object, 0x50) = scratch->matrix.rotation_row2_z_pad;
            S32_AT(object, 0x54) = scratch->matrix.translation_x;
            S32_AT(object, 0x58) = scratch->matrix.translation_y;
            S32_AT(object, 0x5C) = scratch->matrix.translation_z;

            scratch->translation_x = S32_AT(object, 0x10);
            scratch->translation_y = S32_AT(object, 0x14);
            scratch->translation_z = S32_AT(object, 0x18);
            TransMatrix(work_matrix, translation);
            RotMatrix(object_render_rotation_angles, work_matrix);
            CompMatrix(matrix, work_matrix, matrix);
            SetRotMatrix(matrix);
            SetTransMatrix(matrix);
        } else {
            TransMatrix(matrix, object + 0x30);
            RotMatrix(object + 0x8, matrix);
            ScaleMatrix(matrix, &scratch->input_x);
            CompMatrix(PTR_AT(object, 0x4) + 0x40, matrix, matrix);

            S32_AT(object, 0x40) = scratch->matrix.rotation_row0_xy;
            S32_AT(object, 0x44) = scratch->matrix.rotation_row0_z_row1_x;
            S32_AT(object, 0x48) = scratch->matrix.rotation_row1_yz;
            S32_AT(object, 0x4C) = scratch->matrix.rotation_row2_xy;
            S32_AT(object, 0x50) = scratch->matrix.rotation_row2_z_pad;
            S32_AT(object, 0x54) = scratch->matrix.translation_x;
            S32_AT(object, 0x58) = scratch->matrix.translation_y;
            S32_AT(object, 0x5C) = scratch->matrix.translation_z;

            scratch->translation_x = S32_AT(object, 0x10);
            scratch->translation_y = S32_AT(object, 0x14);
            scratch->translation_z = S32_AT(object, 0x18);
            TransMatrix(work_matrix, &scratch->translation_x);
            RotMatrix(object_render_rotation_angles, work_matrix);
            CompMatrix(matrix, work_matrix, matrix);
            SetRotMatrix(matrix);
            SetTransMatrix(matrix);
        }

        if (sprite_data != 0) {
            sprite = sprite_data + 1;
sprite_loop:
            primitive = (u8 *)scratch->primitive_cursor;
            scratch->primitive_cursor = (s32)(primitive + 0x28);

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

            if ((U8_AT(sprite_data, 0) ^ scratch->context_flags) & 1) {
                coord = -((s32)(U8_AT(sprite, 1) << 24) >> 23);
                scratch->vertices[2].x = coord;
                scratch->vertices[0].x = coord;
                coord -= (u16)scratch->uv_u_extent;
            } else {
                coord = (s32)(U8_AT(sprite, 1) << 24) >> 23;
                scratch->vertices[2].x = coord;
                scratch->vertices[0].x = coord;
                coord += (u16)scratch->uv_u_extent;
            }
            scratch->vertices[3].x = coord;
            scratch->vertices[1].x = coord;

            if ((U8_AT(sprite_data, 0) ^ scratch->context_flags) & 2) {
                coord = -((s32)(U8_AT(sprite, 2) << 24) >> 23);
                scratch->vertices[1].y = coord;
                scratch->vertices[0].y = coord;
                coord -= (u16)scratch->uv_v_extent;
                scratch->vertices[3].y = coord;
                scratch->vertices[2].y = coord;
            } else {
                coord = (s32)(U8_AT(sprite, 2) << 24) >> 23;
                scratch->vertices[1].y = coord;
                scratch->vertices[0].y = coord;
                coord += (u16)scratch->uv_v_extent;
                scratch->vertices[3].y = coord;
                scratch->vertices[2].y = coord;
            }

            RotTransPers4(&scratch->vertices[0], &scratch->vertices[1],
                          &scratch->vertices[2], &scratch->vertices[3],
                          &scratch->projected_vertices[0], &scratch->projected_vertices[1],
                          &scratch->projected_vertices[2], &scratch->projected_vertices[3],
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
                U16_AT(primitive, 0x16) = tpage_value;
                visible = S16_AT(primitive, 0x8);
                U16_AT(primitive, 0x1C) = (u16)scratch->uv_v_extent + (u16)scratch->uv_u_start;
                sum_u = (u16)scratch->uv_v_extent;
                clut_base = (u16)scratch->uv_u_extent;
                coord = S16_AT(primitive, 0x20);
                sum_u += clut_base;
                U16_AT(primitive, 0x24) = sum_u;

                if (coord < visible) {
                    U8_AT(primitive, 0x14) -= 1;
                    U8_AT(primitive, 0x24) -= 1;
                }
                if (S16_AT(primitive, 0xA) > S16_AT(primitive, 0x22)) {
                    U8_AT(primitive, 0x1D) -= 1;
                    U8_AT(primitive, 0x25) -= 1;
                }
                if (scratch->input_x >= 0x1800) {
                    U8_AT(primitive, 0x14) -= 1;
                    U8_AT(primitive, 0x24) -= 1;
                }
                if (scratch->input_y >= 0x1800) {
                    U8_AT(primitive, 0x1D) -= 1;
                    U8_AT(primitive, 0x25) -= 1;
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
                AddPrim((u8 *)scratch->ordering_table + (scratch->ordering_depth * 4), primitive);
            } else {
                context->flags |= 0x8000;
            }

            if (S8_AT(sprite_data, 0) >= 0) {
                sprite_data += 0xC;
                sprite += 0xC;
                if (sprite_data != 0) {
                    goto sprite_loop;
                }
            }
        }

        S32_AT(state_ptr[0], 0x8D0) = scratch->primitive_cursor;
        if (callback != 0) {
            callback(node);
        }
        scratch->primitive_cursor = S32_AT(state_ptr[0], 0x8D0);

        next_node = PTR_AT(node, -8);
        node = next_node + 0x20;
        if (next_node == 0) {
            break;
        }
        transform = PTR_AT(next_node, 0x8);
        context = NODE_HEADER(next_node + 0x20)->sprite;
    }

    PopMatrix();
    S32_AT(state_ptr[0], 0x8D0) = scratch->primitive_cursor;
    return 0;
}
