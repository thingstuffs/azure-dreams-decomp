#include "shared/audio_commands.h"
#include "dungeon/effect/shaded_quad_scratch.h"
#include "shared/slus_callbacks.h"
#include "sdk/libc.h"
#include "dungeon/effect/mesh.h"
#include "dungeon/effect/mesh/projectile_trail_flash.h"
#include "dungeon/effect/mesh/star_edge_effect.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
/* Mesh and point rendering, star effects, and projectile trails with target hit animation. */
#include "modules/dungeon_native_abi.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/actor/status.h"
#include "engine/graphics.h"
#include "dungeon/item/message.h"
#include "sdk/libgpu.h"
#include "dungeon/system.h"

#include "dungeon/effect/screen.h"
#include "dungeon/item.h"
#include "dungeon/actor.h"
#include "dungeon/data.h"

void (*const dungeon_189a800_entry)(ProjectileEffect *, ObjectPosition *, SpriteFrameState *) = update_projectile_trail_and_hit_effect;


extern s32 wind_protect_text;

/* Attempts to apply an effect and reports the outcome for flagged targets. */
void try_apply_wind_protection(ActorRecord *target, s32 effect_arg, ActorRecord *caster)
{
    void *message;
    void *message_start;

    if (try_trigger_target_record_effect(target, 4, caster) == 0) {
        /*
         * BUG: set_or_clear_actor_status_slot returns a slot index (0..3), or -1 on
         * failure. Testing it as nonzero misreports slot 0 as failure and -1 as success.
         * Slot-0 success instead prints the no-effect message; rejected insertion prints success.
         * try_apply_confusion_status uses the nonnegative success test.
         */
        if ((set_or_clear_actor_status_slot(target, STATUS_WIND_PROTECT,
                           (s8)(get_random_scaled_value(effect_arg & 0xFF) + 2)) << 16) != 0) {
            if (target->flags14 & ACTOR_PARTY_MEMBER) {
                adjust_source_value_and_finalize(target, &wind_protect_text);
                return;
            }
        } else if (target->flags14 & ACTOR_PARTY_MEMBER) {
            message = get_unused_text_buffer();
            message_start = message;
            message = expand_text_control_codes(no_effect_target_prefix, message);
            message = append_entity_display_text(target, message);
            message = expand_text_control_codes(no_effect_target_period, message);
            clear_byte_and_advance(message);
            display_text_with_fullwidth_adjustment(message_start);
        }
    }
}
#include "modules/dungeon_ovl_189a800.h"
#include "shared/game_work.h"

#include "sdk/libgte_matrix.h"

typedef struct {} EmptyArg;

typedef struct S_func_800241A8_6 {
    struct {
        u8 pad_00[0x3];
        u8 unk_03;
    } unk_00;
    union {
        u32 as_u32_04;
        struct {
            u8 pad_04[0x3];
            u8 unk_07;
        } as_u8_07;
    } unk_04;
    s16 unk_08;
    s16 unk_0A;
    u16 unk_0C;
    u16 unk_0E;
    u16 unk_10;
    u16 unk_12;
    union {
        u16 as_u16_14;
        u8 as_u8_14;
    } unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    union {
        u16 as_u16_1C;
        struct {
            u8 pad_1C[0x1];
            u8 unk_1D;
        } as_u8_1D;
    } unk_1C;
    u8 pad_1E[0x2];
    s16 unk_20;
    s16 unk_22;
    union {
        u16 as_u16_24;
        u8 as_u8_24;
        struct {
            u8 pad_24[0x1];
            u8 unk_25;
        } as_u8_25;
    } unk_24;
} S_func_800241A8_6;

extern void CompMatrix(void *, void *, void *);
extern void PushMatrix(void);
extern void PopMatrix(void);
extern void ReadRotMatrix(void *);
extern void ScaleMatrix(void *, void *);
extern void SetRotMatrix(void *);
extern void SetTransMatrix(void *);
extern s32 RotAverage4(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, EmptyArg);
extern void RotMatrix(void *, void *);

typedef struct {
    u8 flags;
    u8 texture_flags;
    u8 pad_02[0x2];
    u16 tpage;
    u16 clut;
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} MeshTexture;


/* Transform the mesh and enqueue textured quads or lines in the ordering table. */
void transform_and_queue_mesh_primitives(S_func_800241A8_4 *mesh, ObjectPosition *transform, SpriteFrameState *object, s32 depth_bias)
{
    ShadedQuadScratch *scratch = SHADED_QUAD_SCRATCH;
    MeshTexture *texture;
    s32 depth_offset;
    MATRIX matrix;
    u32 render_flags;
    GameWork *game_work;

    game_work = &g_game_work;
    scratch->ordering_table = &game_work->draw_buffer->orderTag[GPU_ORDER_DEPTH_BASE];
    scratch->local_matrix.t[0] = transform->x.w.i;
    scratch->local_matrix.t[1] = transform->y.w.i;
    scratch->local_matrix.t[2] = transform->z.w.i;
    object->flags |= 0x8000;

    PushMatrix();

    scratch->scale.vz = 0x2000;
    scratch->scale.vy = 0x2000;
    scratch->scale.vx = 0x2000;
    scratch->angles.vx = object->angle_x;
    scratch->angles.vz = object->angle_z;
    scratch->angles.vy = object->angle_y;
    RotMatrix(&scratch->angles, &scratch->local_matrix);
    ReadRotMatrix(&matrix);
    CompMatrix(&matrix, &scratch->local_matrix, &scratch->composed_matrix);
    ScaleMatrix(&scratch->composed_matrix, &scratch->scale);
    SetTransMatrix(&scratch->composed_matrix);
    SetRotMatrix(&scratch->composed_matrix);

    depth_offset = (s16)depth_bias;
    texture = object->source;
    scratch->render_flags = object->flags;

    for (;;) {
        if (mesh->unk_4E != 0) {
            S_func_800241A8_6 *packet;
            s32 ot_index;
            u8 texture_flags;
            s32 texture_adjust;
            GpuContext *render_state;

            render_state = game_work->draw_buffer;
            packet = render_state->packetCursor;
            render_state->packetCursor = (u8 *)packet + 0x28;

            scratch->uv_u_start = texture->r;
            scratch->uv_v_start = texture->g;
            scratch->uv_u_extent = texture->b;
            scratch->uv_v_extent = texture->a;

            scratch->vertices[0].vx = mesh->unk_58.as_u16_58;
            scratch->vertices[1].vx = mesh->unk_5A.as_u16_5A;
            scratch->vertices[2].vx = mesh->unk_5C.as_u16_5C;
            scratch->vertices[3].vx = mesh->unk_5E.as_u16_5E;
            scratch->vertices[0].vy = mesh->unk_60.as_u16_60;
            scratch->vertices[1].vy = mesh->unk_62.as_u16_62;
            scratch->vertices[2].vy = mesh->unk_64.as_u16_64;
            scratch->vertices[3].vy = mesh->unk_66.as_u16_66;
            scratch->vertices[0].vz = mesh->unk_68.as_u16_68;
            scratch->vertices[1].vz = mesh->unk_6A.as_u16_6A;
            scratch->vertices[2].vz = mesh->unk_6C.as_u16_6C;
            scratch->vertices[3].vz = mesh->unk_6E.as_u16_6E;

            ot_index = RotAverage4(&scratch->vertices[0], &scratch->vertices[1],
                                     &scratch->vertices[2], &scratch->vertices[3],
                                     &packet->unk_08, &packet->unk_10,
                                     &packet->unk_18, &packet->unk_20,
                                     &scratch->depth_cue, &scratch->gte_flag,
                                     ({ EmptyArg empty; empty; })) - depth_offset - 6;
            scratch->ot_index = ot_index;

            if ((u32)ot_index < 0x1E0 &&
                ((((u16)(packet->unk_08 + 0x20) < 0x181) &&
                  ((u16)(packet->unk_0A + 0x20) < 0x121)) |
                 (((u16)(packet->unk_10 + 0x20) < 0x181) &&
                  ((u16)(packet->unk_12 + 0x20) < 0x121)) |
                 (((u16)(packet->unk_18 + 0x20) < 0x181) &&
                  ((u16)(packet->unk_1A + 0x20) < 0x121)) |
                 (((u16)(packet->unk_20 + 0x20) < 0x181) &&
                  ((u16)(packet->unk_22 + 0x20) < 0x121)))) {
                packet->unk_00.unk_03 = 9;
                packet->unk_04.as_u8_07.unk_07 = 0x2C;
                object->flags &= 0x7FFF;

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

                {
                    u32 palette_id;
                    texture_adjust = object->clut;
                    if (texture_adjust != 0) {
                        if (scratch->render_flags & 0x100) {
                            packet->unk_0E = texture_adjust;
                        } else {
                            palette_id = texture_adjust + texture->clut;
                            packet->unk_0E = palette_id;
                        }
                    } else {
                        palette_id = texture->clut;
                        packet->unk_0E = palette_id;
                    }
                }

                packet->unk_0C = scratch->uv_v_start +
                                           scratch->uv_u_start;
                packet->unk_14.as_u16_14 = scratch->uv_v_start +
                                           scratch->uv_u_extent;

                texture_adjust = object->tpage_abr;
                if (texture_adjust != 0) {
                    packet->unk_16 = texture_adjust + (texture->tpage & 0xFF9F);
                } else {
                    packet->unk_16 = texture->tpage;
                }

                packet->unk_1C.as_u16_1C = scratch->uv_v_extent +
                                           scratch->uv_u_start;
                packet->unk_24.as_u16_24 = scratch->uv_v_extent +
                                           scratch->uv_u_extent;

                if (packet->unk_08 > packet->unk_20) {
                    packet->unk_14.as_u8_14--;
                    packet->unk_24.as_u8_24--;
                }
                if (packet->unk_0A > packet->unk_22) {
                    packet->unk_1C.as_u8_1D.unk_1D--;
                    packet->unk_24.as_u8_25.unk_25--;
                }

                texture_flags = texture->texture_flags;
                object->color.c.code = texture_flags;
                render_flags = scratch->render_flags;
                if (render_flags & 8) {
                    object->color.c.code = (render_flags & 4) ?
                        (texture_flags | 2) : (texture_flags & 0xFD);
                }

                packet->unk_04.as_u32_04 = ((u32)(object->color.word));
                setaddr(packet, getaddr(scratch->ordering_table + scratch->ot_index));
                setaddr(scratch->ordering_table + scratch->ot_index, packet);
            }
        }

        if (mesh->unk_4E == 0) {
            s32 ot_index;
            s32 midpoint;
            s32 midpoint_z;
            s32 coord_a;
            s32 coord_b;
            s32 end_z_a;
            s32 end_z_b;
            S_func_800241A8_6 *line;
            S_func_800241A8_6 *tpage;
            GpuContext *render_state;
            GpuContext *tpage_state;

            render_state = game_work->draw_buffer;
            line = render_state->packetCursor;
            render_state->packetCursor = &line->unk_10;

            coord_a = mesh->unk_58.as_s16_58;
            coord_b = mesh->unk_5C.as_s16_5C;
            midpoint = (coord_a + coord_b) / 2;
            scratch->vertices[2].vx = midpoint;
            scratch->vertices[0].vx = midpoint;
            coord_a = mesh->unk_5A.as_s16_5A;
            coord_b = mesh->unk_5E.as_s16_5E;
            midpoint = (coord_a + coord_b) / 2;
            scratch->vertices[3].vx = midpoint;
            scratch->vertices[1].vx = midpoint;
            coord_a = mesh->unk_60.as_s16_60;
            coord_b = mesh->unk_64.as_s16_64;
            midpoint = (coord_a + coord_b) / 2;
            scratch->vertices[2].vy = midpoint;
            scratch->vertices[0].vy = midpoint;
            coord_a = mesh->unk_62.as_s16_62;
            coord_b = mesh->unk_66.as_s16_66;
            midpoint = (coord_a + coord_b) / 2;
            scratch->vertices[3].vy = midpoint;
            scratch->vertices[1].vy = midpoint;
            coord_a = mesh->unk_68.as_s16_68;
            coord_b = mesh->unk_6C.as_s16_6C;
            midpoint = (coord_a + coord_b) / 2;
            scratch->vertices[2].vz = midpoint;
            scratch->vertices[0].vz = midpoint;
            end_z_a = mesh->unk_6A.as_s16_6A;
            end_z_b = mesh->unk_6E.as_s16_6E;
            midpoint_z = (end_z_a + end_z_b) / 2;
            scratch->vertices[3].vz = midpoint_z;
            scratch->vertices[1].vz = midpoint_z;

            ot_index = RotAverage4(&scratch->vertices[0], &scratch->vertices[1],
                                     &scratch->vertices[2], &scratch->vertices[3],
                                     &line->unk_08, &line->unk_0C,
                                     &line->unk_08, &line->unk_0C,
                                     &scratch->depth_cue, &scratch->gte_flag,
                                     ({ EmptyArg empty; empty; })) - depth_offset - 6;
            scratch->ot_index = ot_index;

            render_flags = scratch->render_flags;
            if (render_flags & 8) {
                if (render_flags & 4) {
                    object->color.c.code |= 2;
                } else {
                    object->color.c.code &= 0xFD;
                }
            }

            render_flags = ((u32)(object->color.word));
            line->unk_00.unk_03 = 3;
            line->unk_04.as_u32_04 = render_flags;
            line->unk_04.as_u8_07.unk_07 = 0x42;
            setaddr(line, getaddr(scratch->ordering_table + scratch->ot_index));
            setaddr(scratch->ordering_table + scratch->ot_index, line);

            tpage_state = game_work->draw_buffer;
            tpage = tpage_state->packetCursor;
            tpage_state->packetCursor = &tpage->unk_0C;
            SetDrawMode(tpage, 0, 0, GetTPage(0, 1, 0, 0) & 0xFFFF, 0);
            setaddr(tpage, getaddr(scratch->ordering_table + scratch->ot_index));
            setaddr(scratch->ordering_table + scratch->ot_index, tpage);
        }

        if ((s8)texture->flags < 0) {
            break;
        }
        texture++;
    }
    PopMatrix();
}
#include "shared/object_node.h"


/* Retail 8187B1A0 (draw_chained_mesh_records).
 * Draw the record and then every record chained through the previous header's unk_18 link (node + 0x20 is the
 * next record); each node supplies the context and data pointers for its record. */
s32 draw_chained_mesh_records(void *record, void *context, void *data) {
    ObjectNodeHeader *node;

    for (;;) {
        transform_and_queue_mesh_primitives(record, context, data, 0);
        node = NODE_HEADER(record)->chain_next;
        if (node == 0) {
            return 0;
        }
        record = node + 1;
        context = node->position;
        data = node->sprite;
    }
}
#include "shared/position_views.h"

typedef struct S_8187B1F4_4 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; s8 v; } at03; } unk_00;   /* overlapping accesses */
    union {
        struct { s32 v; } at00;
        struct { s8 v; } at00u;
        struct { u8 v; } at00p;
        struct { u8 pad[0x1]; u8 v; } at01;
        struct { u8 pad[0x2]; u8 v; } at02;
        struct { u8 pad[0x3]; s8 v; } at03;
    } unk_04;   /* overlapping accesses */
} S_8187B1F4_4;

#define VFIELD(base, type, offset) (((struct { u8 _pad_[offset]; type v; } *)(base))->v)

typedef struct GlobalState {
    u8 pad[0x8D0];
    u8 *next;
} GlobalState;

extern void CompMatrix(void *, void *, void *);
extern void PushMatrix(void);
extern void PopMatrix(void);
extern void ReadRotMatrix(void *);
extern void ScaleMatrix(void *, void *);
extern void SetRotMatrix(void *);
extern void SetTransMatrix(void *);
extern u32 RotTransPers(void *, void *, void *, void *);
extern void RotMatrix(void *, void *);

typedef struct GlobalRef {
    GlobalState *cur;
} GlobalRef;

typedef struct PrimitiveTag { unsigned addr : 24; unsigned len : 8; } PrimitiveTag;

/* Projects points and adds brightness-scaled pixel primitives to the ordering table. */
s32 project_shaded_points_to_ordering_table(RandomRadialVectorEffectBody *points, ObjectPosition *position, SpriteFrameState *sprite) {
    s32 view_matrix[8];
    void *model_matrix;
    ShadedQuadScratch *scratch;
    MATRIX *transform_matrix;
    GlobalRef *global;
    register GlobalState *state;
    GlobalState *cur_state;
    GlobalState *tag_state;
    u8 *ordering_table;
    u8 *point_packet;
    u8 *draw_mode_packet;
    u8 *unused_ptr;
    s32 point_index;
    u16 *point_coords;
    u32 depth;
    s32 point_count;
    s32 hard_zero = 0;
    u16 component;
    void *vertex;
    void *depth_cue;
    void *projection_flags;
    u8 *tail;
    ObjectNodeHeader *tail_2;

    global = (GlobalRef *)((GlobalState * *)(&g_game_work));
    scratch = SHADED_QUAD_SCRATCH;
    model_matrix = &scratch->local_matrix;
    transform_matrix = &scratch->composed_matrix;
    do {
        scratch->local_matrix.t[0] = position->x.w.i;
        scratch->local_matrix.t[1] = position->y.w.i;
        scratch->local_matrix.t[2] = position->z.w.i;
        PushMatrix();
        scratch->scale.vz = 0x1000;
        scratch->scale.vy = 0x1000;
        scratch->scale.vx = 0x1000;
        scratch->angles.vx = sprite->angle_x;
        scratch->angles.vz = sprite->angle_z;
        component = sprite->angle_y;
        scratch->angles.vy = component;
        RotMatrix(&scratch->angles, model_matrix);
        ReadRotMatrix(&view_matrix);
        CompMatrix(&view_matrix, model_matrix, transform_matrix);
        ScaleMatrix(transform_matrix, &scratch->scale);
        SetTransMatrix(transform_matrix);
        SetRotMatrix(transform_matrix);
        state = global->cur;
        ordering_table = (u8 *)state;
        state = (GlobalState *)state->next;
        ordering_table += 0xB0;
        VFIELD(scratch, void *, 0x24) = ordering_table;
        VFIELD(scratch, void *, 0x1C) = state;
        point_index = 0;
        if (points->point_count > 0) {
            point_coords = (u16 *)points;
            do {
                scratch->position.vx = point_coords[point_index + 0xB];
                scratch->position.vy = point_coords[point_index + 0x22];
                vertex = &scratch->position;
                component = point_coords[point_index + 0x39];
                cur_state = global->cur;
                depth_cue = &scratch->depth_cue;
                scratch->position.vz = component;
                point_packet = cur_state->next;
                projection_flags = &scratch->gte_flag;
                cur_state->next = point_packet + 0xC;
                depth = RotTransPers(vertex, point_packet + 8,
                                      depth_cue, projection_flags);
                VFIELD(scratch, u32, 0x100) = depth;
                if (depth < 0x1E0U) {
                    ((S_8187B1F4_4 *)point_packet)->unk_04.at00.v = points->color;
                    ((S_8187B1F4_4 *)point_packet)->unk_04.at00u.v =
                        (s8)((((S_8187B1F4_4 *)point_packet)->unk_04.at00p.v *
                        points->intensity.s) / points->divisor);
                    ((S_8187B1F4_4 *)point_packet)->unk_04.at01.v =
                        (u8)((((S_8187B1F4_4 *)point_packet)->unk_04.at01.v *
                        points->intensity.s) / points->divisor);
                    ((S_8187B1F4_4 *)point_packet)->unk_04.at02.v =
                        (u8)((((S_8187B1F4_4 *)point_packet)->unk_04.at02.v *
                        points->intensity.s) / points->divisor);
                    ((S_8187B1F4_4 *)point_packet)->unk_00.at03.v = 2;
                    ((S_8187B1F4_4 *)point_packet)->unk_04.at03.v = 0x6A;
                    ((PrimitiveTag *)point_packet)->addr =
                        ((PrimitiveTag *)((u8 *)VFIELD(scratch, void *, 0x24) +
                               VFIELD(scratch, u32, 0x100) * 4))->addr;
                    tail = (u8 *)(VFIELD(scratch, u32, 0x100) * 4);
                    tail += (u32)VFIELD(scratch, void *, 0x24);
                    ((PrimitiveTag *)tail)->addr = (u32)point_packet;
                    draw_mode_packet = global->cur->next;
                    global->cur->next = draw_mode_packet + 0xC;
                    SetDrawMode(draw_mode_packet, 0, 0,
                                  GetTPage(0, 1, 0, 0) & 0xFFFF, 0);
                    ((PrimitiveTag *)draw_mode_packet)->addr =
                        ((PrimitiveTag *)((u8 *)VFIELD(scratch, void *, 0x24) +
                               VFIELD(scratch, u32, 0x100) * 4))->addr;
                    tag_state = (GlobalState *)(VFIELD(scratch, u32, 0x100) * 4);
                    tag_state = (GlobalState *)((u8 *)tag_state +
                                                (u32)VFIELD(scratch, void *, 0x24));
                    ((PrimitiveTag *)tag_state)->addr = (u32)draw_mode_packet;
                    point_count = points->point_count;
                } else {
                    point_count = points->point_count;
                }
                point_index += 1;
            } while (point_index < point_count);
        }
        PopMatrix();
        tail_2 = NODE_HEADER(points)->chain_next;
        points = NODE_BODY(tail_2);
        if (tail_2 == 0) {
            break;
        }
        position = tail_2->position;
        sprite = tail_2->sprite;
    } while (1);
    return hard_zero;
}
#include "shared/object_flags.h"

/* Add the object increment to the target and flag completion when its countdown expires. */
void rotate_point_cloud_until_expired(RandomRadialVectorEffectBody *object, ObjectPosition *unused, SpriteFrameState *target) {
    RandomRadialVectorEffectBody *object_data = object;
    u8 *global_base = (u8 *)&point_cloud_update_flag - 0x694C;
    u16 remaining;

    target->angle_z += object_data->spin_rate;
    remaining = object_data->intensity.u - 0x20;
    *(s16 *)(global_base + 0x694C) = 1;
    object_data->intensity.u = remaining;
    if ((s16)remaining <= 0) {
        NODE_HEADER(object_data)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

#include "shared/gpu_packets.h"
#include "sdk/libgpu_types.h"
#include "sdk/libgpu_packets.h"
#include "engine/graphics/sprite_scratch.h"

extern u8 resident_globals_page[];
extern u32 RotTransPers();

/* Projects a colored point and links its drawing packets into the ordering table. */
s32 project_colored_point_to_ordering_table(TerrainSeekingColoredPointBody *render_data, ObjectPosition *position)
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

    context_slot = (GpuContext **)(resident_globals_page + 0x3160);
    context = *context_slot;
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

        depth_index = RotTransPers(&scratch->position, &point_packet->x0, &scratch->depth_cue,
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

/* Conditionally advances the position and decrements a counter, setting flags when it expires. */
void advance_colored_point_toward_terrain(TerrainSeekingColoredPointBody *object, ObjectPosition *position)
{
    s16 counter;

    s16 minimum_height = position->z.w.i + 2;
    u16 query_x = position->x.w.i;
    u16 query_y = position->y.w.i;

    *point_cloud_update_flag = 1;
    if (position->z.w.i < (s16)sample_terrain_surface_height(query_x, query_y, minimum_height)) {
        position->z.v += object->z_velocity;
    }

    counter = object->intensity - 4;
    object->intensity = counter;
    if ((counter << 16) <= 0) {
        NODE_HEADER(object)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
#include "shared/dungeon_moving_views.h"

#ifndef NULL
#define NULL 0
#endif

/* Creates an object at a randomized offset from the source and initializes its actor data. */
void create_terrain_seeking_colored_point(
    void *source,
    s32 field_04_value,
    s32 field_00_value,
    s16 paired_value,
    s16 x_offset,
    s16 y_offset,
    s32 z_offset)
{
    ObjectNodeHeader *source_obj = source;
    s16 saved_field_04 = field_04_value;
    u32 saved_field_00 = field_00_value;
    s16 saved_pair ;
    s32 saved_z_offset = z_offset;
    ObjectNodeHeader *spawned_obj;
    TerrainSeekingColoredPointBody *actor_data;
    s32 y_jitter;
    s32 z_jitter;
    s16 x_bias;
    s16 y_bias;
    s32 z_bias;
    s16 x_pos;
    s16 y_pos;
    s32 z_pos;
    ObjectPosition *x_dest;
    ObjectPosition *y_dest;
    ObjectPosition *z_dest;

    spawned_obj = allocate_list_node(0x211, &source_obj->next);
    if (spawned_obj != NULL) {
        saved_pair = paired_value;
        spawned_obj->update_callback = advance_colored_point_toward_terrain;
        z_offset = rand() & 0x1F;
        x_pos = source_obj->position->x.unsigned_parts.integer;
        x_dest = spawned_obj->position;
        x_pos += z_offset;
        x_bias = x_offset - 0x10;
        x_pos += x_bias;
        x_dest->x.w.i = (s16)x_pos;

        y_jitter = rand() & 0x1F;
        y_pos = source_obj->position->y.unsigned_parts.integer;
        y_dest = spawned_obj->position;
        y_pos += y_jitter;
        y_bias = y_offset - 0x10;
        y_pos += y_bias;
        y_dest->y.w.i = (s16)y_pos;

        z_jitter = rand();
        z_jitter &= 0x1F;
        z_pos = source_obj->position->z.unsigned_parts.integer;
        actor_data = NODE_BODY(spawned_obj);
        z_dest = spawned_obj->position;
        z_pos += z_jitter;
        z_bias = saved_z_offset - 0x10;
        z_pos += z_bias;
        z_dest->z.w.i = (s16)z_pos;
        actor_data->direction = saved_field_04;
        actor_data->intensity = saved_pair;
        actor_data->divisor = saved_pair;
        register_node(spawned_obj, project_colored_point_to_ordering_table);
        actor_data->z_velocity = rand() + 0x10000;
        actor_data->color = saved_field_00;
    }
}

#include "shared/dungeon_projectile_views.h"

#ifndef NULL
#define NULL 0
#endif


   /* r0 in func_800251E8 */

s32 rsin(s32);
s32 rcos(s32);

/* Create an effect with 23 random radial vectors and initialize its position and state. */
void create_random_radial_vector_effect(s32 radius, s32 initial_value, s16 extent, s32 position_x_word, s32 position_y_word, s32 position_z_word) {
    /* Retail accepts word arguments, then carries their low halves across calls. */
    u16 position_x = (u16)position_x_word;
    u16 position_y = (u16)position_y_word;
    u16 position_z = (u16)position_z_word;
    s32 point_count;
    s32 angle_a;
    s32 angle_b;
    s32 plane_radius;
    u32 component;
    ObjectPosition *position;
    ObjectNodeHeader *effect;
    RandomRadialVectorEffectBody *state;
    SpriteFrameState *scale;

    effect = allocate_flagged_object_node(0x212);
    if (effect != NULL) {
        point_count = 0;
        state = NODE_BODY(effect);
        do {
            angle_a = rand() & 0xFFF;
            angle_b = rand() & 0xFFF;
            plane_radius = (radius * rcos(angle_a)) >> 12;
            component = (plane_radius * rsin(angle_b)) >> 12;
            state->point_x[point_count] = component;
            component = (plane_radius * rcos(angle_b)) >> 12;
            state->point_y[point_count] = component;
            component = (radius * rsin(angle_a)) >> 12;
            state->point_z[point_count] = component;
            point_count++;
        } while (point_count < 0x17);
        position = effect->position;
        position->x.unsigned_parts.integer = position_x;
        position->y.unsigned_parts.integer = position_y;
        position->z.unsigned_parts.integer = position_z;
        scale = effect->sprite;
        scale->scale_y = 0x1000;
        scale->scale_x = 0x1000;
        state->point_count = 0x17;
        effect->update_callback = rotate_point_cloud_until_expired;
        state->spin_rate = (rand() & 0x3F) + 0x3C;
        state->intensity.s = extent;
        state->divisor = extent;
        register_node(effect, project_shaded_points_to_ordering_table);
        state->color = initial_value;
    }
}


/* Advance the effect animation, fade its colors, and mark it for removal when its lifetime ends. */
void advance_fading_effect_animation(StarEdgeEffectBody *effect_data, ObjectPosition *unused_arg, SpriteFrameState *color_data) {
    SpriteFrameState *colors = color_data;
    register s32 tick_limit;
    s32 phase_state;

    point_cloud_update_flag[0] = 1;
    effect_data->remaining_ticks--;

    if (effect_data->unk_40.at00.v == 0) {
        s32 mid_y;
        u16 mid_x;

        effect_data->tip_x =
            (effect_data->end_x + effect_data->quad_x0) / 2;
        mid_y = (effect_data->end_y + effect_data->quad_y0) / 2;
        effect_data->tip_y = mid_y;
        mid_x = *(u16 *)((u8 *)effect_data + 0x20);
        effect_data->quad_y3 = mid_y;
        effect_data->quad_y1 = mid_y;
        effect_data->quad_x3 = mid_x;
        effect_data->quad_x1 = mid_x;
    }

    phase_state = effect_data->unk_40.at00.v;
    tick_limit = 1;
    if (phase_state == tick_limit) {
        effect_data->tip_x =
            (effect_data->end_x + effect_data->quad_x0) / 2;
        effect_data->tip_x =
            (effect_data->end_x + effect_data->tip_x) / 2;
        effect_data->tip_y =
            (effect_data->end_y + effect_data->quad_y0) / 2;
        effect_data->tip_y =
            (effect_data->end_y + effect_data->tip_y) / 2;
        effect_data->quad_x1 = effect_data->quad_x3 =
            effect_data->tip_x;
        effect_data->quad_y1 = effect_data->quad_y3 =
            effect_data->tip_y;
    }

    if (effect_data->unk_40.at00.v == 0x10000) {
        u32 start_x = (u16)effect_data->end_x;
        u32 start_y = (u16)effect_data->end_y;

        effect_data->quad_x3 = start_x;
        effect_data->quad_x1 = start_x;
        effect_data->quad_y3 = start_y;
        effect_data->quad_y1 = start_y;
    }

    if (effect_data->unk_40.at00u.v == tick_limit) {
        s32 phase;
        effect_data->unk_40.at00u.v = 0;
        phase = effect_data->unk_40.at02.v;
        switch (phase) {
        case 0:
        effect_data->unk_40.at02.v = 1;
        break;

        case 1:
        effect_data->unk_40.at02.v = 2;
        effect_data->texture_u += 0x20;
        break;

        case 2:
        effect_data->unk_40.at02.v = 3;
        effect_data->texture_u += 0x20;
        break;

        case 3:
        effect_data->unk_40.at02.v = 4;
        effect_data->texture_u += 0x20;
        break;

        case 4:
        effect_data->unk_40.at02.v = 5;
        effect_data->texture_u = 0x80;
        effect_data->texture_v += 0x20;
        break;

        case 5:
        effect_data->unk_40.at02.v = 6;
        effect_data->texture_u += 0x20;
        break;

        case 6:
        effect_data->unk_40.at02.v = 7;
        effect_data->texture_u += 0x20;
        break;

        case 7:
        effect_data->texture_width = 0;
        effect_data->texture_height = 0;
        colors->color.c.g = 0xFF;
        colors->color.c.r = 0xFF;
        colors->color.c.b = 0;
        effect_data->base_green = 0xFF;
        effect_data->base_red = 0xFF;
        effect_data->base_blue = 0;
        colors->flags |= 0xC;
        break;
        case 8:
        default:
            break;
        }
    } else {
        effect_data->unk_40.at00p.v++;
    }

    if ((s16)effect_data->remaining_ticks < 30) {
        colors->color.c.r =
            (effect_data->base_red * (s16)effect_data->remaining_ticks) / 30;
        colors->color.c.g =
            (effect_data->base_green * (s16)effect_data->remaining_ticks) / 30;
        colors->color.c.b =
            (effect_data->base_blue * (s16)effect_data->remaining_ticks) / 30;
    }

    if ((s16)effect_data->remaining_ticks <= 0) {
        (*(u16 *)((u8 *)effect_data + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}




/* Advance the effect fade, scale primitive colors, and flag completion. */
void update_projectile_trail_flash(ProjectileTrailFlashBody *effect, s32 unused, SpriteFrameState *primitive)
{
    s16 phase;

    point_cloud_update_flag[0] = 1;
    effect->remaining_ticks--;

    phase = effect->flicker_phase;
    switch (phase) {
    case 0:
        effect->flicker_phase = 1;
        effect->texture_u += 24;
        break;
    case 1:
        effect->flicker_phase = 0;
        effect->texture_u -= 24;
        break;
    }

    primitive->color.c.r =
        effect->base_red * effect->remaining_ticks /
        effect->duration;
    primitive->color.c.g =
        effect->base_green * effect->remaining_ticks /
        effect->duration;
    primitive->color.c.b =
        effect->base_blue * effect->remaining_ticks /
        effect->duration;

    if (effect->remaining_ticks <= 0) {
        NODE_HEADER(effect)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }

    if (primitive->flags & 0x8000) {
        NODE_HEADER(effect)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}


typedef struct {
    u8 bytes[12];
} Data12;

extern s32 rsin(s32);
extern s32 rcos(s32);

/* Initializes a five-point star and spawns its edge effects over successive updates. */
void initialize_star_effect_sequence(StarSequenceBody *state_data, ObjectPosition *source_position) {
    ObjectNodeHeader *node;
    StarEdgeEffectBody *edge_data;
    SpriteFrameState *sprite;
    ObjectPosition *dest_position;
    u8 *globals_page = (u8 *)0x80020000;
    s32 vertex_index;
    s32 angle_offset;
    s16 blended_coord;
    s32 mode;

    mode = state_data->mode;
    *(s16 *)((u8 *)&point_cloud_update_flag) = 1;

    switch (mode) {
    default:
        return;
    case 0:
        vertex_index = 0;
        do {
            angle_offset = (vertex_index << 12) / 5;
            state_data->x[vertex_index] =
                (state_data->radius *
                 rcos(state_data->base_angle + angle_offset)) >> 12;
            state_data->y[vertex_index] =
                (state_data->radius *
                 rsin(state_data->base_angle + angle_offset)) >> 12;
            vertex_index++;
        } while (vertex_index < 5);

        state_data->edge_index = 0;
        state_data->frame = 0;
        state_data->mode++;
                        /* fallthrough */
    case 1:
        if (state_data->frame == 0) {
            state_data->frame++;
            node = allocate_flagged_object_node(0x212);
            if (node == 0) {
                break;
            }

            edge_data = NODE_BODY(node);
            edge_data->remaining_ticks = 0x37 - (state_data->edge_index * 4);
            node->update_callback = advance_fading_effect_animation;
            register_node(node, draw_chained_mesh_records);

            sprite = node->sprite;
            sprite->flags &= 0xFFF3;

            dest_position = node->position;
            dest_position->x.w.i = source_position->x.w.i;
            dest_position->y.w.i = source_position->y.w.i;
            dest_position->z.w.i = source_position->z.w.i;

            switch (state_data->edge_index) {
            case 0:
                edge_data->quad_x0 = edge_data->quad_x2 =
                    state_data->x[0];
                edge_data->quad_x1 = edge_data->quad_x3 =
                    state_data->x[2];
                edge_data->quad_y0 = edge_data->quad_y2 =
                    state_data->y[0];
                {
                    u16 next_coord = state_data->y[2];

                    edge_data->quad_z0 = edge_data->quad_z1 = 0;
                    edge_data->quad_z2 = edge_data->quad_z3 = 0x18;
                    edge_data->quad_y1 = edge_data->quad_y3 = next_coord;
                }
                break;
            case 1:
                edge_data->quad_x0 = edge_data->quad_x2 =
                    state_data->x[2];
                edge_data->quad_x1 = edge_data->quad_x3 =
                    state_data->x[4];
                edge_data->quad_y0 = edge_data->quad_y2 =
                    state_data->y[2];
                {
                    u16 next_coord = state_data->y[4];

                    edge_data->quad_z0 = edge_data->quad_z1 = 0;
                    edge_data->quad_z2 = edge_data->quad_z3 = 0x18;
                    edge_data->quad_y1 = edge_data->quad_y3 = next_coord;
                }
                break;
            case 2:
                edge_data->quad_x0 = edge_data->quad_x2 =
                    state_data->x[4];
                edge_data->quad_x1 = edge_data->quad_x3 =
                    state_data->x[1];
                edge_data->quad_y0 = edge_data->quad_y2 =
                    state_data->y[4];
                {
                    u16 next_coord = state_data->y[1];

                    edge_data->quad_z0 = edge_data->quad_z1 = 0;
                    edge_data->quad_z2 = edge_data->quad_z3 = 0x18;
                    edge_data->quad_y1 = edge_data->quad_y3 = next_coord;
                }
                break;
            case 3:
                edge_data->quad_x0 = edge_data->quad_x2 =
                    state_data->x[1];
                edge_data->quad_x1 = edge_data->quad_x3 =
                    state_data->x[3];
                edge_data->quad_y0 = edge_data->quad_y2 =
                    state_data->y[1];
                {
                    u16 next_coord = state_data->y[3];

                    edge_data->quad_z0 = edge_data->quad_z1 = 0;
                    edge_data->quad_z2 = edge_data->quad_z3 = 0x18;
                    edge_data->quad_y1 = edge_data->quad_y3 = next_coord;
                }
                break;
            case 4:
                edge_data->quad_x0 = edge_data->quad_x2 =
                    state_data->x[3];
                edge_data->quad_x1 = edge_data->quad_x3 =
                    state_data->x[0];
                edge_data->quad_y0 = edge_data->quad_y2 =
                    state_data->y[3];
                {
                    u16 next_coord = state_data->y[0];

                    edge_data->quad_z0 = edge_data->quad_z1 = 0;
                    edge_data->quad_z2 = edge_data->quad_z3 = 0x18;
                    edge_data->quad_y1 = edge_data->quad_y3 = next_coord;
                }
                break;
            default:
                break;
            }

            edge_data->end_x = edge_data->quad_x1;
            edge_data->end_y = edge_data->quad_y1;

            blended_coord = (edge_data->end_x + edge_data->quad_x0) / 2;
            edge_data->tip_x = blended_coord;
            blended_coord = (blended_coord + edge_data->quad_x0) / 2;
            edge_data->tip_x = blended_coord;

            blended_coord = (edge_data->end_y + edge_data->quad_y0) / 2;
            edge_data->tip_y = blended_coord;
            blended_coord = (blended_coord + edge_data->quad_y0) / 2;
            edge_data->tip_y = blended_coord;

            edge_data->quad_x1 = edge_data->quad_x3 =
                edge_data->tip_x;
            edge_data->quad_y1 = edge_data->quad_y3 =
                edge_data->tip_y;

            sprite = node->sprite;
            sprite->color.c.r = sprite->color.c.g = 0xE0;
            sprite->color.c.b = 0x20;
            edge_data->base_red = edge_data->base_green = 0xE0;
            edge_data->base_blue = 0x20;
            sprite->scale_x = sprite->scale_y = 0x1000;

            *(Data12 *)((u8 *)edge_data + 0x44) = *(Data12 *)mesh_edge_payload_template;
            sprite->source = (u8 *)edge_data + 0x44;
            return;
        } else {
            state_data->frame++;
            if (state_data->frame >= 4) {
                state_data->frame = 0;
                state_data->edge_index++;
                if (state_data->edge_index >= 5) {
                    NODE_HEADER(state_data)->flags |= NODE_REMOVE;
                    object_flag_block.flags |= OBJECT_REMOVE_PENDING;
                }
            }
            break;
        }
    }
}


#include "shared/entity_height_offsets.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"

typedef struct { u8 b[12]; } AggU12;

typedef struct {
    s16 x;
    u16 y;
} Point __attribute__((packed));

typedef struct {
    Point p[8];
} PointTable __attribute__((packed));

typedef struct {
    u32 w[3];
} Copy12 __attribute__((packed));

typedef struct {
    u8 pad[0x98];
    Copy12 copy;
} PackedArg0 __attribute__((packed));

typedef struct {
    u8 pad[0x64];
    Copy12 copy;
} PackedSpawn __attribute__((packed));

const PointTable projectile_direction_steps = {{{32,0},{32,32},{0,32},{-32,32},{-32,0},{-32,65504},{0,65504},{32,65504}}};
extern Copy12 projectile_trail_sprite_source;
extern u8 D_8007CCD8[];

#define U8(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U32(p, o) (*(u32 *)((u8 *)(p) + (o)))
#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PTR(p, o) (*(void **)((u8 *)(p) + (o)))

/* Update a projectile effect, its trail, and the target hit animation. */
void update_projectile_trail_and_hit_effect(ProjectileEffect *effect, ObjectPosition *motion, SpriteFrameState *sprite) {
    u16 origin_offset[4];
    PointTable direction_steps;
    ActorRecord *owner;
    ObjectNodeHeader *object;
    void *object_data;
    void *effect_object;
    SpriteFrameState *owner_sprite;
    SpriteFrameState *origin_sprite;
    SpriteFrameState *target_data;
    u16 offset_value;
    SpriteFrameState *spawn_sprite;
    void *hit_target;
    void *target;
    u16 render_flags;
    s32 trail_color;
    s32 state_index;
    s32 particle_index;
    s32 finish_tick;
    s32 particle_color;
    s32 effect_busy;
    s32 fade_out_tick;
    s32 target_tick;
    s32 blue_scaled;
    s32 green_scaled;
    s32 red_scaled;
    s32 owner_z;
    s32 effect_z;
    s32 tile_distance;

    owner = effect->owner;
    direction_steps = projectile_direction_steps;
    state_index = effect->state;
    object = NODE_HEADER(owner);
    object_data = object->position;

    switch (state_index) {

    case 0:
        sprite->color.word = 0x00808080;
        sprite->scale_y = 0x1000;
        sprite->scale_x = 0x1000;
        *(AggU12 *)((u8 *)effect + 0x98) = *(AggU12 *)&projectile_trail_sprite_source;
        sprite->source = (u8 *)effect + 0x98;
        {
            u16 facing = owner->facing;
            point_cloud_update_flag[0] = 1;
            effect->direction = (facing >> 9) & 7;
        }
        effect->state += 1;

    case 1:
        origin_sprite = object->sprite;
        if (get_sprite_attachment_vector(origin_sprite->source, origin_sprite, origin_offset, 0) == 0) {
            if (!(object->sprite->flags & 0x8000)) {
                return;
            }
        }

        motion->x.w.i = U16(object_data, 2);
        motion->y.w.i = U16(object_data, 6);
        owner_z = U16(object_data, 0xA);
        motion->z.w.i = owner_z;
        if (!(object->sprite->flags & 0x8000)) {
            motion->x.w.i = (u16)motion->x.w.i + origin_offset[0];
            motion->y.w.i = (u16)motion->y.w.i + origin_offset[1];
            effect_z = (u16)motion->z.w.i + origin_offset[2];
            motion->z.w.i = effect_z;
        } else {
            motion->z.w.i = owner_z - 0x40;
        }

        if (!(effect->animation->flags & 0x80)) {
            return;
        }

        if (!(effect->flags & 4)) {
            effect_object = (u8 *)effect - 0x20;
            register_node(effect_object, project_sprite_chain);
            sprite->tpage_abr = 0x20;
            sprite->color.c.g = 0x80;
            sprite->color.c.r = 0x80;
            sprite->color.c.b = 0x20;
            sprite->flags |= 0xC;
            effect->flags |= 4;
        }

        hit_target = owner->target;
        offset_value = 0x10;
        if (hit_target != 0) {
            object = PTR(hit_target, -0x18);
            effect->target_x = U16(object, 2);
            effect->target_y = U16(object, 6);
            {
                s32 height = entity_height_offsets[U8(owner->target, 0x13)] + 0x20;
                effect->target_z = U16(object, 0xA) - height;
            }
            owner_sprite = PTR(owner, -0x14);
            effect->next_tile_x = owner_sprite->tile_x + *(u8 *)&dir_step_x[effect->direction];
            effect->next_tile_y = owner_sprite->tile_y + *(u8 *)&dir_step_y[effect->direction];
            {
                s32 grid;
                tile_distance = owner->target_tile_x;
                grid = owner_sprite->tile_x;
                if (tile_distance != grid) {
                    tile_distance -= grid;
                } else {
                    tile_distance = owner->target_tile_y;
                    grid = owner_sprite->tile_y;
                    tile_distance -= grid;
                }
            }
            if (tile_distance < 0) {
                tile_distance = -tile_distance;
            }
            effect->travel_ticks = tile_distance * 2 - 1;
        } else {
            effect->travel_ticks = (u32)offset_value;
            offset_value = (u16)direction_steps.p[effect->direction].x << 4;
            {
                s16 travel_ticks;
                u16 y_step;
                effect->target_x = (u16)motion->x.w.i + (u32)offset_value;
                y_step = direction_steps.p[effect->direction].y;
                travel_ticks = (u8)effect->travel_ticks;
                travel_ticks = (s8)travel_ticks;
                effect->target_y = (u16)motion->y.w.i + y_step * (s8)travel_ticks;
            }
            effect->target_z = owner->ground_height - 0x50;
        }

        motion->velocity_x = direction_steps.p[effect->direction].x << 16;
        motion->velocity_y = direction_steps.p[effect->direction].y << 16;
        motion->velocity_z = ((effect->target_z << 16) - motion->z.v) / effect->travel_ticks;
        effect->timer = 0;
        effect->state += 1;
        return;

    case 2:
        trail_color = 0x60;
        do {
            ProjectileTrailFlashBody *flash;
            object = allocate_flagged_object_node(0x12);
            flash = NODE_BODY(object);
            if (object != 0) {
                flash->remaining_ticks = 8;
                flash->duration = 8;
                object->update_callback = update_projectile_trail_flash;
                register_node(object, project_sprite_chain);

                spawn_sprite = object->sprite;

                spawn_sprite->tpage_abr = 0x20;
                spawn_sprite->flags |= 0xC;
                {
                    ObjectPosition *spawn_pos = object->position;
                    spawn_pos->x.w.i = (u16)motion->x.w.i;
                    spawn_pos->y.w.i = (u16)motion->y.w.i;
                    spawn_pos->z.w.i = (u16)motion->z.w.i;
                }
                spawn_sprite = object->sprite;
                spawn_sprite->scale_y = 0x1000;
                spawn_sprite->scale_x = 0x1000;
                spawn_sprite->color.c.g = trail_color;
                spawn_sprite->color.c.r = trail_color;
                spawn_sprite->color.c.b = 0x10;
                flash->base_blue = 0x10;
                flash->base_green = trail_color;
                flash->base_red = trail_color;
                *(AggU12 *)((u8 *)object + 0x64) = *(AggU12 *)&projectile_trail_sprite_source;
                spawn_sprite->source = (u8 *)object + 0x64;
            }

            if ((s16)check_adjacent_tile_height_clearance((u16)motion->x.w.i, (u16)motion->y.w.i, motion->z.w.i,
                                   owner->target) != 0) {
                {
                    effect->state = 7;
                    effect->timer = 0;
                    render_flags = sprite->flags;
                    render_flags |= 0x80;
                    sprite->flags = render_flags;
                    return;
                }
            }

            effect->travel_ticks = effect->travel_ticks - 1;
            if (effect->travel_ticks <= 0) {
                if (owner->target != 0) {
                    {
                        effect->state = 3;
                        effect->timer = 0;
                        object = PTR(owner->target, -0x18);
                        motion->x.w.i = U16(object, 2);
                        motion->y.w.i = U16(object, 6);
                        motion->z.w.i = effect->target_z;
                        play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
                        return;
                    }
                }
                effect->state = 7;
                effect->timer = 0;
                render_flags = sprite->flags;
                sprite->color.c.b = 0;
                sprite->color.c.g = 0;
                sprite->color.c.r = 0;
                render_flags |= 0x80;
                sprite->flags = render_flags;
                return;
            }

            motion->velocity_x = ((effect->target_x << 16) - motion->x.v) / effect->travel_ticks;
            motion->velocity_y = ((effect->target_y << 16) - motion->y.v) / effect->travel_ticks;
            motion->velocity_z = ((effect->target_z << 16) - motion->z.v) / effect->travel_ticks;
            motion->x.v += motion->velocity_x;
            motion->y.v += motion->velocity_y;
            motion->z.v += motion->velocity_z;
        } while (1);

    case 3:
        if (effect->impact_phase == 0) {
            effect->impact_phase = 1;
            effect->sprite_data.unk_A0 = effect->sprite_data.unk_A0 + 0x18;
        } else {
            effect->impact_phase = 0;
            effect->sprite_data.unk_A0 = effect->sprite_data.unk_A0 - 0x18;
        }

        object = allocate_flagged_object_node(0x12);
        object_data = NODE_BODY(object);
        if (object != 0) {
            U16(object_data, 2) = 8;
            U16(object_data, 4) = 8;
            U16(object_data, 0xA) = 0x30;
            S16(object_data, 0xC) = -0xDE;
            object->update_callback = initialize_star_effect_sequence;
            spawn_sprite = object->sprite;
            spawn_sprite->tpage_abr = 0x20;
            spawn_sprite->flags |= 0xC;
            {
                ObjectPosition *spawn_pos = object->position;
                spawn_pos->x.w.i = (u16)motion->x.w.i;
                spawn_pos->y.w.i = (u16)motion->y.w.i;
                spawn_pos->z.w.i = (u16)motion->z.w.i;
            }
            *(AggU12 *)((u8 *)object + 0x64) = *(AggU12 *)&mesh_edge_payload_template;
            spawn_sprite->source = (u8 *)object + 0x64;
        }
        effect->blue = 0;
        effect->green = 0;
        effect->red = 0;
        effect->state = 4;
        effect->timer = 0;
        return;

    case 4:
    {
        u16 next_tick = effect->timer + 1;
        fade_out_tick = (s16)next_tick;
        effect->timer = next_tick;
    }
        if (fade_out_tick < 0x14) {
            sprite->color.c.r = ((0x14 - fade_out_tick) * 0xE0) / 0x14;
            sprite->color.c.g = ((0x14 - effect->timer) * 0xE0) / 0x14;
            sprite->color.c.b = ((0x14 - effect->timer) * 0x20) / 0x14;
            if (effect->impact_phase == 0) {
                effect->impact_phase = 1;
                effect->sprite_data.unk_A0 = effect->sprite_data.unk_A0 + 0x18;
            } else {
                effect->impact_phase = 0;
                effect->sprite_data.unk_A0 = effect->sprite_data.unk_A0 - 0x18;
            }

            particle_index = 0;
loop_0:
            {
                particle_color = rand();
                {
                    s32 base_color;
                    s32 brightness;
                    target = (u8 *)effect - 0x20;
                    base_color = 0x0020E0E0;
                    particle_color &= 0xFF;
                    brightness = particle_color | 0x80;
                    create_terrain_seeking_colored_point(target, effect->direction, base_color, brightness, 0, 0, 0);
                }
                particle_index += 1;
            }
            if (particle_index < 4)
                goto loop_0;
            return;

        }

        effect->timer = 0;
        effect->state += 1;
        return;

    case 5:
        effect->timer++;
        blue_scaled = effect->timer * 0x20;
        effect->blue = blue_scaled / 0x28;
        green_scaled = effect->timer * 8;
        green_scaled = (green_scaled - effect->timer) * 32;
        effect->green = green_scaled / 0x28;
        red_scaled = effect->timer * 8;
        red_scaled = (red_scaled - effect->timer) * 32;
        effect->red = red_scaled / 0x28;

        object = PTR(owner->target, -0x18);
        for (particle_index = 0; particle_index < 2; particle_index++) {
            particle_color = (effect->blue << 16) + (effect->green << 8) + effect->red;
            create_random_radial_vector_effect((entity_height_offsets[U8(owner->target, 0x13)] >> 1) + 4,
                          particle_color, 0x80, S16(object, 2), S16(object, 6),
                          (s16)(U16(object, 0xA) -
                                (entity_height_offsets[U8(owner->target, 0x13)] >> 1)));
        }
        if (effect->timer >= 0x28) {
            effect->timer = 0;
            effect->state += 1;
            return;
        }
        return;

    case 6:
    {
        u16 next_tick = effect->timer + 1;
        target_tick = (s16)next_tick;
        effect->timer = next_tick;
    }
        if (target_tick >= 0x24) {
            effect->blue = ((0x46 - target_tick) * 0x20) / 0x23;
            effect->green = ((0x46 - effect->timer) * 0xE0) / 0x23;
            effect->red = ((0x46 - effect->timer) * 0xE0) / 0x23;
        }

        object = PTR(owner->target, -0x18);
        for (particle_index = 0; particle_index < 2; particle_index++) {
            particle_color = (effect->blue << 16) + (effect->green << 8) + effect->red;
            create_random_radial_vector_effect((entity_height_offsets[U8(owner->target, 0x13)] >> 1) + 4,
                          particle_color, 0x80, S16(object, 2), S16(object, 6),
                          (s16)(U16(object, 0xA) -
                                (entity_height_offsets[U8(owner->target, 0x13)] >> 1)));
        }

        target = owner->target;
        U32(target, 0x1C) |= 0x10000000;
        target_data = PTR(target, -0x14);
        if (effect->timer >= 0x24) {
            target_data->color.c.r -= 3;
            target_data->color.c.g -= 3;
            target_data->color.c.b += 2;
        } else {
            target_data->color.c.r += 3;
            target_data->color.c.g += 3;
            target_data->color.c.b -= 2;
        }
        if (effect->timer < 0x46) {
            return;
        }

        {
            void *released = owner->target;
            target_data = PTR(released, -0x14);
            U32(released, 0x1C) &= 0xEFFFFFFF;
        }
        target_data->color.c.b = 0x80;
        target_data->color.c.g = 0x80;
        target_data->color.c.r = 0x80;
        try_apply_wind_protection(owner->target, effect->variant, owner);
        effect->timer = 0x14;
        effect->state += 1;
        return;

    case 7:
        finish_tick = (u16)effect->timer;
        effect->timer = finish_tick + 1;
        if ((s16)finish_tick < 0x15) {
            return;
        }
        effect_busy = point_cloud_update_flag[0];
        effect->timer = finish_tick;
        if (effect_busy == 0) {
            S32(D_8007CCD8 + 13096, 0x346C) = 0;
            U16(effect, -2) |= 0x8000;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
            return;
        }
        {
            point_cloud_update_flag[0] = 0;

            return;
        }
    default:
        return;
    }
}
