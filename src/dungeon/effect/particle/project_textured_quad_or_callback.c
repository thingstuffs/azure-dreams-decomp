#include "common.h"
#include "sdk/libc.h"
#include "shared/audio_commands.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "sdk/libgpu.h"
#include "dungeon/actor/status.h"
/* Effect quad projection, child particle updates, and a moving status-effect sequence. */

struct ObjectPosition;
#include "dungeon/effect/particle/project_textured_quad_or_callback.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "engine/graphics.h"
#include "sdk/libgte.h"
#include "dungeon/item/message.h"
#include "dungeon/item.h"
#include "dungeon/actor.h"
#include "dungeon/effect/particle.h"
#include "dungeon/system.h"
void (*const dungeon_1894800_entry)(TargetParticleStatusSpellBody *, ObjectPosition *, SpriteFrameState *) = update_animated_effect_sprite;


#include "modules/dungeon_native_abi.h"

extern u8 water_protect_text[38];

#include "dungeon/effect/screen.h"

/* Applies a directional effect and reports the result for flagged entities. */
void apply_water_protect_status(void *entity, s32 direction, void *unused)
{
    void *message_start;
    void *message_end;

    if (try_trigger_target_record_effect(entity, 2, unused) == 0) {
        /*
         * BUG: set_or_clear_actor_status_slot returns a slot index (0..3), or -1 on
         * failure. Testing it as nonzero misreports slot 0 as failure and -1 as success.
         * Slot-0 success instead prints the no-effect message; rejected insertion prints success.
         * try_apply_confusion_status uses the nonnegative success test.
         */
        if (set_or_clear_actor_status_slot(
                entity, STATUS_WATER_PROTECT,
                ((get_random_scaled_value(direction & 0xFF) + 4) << 24) >> 24) << 16) {
            if (*(s32 *)((u8 *)entity + 0x14) & ACTOR_PARTY_MEMBER) {
                adjust_source_value_and_finalize(entity, water_protect_text);
                return;
            }
        } else if (*(s32 *)((u8 *)entity + 0x14) & ACTOR_PARTY_MEMBER) {
            message_end = get_unused_text_buffer();
            message_start = message_end;
            message_end = expand_text_control_codes(no_effect_target_prefix, message_end);
            message_end = append_entity_display_text(entity, message_end);
            message_end = expand_text_control_codes(no_effect_target_period, message_end);
            clear_byte_and_advance(message_end);
            display_text_with_fullwidth_adjustment(message_start);
        }
    }
}
#include "shared/gpu_packets.h"
#include "shared/game_work.h"

#include "sdk/libgte_matrix.h"
#include "sdk/libgpu_packets.h"
#include "dungeon/effect/shaded_quad_scratch.h"

typedef void (*Callback)(void *, void *, void *, void *);

   /* global_value in project_textured_quad_or_callback */

typedef struct S_81874988_4 {
    u8 pad_00[0x50];
    u16 unk_50;
    u16 unk_52;
    u16 unk_54;
    u16 unk_56;
    u16 unk_58;
    u16 unk_5A;
    u16 unk_5C;
    u16 unk_5E;
    u16 unk_60;
    u16 unk_62;
    u16 unk_64;
    u16 unk_66;
} S_81874988_4;   /* arg0 in project_textured_quad_or_callback */

/* Projects a textured quad and queues it for drawing, or invokes its texture callback. */
void project_textured_quad_or_callback(void *quad_arg, ObjectPosition *position, SpriteFrameState *material, s16 depth_bias)
{
    S_81874988_4 *quad = quad_arg;
    GpuContext *render_state = g_game_work.draw_buffer;
    ShadedQuadScratch *scratch = SHADED_QUAD_SCRATCH;
    POLY_FT4 *packet;
    u32 tex_attr;
    u8 *texture;
    Callback callback;
    s32 depth_index;
    u16 draw_flags;
    s32 tex_adjust;
    u8 tex_flags;
    MATRIX view_matrix;

    scratch->ordering_table = &render_state->orderTag[GPU_ORDER_DEPTH_BASE];
    scratch->local_matrix.t[0] = position->x.w.i;
    scratch->local_matrix.t[1] = position->y.w.i;
    scratch->local_matrix.t[2] = position->z.w.i;

    packet = render_state->packetCursor;
    render_state->packetCursor = packet + 1;

    material->flags |= 0x8000;
    PushMatrix();

    scratch->scale.vz = 0x2000;
    scratch->scale.vy = 0x2000;
    scratch->scale.vx = 0x2000;
    scratch->angles.vx = material->angle_x;
    scratch->angles.vz = material->angle_z;
    scratch->angles.vy = material->angle_y;
    RotMatrix(&scratch->angles, &scratch->local_matrix);
    ReadRotMatrix(&view_matrix);
    CompMatrix(&view_matrix, &scratch->local_matrix, &scratch->composed_matrix);
    ScaleMatrix(&scratch->composed_matrix, &scratch->scale);
    SetTransMatrix(&scratch->composed_matrix);
    SetRotMatrix(&scratch->composed_matrix);

    texture = material->source;
    scratch->render_flags = material->flags;

    if (!(texture[0] & 0x20)) {
        scratch->uv_u_start = texture[8];
        scratch->uv_v_start = texture[9];
        scratch->uv_u_extent = texture[0xA];
        scratch->uv_v_extent = texture[0xB];

        scratch->vertices[0].vx = quad->unk_50;
        scratch->vertices[1].vx = quad->unk_52;
        scratch->vertices[2].vx = quad->unk_54;
        scratch->vertices[3].vx = quad->unk_56;
        scratch->vertices[0].vy = quad->unk_58;
        scratch->vertices[1].vy = quad->unk_5A;
        scratch->vertices[2].vy = quad->unk_5C;
        scratch->vertices[3].vy = quad->unk_5E;
        scratch->vertices[0].vz = quad->unk_60;
        scratch->vertices[1].vz = quad->unk_62;
        scratch->vertices[2].vz = quad->unk_64;
        scratch->vertices[3].vz = quad->unk_66;

        depth_index = RotAverage4(&scratch->vertices[0], &scratch->vertices[1],
                              &scratch->vertices[2], &scratch->vertices[3],
                              (s32 *)&packet->x0, (s32 *)&packet->x1,
                              (s32 *)&packet->x2, (s32 *)&packet->x3,
                              &scratch->depth_cue, &scratch->gte_flag) - depth_bias - 6;
        scratch->ot_index = depth_index;

        if ((u32)depth_index < 0x1E0) {
            if (
                (((u16)((u16)packet->x0 + 0x20) < 0x181) &&
                 ((u16)((u16)packet->y0 + 0x20) < 0x121)) |
                (((u16)(packet->x1 + 0x20) < 0x181) &&
                 ((u16)(packet->y1 + 0x20) < 0x121)) |
                (((u16)(packet->x2 + 0x20) < 0x181) &&
                 ((u16)(packet->y2 + 0x20) < 0x121)) |
                (((u16)((u16)packet->x3 + 0x20) < 0x181) &&
                 ((u16)((u16)packet->y3 + 0x20) < 0x121))
                ) {
                ((GpuLinkTag *)&packet->tag)->len = 9;
                packet->code = 0x2C;
                material->flags &= 0x7FFF;

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

                tex_adjust = material->clut;
                if (tex_adjust) {
                    if (scratch->render_flags & 0x100) {
                        packet->clut = tex_adjust;
                    } else {
                        tex_attr = tex_adjust + (*(u16 *)(texture + 6));
                        packet->clut = tex_attr;
                    }
                } else {
                    packet->clut = (*(u16 *)(texture + 6));
                }

                /* BYTES: The packed UV pair is stored together. Separate members generate two byte stores. */
                *(u16 *)&packet->u0 = scratch->uv_v_start +
                                          scratch->uv_u_start;
                /* BYTES: The packed UV pair is stored together. Separate members generate two byte stores. */
                *(u16 *)&packet->u1 = scratch->uv_v_start +
                                           scratch->uv_u_extent;

                tex_adjust = material->tpage_abr;
                if (tex_adjust) {
                    packet->tpage = tex_adjust +
                                   ((*(u16 *)(texture + 4)) & 0xFF9F);
                } else {
                    packet->tpage = (*(u16 *)(texture + 4));
                }

                /* BYTES: The packed UV pair is stored together. Separate members generate two byte stores. */
                *(u16 *)&packet->u2 = scratch->uv_v_extent +
                                           scratch->uv_u_start;
                /* BYTES: The packed UV pair is stored together. Separate members generate two byte stores. */
                *(u16 *)&packet->u3 = scratch->uv_v_extent +
                                           scratch->uv_u_extent;

                if (packet->x0 > packet->x3) {
                    packet->u1--;
                    packet->u3--;
                }
                if (packet->y0 > packet->y3) {
                    packet->v2--;
                    packet->v3--;
                }

                tex_flags = texture[1];
                material->color.c.code = tex_flags;
                draw_flags = scratch->render_flags;
                if (draw_flags & 8) {
                    material->color.c.code = (draw_flags & 4) ?
                        (tex_flags | 2) : (tex_flags & 0xFD);
                }

                /* BYTES: The sprite color and command are written together. Separate members generate four byte stores. */
                *(u32 *)&packet->r0 = material->color.word;
                packet->tag = (packet->tag & 0xFF000000) |
                    (scratch->ordering_table[scratch->ot_index] & 0x00FFFFFF);
                scratch->ordering_table[scratch->ot_index] =
                    (scratch->ordering_table[scratch->ot_index] & 0xFF000000) |
                    ((u32)packet & 0x00FFFFFF);
            }
        }
    } else {
        callback = (*(Callback *)(texture + 8));
        if (callback != 0) {
            callback(quad, position, material, texture);
        }
    }
    PopMatrix();
}
#include "shared/object_node.h"

/* Retail 81874F04 (project_linked_quad_record).
 * Draw the record and then every record chained through the previous header's unk_18 link (node + 0x20 is the
 * next record); each node supplies the context and data pointers for its record. */
s32 project_linked_quad_record(void *record, ObjectPosition *context, SpriteFrameState *data) {
    ObjectNodeHeader *node;

    for (;;) {
        project_textured_quad_or_callback(record, context, data, 0);
        node = NODE_HEADER(record)->chain_next;
        if (node == 0) {
            return 0;
        }
        record = node + 1;
        context = node->position;
        data = node->sprite;
    }
}
/* Draws a textured spherical mesh and adds its visible quads to the ordering table. */
void draw_textured_sphere_mesh(TexturedSparkSphereBody *mesh, ObjectPosition *position, SpriteFrameState *material, u16 depth_bias) {
    MATRIX view_matrix;
    u16 saved_depth_bias;
    u8 *texture;
    s32 column;
    s32 row;
    ShadedQuadScratch *scratch = SHADED_QUAD_SCRATCH;
    GpuContext *page;
    GpuContext *initial_page;
    u32 page_dependency;
    GpuContext **page_ptr;
    POLY_FT4 *quad;
    s32 column_count;
    s32 row_count;
    s32 latitude_span;
    s32 latitude_offset;
    s32 next_latitude_offset;
    s32 longitude_offset;
    s32 ring_radius;
    s32 next_ring_radius;
    s32 longitude;
    s32 next_longitude;
    s32 latitude;
    s32 next_latitude;
    s32 depth_index;
    s32 clut;
    s32 tpage;
    s32 uv_end;
    s32 clut_override;
    s32 tpage_override;
    s32 material_flags;
    s32 screen_y;
    s32 corner_0_visible;
    s32 corner_1_visible;
    s32 corner_2_visible;
    s32 corner_3_visible;
    s32 any_corner_visible;
    s32 last_vertex_z;
    u8 texture_flags;
    u8 draw_flags;

    page_ptr = &g_game_work.draw_buffer;
    initial_page = *page_ptr;
    scratch->ordering_table = &initial_page->orderTag[GPU_ORDER_DEPTH_BASE];
    scratch->local_matrix.t[0] = position->x.w.i;
    scratch->local_matrix.t[1] = position->y.w.i;
    scratch->local_matrix.t[2] = position->z.w.i;
    material->flags = material->flags | 0x8000;
    saved_depth_bias = depth_bias;
    PushMatrix();
    scratch->scale.vz = 0x2000;
    scratch->scale.vy = 0x2000;
    scratch->scale.vx = 0x2000;
    scratch->angles.vx = material->angle_x;
    scratch->angles.vz = material->angle_z;
    scratch->angles.vy = material->angle_y;
    RotMatrix(&scratch->angles, &scratch->local_matrix);
    ReadRotMatrix(&view_matrix);
    CompMatrix(&view_matrix, &scratch->local_matrix, &scratch->composed_matrix);
    ScaleMatrix(&scratch->composed_matrix, &scratch->scale);
    SetTransMatrix(&scratch->composed_matrix);
    SetRotMatrix(&scratch->composed_matrix);
    texture = material->source;
    scratch->render_flags = material->flags;
    for (;;) {
        for (row = 0; row < mesh->rows; row++) {
            for (column = 0; column < mesh->columns; column++) {
                scratch->uv_u_start = *(texture + 8);
                scratch->uv_v_start = *(texture + 9);
                scratch->uv_u_extent = *(texture + 10);
                page = *page_ptr;
                scratch->uv_v_extent = *(texture + 11);
                quad = page->packetCursor;
                page->packetCursor = quad + 1;
                column_count = mesh->columns;
                longitude = (column << 0xC) / column_count;
                latitude_span = -mesh->latitude_span;
                row_count = mesh->rows;
                latitude_offset = (latitude_span * row) / row_count;
                next_latitude_offset = (latitude_span * (row + 1)) / row_count;
                longitude_offset = mesh->longitude_offset;
                next_longitude = ((column + 1) << 0xC) / column_count;
                longitude = longitude + longitude_offset;
                latitude = latitude_offset + 0x400;
                next_latitude = next_latitude_offset + 0x400;
                if (longitude >= 0x1001) {
                    longitude -= 0x1000;
                }
                if (longitude < 0) {
                    longitude += 0x1000;
                }
                next_longitude = next_longitude + longitude_offset;
                if (next_longitude >= 0x1001) {
                    next_longitude -= 0x1000;
                }
                if (next_longitude < 0) {
                    next_longitude += 0x1000;
                }
                ring_radius = ((mesh->radius.v >> 8) * rcos(latitude)) >> 0x14;
                next_ring_radius = ((mesh->radius.v >> 8) * rcos(next_latitude)) >> 0x14;
                scratch->vertices[0].vx = (ring_radius * rsin(longitude)) >> 0xC;
                scratch->vertices[0].vy = (ring_radius * rcos(longitude)) >> 0xC;
                scratch->vertices[0].vz = -(((mesh->radius.v >> 8) * rsin(latitude)) >> 0x14);
                scratch->vertices[1].vx = (ring_radius * rsin(next_longitude)) >> 0xC;
                scratch->vertices[1].vy = (ring_radius * rcos(next_longitude)) >> 0xC;
                scratch->vertices[1].vz = -(((mesh->radius.v >> 8) * rsin(latitude)) >> 0x14);
                scratch->vertices[2].vx = (next_ring_radius * rsin(longitude)) >> 0xC;
                scratch->vertices[2].vy = (next_ring_radius * rcos(longitude)) >> 0xC;
                scratch->vertices[2].vz = -(((mesh->radius.v >> 8) * rsin(next_latitude))
                    >> 0x14);
                scratch->vertices[3].vx = (next_ring_radius * rsin(next_longitude)) >> 0xC;
                scratch->vertices[3].vy = (next_ring_radius * rcos(next_longitude)) >> 0xC;
                last_vertex_z = -(((mesh->radius.v >> 8) * rsin(next_latitude)) >> 0x14);
                depth_index = (RotAverage4(&scratch->vertices[0], &scratch->vertices[1], &scratch->vertices[2],
                    &scratch->vertices[3], (s32 *)&quad->x0, (s32 *)&quad->x1, (s32 *)&quad->x2, (s32 *)&quad->x3,
                    &scratch->depth_cue, (scratch->vertices[3].vz = last_vertex_z, &scratch->gte_flag)) - (s16)saved_depth_bias) - 6;
                scratch->ot_index = depth_index;
                if ((u32)depth_index < 0x1E0U) {
                    corner_0_visible = 0;
                    if ((u32)(((u16)quad->x0 + 0x20) & 0xFFFF) < 0x181U) {
                        screen_y = (u16)quad->y0 + 0x20;
                        screen_y = screen_y & 0xFFFF;
                        corner_0_visible = (u32)screen_y < 0x121U;
                    }
                    corner_1_visible = 0;
                    if ((u32)(((u16)quad->x1 + 0x20) & 0xFFFF) < 0x181U) {
                        screen_y = (u16)quad->y1 + 0x20;
                        screen_y = screen_y & 0xFFFF;
                        corner_1_visible = (u32)screen_y < 0x121U;
                    }
                    corner_2_visible = 0;
                    corner_0_visible = corner_0_visible | corner_1_visible;
                    if ((u32)(((u16)quad->x2 + 0x20) & 0xFFFF) < 0x181U) {
                        screen_y = (u16)quad->y2 + 0x20;
                        screen_y = screen_y & 0xFFFF;
                        corner_2_visible = (u32)screen_y < 0x121U;
                    }
                    corner_3_visible = 0;
                    any_corner_visible = corner_0_visible | corner_2_visible;
                    if ((u32)(((u16)quad->x3 + 0x20) & 0xFFFF) < 0x181U) {
                        screen_y = (u16)quad->y3 + 0x20;
                        screen_y = screen_y & 0xFFFF;
                        corner_3_visible = (u32)screen_y < 0x121U;
                    }
                    if ((any_corner_visible | corner_3_visible) != 0) {
                        material->flags = material->flags & 0x7FFF;
                        SetPolyFT4(quad);
                        uv_end = scratch->uv_u_extent + scratch->uv_u_start;
                        scratch->uv_u_extent = uv_end;
                        if (uv_end & 0x100) {
                            scratch->uv_u_extent = uv_end - 1;
                        }
                        uv_end = scratch->uv_v_extent + scratch->uv_v_start;
                        scratch->uv_v_extent = uv_end;
                        if (uv_end & 0x100) {
                            scratch->uv_v_extent = uv_end - 1;
                        }
                        scratch->uv_v_start = scratch->uv_v_start << 8;
                        scratch->uv_v_extent = scratch->uv_v_extent << 8;
                        clut_override = material->clut;
                        if (clut_override != 0) {
                            if (scratch->render_flags & 0x100) {
                                quad->clut = clut_override;
                            } else {
                                clut = clut_override + *(u16 *)(texture + 6);
                                quad->clut = clut;
                            }
                        } else {
                            clut = *(u16 *)(texture + 6);
                            quad->clut = clut;
                        }
                        /* BYTES: The packed UV pair is stored together. Separate members generate two byte stores. */
                        *(u16 *)&quad->u0 = scratch->uv_v_start + scratch->uv_u_start;
                        /* BYTES: The packed UV pair is stored together. Separate members generate two byte stores. */
                        *(u16 *)&quad->u1 = scratch->uv_v_start + scratch->uv_u_extent;
                        tpage_override = material->tpage_abr;
                        if (tpage_override != 0) {
                            tpage = tpage_override + (*(u16 *)(texture + 4) & 0xFF9F);
                        } else {
                            tpage = *(u16 *)(texture + 4);
                        }
                        quad->tpage = tpage;
                        /* BYTES: The packed UV pair is stored together. Separate members generate two byte stores. */
                        *(u16 *)&quad->u2 = scratch->uv_v_extent + scratch->uv_u_start;
                        /* BYTES: The packed UV pair is stored together. Separate members generate two byte stores. */
                        *(u16 *)&quad->u3 = scratch->uv_v_extent + scratch->uv_u_extent;
                        if (quad->x0 > quad->x3) {
                            quad->u1--;
                            quad->u3--;
                        }
                        if (quad->y0 > quad->y3) {
                            quad->v2--;
                            quad->v3--;
                        }
                        texture_flags = *(texture + 1);
                        material->color.c.code = texture_flags;
                        material_flags = scratch->render_flags;
                        if (material_flags & 8) {
                            if (material_flags & 4) {
                                draw_flags = texture_flags | 2;
                                material->color.c.code = draw_flags;
                            } else {
                                draw_flags = texture_flags & 0xFD;
                                material->color.c.code = draw_flags;
                            }
                        }
                        {
                            u32 address_mask = 0x00FFFFFF;
                            u32 tag_mask = 0xFF000000;
                            u32 *ordering_slot;
                            /* BYTES: Color and command are written together. Separate members generate four byte stores. */
                            *(s32 *)&quad->r0 = material->color.word;
                            ((GpuLinkTag *)&quad->tag)->addr = ((GpuLinkTag *)&scratch->ordering_table[scratch->ot_index])->addr;
                            ordering_slot = (u32 *)(scratch->ot_index * 4 + (unsigned long)scratch->ordering_table);
                            ((GpuLinkTag *)ordering_slot)->addr = (u32)quad;
                        }
                    }
                }
            }
        }
        if (*(s8 *)texture < 0) {
            break;
        }
        texture += 12;
    }
    PopMatrix();
}

/* Retail 818757D4 (draw_chained_object_records).
 * Draw the record and then every record chained through the previous header's unk_18 link (node + 0x20 is the
 * next record); each node supplies the context and data pointers for its record. */
s32 draw_chained_object_records(TexturedSparkSphereBody *record, ObjectPosition *context, SpriteFrameState *data) {
    ObjectNodeHeader *node;

    for (;;) {
        draw_textured_sphere_mesh(record, context, data, 0);
        node = NODE_HEADER(record)->chain_next;
        if (node == 0) {
            return 0;
        }
        record = NODE_BODY(node);
        context = node->position;
        data = node->sprite;
    }
}

#include "sdk/libgpu_types.h"
#include "engine/graphics/sprite_scratch.h"

/* Projects a colored point and links its drawing packets into the ordering table. */
s32 project_colored_point(TerrainSeekingPointBody *render_data, ObjectPosition *position)
{
    GpuContext **context_slot;
    SpriteQuadScratch *scratch;
    GpuContext *context;
    TILE_1 *point_packet;
    DR_MODE *mode_packet;
    ObjectNodeHeader *next_node;
    u8 blue;
    u32 depth_index;
    u32 length_mask;
    u32 address_mask;
    u32 *mode_ot_entry;

    context = g_game_work.draw_buffer;
    context_slot = &g_game_work.draw_buffer;
    address_mask = 0x00FFFFFF;
    length_mask = 0xFF000000;
    scratch = SPRITE_SCRATCH;
    scratch->packet_cursor = context->packetCursor;
    scratch->ordering_table = &context->orderTag[GPU_ORDER_DEPTH_BASE];
    do {
        point_packet = scratch->packet_cursor;
        scratch->position.vx = position->x.w.i;
        scratch->position.vy = position->y.w.i;
        scratch->position.vz = position->z.w.i;
        scratch->packet_cursor = point_packet + 1;

        depth_index = RotTransPers(&scratch->position, (s32 *)&point_packet->x0, &scratch->depth_cue,
                                   &scratch->gte_flag);
        scratch->sort_depth = depth_index;
        if (depth_index < 0x1E0U) {
            /* BYTES: The tile color and command are written together. Separate members generate four byte stores. */
            *(u32 *)&point_packet->r0 = render_data->color;
            point_packet->r0 = (u8)((point_packet->r0 * render_data->intensity) /
                                      render_data->divisor);
            point_packet->g0 = (u8)((point_packet->g0 * render_data->intensity) /
                                      render_data->divisor);
            blue = (u8)((point_packet->b0 * render_data->intensity) /
                        render_data->divisor);
            ((GpuLinkTag *)&point_packet->tag)->len = 2;
            point_packet->code = 0x6A;
            point_packet->b0 = blue;

            point_packet->tag = (point_packet->tag & length_mask) |
                (scratch->ordering_table[scratch->sort_depth] & address_mask);
            {
                u32 *ot_entry;
                u32 ot_tag;
                ot_entry = (u32 *)(scratch->sort_depth * 4 + (u32)scratch->ordering_table);
                ot_tag = *ot_entry;
                *ot_entry = (ot_tag & length_mask) |
                           ((u32)point_packet & address_mask);
            }

            mode_packet = scratch->packet_cursor;
            scratch->packet_cursor = mode_packet + 1;
            SetDrawMode(mode_packet, 0, 0, GetTPage(0, 1, 0, 0) & 0xFFFF, 0);

            mode_packet->tag = (mode_packet->tag & length_mask) |
                (scratch->ordering_table[scratch->sort_depth] & address_mask);
            mode_ot_entry = (u32 *)(scratch->sort_depth * 4 + (u32)scratch->ordering_table);
            *mode_ot_entry = (*mode_ot_entry & length_mask) | ((u32)mode_packet & address_mask);
        }

        next_node = NODE_HEADER(render_data)->chain_next;
        render_data = NODE_BODY(next_node);
        if (next_node == 0) {
            break;
        }
        position = next_node->position;
    } while (1);
    (*context_slot)->packetCursor = scratch->packet_cursor;
    return 0;
}
#include "shared/object_flags.h"

/* Adjust height conditionally and set flags when the countdown reaches zero or below. */
void advance_point_effect_toward_terrain(TerrainSeekingPointBody *state, ObjectPosition *position)
{
    s16 countdown;

    sphere_particle_effect_updated = 1;
    if (position->z.w.i < (s16)sample_terrain_surface_height(
            (u16)position->x.w.i, (u16)position->y.w.i, position->z.w.i + 2)) {
        position->z.v += state->z_velocity;
    }

    countdown = state->intensity - 4;
    state->intensity = countdown;
    if ((countdown << 16) <= 0) {
        NODE_HEADER(state)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
#include "shared/dungeon_moving_views.h"

#ifndef NULL
#define NULL 0
#endif

/* Spawn and initialize an effect at a randomly offset position relative to the source. */
void create_terrain_seeking_point_effect(
    ObjectNodeHeader *source_obj,
    s32 property_34,
    s32 property_28,
    s16 property_52,
    s16 x_offset,
    s16 y_offset,
    s16 z_offset)
{
    TerrainSeekingPointBody *body;
    ObjectNodeHeader *effect_obj;
    u16 jitter;
    u16 effect_pos;

    effect_obj = allocate_list_node(0x211, &source_obj->next);
    if (effect_obj != NULL) {
        effect_obj->update_callback = advance_point_effect_toward_terrain;
        jitter = rand() & 0x1F;
        effect_pos = source_obj->position->x.unsigned_parts.integer + jitter;
        effect_pos += x_offset - 0x10;
        effect_obj->position->x.w.i = effect_pos;

        jitter = rand() & 0x1F;
        effect_pos = source_obj->position->y.unsigned_parts.integer + jitter;
        effect_pos += y_offset - 0x10;
        effect_obj->position->y.w.i = effect_pos;

        jitter = rand() & 0x1F;
        body = NODE_BODY(effect_obj);
        effect_pos = source_obj->position->z.unsigned_parts.integer + jitter;
        effect_pos += z_offset - 0x10;
        effect_obj->position->z.w.i = effect_pos;
        body->direction = property_34;
        body->intensity = property_52;
        body->divisor = property_52;
        register_node(effect_obj, project_colored_point);
        body->z_velocity = rand() + 0x10000;
        body->color = property_28;
    }
}


extern SphereSpriteSource spark_burst_sprite_source;

/* Per-state particle step: the c4 state spawns 0x20 randomised sparks in one do-while. */
void spawn_randomized_spark_burst(TexturedSparkSphereBody *p, ObjectPosition *unused, SpriteFrameState *context)
{
    s16 old;
    s16 temp;
    s16 h0;
    s16 timer0;
    s16 state0;
    s16 limit0;
    s16 timer1;
    s16 adv;
    s16 state1;
    s16 h1;
    s32 i;
    s32 color;
    s32 r0;
    s32 r1;
    s32 r2;
    s32 r3;
    s32 velocity;
    s32 state;

    state = p->mode;
    sphere_particle_effect_updated = 1;

    switch (state) {
    case 0:
        h0 = p->current_radius;
        old = p->sprite_source.command.data.texture.u0;
        p->radius.w.frac = 0;
        p->radius.w.i = h0;
        p->sprite_source.command.data.texture.u0 = old + 2;
        if ((u8)(old + 2) >= 0xE0) {
            p->sprite_source.command.data.texture.u0 = old - 0x1E;
        }
        timer0 = p->latitude_span + 0x28;
        p->latitude_span = timer0;
        if (timer0 < 0x800) {
            return;
        }
        limit0 = 0x800;
        state0 = p->mode;
        p->latitude_span = limit0;
        p->mode = state0 + 1;
        return;

    case 1:
        old = p->sprite_source.command.data.texture.u0;
        p->sprite_source.command.data.texture.u0 = old + 2;
        if ((u8)(old + 2) >= 0xE0) {
            p->sprite_source.command.data.texture.u0 = old - 0x1E;
        }
        timer1 = p->timer + 1;
        p->timer = timer1;
        if (timer1 >= 11) {
            state1 = p->mode;
            p->timer = 0;
            p->mode = state1 + 1;
        }
        h1 = p->current_radius;
        p->radius.w.frac = 0;
        p->velocity = 0;
        p->acceleration = -0x900;
        p->radius.w.i = h1;
        return;

    case 2:
        old = p->sprite_source.command.data.texture.u0;
        p->sprite_source.command.data.texture.u0 = old + 2;
        if ((u8)(old + 2) >= 0xE0) {
            p->sprite_source.command.data.texture.u0 = old - 0x1E;
        }
        if (p->radius.w.i < 31) {
            adv = p->mode;
            p->timer = 0;
            p->mode = adv + 1;
            return;
        }
        velocity = p->velocity + p->acceleration;
        p->radius.v += velocity;
        p->velocity = velocity;
        p->current_radius = p->radius.w.i;
        return;

    case 3:
        old = p->sprite_source.command.data.texture.u0;
        p->sprite_source.command.data.texture.u0 = old + 2;
        if ((u8)(old + 2) >= 0xE0) {
            p->sprite_source.command.data.texture.u0 = old - 0x1E;
        }
        temp = p->timer + 1;
        p->timer = temp;
        if (temp >= 31) {
            adv = p->mode;
            p->timer = 0;
            p->mode = adv + 1;
            return;
        }
        return;

    case 4:
        p->sprite_source = spark_burst_sprite_source;
        context->source = &p->sprite_source;
        temp = p->mode;
        p->timer = 0;
        p->mode = temp + 1;
        p->spell->burst_done = 1;

        i = 0;
        do {
            r0 = (rand() & 0xFF) | 0x80;
            i++;
            r1 = (s16)((rand() & 0x7F) - 0x40);
            r2 = (s16)((rand() & 0x7F) - 0x40);
            r3 = (s16)((rand() & 0x3F) - 0x60);
            color = 0xE04040;
            create_terrain_seeking_point_effect(NODE_HEADER(p), 0, color, r0, r1, r2, r3);
        } while (i < 0x20);
        return;

    case 5:
        temp = p->timer + 1;
        p->timer = temp;
        if (temp >= 16) {
            adv = p->mode;
            p->timer = 0;
            p->mode = adv + 1;
            return;
        }
        return;

    case 6:
        if (context->color.c.r >= 5) {
            context->color.c.r -= 5;
            context->color.c.g -= 5;
            context->color.c.b -= 5;
        }
        if (context->color.c.r < 6) {
            adv = p->mode;
            p->timer = 0;
            p->mode = adv + 1;
            return;
        }
        return;

    case 7:
        temp = p->timer - 1;
        p->timer = temp;
        if (temp > 0) {
            return;
        }
        NODE_HEADER(p)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    default:
        return;
    }
}

typedef struct S_81876014_1 {
    u8 pad_00[0xA];
    s16 unk_0A;
    u8 pad_0C[0x90];
    s16 unk_9C;
} S_81876014_1;


typedef struct S_81876014_3 {
    s32 unk_00;
} S_81876014_3;


typedef struct S_81876014_5 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
} S_81876014_5;   /* ((S_81876014_0 *)arg0)->unk_44 in update_effect_quad_and_completion */

typedef struct S_81876014_6 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_81876014_6;   /* ((S_81876014_0 *)arg0)->unk_48 in update_effect_quad_and_completion */

/* Update the effect quad, copy its position and color, and flag completion based on owner state. */
void update_effect_quad_and_completion(RotatingEffectQuadBody *effect, ObjectPosition *position_out_arg, SpriteFrameState *color_out_arg) {
    SpriteFrameState *color_out = color_out_arg;
    ObjectPosition *position_out = position_out_arg;
    s32 y_factor;
    s16 next_angle;
    u16 angle;
    S_81876014_1 *owner;

    owner = effect->unk_4C;
    sphere_particle_effect_updated = 1;
    if (owner->unk_9C == 0x37) {
        /* vertex 0 of the quad */
        effect->unk_50 =
            (u16)((effect->unk_0A *
                   rcos(effect->unk_0C)) >> 12);
        y_factor = rsin(effect->unk_0C);
        effect->unk_58 = (effect->unk_0A * y_factor) >> 12;
        effect->unk_60 = 0;
        /* x of vertices 1..3 */
        effect->unk_52 = effect->unk_50 + 0x10;
        effect->unk_54 = effect->unk_50;
        effect->unk_56 = effect->unk_50 + 0x10;
        /* y of vertices 1..3 */
        effect->unk_5A = effect->unk_58;
        effect->unk_5C = effect->unk_58;
        effect->unk_5E = effect->unk_58;
        /* z of vertices 1..3 */
        effect->unk_62 = effect->unk_60;
        effect->unk_64 = effect->unk_60 + 0x10;
        effect->unk_66 = effect->unk_60 + 0x10;
        position_out->x.v = ((S_81876014_3 *)(effect->unk_44))->unk_00;
        position_out->y.v = ((S_81876014_5 *)(effect->unk_44))->unk_04;
        position_out->z.v = ((S_81876014_5 *)(effect->unk_44))->unk_08;
        color_out->color.c.r = ((S_81876014_6 *)(effect->unk_48))->unk_0C;
        color_out->color.c.g = ((S_81876014_6 *)(effect->unk_48))->unk_0D;
        color_out->color.c.b = ((S_81876014_6 *)(effect->unk_48))->unk_0E;
        angle = effect->unk_0C;
        next_angle = angle - 0x64;
        effect->unk_0C = next_angle;
        if (next_angle < 0) {
            effect->unk_0C = angle + 0xF9C;
        }
        if (owner->unk_0A < 5) {
            return;
        }
    }
    (*(u16 *)((u8 *)effect + -2)) |= NODE_REMOVE;
    object_flag_block.flags |= OBJECT_REMOVE_PENDING;
}
#include "shared/entity_height_offsets.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"




typedef struct S_800259D8_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_800259D8_1;   /* base in update_animated_effect_sprite */


typedef struct S_800259D8_3_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800259D8_3_pre;   /* the 0x14 bytes before obj in update_animated_effect_sprite, addressed as obj[-1] */

typedef struct S_800259D8_3 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x34];
    void * unk_60;
    u8 pad_64[0xE];
    s8 unk_72;
    u8 pad_73[0x15];
    u16 unk_88;
} S_800259D8_3;   /* obj in update_animated_effect_sprite */


typedef struct S_800259D8_5 {
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x2]; s16 v; } at02;
        struct { u8 pad[0x2]; u16 v; } at02u;
    } unk_00;   /* overlapping accesses */
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x2]; s16 v; } at02;
        struct { u8 pad[0x2]; u16 v; } at02u;
    } unk_04;   /* overlapping accesses */
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x2]; u16 v; } at02;
        struct { u8 pad[0x2]; s16 v; } at02u;
    } unk_08;   /* overlapping accesses */
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    s16 unk_12;
    u8 pad_14[0x6];
    s16 unk_1A;
    s16 unk_1C;
    u8 pad_1E[0x1A];
    void * unk_38;
    void * unk_3C;
    void * unk_40;
    void * unk_44;
    void * unk_48;
    void * unk_4C;
} S_800259D8_5;   /* entry in update_animated_effect_sprite */


   /* work in update_animated_effect_sprite */

typedef struct S_800259D8_10_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800259D8_10_pre;   /* the 0x14 bytes before fade_node in update_animated_effect_sprite, addressed as fade_node[-1] */

typedef struct S_800259D8_10 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_800259D8_10;   /* fade_node in update_animated_effect_sprite */

typedef struct S_800259D8_11 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_800259D8_11;   /* fade_entry in update_animated_effect_sprite */

typedef struct S_800259D8_12_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800259D8_12_pre;   /* the 0x14 bytes before tail_node in update_animated_effect_sprite, addressed as tail_node[-1] */

typedef struct S_800259D8_12 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_800259D8_12;   /* tail_node in update_animated_effect_sprite */

typedef struct S_800259D8_13 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
} S_800259D8_13;   /* ((S_800259D8_1 *)base)->unk_0C in update_animated_effect_sprite */


typedef struct S_800259D8_15_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_800259D8_15_pre;   /* the 0x18 bytes before ((S_800259D8_3 *)obj)->unk_60 in update_animated_effect_sprite, addressed as ((S_800259D8_3 *)obj)->unk_60[-1] */

typedef struct S_800259D8_15 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_800259D8_15;   /* ((S_800259D8_3 *)obj)->unk_60 in update_animated_effect_sprite */

typedef struct DirectionOffset {
    s16 x;
    u16 y;
} DirectionOffset;
typedef union DirectionOffsetCopy {
    DirectionOffset pairs[8];
    u8 bytes[32];
} Copy32;


typedef struct {
    s16 x;
    s16 y;
    u16 z;
} Vec3s;

typedef u16 H16;

typedef struct {
    H16 x;
    H16 y;
} Pair;

/* These resident data/code addresses are not present in the catalog for this
 * cold overlay row; the binds retain real link-resolved symbols. */

const Copy32 textured_quad_octant_offsets = {{ {8, 0}, {8, 8}, {0, 8}, {-8, 8}, {-8, 0}, {-8, 65528}, {0, 65528}, {8, 65528} }};
extern SphereSpriteSource animated_effect_sprite_source;
extern SphereSpriteSource animated_effect_burst_sprite_source;
extern SphereSpriteSource animated_effect_target_sprite_source;

/* Moves an effect toward its target, emits particles, changes target colors, and applies a timed status. */
void update_animated_effect_sprite(TargetParticleStatusSpellBody *effect, ObjectPosition *entity, SpriteFrameState *sprite)
{
    Vec3s delta;
    Copy32 copy;
    ActorRecord *obj;
    S_800259D8_1 *base;
    S_800259D8_5 *entry;
    void *node;
    SpriteFrameState *work;
    ObjectPosition *dst;
    u32 state;
    u16 old_count;
    s16 count;
    s32 result;
    s32 index;
    s32 value;
    s32 i;

    obj = effect->spell.caster;
    copy = textured_quad_octant_offsets;
    state = effect->spell.phase;
    base = (S_800259D8_1 *)((u8 *)obj - 0x20);
    entry = base->unk_08;
    switch (state) {
    case 0:
    {
        s32 setup;
        setup = 0x00808080;
        sprite->color.word = setup;
        setup = 0x1000;
        sprite->scale_y = setup;
        sprite->scale_x = setup;
    }
        *(SphereSpriteSource *)((u8 *)effect + 0xA2) = animated_effect_sprite_source;
        {
            s32 init_value;
            u16 init_count;
            sprite->source = (u8 *)effect + 0xA2;
            init_value = (((S_800259D8_3 *)obj)->unk_2A >> 9) & 7;
            (&sphere_particle_effect_updated)[0] = 1;
            init_count = effect->spell.phase + 1;
            effect->direction = init_value;
            effect->spell.phase = init_count;
        }
    case 1:
        result = get_sprite_attachment_vector(
            ((S_800259D8_13 *)(base->unk_0C))->unk_08,
            base->unk_0C, &delta, 0);
        if (result == 0) {
            if (!(((S_800259D8_13 *)(base->unk_0C))->unk_14 & 0x8000U)) {
                return;
            }
        }
        {
            u16 z_value;
            entity->x.w.i = entry->unk_00.at02.v;
            entity->y.w.i = entry->unk_04.at02.v;
            z_value = entry->unk_08.at02.v;
            entity->z.unsigned_parts.integer = z_value;
            if (!(((S_800259D8_13 *)(base->unk_0C))->unk_14 & 0x8000U)) {
                entity->x.w.i += delta.x;
                entity->y.w.i += delta.y;
                entity->z.w.i = entity->z.unsigned_parts.integer + delta.z;
            } else {
L0_adjust_z:
                                           /* MATCH: retain the alternate z calculation's scheduling boundary. */
                entity->z.w.i = z_value - 0x40;
            }
        }
        if (!(*effect->spell.context & 0x80U)) {
            return;
        }
        if (!(effect->render_flags & 4U)) {
            register_node((u8 *)effect - 0x20, project_sprite_chain);
            sprite->tpage_abr = 0x20;
            sprite->color.c.b = 0x80;
            sprite->color.c.g = 0x80;
            sprite->color.c.r = 0x80;
            sprite->flags |= 0xC;
            effect->render_flags |= 4;
        }
        if (obj->target != 0) {
            SpriteFrameState *resident_work;
            entry = ((S_800259D8_15_pre *)(obj->target))[-1].unk_00;
            effect->dest_x = entry->unk_00.at02u.v;
            effect->dest_y = entry->unk_04.at02u.v;
            {
                s32 depth_bias;
                s32 resident_value;
                depth_bias = entity_height_offsets[((S_800259D8_15 *)(obj->target))->unk_13];
                resident_value = entry->unk_08.at02.v - depth_bias - 0x60;
                effect->dest_z = resident_value;
            }
            resident_work = ((S_800259D8_3_pre *)obj)[-1].unk_00;
            effect->front_tile_x = resident_work->tile_x +
                dir_step_x[effect->direction];
            effect->front_tile_y = resident_work->tile_y +
                dir_step_y[effect->direction];
            entry = ((S_800259D8_15_pre *)(obj->target))[-1].unk_00;
            {
                if (obj->target_tile_x != resident_work->tile_x) {
                    s32 resident_delta;
                    s32 resident_copy;
                    resident_delta = entity->x.w.i;
                    resident_delta = resident_delta - entry->unk_00.at02.v;
                    resident_copy = *(s16 *)((u8 *)&copy + (effect->direction << 2));
                    resident_delta = abs(resident_delta);
                    resident_copy = abs(resident_copy);
                    effect->travel_ticks = resident_delta / resident_copy;
                } else {
                    Pair *cp;
                    s32 cidx;
                    s32 resident_delta;
                    s32 resident_copy;
                    resident_delta = entity->y.w.i;
                    cidx = effect->direction << 2;
                    resident_delta = resident_delta - entry->unk_04.at02.v;
                    cp = (Pair *)&copy;
                    resident_copy = ((Pair *)((u8 *)cp + cidx))->y;
                    resident_delta = abs(resident_delta);
                    resident_copy = (s32)((u32)resident_copy << 16) >> 16;
                    resident_copy = abs(resident_copy);
                    effect->travel_ticks = resident_delta / resident_copy;
                }
            }
        } else {
            {
                effect->travel_ticks = 0x80;
                effect->dest_x = entity->x.unsigned_parts.integer +
                    (((Pair *)((u8 *)&copy + (effect->direction << 2)))->x << 7);
                effect->dest_y = entity->y.unsigned_parts.integer +
                    (((Pair *)((u8 *)&copy + (effect->direction << 2)))->y *
                     (u16)effect->travel_ticks);
                effect->dest_z = ((S_800259D8_3 *)obj)->unk_88 - 0x50;
            }
        }
        {
            Pair *cp = (Pair *)&copy;
            entity->velocity_x =
                (s16)((Pair *)((u8 *)cp + (effect->direction << 2)))->x << 16;
            entity->velocity_y =
                ((Pair *)((u8 *)cp + (effect->direction << 2)))->y << 16;
        }
        entity->velocity_z =
            ((effect->dest_z << 16) - entity->z.v) /
            effect->travel_ticks;
        effect->phase_timer = 0;
        effect->quad_marker = 55;
        effect->spell.phase++;
        i = 0;
        do {
            ObjectNodeHeader *spawn;
            spawn = allocate_flagged_object_node(0x12);
            if (spawn != 0) {
                entry = NODE_BODY(spawn);
                {
                    void *spawn_copy = spawn;
                    u8 *tbl = project_linked_quad_record;
                    entry->unk_38 = obj;
                    entry->unk_44 = entity;
                    entry->unk_48 = sprite;
                    entry->unk_4C = effect;
                    spawn->update_callback = (void *)update_effect_quad_and_completion;
                    register_node(spawn_copy, tbl);
                }
                work = spawn->sprite;
                work->flags |= 0xC;
                work->tpage_abr = 0x20;
                dst = spawn->position;
                entry->unk_08.at02u.v = (rand() & 7) + 12;
                entry->unk_0C = rand() & 0xFFF;
                work->angle_x = (rand() & 0xFF) << 4;
                work->angle_y = (rand() & 0xFF) << 4;
                work->angle_z = (rand() & 0xFF) << 4;
                value = rcos(entry->unk_0C);
                dst->x.v = (entry->unk_08.at02u.v * value) << 4;
                value = rsin(entry->unk_0C);
                dst->y.v = (entry->unk_08.at02u.v * value) << 4;
                dst->z.w.i = entity->z.unsigned_parts.integer;
                work = spawn->sprite;
                {
                    s32 scale1;
                    scale1 = 0x1000;
                    work->scale_y = scale1;
                    work->scale_x = scale1;
                }
                {
                    s32 alpha;
                    alpha = 0x80;
                    work->color.c.b = alpha;
                    work->color.c.g = alpha;
                    work->color.c.r = alpha;
                }
                *(SphereSpriteSource *)((u8 *)spawn + 0x4C) = animated_effect_burst_sprite_source;
                work->source = (u8 *)spawn + 0x4C;
            }
            i++;
            if (i < 8) {
                continue;
            }
        } while (i < 8);
        return;

    case 2:
        if (effect->flicker_phase == 0) {
            effect->flicker_phase = 1;
            effect->unk_AA += 0x18;
        } else {
            effect->unk_AA -= 0x18;
            effect->flicker_phase = 0;
        }
        result = check_adjacent_tile_height_clearance(entity->x.unsigned_parts.integer, entity->y.unsigned_parts.integer,
                               entity->z.w.i, obj->target);
        if ((result << 16) == 0) {
            node = obj->target;
            if (node == 0) {
                sprite->color.c.r -= 4;
                sprite->color.c.g -= 4;
                sprite->color.c.b -= 4;
                if (sprite->color.c.r == 0) {
                    effect->travel_ticks = 1;
                }
            }
            count = effect->travel_ticks - 1;
            effect->travel_ticks = count;
            if (count > 0) {
                goto L1_calc;
            }
            if (obj->target != 0) {
                effect->spell.phase = 3;
                effect->phase_timer = 0;
                entry = ((S_800259D8_15_pre *)(obj->target))[-1].unk_00;
                entity->x.unsigned_parts.integer = entry->unk_00.at02u.v;
                entity->y.unsigned_parts.integer = entry->unk_04.at02u.v;
                entity->z.unsigned_parts.integer = effect->dest_z;
                play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
                return;
            }
        }
        effect->spell.phase = 7;
        effect->phase_timer = 0;
        sprite->color.c.b = 0;
        sprite->color.c.g = 0;
        sprite->color.c.r = 0;
        return;

L1_calc:
        entity->velocity_x =
            ((effect->dest_x << 16) - entity->x.v) / count;
        entity->velocity_y =
            ((effect->dest_y << 16) - entity->y.v) /
            effect->travel_ticks;
        entity->velocity_z =
            ((effect->dest_z << 16) - entity->z.v) /
            effect->travel_ticks;
        entity->x.v += entity->velocity_x;
        entity->y.v += entity->velocity_y;
        entity->z.v += entity->velocity_z;
        return;

    case 3:
        if (effect->flicker_phase == 0) {
            effect->flicker_phase = 1;
            effect->unk_AA += 0x18;
        } else {
            effect->unk_AA -= 0x18;
            effect->flicker_phase = 0;
        }
        {
            ObjectNodeHeader *spawn;
            TexturedSparkSphereBody *sphere;
            ActorRecord *target_actor;
            spawn = allocate_flagged_object_node(0x12);
            if (spawn != 0) {
                entry = NODE_BODY(spawn);
                entry->unk_00.at02.v = 0;
                entry->unk_38 = obj;
                entry->unk_3C = obj->target;
                entry->unk_40 = effect;
                entry->unk_08.at02u.v = 0x0C;
                entry->unk_0C = 8;
                entry->unk_0E = 0;
                entry->unk_10 = 0;
                entry->unk_12 = 0;
                entry->unk_1C = 0;
                entry->unk_1A = 0x40;
                entry = ((S_800259D8_15_pre *)(obj->target))[-1].unk_00;
                spawn->update_callback = spawn_randomized_spark_burst;
                register_node(spawn, draw_chained_object_records);
                work = spawn->sprite;
                work->tpage_abr = 0x20;
                work->flags |= 0x000C;
                dst = spawn->position;
                dst->x.v = entry->unk_00.at00.v;
                dst->y.v = entry->unk_04.at00.v;
                target_actor = obj->target;
                index = target_actor->species;
                dst->z.v = entry->unk_08.at00.v -
                    (entity_height_offsets[index] << 15);
                work = spawn->sprite;
                {
                    s16 scale2 = 0x1000;
                    work->scale_y = scale2;
                    work->scale_x = scale2;
                }
                work->color.c.b = 0x80;
                work->color.c.g = 0x80;
                work->color.c.r = 0x80;
                sphere = NODE_BODY(spawn);
                sphere->sprite_source = animated_effect_target_sprite_source;
                work->source = &sphere->sprite_source;
            }
        }
        effect->spell.phase = 4;
        effect->phase_timer = 0;
        return;

    case 4:
        count = effect->phase_timer + 1;
        effect->phase_timer = count;
        if (count < 30) {
            sprite->color.c.r = ((30 - effect->phase_timer) * 0x80) / 30;
            sprite->color.c.g = ((30 - effect->phase_timer) * 0x80) / 30;
            sprite->color.c.b = ((30 - effect->phase_timer) * 0xE0) / 30;
            if (effect->flicker_phase == 0) {
                effect->flicker_phase = 1;
                effect->unk_AA += 0x18;
            } else {
                effect->unk_AA -= 0x18;
                effect->flicker_phase = 0;
            }
            i = 0;
            while (1) {
                value = rand();
                create_terrain_seeking_point_effect(NODE_HEADER(effect), effect->direction, 0x00E02020, (value & 0xFF) | 0x80, 0,
                    0, 0);
                i++;
                if (i >= 4) {
                    return;
                }
            }
        }
        effect->spell.phase++;
        effect->phase_timer = 0;
        sprite->flags |= 0x80;
        return;

    case 5:
        if (effect->burst_done == 0) {
            return;
        }
        {
            effect->phase_timer = 0;
            effect->spell.phase++;
            return;
        }

    case 6:
    {
        void *fade_node;
        S_800259D8_11 *fade_entry;
        count = effect->phase_timer + 1;
        effect->phase_timer = count;
        fade_node = obj->target;
        ((S_800259D8_10 *)fade_node)->unk_1C |= 0x10000000;
        fade_entry = ((S_800259D8_10_pre *)fade_node)[-1].unk_00;
        if (effect->phase_timer >= 36) {
            fade_entry->unk_0C += 2;
            fade_entry->unk_0D += 2;
            fade_entry->unk_0E -= 3;
        } else {
            fade_entry->unk_0C -= 2;
            fade_entry->unk_0D -= 2;
            fade_entry->unk_0E += 3;
        }
        if (effect->phase_timer < 71) {
            return;
        }
        {
            void *tail_node;
            tail_node = obj->target;
            ((S_800259D8_12 *)tail_node)->unk_1C &= 0xEFFFFFFF;
            fade_entry = ((S_800259D8_12_pre *)tail_node)[-1].unk_00;
            fade_entry->unk_0E = 0x80;
            fade_entry->unk_0D = 0x80;
            fade_entry->unk_0C = 0x80;
            apply_water_protect_status(obj->target, effect->spell.variant, obj);
        }
        effect->phase_timer = 13;
        effect->spell.phase++;
        return;
    }

    case 7:
        old_count = effect->phase_timer;
        effect->phase_timer = old_count + 1;
        if ((s16)old_count < 15) {
            return;
        }
        {
            s32 seen;
            seen = (&sphere_particle_effect_updated)[0];
            effect->phase_timer = old_count;
            if (seen == 0) {
                g_dungeon_status.active_actor = 0;
                NODE_HEADER(effect)->flags |= 0x8000;
                object_flag_block.flags |= OBJECT_REMOVE_PENDING;
                return;
            }
        }
        (&sphere_particle_effect_updated)[0] = 0;
        return;
    }

    return;
}
