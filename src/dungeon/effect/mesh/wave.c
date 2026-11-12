#include "shared/object_node_flags.h"
#include "shared/audio_commands.h"
/* Wave-displaced sprite strips, shaded particles, timed fades, and projectile impact effects. */
#include "shared/sprite_frame_state.h"
#include "modules/dungeon_ovl_1918800.h"
#include "common.h"
#include "slus/data.h"
#include "dungeon/system/random.h"
#include "dungeon/actor.h"
#include "dungeon/effect/mesh.h"
#include "engine/graphics.h"
#include "sdk/libc.h"
#include "sdk/libgpu.h"
#include "sdk/libgte.h"
#include "sdk/libgte_matrix.h"
#include "sdk/libgpu_packets.h"
#include "engine/graphics/sprite_scratch.h"
#include "shared/gpu_packets.h"
#include "shared/sprite_part_command.h"
#include "shared/object_node.h"
#include "dungeon/system.h"

void (*const dungeon_1918800_entry)(struct ProjectileSelf *self, struct ObjectPosition *position, struct SpriteFrameState *render_data) = set_record_pair_to_one;
const PackedVector wave_texture_rect = {832,340,96,84};
const PackedVector wave_source_rect = {832,256,96,84};
const Copy24 wave_direction_steps = {{{32,0},{32,32},{0,32},{-32,32},{-32,0},{-32,65504},{0,65504},{32,65504}}};
/* cfail-repair: tf7-phase1-cache-v3 */
#include "shared/game_work.h"

extern void func_80067EF4(void *, s32, s32);

/* Draw sprite parts as textured strips displaced by a wave along either axis. */
void draw_wave_distorted_sprite(WaveScreenOrigin *screen_pos, ParticleState *wave, void *context, u32 *ordering_table, s32 draw_control)
{
    POLY_FT4 base_quad;
    POLY_FT4 strip_quad;
    u16 saved_draw_control;
    ObjectPosition *callback_arg;
    SpritePartCommand *part;
    s32 tag_mask;
    s16 flipped_x;
    s16 start_x;
    s16 end_x;
    s16 flipped_y;
    s16 start_y;
    s16 end_y;
    s32 phase;
    s32 row_phase;
    s32 column_phase;
    SpritePartCallback draw_part;
    u32 *row_link;
    u32 *column_link;
    u32 *start_link;
    u32 *end_link;
    POLY_FT4 *end_packet;
    POLY_FT4 *packet;
    s32 texture_right;
    s32 texture_bottom;
    u16 projected_y;
    u16 screen_y;
    s32 origin_x;
    s32 origin_y;
    u16 next_y;
    u16 sprite_flags;
    u16 clut_base;
    u16 texture_page;
    u16 next_x;
    u8 part_command;
    u8 right_u;
    u8 bottom_v;
    u8 draw_command;
    SpriteFrameState *sprite;
    GameWork *globals;
    MATRIX *view_matrix;
    u32 screen_link;
    s32 wave_index;
    SpriteQuadScratch *scratch;
    globals = &g_game_work;
    sprite = NODE_HEADER(context)->sprite;
    part = sprite->source;
    callback_arg = NODE_HEADER(context)->position;
    scratch = (SpriteQuadScratch *) 0x1F800000;
    scratch->local_matrix.t[2] = 0;
    scratch->vertices[3].vz = 0;
    scratch->vertices[2].vz = 0;
    scratch->vertices[1].vz = 0;
    scratch->vertices[0].vz = 0;
    packet = ((GpuContext *) g_game_work.draw_buffer)->packetCursor;
    scratch->ordering_table = ordering_table;
    scratch->sort_depth = 0;
    scratch->screen_origin.x = screen_pos->x - 0xA0;
    scratch->screen_origin.y = screen_pos->y - 0x78;
    saved_draw_control = draw_control;
    tag_mask = 0;
    if ((draw_control << 0x10) != 0) {
        func_80067EF4(packet, 0, 0);
        tag_mask = 0xFF000000;
        packet->tag = (packet->tag & 0xFF000000) | (*scratch->ordering_table & 0xFFFFFF);
        start_link = scratch->ordering_table;
        screen_link = (u32) packet & 0xFFFFFF;
        packet = (POLY_FT4 *) ((u32 *) packet + 3);
        *start_link = (*start_link & 0xFF000000) | screen_link;
    }
    view_matrix = &effect_view_matrix;
    view_matrix->t[2] = globals->view.projection_distance;
    PushMatrix();
    scratch->input.vx = globals->view.camera_rotation.parts.camera_rotation_x;
    scratch->input.vy = globals->view.camera_rotation.parts.camera_rotation_y;
    scratch->input.vz = globals->view.camera_rotation.parts.viewAngle;
    scratch->angles.vx = sprite->angle_x;
    scratch->angles.vz = sprite->angle_z - scratch->input.vy;
    scratch->angles.vy = (s16) ((((scratch->input.vz + 0x100) & 0x1FF) - 0x100) + sprite->angle_y);
    origin_x = sprite->offset_x;
    scratch->local_matrix.t[0] = origin_x;
    scratch->extent_x = origin_x;
    origin_y = sprite->offset_y;
    scratch->local_matrix.t[1] = origin_y;
    scratch->extent_y = origin_y;
    RotMatrix(&scratch->angles, &scratch->local_matrix);
    scratch->input.vx = sprite->scale_x;
    scratch->input.vy = sprite->scale_y;
    scratch->input.vz = 0x1000;
    ScaleMatrix(&scratch->local_matrix, &scratch->input);
    CompMatrix(view_matrix, &scratch->local_matrix, &scratch->matrix);
    SetTransMatrix(&scratch->matrix);
    SetRotMatrix(&scratch->matrix);
    scratch->sprite_flags = sprite->flags;
    for (;;) {
        if (!(part->flags & 0x20)) {
            scratch->uv_u_start = part->data.texture.u0;
            scratch->uv_v_start = part->data.texture.v0;
            scratch->uv_u_extent = part->data.texture.width;
            scratch->uv_v_extent = part->data.texture.height;
            if ((part->flags ^ scratch->sprite_flags) & 1) {
                flipped_x = (0 - part->offset_x) - scratch->extent_x;
                scratch->vertices[2].vx = flipped_x;
                scratch->vertices[0].vx = flipped_x;
                end_x = flipped_x - scratch->uv_u_extent;
                scratch->vertices[3].vx = end_x;
                scratch->vertices[1].vx = end_x;
            }
            else {
                start_x = part->offset_x - scratch->extent_x;
                scratch->vertices[2].vx = start_x;
                scratch->vertices[0].vx = start_x;
                end_x = start_x + scratch->uv_u_extent;
                scratch->vertices[3].vx = end_x;
                scratch->vertices[1].vx = end_x;
            }
            if ((part->flags ^ scratch->sprite_flags) & 2) {
                flipped_y = (0 - part->offset_y) - scratch->extent_y;
                scratch->vertices[1].vy = flipped_y;
                scratch->vertices[0].vy = flipped_y;
                end_y = flipped_y - scratch->uv_v_extent;
                scratch->vertices[3].vy = end_y;
                scratch->vertices[2].vy = end_y;
            }
            else {
                start_y = part->offset_y - scratch->extent_y;
                scratch->vertices[1].vy = start_y;
                scratch->vertices[0].vy = start_y;
                end_y = start_y + scratch->uv_v_extent;
                scratch->vertices[3].vy = end_y;
                scratch->vertices[2].vy = end_y;
            }
            RotTransPers4(&scratch->vertices[0], &scratch->vertices[1], &scratch->vertices[2], &scratch->vertices[3],
                (s32 *) &scratch->projected_vertices[0], (s32 *) &scratch->projected_vertices[1],
                (s32 *) &scratch->projected_vertices[2], (s32 *) &scratch->projected_vertices[3],
                &scratch->depth_cue, &scratch->gte_flag);
            packet->x0 = scratch->projected_vertices[0].x + scratch->screen_origin.x;
            packet->y0 = scratch->projected_vertices[0].y + scratch->screen_origin.y;
            packet->x1 = scratch->projected_vertices[1].x + scratch->screen_origin.x;
            packet->y1 = scratch->projected_vertices[1].y + scratch->screen_origin.y;
            packet->x2 = scratch->projected_vertices[2].x + scratch->screen_origin.x;
            packet->y2 = scratch->projected_vertices[2].y + scratch->screen_origin.y;
            packet->x3 = scratch->projected_vertices[3].x + scratch->screen_origin.x;
            projected_y = scratch->projected_vertices[3].y;
            screen_y = scratch->screen_origin.y;
            ((GpuLinkTag *) &packet->tag)->len = 9;
            packet->y3 = projected_y + screen_y;
            texture_right = scratch->uv_u_extent + (scratch->uv_u_start - 1);
            scratch->uv_u_extent = texture_right;
            if (texture_right & 0x100) {
                scratch->uv_u_extent = texture_right - 1;
            }
            texture_bottom = scratch->uv_v_extent + (scratch->uv_v_start - 1);
            scratch->uv_v_extent = texture_bottom;
            if (texture_bottom & 0x100) {
                scratch->uv_v_extent = texture_bottom - 1;
            }
            scratch->uv_v_extent <<= 8;
            scratch->uv_v_start <<= 8;
            clut_base = sprite->clut;
            if (clut_base != 0) {
                if (scratch->sprite_flags & 0x100) {
                    packet->clut = clut_base;
                }
                else {
                    packet->clut = clut_base + part->clut;
                }
            }
            else {
                packet->clut = part->clut;
            }
            /* BYTES: retail writes the packet u/v byte pair with one sh of the combined value; storing u and v separately compiles to two sb */
            *(s16 *) &packet->u0 = scratch->uv_v_start + scratch->uv_u_start;
            /* BYTES: retail writes the packet u/v byte pair with one sh of the combined value; storing u and v separately compiles to two sb */
            *(s16 *) &packet->u1 = scratch->uv_v_start + scratch->uv_u_extent;
            texture_page = sprite->tpage_abr;
            if (texture_page != 0) {
                packet->tpage = texture_page + (part->tpage & 0xFF9F);
            }
            else {
                packet->tpage = part->tpage;
            }
            /* BYTES: retail writes the packet u/v byte pair with one sh of the combined value; storing u and v separately compiles to two sb */
            *(s16 *) &packet->u2 = scratch->uv_v_extent | scratch->uv_u_start;
            /* BYTES: retail writes the packet u/v byte pair with one sh of the combined value; storing u and v separately compiles to two sb */
            *(s16 *) &packet->u3 = scratch->uv_v_extent | scratch->uv_u_extent;
            if (packet->x0 > packet->x3) {
                right_u = packet->u3;
                packet->u3 = right_u + 0xFF;
                packet->u1 = right_u;
            }
            if (packet->y0 > packet->y3) {
                bottom_v = packet->v3;
                packet->v3 = bottom_v + 0xFF;
                packet->v2 = bottom_v;
            }
            part_command = part->code;
            sprite->color.c.code = part_command;
            sprite_flags = scratch->sprite_flags;
            if (sprite_flags & 8) {
                if (sprite_flags & 4) {
                    draw_command = part_command | 2;
                }
                else {
                    draw_command = part_command & 0xFD;
                }
                sprite->color.c.code = draw_command;
            }
            /* BYTES: retail stores the sprite colour word (r0, g0, b0 and code) with one sw; member stores compile to four sb */
            *(s32 *) &packet->r0 = sprite->color.word;
            base_quad = *packet;
            strip_quad = base_quad;
            phase = wave->rotation_angle;
            wave_index = 0;
            if (wave->wave_axis == 0) {
                do {
                    ((GpuLinkTag *) &packet->tag)->len = 9;
                    *packet = base_quad;
                    packet->x0 = packet->x0
                        + ((rsin(phase) * wave->levels[wave_index]) >> 0x10);
                    packet->x1 = packet->x1 + ((rsin(phase) * wave->levels[wave_index]) >> 0x10);
                    row_phase = phase + wave->unk_9A;
                    if (row_phase >= 0x1001) {
                        row_phase -= 0x1000;
                    }
                    packet->x2 = packet->x2 + ((rsin(row_phase) * wave->levels[wave_index]) >> 0x10);
                    packet->x3 = packet->x3 + ((rsin(row_phase) * wave->levels[wave_index]) >> 0x10);
                    wave_index += 1;
                    if (wave_index >= 0x60) {
                        wave_index = 0;
                    }
                    packet->y0 = strip_quad.y0;
                    packet->y1 = strip_quad.y0;
                    packet->y2 = strip_quad.y0 + 1;
                    packet->y3 = strip_quad.y0 + 1;
                    packet->v0 = strip_quad.v0;
                    packet->v1 = strip_quad.v0;
                    packet->v2 = strip_quad.v0 + 1;
                    packet->v3 = strip_quad.v0 + 1;
                    packet->tag = (packet->tag & 0xFF000000) | (*scratch->ordering_table & 0xFFFFFF);
                    row_link = scratch->ordering_table;
                    *row_link = (*row_link & 0xFF000000) | ((u32) packet & 0xFFFFFF);
                    strip_quad = *packet;
                    next_y = strip_quad.y0 + 1;
                    strip_quad.y0 = next_y;
                    strip_quad.v0 += 1;
                    phase = row_phase + wave->unk_9A;
                    packet += 1;
                    if (phase >= 0x1001) {
                        phase -= 0x1000;
                    }
                }
                while ((s16) next_y < base_quad.y2);
            }
            else {
                do {
                    ((GpuLinkTag *) &packet->tag)->len = 9;
                    *packet = base_quad;
                    packet->y0 = packet->y0
                        + ((rsin(phase) * wave->levels[wave_index]) >> 0x10);
                    packet->y2 = packet->y2 + ((rsin(phase) * wave->levels[wave_index]) >> 0x10);
                    column_phase = phase + wave->unk_9A;
                    if (column_phase >= 0x1001) {
                        column_phase -= 0x1000;
                        packet->y1 = packet->y1 + ((rsin(column_phase) * wave->levels[wave_index]) >> 0x10);
                        packet->y3 = packet->y3 + ((rsin(column_phase) * wave->levels[wave_index]) >> 0x10);
                        wave_index += 1;
                    } else {
                        packet->y1 = packet->y1 + ((rsin(column_phase) * wave->levels[wave_index]) >> 0x10);
                        packet->y3 = packet->y3 + ((rsin(column_phase) * wave->levels[wave_index]) >> 0x10);
                        wave_index += 1;
                    }
                    if (wave_index >= 0x60) {
                        wave_index = 0;
                    }
                    do {
                        do {
                            do {
                                packet->x0 = strip_quad.x0;
                                packet->x2 = strip_quad.x0;
                                packet->x1 = strip_quad.x0 + 1;
                                packet->x3 = strip_quad.x0 + 1;
                                packet->u0 = strip_quad.u0;
                                packet->u2 = strip_quad.u0;
                                packet->u1 = strip_quad.u0 + 1;
                                packet->u3 = strip_quad.u0 + 1;
                                packet->tag = (packet->tag & 0xFF000000)
                                | (*scratch->ordering_table & 0xFFFFFF);
                                column_link = scratch->ordering_table;
                                *column_link = (*column_link & 0xFF000000) | ((u32) packet & 0xFFFFFF);
                                strip_quad = *packet;
                                next_x = strip_quad.x0 + 1;
                                strip_quad.x0 = next_x;
                                strip_quad.u0 += 1;
                                phase = column_phase + wave->unk_9A;
                                packet += 1;
                            } while (0);
                        } while (0);
                    } while (0);
                    if (phase >= 0x1001) {
                        phase -= 0x1000;
                    }
                }
                while ((s16) next_x < base_quad.x1);
            }
        }
        else {
            draw_part = part->data.callback;
            if (draw_part != 0) {
                packet = draw_part(context, callback_arg, sprite, part, packet);
            }
        }
        if ((s8) part->flags < 0) {
            break;
        }
        part += 1;
    }
    end_packet = packet;
    if ((saved_draw_control << 0x10) != 0) {
        func_80067EF4(end_packet, 0, 1);
        packet->tag = (packet->tag & 0xFF000000) | (*scratch->ordering_table & 0xFFFFFF);
        end_link = scratch->ordering_table;
        end_packet = (POLY_FT4 *) ((u32) packet & 0xFFFFFF);
        packet = (POLY_FT4 *) ((u32 *) packet + 3);
        *end_link = (*end_link & 0xFF000000) | (u32) end_packet;
    }
    PopMatrix();
    ((GpuContext *) globals->draw_buffer)->packetCursor = packet;
}


typedef struct Position {
    u16 x;
    s16 y;
    s32 value;
} Position;

typedef struct DungeonState {
    u8 pad0[0x8B0];
    u32 ordering_table;
    u8 pad8B4[0x1C];
    u8 *next_packet;
} DungeonState;

typedef struct Packet16 {
    u32 tag;
    u32 code;
    u16 x;
    s16 y;
    s32 value;
} Packet16;

extern u8 upper_draw_context[16];

/* Queue drawing with an optional cleared rectangle, then restore the drawing area. */
void draw_wave_sprite_in_draw_area(ParticleState *wave, void *context, Position *restore_area, Position *draw_pos,
                   u32 clear_area, s32 draw_option)
{
    WaveScreenOrigin pos;
    u16 clear_enabled;
    DungeonState *state;
    void **state_ptr;
    u8 *packet;
    u32 *ordering_table;
    s16 offset_y;
    s32 y;
    s32 saved_option = draw_option;

    state = g_game_work.draw_buffer;
    state_ptr = &g_game_work.draw_buffer;
    packet = state->next_packet;
    offset_y = state != (DungeonState *)upper_draw_context;
    state->next_packet = packet + 12;
    clear_enabled = clear_area;

    SetDrawArea(packet, g_game_work.draw_buffer);
    *(u32 *)packet = (*(u32 *)packet & 0xFF000000) |
                     (state->ordering_table & 0x00FFFFFF);
    state->ordering_table = (state->ordering_table & 0xFF000000) |
                            ((u32)packet & 0x00FFFFFF);

    pos.x = draw_pos->x;
    y = draw_pos->y;
    ordering_table = &state->ordering_table;
    if (offset_y) {
        y -= 0xE0;
    }
    pos.y = y;

    {
        s32 signed_option = (s16)saved_option;
        draw_wave_distorted_sprite(&pos, wave, context, ordering_table, signed_option);
    }

    if (clear_enabled != 0) {
        Packet16 *clear_packet;
        DungeonState *alloc_state;

        alloc_state = g_game_work.draw_buffer;
        clear_packet = (Packet16 *)alloc_state->next_packet;
        alloc_state->next_packet = (u8 *)clear_packet + 16;
        clear_packet->code = 0x60000000;
        ((u8 *)clear_packet)[3] = 3;
        clear_packet->x = restore_area->x;
        y = restore_area->y;
        if (offset_y) {
            y -= 0xE0;
        }
        clear_packet->y = y;
        clear_packet->value = restore_area->value;
        clear_packet->tag = (clear_packet->tag & 0xFF000000) |
                     (state->ordering_table & 0x00FFFFFF);
        state->ordering_table = (state->ordering_table & 0xFF000000) |
                                ((u32)clear_packet & 0x00FFFFFF);
    }

    {
        DungeonState *tail_state;

        tail_state = state_ptr[0];
        packet = tail_state->next_packet;
        tail_state->next_packet = packet + 12;
        SetDrawArea(packet, restore_area);
    }
    *(u32 *)packet = (*(u32 *)packet & 0xFF000000) |
                     (*ordering_table & 0x00FFFFFF);
    *ordering_table = (*ordering_table & 0xFF000000) |
                      ((u32)packet & 0x00FFFFFF);
}

#include "shared/dungeon_effect_views.h"
#include "modules/dungeon_ovl_1918800.h"
#include "shared/gpu_packets.h"
#include "shared/entity.h"
#include "shared/game_work.h"
#include "shared/object_node.h"

/* GPU scratchpad (0x1F800000) workspace used while projecting. */
typedef struct Scratch80024EDC {
    u16 x;
    u16 y;
    u16 z;
    u8 pad_06[0x12];
    u8 *cursor;         /* next free packet */
    u8 pad_1C[4];
    u32 *ot;            /* ordering table */
    u8 pad_24[0x6C];
    u32 xy;
    u32 depth;
    u8 pad_98[0x28];
    u32 index;          /* ordering table slot */
} Scratch80024EDC;

/* Retail 818F96DC (draw_linked_brightness_points): projects each linked point and queues a brightness-scaled shaded point
 * followed by a draw-mode packet for it. */
s32 draw_linked_brightness_points(PointRecord *start_node, ObjectPosition *start_coords)
{
    GpuContext **state_ptr;
    Scratch80024EDC *scratch;
    GpuContext *render_state;
    GpuContext *final_state;
    PointPacket *packet;
    PointRecord *node;
    ObjectPosition *coords;
    ObjectNodeHeader *prev_entry;
    u32 depth_index;
    u16 coord_x;

    node = start_node;
    coords = start_coords;
    state_ptr = (GpuContext **)&g_game_work;
    render_state = *state_ptr;
    scratch = (Scratch80024EDC *)0x1F800000;

    scratch->cursor = render_state->packetCursor;
    scratch->ot = (u32 *)&render_state->orderTag;

    for (;;) {
        coord_x = coords->x.w.i;
        packet = (PointPacket *)scratch->cursor;
        scratch->x = coord_x;
        scratch->y = (u16)coords->y.w.i;
        scratch->z = (u16)coords->z.w.i;
        scratch->cursor = (u8 *)packet + 0xC;

        depth_index = RotTransPers(scratch, &packet->data, &scratch->xy, &scratch->depth);
        scratch->index = depth_index;

        if (depth_index < 0x1E0) {
            s32 color_or_tpage;
            PointPacket *mode_packet;

            *(u32 *)&packet->r = node->color;
            color_or_tpage = packet->r * node->brightness;
            if (color_or_tpage < 0) {
                color_or_tpage += 0xFF;
            }
            packet->r = color_or_tpage >> 8;

            color_or_tpage = packet->g * node->brightness;
            if (color_or_tpage < 0) {
                color_or_tpage += 0xFF;
            }
            packet->g = color_or_tpage >> 8;

            color_or_tpage = packet->b * node->brightness;
            if (color_or_tpage < 0) {
                color_or_tpage += 0xFF;
            }
            packet->b = color_or_tpage >> 8;
            ((u8 *)packet)[3] = 2;
            packet->code = 0x6A;

            ((GpuLinkTag *)&packet->tag)->addr = ((GpuLinkTag *)&scratch->ot[scratch->index])->addr;
            scratch->ot[scratch->index] = (scratch->ot[scratch->index] & 0xFF000000) | ((u32)packet & 0x00FFFFFF);

            mode_packet = (PointPacket *)scratch->cursor;
            scratch->cursor = (u8 *)mode_packet + 0xC;
            color_or_tpage = GetTPage(0, 1, 0, 0);
            SetDrawMode(mode_packet, 0, 0, (u16)color_or_tpage, 0);

            ((GpuLinkTag *)&mode_packet->tag)->addr = ((GpuLinkTag *)&scratch->ot[scratch->index])->addr;
            scratch->ot[scratch->index] = (scratch->ot[scratch->index] & 0xFF000000) | ((u32)mode_packet & 0x00FFFFFF);
        }

        prev_entry = NODE_HEADER(node)->chain_next;
        node = NODE_BODY(prev_entry);
        if (prev_entry == 0) {
            break;
        }
        coords = prev_entry->position;
    }

    final_state = *state_ptr;
    final_state->packetCursor = scratch->cursor;
    return 0;
}


/* Return a random sign of either -1 or 1. */
s32 advance_effect_sequence(void) {
    s32 sign;

    sign = rand() & 1;
    if (sign == 0) {
        sign = -1;
    }
    return sign;
}

#include "shared/dungeon_effect_views.h"
#include "modules/dungeon_ovl_1918800.h"
#include "modules/dungeon_native_abi.h"
#include "shared/object_flags.h"

/* Raise the entity toward the queried ground height and set flags when the countdown expires. */
void raise_entity_to_ground(PointRecord *state, ObjectPosition *position)
{
    u16 countdown;

    wave_effect_update_flag = 1;
    if (position->z.w.i <
        (s16)sample_terrain_surface_height((u16)position->x.w.i, (u16)position->y.w.i,
                      (s16)(position->z.w.i + 2))) {
        position->z.v += 0x20000 + (rand() & 0xFFF);
    }

    countdown = state->brightness - 8;
    state->brightness = countdown;
    if ((s32)(countdown << 16) <= 0) {
        NODE_HEADER(state)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}


/* Retail 818F9A28 (create_random_jitter_child): spawn an effect object under the parent node, placed at the parent's
 * position plus a random jitter (0..31 per axis) and the given offsets (minus half the jitter range). */
void create_random_jitter_child(
    ObjectNodeHeader *parent,
    s16 field_34,
    s32 field_28,
    s16 field_52,
    s16 offset_x,
    s16 offset_y,
    s16 offset_z)
{
    ObjectNodeHeader *source_obj = parent;
    u32 saved_field_28 = field_28;
    s16 saved_field_52 = field_52;
    ObjectNodeHeader *spawned;
    PointRecord *fields;
    s32 jitter_x;
    s32 jitter_y;
    s32 jitter_z;
    s16 bias_x;
    s16 bias_y;
    s16 bias_z;
    s16 position_x;
    s16 position_y;
    s16 position_z;
    void *init_data;
    ObjectPosition *dest_x;
    ObjectPosition *dest_y;
    ObjectPosition *dest_z;

    /* the parent's next slot is the list head the new node links behind */
    spawned = allocate_list_node(0x211, (ObjectNodeHeader **)source_obj);
    if (spawned != 0) {
        spawned->update_callback = (void *)raise_entity_to_ground;
        jitter_x = rand() & 0x1F;
        position_x = source_obj->position->x.w.i;
        dest_x = spawned->position;
        position_x += jitter_x;
        bias_x = offset_x - 0x10;
        position_x += bias_x;
        dest_x->x.w.i = position_x;

        jitter_y = rand() & 0x1F;
        position_y = source_obj->position->y.w.i;
        dest_y = spawned->position;
        position_y += jitter_y;
        bias_y = offset_y - 0x10;
        position_y += bias_y;
        dest_y->y.w.i = position_y;

        jitter_z = rand();
        init_data = draw_linked_brightness_points;
        jitter_z &= 0x1F;
        position_z = source_obj->position->z.w.i;
        fields = NODE_BODY(spawned);
        dest_z = spawned->position;
        position_z += jitter_z;
        bias_z = offset_z - 0x10;
        position_z += bias_z;
        dest_z->z.w.i = position_z;
        fields->unk_14 = field_34;
        fields->brightness = saved_field_52;
        register_node(spawned, init_data);
        fields->color = saved_field_28;
    }
}


/* The effect's record; its ObjectNodeHeader sits right before it. */
typedef struct CountdownRecord {
    u16 pad_00;
    u16 counter;
} CountdownRecord;

/* Decrement the record counter and set completion flags when it reaches zero. */
void advance_record_counter(CountdownRecord *record)
{
    u16 counter;

    counter = record->counter;
    wave_effect_update_flag = 1;
    counter--;
    record->counter = counter;
    if ((counter << 16) <= 0) {
        NODE_HEADER(record)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}


typedef struct CursorView {
    u8 pad_00[0x38];
    u8 unk_38;
} CursorView;

/* Update the effect's fade and rotation, draw it, and flag completion at its final frame. */
void process_five_context_entries_or_fallback(ParticleState *effect, void *unused, SpriteFrameState *output)
{
    PackedVector source;
    PackedVector *source_ptr;
    PackedVector *render_source;
    Pair16 *derived_ptr;
    Pair16 derived;
    s32 frame;
    s32 peak_frame;
    s32 end_frame;
    s32 state;
    s32 next_state;
    s16 next_frame;
    s32 fade_in;
    s32 fade_out;
    s32 shade_index;
    s32 one;
    u16 angle;
    u16 next_angle;
    s32 vertex_x;
    s32 vertex_y;
    s32 fill_shade;
    void *shade_cursor;

    source_ptr = (PackedVector *)(&wave_texture_rect);
    source = *source_ptr;
    frame = effect->frame;
    peak_frame = effect->peak_frame;
    wave_effect_update_flag = 1;

    if (frame < peak_frame) {
        fade_in = (frame << 7) / peak_frame;
        output->scale_x += 0x50;
        output->scale_y += 0x50;
        output->color.c.b = fade_in;
        output->color.c.g = fade_in;
        output->color.c.r = fade_in;
    } else {
        end_frame = effect->unk_02;
        fade_out = ((end_frame - frame) << 7) / (end_frame - peak_frame);
        vertex_x = output->scale_x;
        vertex_y = output->scale_y;
        vertex_x += 0x50;
        vertex_y += 0x50;
        output->scale_x = vertex_x;
        output->scale_y = vertex_y;
        output->color.c.b = fade_out;
        output->color.c.g = fade_out;
        output->color.c.r = fade_out;
    }

    angle = effect->rotation_angle;
    next_angle = angle - 0x28;
    effect->rotation_angle = next_angle;
    if ((s16)next_angle < 0) {
        effect->rotation_angle = angle + 0xFD8;
    }

    shade_index = 0x5F;
    if (effect->frame < 0x32) {
        fill_shade = 0x46;
        shade_cursor = (u8 *)effect + 0x5F;
        do {
            ((CursorView *)shade_cursor)->unk_38 = fill_shade;
            shade_index--;
            shade_cursor = (u8 *)shade_cursor - 1;
        } while (shade_index >= 0);
        state = effect->phase;
        effect->unk_9A = 0x64;
    } else {
        state = effect->phase;
        effect->unk_9A = 0x64;
    }
    next_state = (u16)effect->phase + 1;
    switch (state) {
    case 0:
        effect->phase = next_state;
        output->flags &= 0xFF7F;
        break;
    case 1:
        break;
    default:
        return;
    }

    render_source = &source;
    derived_ptr = &derived;
    derived.x = source.x + ((s16)source.z >> 1);
    one = 1;
    derived.y = source.y + 0x3C;
    draw_wave_sprite_in_draw_area(effect, effect->flash_state, render_source, derived_ptr, one, one);

    next_frame = (u16)effect->frame + 1;
    effect->frame = next_frame;
    if (next_frame == effect->unk_02) {
        NODE_HEADER(effect)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}


/* Updates a grayscale fade, advances its progress, and flags completion. */
void advance_grayscale_fade(ParticleState *state, s32 unused, SpriteFrameState *out)
{
    s32 current;
    s32 target;
    s32 limit;
    s16 intensity;
    s16 next_step;

    current = state->frame;
    target = state->peak_frame;
    wave_effect_update_flag = 1;

    if (current < target) {
        intensity = (current * 0x60) / target;
        out->color.c.b = intensity;
    } else {
        limit = state->unk_02;
        intensity = ((limit - current) * 0x60) / (limit - target);
        out->color.c.b = intensity;
    }
    out->color.c.g = intensity;
    out->color.c.r = intensity;

    next_step = (u16)state->frame + 1;
    state->frame = next_step;
    if (next_step >= state->unk_02) {
        NODE_HEADER(state)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}


struct ParentView;
struct SelfChildView;

typedef struct ProjectileSelf {
    struct ParentView *parent;
    struct SelfChildView *owner_data;
    u8 pad_08[0x1];
    u8 unk_09;
    u16 state;
    u8 pad_0C[0x6C];
    s16 target_y;
    u8 flags;
    u8 frames_left;
    u8 pad_7C[0x2];
    s16 direction;
    u8 pad_80[0x2];
    u16 timer;
    u8 pad_84[0x4];
    s16 frames_copy;
    s16 frames_squared;
    u8 pad_8C[0x4];
    s16 shrinking;
    u16 pulse_ticks;
    s16 pulse_period;
    u16 pulse_step;
    u8 pad_98[0x4];
    s16 unk_9C;
    u8 pad_9E[0x4];
    Copy12 copy12;
    u8 pad_AE[0xC];
    u8 tile_x;
    u8 tile_y;
} ProjectileSelf;

/* Update a timed visual effect using its owner's appearance and position. */
void update_timed(ParticleState *state, ObjectPosition *position_out, SpriteFrameState *effect_arg_arg) {
    SpriteFrameState *effect_arg = effect_arg_arg;
    PackedVector origin;
    Pair16 anchor;
    s32 level_index;
    u8 intensity;
    s16 frame_or_phase;
    u16 effect_flags;
    void *owner;
    SpriteFrameState *motion;
    ObjectPosition *owner_position;
    u16 saved_scale_x;
    u16 saved_scale_y;
    s32 one;

    origin = wave_source_rect;
    wave_effect_update_flag = 1;
    state->rotation_angle += 0xC8;

    if (state->unk_02 < 0x32) {
        level_index = 0;
        do {
            state->levels[level_index]++;
            level_index++;
        } while (level_index < 0x60);
    } else {
        level_index = 0;
        do {
            intensity = state->levels[level_index];
            if (intensity != 0) {
                state->levels[level_index] = intensity - 1;
            }
            level_index++;
        } while (level_index < 0x60);
    }

    frame_or_phase = state->unk_02;
    if (frame_or_phase < 0x15) {
        intensity = (frame_or_phase * 6) - 0x79;
        effect_arg->color.c.b = intensity;
        effect_arg->color.c.g = intensity;
        effect_arg->color.c.r = intensity;
    } else if (frame_or_phase >= 0x50) {
        intensity = ((0x64 - frame_or_phase) * 6) - 0x80;
        effect_arg->color.c.b = intensity;
        effect_arg->color.c.g = intensity;
        effect_arg->color.c.r = intensity;
    }

    state->unk_9A += 4;
    owner = state->target;
    owner_position = NODE_HEADER(owner)->position;
    motion = NODE_HEADER(owner)->sprite;
    position_out->x.v = owner_position->x.v;
    position_out->y.v = owner_position->y.v;
    position_out->z.v = owner_position->z.v;

    switch (state->phase) {
    case 0:
    state->phase = (u16) ((u16) state->phase + 1);
    effect_flags = effect_arg->flags & 0xFF7F;
    effect_arg->flags = effect_flags;
    effect_arg->flags = effect_flags | (motion->flags & 0xC);
    effect_arg->tpage_abr = motion->tpage_abr;
    effect_arg->color.c.r = motion->color.c.r;
    effect_arg->color.c.g = motion->color.c.g;
    effect_arg->color.c.b = motion->color.c.b;
    motion->flags |= 0x80;
        break;
    case 1:
        break;
    default:
        return;
    }
    one = 1;
    anchor.x = origin.x + ((s16)origin.z >> 1);
    anchor.y = origin.y + 0x48;
    saved_scale_x = motion->scale_x;
    saved_scale_y = motion->scale_y;
    effect_arg->scale_x = saved_scale_x;
    effect_arg->scale_y = motion->scale_y;
    motion->scale_y = 0x1000;
    motion->scale_x = 0x1000;
    draw_wave_sprite_in_draw_area(state, state->target, &origin, &anchor, one, one);
    motion->scale_x = saved_scale_x;
    motion->scale_y = saved_scale_y;

    frame_or_phase = (u16) state->unk_02 + 1;
    state->unk_02 = frame_or_phase;
    if (frame_or_phase >= 0x65) {
        state->unk_02 = 0;
        state->phase = (u16) ((u16) state->phase + 1);
        motion->flags &= 0xFF7F;
        state->source->unk_9C = one;
        NODE_HEADER(state)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

/* MECHANISM: Separate packed source/derived locals preserve the 0x40 frame and retail slots. */

#include "shared/entity_height_offsets.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/dungeon_moving_views.h"

typedef struct Pair {
    s32 a;
    s32 b;
} Pair;

typedef struct OutPair {
    u16 x;
    u16 y;
    u16 z;
    GpuRectBuffer pair;
} OutPair;

typedef struct Triple {
    s32 a;
    s32 b;
    s32 c;
} Triple;

extern Copy12 D_80026668;
extern Copy12 D_80026674;
extern Copy12 D_80026680;
extern Copy12 D_80026698;
extern Copy12 D_800266A4;
extern u8 current_spell_effect_variant[256];

#include "dungeon/effect/screen.h"
extern void try_apply_action_by_chance(void *, s32, s32);

typedef struct ParentHead {
    void * unk_00;
    u8 pad_04[0x10];
} ParentHead;

typedef struct ParentView {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x34];
    union { u8 * p; void * p2; } unk_60;   /* accessed as both */
    u8 pad_64[0xE];
    u8 unk_72;
    u8 unk_73;
    u8 pad_74[0x14];
    u16 unk_88;
} ParentView;

typedef struct ColorsView {
    u8 pad_00[0x10];
    u8 unk_10;
    u8 unk_11;
    u8 unk_12;
    u8 pad_13[0x1];
    u8 unk_14;
    u8 unk_15;
    u8 unk_16;
} ColorsView;

typedef struct ObjDataView {
    u8 pad_00[0x6];
    u16 unk_06;
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0x4];
    u8 unk_24;
    u8 unk_25;
} ObjDataView;

typedef struct Obj2DataView {
    u8 pad_00[0x6];
    u16 unk_06;
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} Obj2DataView;


typedef struct TmpSrcView {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
} TmpSrcView;

typedef struct SelfChildView {
    u16 unk_00;
} SelfChildView;

typedef struct ParentLink {
    u8 pad_00[0x13];
    u8 unk_13;
} ParentLink;

typedef struct ParentLinkMinus14 {
    void * unk_00;
} ParentLinkMinus14;

typedef struct EffectObject {
    u8 pad_00[0x8];
    s32 *position;
    void *render;
    void *callback;
    u8 pad_14[0xE];
    u16 unk_22;
    u8 pad_24[0x16];
    Copy12 anim;
} EffectObject;

/* Update a projectile effect, spawn impact particles, and advance its cleanup state. */
void set_record_pair_to_one(ProjectileSelf *self, ObjectPosition *position, SpriteFrameState *render_data)
{
    ParentView *parent;
    ObjectNodeHeader *parent_base;
    ObjectPosition *target_pos;
    ObjectPosition *origin;
    OutPair out_pair;
    Copy24 velocities;
    s32 state;

    Copy24 *velocity_table;
    EffectObject *impact;
    parent = self->parent;
    velocities = wave_direction_steps;
    parent_base = NODE_HEADER(parent);
    state = (s16)self->state;
    origin = parent_base->position;
    switch (state) {
        s32 index;
        u32 reg_tmp;
        s32 *flash_pos;
        s32 flags;
        ParticleState *particle_state;
        s32 angle;

    case 0:
    {
        s32 packed_pos;
        s32 packed_size;
        ColorsView *colors;
        s32 phase;
        render_data->color.word = 0x00808080;
        packed_pos = 0x1400340;
        self->copy12 = D_80026698;
        packed_size = 0x400040;
        colors = (ColorsView *)&D_800266A4;
        render_data->source = (u8 *)self + 0xA2;
        self->direction = (parent->unk_2A >> 9) & 7;
        colors->unk_10 = 0x80;
        colors->unk_11 = 0x80;
        colors->unk_12 = 0x80;
        colors->unk_14 = 4;
        colors->unk_15 = 4;
        colors->unk_16 = 4;
        out_pair.pair.words[0] = packed_pos;
        out_pair.pair.words[1] = packed_size;
        draw_textured_ellipse(colors, &out_pair.pair.rect, 1, 0);
        phase = self->state;
        wave_effect_update_flag = 1;
        self->state = phase + 1;
    }

    case 1:
    {
        u8 *target;
        ObjDataView *parent_data;
        u32 step_result;
        s32 height;
        s32 origin_z;
        s8 frames;
        s16 frames_copy;
        u32 target_height;
        s32 tile_distance;
        s32 tile;

        step_result = get_sprite_attachment_vector(parent_base->sprite->source,
            parent_base->sprite, &out_pair, 0);
        if (step_result == 0 && !(parent_base->sprite->flags & 0x8000)) {
            return;
        }
        position->x.unsigned_parts.integer = origin->x.unsigned_parts.integer;
        position->y.unsigned_parts.integer = origin->y.unsigned_parts.integer;
        origin_z = origin->z.unsigned_parts.integer;
        position->z.unsigned_parts.integer = origin_z;
        if (!(parent_base->sprite->flags & 0x8000)) {
            position->x.unsigned_parts.integer += out_pair.x;
            position->y.unsigned_parts.integer += out_pair.y;
            position->z.unsigned_parts.integer += out_pair.z;
        } else {
            position->z.unsigned_parts.integer = origin_z - 0x40;
        }
        if (!(self->owner_data->unk_00 & 0x80)) {
            return;
        }
        if (!(self->flags & 4)) {
            register_node((u8 *)self - 0x20, project_sprite_chain);
            render_data->tpage_abr = 0x20;
            render_data->color.c.b = 0x20;
            render_data->color.c.r = 0x20;
            render_data->flags |= 0x0C;
            render_data->color.c.g = 0xE0;
            render_data->scale_y = 2000;
            render_data->scale_x = 2000;
            render_data->flags &= 0xFFFC;
            self->flags |= 4;
            target = parent->unk_60.p;
        } else {
            target = parent->unk_60.p;
        }
        if (target != 0) {
            target_pos = NODE_HEADER(target)->position;
            target_height = entity_height_offsets[((ParentLink *)target)->unk_13];
            self->target_y = target_pos->z.unsigned_parts.integer - (target_height >> 1);
            parent_data = ((ParentHead *)parent)[-1].unk_00;
            self->tile_x = parent_data->unk_24
            + (u8)dir_step_x[self->direction];
            self->tile_y = parent_data->unk_25
            + (u8)dir_step_y[self->direction];
            flags = (s8)parent->unk_72;
            tile = parent_data->unk_24;
            if (flags != tile) {
                flags = flags - tile;
            } else {
                flags = (s8)parent->unk_73;
                tile = parent_data->unk_25;
                flags = flags - tile;
            }
            tile_distance = abs(flags);
            self->frames_left = tile_distance * 2 - 1;
        } else {
            self->target_y = parent->unk_88 - 0x50;
            self->frames_left = 0x20;
        }
        position->velocity_x = (s32)velocities.entries[self->direction].x << 16;
        position->velocity_y = (u32)velocities.entries[self->direction].y << 16;
        position->velocity_z = (((s32)self->target_y << 16)
            - position->z.v)
        / (s8)self->frames_left;
        self->timer = 0;
        self->shrinking = 0;
        self->pulse_ticks = 0;
        self->pulse_period = 5;
        self->pulse_step = 200;
        self->state++;
        self->frames_copy = (s8)self->frames_left;
        step_result = self->frames_left << 24;
        frames = step_result >> 24;
        frames_copy = frames;
        reg_tmp = frames * frames_copy;
        self->frames_squared = reg_tmp;
        return;
    }

    case 2:
    {
        s32 random_bits;
        s32 hit_result;
        s16 pulse_ticks;
        s32 shrinking;
        EffectObject *flash;
        Obj2DataView *flash_data;
        void *flash_state;
        void *animation;
        ObjDataView *impact_data;
        u8 *clear_cursor;

        index = 0;
        do {
            u8 *emitter;
            s32 direction;
            s32 color;
            s32 intensity;
            random_bits = rand();
            emitter = (u8 *)self - 0x20;
            color = 0x40E020;
            intensity = (random_bits & 0xFF) | 0x80;
            direction = self->direction;
            create_random_jitter_child(emitter, direction, color, intensity, 0, 0, 0);
            index++;
        } while (index < 8);
        hit_result = check_adjacent_tile_height_clearance(position->x.unsigned_parts.integer, position->y.unsigned_parts.integer,
            position->z.w.i, parent->unk_60.p2);
        if (hit_result << 16) {
            (self->state) = 8;
            (self->timer) = 0;
            render_data->color.c.b = 0;
            render_data->color.c.g = 0;
            render_data->color.c.r = 0;
            return;
        }
        {
            s32 scale_y;
            angle = render_data->angle_z;
            angle += 0x400;
            if (angle >= 0x1001) {
                angle -= 0x1000;
            }
            render_data->angle_z = angle;
            shrinking = self->shrinking;
            if (shrinking == 0) {
                render_data->scale_x += self->pulse_step;
                render_data->scale_y += self->pulse_step;
            } else {
                render_data->scale_x -= self->pulse_step;
                render_data->scale_y -= self->pulse_step;
            }
        }
        pulse_ticks = self->pulse_ticks + 1;
        self->pulse_ticks = pulse_ticks;
        if (pulse_ticks >= self->pulse_period) {
            self->pulse_ticks = 0;
            self->shrinking ^= 1;
        }
        self->frames_left--;
        if ((s8)self->frames_left <= 0) {
            if (parent->unk_60.p != 0) {
                self->state = 3;
                self->timer = 0;
                target_pos = NODE_HEADER(parent->unk_60.p)->position;
                position->x.unsigned_parts.integer = target_pos->x.unsigned_parts.integer;
                position->y.unsigned_parts.integer = target_pos->y.unsigned_parts.integer;
                position->z.unsigned_parts.integer = target_pos->z.unsigned_parts.integer
                - entity_height_offsets[((ParentLink *)(parent->unk_60.p))->unk_13];
                play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
                flash = allocate_flagged_object_node(0x212);
                if (flash != 0) {
                    flash->unk_22 = 120;
                    flash->callback = advance_record_counter;
                    register_node(flash, project_sprite_chain);
                    flash_data = flash->render;
                    flash_data->unk_14 |= 0x0C;
                    flash_data->unk_10 = 0;
                    flash_data->unk_06 = 0;
                    flash_data->unk_14 |= 0x80;
                    target_pos = NODE_HEADER(parent->unk_60.p)->position;
                    flash_pos = flash->position;
                    flash_pos[0] = target_pos->x.v;
                    flash_pos[1] = target_pos->y.v;
                    flash_pos[2] = target_pos->z.v;
                    flash_data = flash->render;
                    flash_data->unk_1E = 0x1000;
                    flash_data->unk_1C = 0x1000;
                    flash_data->unk_0E = 0x80;
                    flash_data->unk_0D = 0x80;
                    flash_data->unk_0C = 0x80;
                    flash->anim = D_80026680;
                    flash_data->unk_08 = &flash->anim;
                }
                impact = allocate_flagged_object_node(0x212);
                if (impact != 0) {
                    particle_state = (ParticleState *)((u8 *)impact + 0x20);
                    index = 95;
                    clear_cursor = (u8 *)particle_state + 95;
                    particle_state->unk_02 = 0x50;
                    particle_state->peak_frame = 0x14;
                    particle_state->frame = 0;
                    particle_state->parent = parent;
                    particle_state->target = parent->unk_60.p2;
                    particle_state->source = self;
                    flash_state = (u8 *)flash + 0x20;
                    particle_state->flash_state = flash_state;
                    for (; index >= 0; index--) {
                        ((CursorView *)clear_cursor)->unk_38 = 0;
                        clear_cursor--;
                    }
                    index = 96;
                    particle_state->unk_9A = 0;
                    impact->callback = process_five_context_entries_or_fallback;
                    register_node(impact, project_sprite_chain);
                    impact_data = impact->render;
                    impact_data->unk_14 = 0x0C;
                    impact_data->unk_10 = index;
                    impact_data->unk_06 = 6;
                    impact_data->unk_14 |= 0x80;
                    flash_pos = impact->position;
                    flash_pos[0] = position->x.v;
                    flash_pos[1] = position->y.v;
                    flash_pos[2] = position->z.v + 0x400000;
                    impact_data = impact->render;
                    impact_data->unk_1C = 0x2000;
                    impact_data->unk_1E = 0x1800;
                    impact_data->unk_0E = 0;
                    impact_data->unk_0D = 0;
                    impact_data->unk_0C = 0;
                    particle_state->anim = D_80026674;
                    animation = &particle_state->anim;
                    impact_data->unk_08 = animation;
                }
            } else {
                self->state = 8;
                self->timer = 0;
            }
            render_data->color.c.b = 0;
            render_data->color.c.g = 0;
            render_data->color.c.r = 0;
            render_data->scale_y = 0;
            render_data->scale_x = 0;
            return;
        }
        position->x.v += position->velocity_x;
        position->y.v += position->velocity_y;
        position->z.v += position->velocity_z;
        return;
    }

    case 3:
    {
        s16 ticks;
        ObjDataView *flash_data;
        u8 *clear_cursor;
        s32 render_flags;

        ticks = self->timer + 1;
        self->timer = ticks;
        if ((s16)ticks != 4) {
            return;
        }
        impact = allocate_flagged_object_node(0x212);
        if (impact != 0) {
            particle_state = (ParticleState *)((u8 *)impact + 0x20);
            index = 95;
            particle_state->parent = parent;
            particle_state->target = parent->unk_60.p2;
            particle_state->source = self;
            clear_cursor = (u8 *)particle_state + 95;
            for (; index >= 0; index--) {
                ((CursorView *)clear_cursor)->unk_38 = 0;
                clear_cursor--;
            }
            particle_state->unk_9A = 0;
            impact->callback = update_timed;
            register_node(impact, project_sprite_chain);
            flash_data = impact->render;
            render_flags = flash_data->unk_14 & 0xFFF3;
            flash_data->unk_14 = render_flags;
            flash_data->unk_10 = 0x20;
            flash_data->unk_14 = render_flags | 0x80;
            target_pos = NODE_HEADER(parent->unk_60.p)->position;
            flash_pos = impact->position;
            flash_pos[0] = target_pos->x.v;
            flash_pos[1] = target_pos->y.v;
            flash_pos[2] = target_pos->z.v;
            flash_data = impact->render;
            flash_data->unk_1E = 0x1000;
            flash_data->unk_1C = 0x1000;
            flash_data->unk_0E = 0x80;
            flash_data->unk_0D = 0x80;
            flash_data->unk_0C = 0x80;
            particle_state->anim = D_80026668;
            flash_data->unk_08 = &particle_state->anim;
        }
        if ((s16)self->timer != 4) {
            return;
        }
        self->state = 4;
        self->timer = 0;
        self->unk_9C = 0;
        return;
    }

    case 4:
    {
        s16 ticks;
        ObjDataView *particle_data;
        TmpSrcView *target_data;
        s32 random_bonus;
        s32 amount;
        s32 offset_radius;
        s32 height_random;
        s32 offset_sign;
        s16 effect_kind;
        s32 power_bonus;

        ticks = self->timer + 1;
        self->timer = ticks;
        if (!((ticks & 3) != 0 || (s16)ticks >= 80)) {
            impact = allocate_flagged_object_node(0x212);
            if (impact != 0) {
                particle_state = (ParticleState *)((u8 *)impact + 0x20);
                particle_state->unk_02 = 20;
                particle_state->peak_frame = 10;
                particle_state->frame = 0;
                impact->callback = advance_grayscale_fade;
                register_node(impact, project_sprite_chain);
                particle_data = impact->render;
                particle_data->unk_10 = 0x20;
                particle_data->unk_14 |= 0x0C;
                target_pos = NODE_HEADER(parent->unk_60.p)->position;
                flash_pos = impact->position;
                offset_radius = rand();
                offset_sign = advance_effect_sequence();
                offset_radius &= 0x1F;
                offset_radius += 16;
                reg_tmp = (u32)((u8 *)(offset_radius * offset_sign));
                angle = (s32)((u8 *)reg_tmp) << 16;
                flash_pos[0] = target_pos->x.v + angle;
                offset_radius = rand();
                offset_sign = advance_effect_sequence();
                offset_radius &= 0x1F;
                offset_radius += 16;
                reg_tmp = (u32)((u8 *)(offset_radius * offset_sign));
                angle = (s32)((u8 *)reg_tmp) << 16;
                flash_pos[1] = target_pos->y.v + angle;
                height_random = rand();
                flash_pos[2] = target_pos->z.v
                - (entity_height_offsets[parent->unk_60.p[0x13]] << 15)
                - ((height_random & 0x1F) << 16);
                particle_data = impact->render;
                target_data = ((ParentLinkMinus14 *)(parent->unk_60.p - 0x14))->unk_00;
                particle_data->unk_1C = target_data->unk_1C >> 1;
                particle_data->unk_1E = target_data->unk_1E >> 1;
                particle_data->unk_0E = 0;
                particle_data->unk_0D = 0;
                particle_data->unk_0C = 0;
                impact->anim = D_80026668;
                particle_data->unk_08 = &impact->anim;
            }
        }
        if ((s16)self->timer == 80) {
            if (try_trigger_target_record_effect(parent->unk_60.p2, 4, parent) == 0) {
                random_bonus = generate_random_value();
                power_bonus = self->unk_09 >> 2;
                random_bonus = (random_bonus & 3) + 4;
                amount = power_bonus + random_bonus;
                if (current_spell_effect_variant[0] == 0xFF) {
                    effect_kind = 0xFF;
                } else {
                    effect_kind = 16;
                }
                try_apply_action_by_chance(parent->unk_60.p2, effect_kind, amount);
            }
        }
        if ((s16)self->timer < 120) {
            return;
        }
        self->state++;
        self->timer = 0;
        return;
    }

    case 5:
    {
        if (self->unk_9C == 0) {
            return;
        }
    }

        self->state++;
        self->timer = 0;
        return;

    case 6:
    {
        s16 ticks;
        ticks = self->timer + 1;
        self->timer = ticks;
        if ((s16)ticks < 11) {
            return;
        }
        self->state = 8;
        self->timer = 30;
        return;
    }

    case 8:
    {
        s16 ticks;
        s32 effect_active;
        ticks = self->timer;
        self->timer = ticks + 1;
        if ((s16)(ticks + 1) < 31) {
            return;
        }
        effect_active = wave_effect_update_flag;
        self->timer = ticks;
        if (effect_active == 0) {
            g_dungeon_status.active_actor = 0;
            (NODE_HEADER(self)->flags) |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
            return;
        }
        wave_effect_update_flag = 0;
        return;
    }

    case 7:
    default:
        return;
    }

    return;
}
