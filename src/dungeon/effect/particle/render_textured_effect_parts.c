#include "sdk/libc.h"
#include "shared/object_node_flags.h"
#include "shared/audio_commands.h"
/* Shaded particle rendering, scattered sprite motion, and projectile burst and impact effects. */
#include "dungeon/effect/particle/render_textured_effect_parts.h"
#include "dungeon/effect/particle.h"
#include "common.h"
#include "shared/object_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "shared/gpu_packets.h"
#include "shared/game_work.h"
#include "shared/object_node.h"
#include "modules/dungeon_native_abi.h"
#include "shared/dir_step.h"
#include "shared/dungeon_status.h"
#include "dungeon/actor.h"

void (*const dungeon_183a800_entry)(void *, void *, void *) = advance_projectile_burst_and_impact;
const PathBlock textured_particle_direction_offsets = {{{32,0},{32,32},{0,32},{-32,32},{-32,0},{-32,-32},{0,-32},{32,-32}}};

/* Decrement the record counter, process update data, and flag depletion. */
void render_textured_effect_parts(void *record_data, void *unused, void *update_data) {
    s16 remaining;
    s16 *update_flag;

    update_flag = &textured_effect_update_flag;
    remaining = (s16)((S_8181A800_0 *)((u8 *)record_data - 0x2))->unk_04 - 1;
    update_flag[0] = 1;
    ((S_8181A800_0 *)((u8 *)record_data - 0x2))->unk_04 = remaining;
    advance_sprite_animation_and_textures(update_data);
    if (((S_8181A800_0 *)((u8 *)record_data - 0x2))->unk_04 <= 0) {
        ((S_8181A800_0 *)((u8 *)record_data - 0x2))->unk_00 =
            (u16)(((S_8181A800_0 *)((u8 *)record_data - 0x2))->unk_00 | 0x8000);
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

extern u8 effect_sprite_sources[9];

/* Creates and initializes an object at an offset from the supplied origin. */
void create_offset_paletted_sprite(void *unused_context, void *origin, s32 unused_id, s16 offset_x, s16 offset_y, s16 offset_z) {
    SpriteFrameState *asset;
    ObjectNodeHeader *object;
    s32 asset_param;
    s32 setup_mode;
    D8181A8C0Header *header;
    ObjectPosition *position;

    object = allocate_flagged_object_node(0x212);
    if (object != NULL) {
        header = (D8181A8C0Header *)((u8 *)object + 0x20);
        header->f2 = 1;
        header->f4 = 1;
        object->update_callback = &render_textured_effect_parts;
        register_node(object, project_sprite_chain);
        asset_param = 0x60;
        setup_mode = 2;
        asset = object->sprite;
        asset->tpage_abr = asset_param;
        asset->depth_bias = 0;
        asset->flags = (s16) (asset->flags | 0xC);
        position = object->position;
        position->x.w.i = offset_x;
        position->y.w.i = (s16) offset_y;
        position->z.w.i = (s16) offset_z;
        position->x.w.i += *(u16 *)((u8 *)origin + 2);
        position->y.w.i += *(u16 *)((u8 *)origin + 6);
        position->z.w.i += *(u16 *)((u8 *)origin + 0xA);
        asset = object->sprite;
        asset->scale_y = 0x400;
        asset->scale_x = 0x400;
        asset->color.c.b = 0x80;
        asset->color.c.g = 0x80;
        asset->color.c.r = 0x80;
        asset->clut = 0x7DCF;
        asset->flags = (u16) (asset->flags | 0x100);
        select_record_entry_and_value(asset, effect_sprite_sources, setup_mode);
    }
}

extern s32 GetTPage(s32, s32, s32, s32);
extern void SetDrawMode(void *, s32, s32, s32, s32);

/*
 * Projects linked points and queues brightness-scaled shaded tiles and draw-mode packets for
 * depths below 0x1E0, then saves the packet cursor.
 */
s32 draw_shaded_point_chain(PointRecord *first_point, ObjectPosition *first_position)
{
    PointRecord *point = first_point;
    ObjectPosition *position = first_position;
    GameWork *render_state = &g_game_work;
    u32 addr_mask = 0x00FFFFFF;
    GpuContext *render_ctx = g_game_work.draw_buffer;
    u8 *packet_start;
    u32 tag_mask = 0xFF000000;
    Scratch800241EC *scratch =
        (Scratch800241EC *)0x1F800000;
    PointPacket *tile;
    PointPacket *draw_mode;
    GpuContext *final_render_ctx;
    s32 color_value;
    s32 draw_page;
    ObjectNodeHeader *next_node;

    packet_start = render_ctx->packetCursor;
    scratch->ot = (u32 *)&render_ctx->orderTag;
    scratch->cursor = packet_start;

    for (;;) {
        tile = (PointPacket *)scratch->cursor;
        scratch->x = (u16)position->x.w.i;
        scratch->y = (u16)position->y.w.i;
        scratch->z = (u16)position->z.w.i;
        scratch->cursor = (u8 *)tile + 0xC;
        scratch->index = RotTransPers(scratch, &tile->data,
                                       &scratch->xy, &scratch->depth);

        if (scratch->index < 0x1E0U) {
            *(u32 *)&tile->r = point->color;

            color_value = (s32)tile->r * point->brightness;
            if (color_value < 0) {
                color_value += 0xFF;
            }
            tile->r = color_value >> 8;

            color_value = (s32)tile->g * point->brightness;
            if (color_value < 0) {
                color_value += 0xFF;
            }
            tile->g = color_value >> 8;

            color_value = (s32)tile->b * point->brightness;
            if (color_value < 0) {
                color_value += 0xFF;
            }
            tile->b = color_value >> 8;

            ((GpuLinkTag *)&tile->tag)->len = 2;
            tile->code = 0x6A;
            ((GpuLinkTag *)&tile->tag)->addr = ((GpuLinkTag *)&scratch->ot[scratch->index])->addr;
            ((GpuLinkTag *)&scratch->ot[scratch->index])->addr = (u32)tile;

            draw_mode = (PointPacket *)scratch->cursor;
            scratch->cursor = (u8 *)draw_mode + 0xC;
            draw_page = GetTPage(0, 1, 0, 0);
            SetDrawMode(draw_mode, 0, 0, (u16)draw_page, 0);

            ((GpuLinkTag *)&draw_mode->tag)->addr = ((GpuLinkTag *)&scratch->ot[scratch->index])->addr;
            ((GpuLinkTag *)&scratch->ot[scratch->index])->addr = (u32)draw_mode;
        }

        next_node = ((ObjectNodeHeader *)point - 1)->chain_next;
        if (next_node != 0) {
            point = (PointRecord *)(next_node + 1);
            position = next_node->position;
            continue;
        }

        break;
    }

    final_render_ctx = render_state->draw_buffer;
    final_render_ctx->packetCursor = scratch->cursor;
    return 0;
}

/*
 * Accumulate motion, process the update mode, and mark expired or flagged state.
 *
 * Effect record: the object header precedes it; velocity is added to position every frame.
 */
void create_radial_height_offset_effect(MotionState *state, s32 *sum, SpriteFrameState *flags) {
    s32 update_count;
    s32 more_updates;
    u16 next_tick;

    state->frames_left = state->frames_left - 1;
    state->x = state->x + state->dx;
    state->y = state->y + state->dy;
    state->z = state->z + state->dz;
    sum[0] = sum[0] + state->x;
    sum[1] = sum[1] + state->y;
    textured_effect_update_flag = 1;
    sum[2] = sum[2] + state->z;

    switch (state->mode) {
    case 0:
        advance_sprite_animation_and_textures(flags);
        break;
    case 1:
        if (state->period > 0) {
            update_count = 0;
            do {
                advance_sprite_animation_and_textures(flags);
                update_count = update_count + 1;
                more_updates = update_count < state->period;
            } while (more_updates);
        }
        break;
    case 2:
        next_tick = state->tick + 1;
        state->tick = next_tick;
        if ((s16) next_tick >= state->period) {
            advance_sprite_animation_and_textures(flags);
            state->tick = 0;
        }
        break;
    default:
        break;
    }

    if ((s16) state->frames_left <= 0) {
        ((ObjectNodeHeader *)state - 1)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
    if (flags->flags & 0x8000) {
        ((ObjectNodeHeader *)state - 1)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}


/* Applies randomized movement and reduces speed, setting flags when speed runs out. */
void advance_scattered_directional_particle(void *object_data, s16 *position)
{
    s16 *object = object_data;
    s16 speed;
    s32 delta_x;
    s32 delta_y;

    textured_effect_update_flag = 1;
    if (position[5] < (s16)sample_terrain_surface_height((u16)position[1], (u16)position[3], position[5] + 2)) {
        delta_x = ((dir_step_x[object[10]] * object[25]) << 10) +
            (rand() & 0xFFFF);
        ((s32 *)position)[0] += delta_x;

        delta_y = ((dir_step_y[object[10]] * object[25]) << 10) +
            (rand() & 0xFFFF);
        ((s32 *)position)[1] += delta_y;
        ((s32 *)position)[2] += 0x20000 + (rand() & 0xFFF);
    }

    speed = (u16)object[25] - 8;
    object[25] = speed;
    if ((speed << 16) <= 0) {
        ((u16 *)object)[-1] |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

/* Retail 8181AF58 (func_80024758): spawn an effect object under the parent node, placed at the parent's
 * position plus a random jitter (0..31 per axis) and the given offsets (minus half the jitter range). */
void spawn_scattered_point_particle(ObjectNodeHeader *parent, s16 field_34, s32 field_28, s16 field_52, s16 offset_x,
                   s16 offset_y, s16 offset_z) {
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
    ObjectPosition *dest_x;
    ObjectPosition *dest_y;
    ObjectPosition *dest_z;

    /* the parent's next slot is the list head the new node links behind */
    spawned = allocate_list_node(0x211, (ObjectNodeHeader **)source_obj);
    if (spawned != 0) {
        spawned->update_callback = (void *)advance_scattered_directional_particle;
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
        jitter_z &= 0x1F;
        position_z = source_obj->position->z.w.i;
        fields = (PointRecord *)(spawned + 1);
        dest_z = spawned->position;
        position_z += jitter_z;
        bias_z = offset_z - 0x10;
        position_z += bias_z;
        dest_z->z.w.i = position_z;
        fields->unk_14 = field_34;
        fields->brightness = saved_field_52;
        register_node(spawned, draw_shaded_point_chain);
        fields->color = saved_field_28;
    }
}

/* Advances the object cycle and position, flagging expiry or a flagged source. */
void cycle_moving_effect_phase(void *object, S_8181B078_1 *position, S_8181B078_2 *source)
{
    s32 one;
    s16 phase;

    textured_effect_update_flag = 1;
    ((S_8181B078_0 *)object)->unk_02.s--;

    if (++((S_8181B078_0 *)object)->unk_1C >= 2) {
        ((S_8181B078_0 *)object)->unk_1C = 0;
        phase = ((S_8181B078_0 *)object)->unk_1E;
        one = 1;

        switch (phase) {
        case 0:
            ((S_8181B078_0 *)object)->unk_1E = one;
            ((S_8181B078_0 *)object)->unk_28 += 8;
            break;
        case 1:
            ((S_8181B078_0 *)object)->unk_1E = 2;
            ((S_8181B078_0 *)object)->unk_28 += 8;
            break;
        case 2:
            ((S_8181B078_0 *)object)->unk_1E = 0;
            ((S_8181B078_0 *)object)->unk_28 -= 16;
            break;
        }
    }

    position->unk_08 += ((S_8181B078_0 *)object)->unk_60;

    if (((S_8181B078_0 *)object)->unk_02.u <= 0) {
        ((S_8181B078_0_pre *)object)[-1].unk_00 |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }

    if (source->unk_14 & 0x8000) {
        ((S_8181B078_0_pre *)object)[-1].unk_00 |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

extern s32 D_80025908[];

/* Creates an effect at an offset from the source and initializes its state and appearance. */
void decrement_object_counter(void *source, s32 offset_x, s32 offset_y, s32 offset_z, s16 effect_value) {
    SpriteFrameState *render;
    S_8181B1A0_0 *state;
    void *effect;
    ObjectPosition *position;

    effect = allocate_flagged_object_node(0x212);
    if (effect != NULL) {
        state = effect + 0x20;
        state->unk_02 = effect_value;
        state->unk_60 = (s32) ((rand() & 0x1FFFF) + 0x10000);
        ((ObjectNodeHeader *)effect)->update_callback = &cycle_moving_effect_phase;
        register_node(effect, project_sprite_chain);
        render = ((ObjectNodeHeader *)effect)->sprite;
        render->flags = (u16) (render->flags | 0xC);
        position = ((ObjectNodeHeader *)effect)->position;
        position->x.w.i = (s16) (((MovingPosition *)(((S_8181B1A0_4 *)source)->unk_08))->x + offset_x);
        position->y.w.i = (s16) (((MovingPosition *)(((S_8181B1A0_4 *)source)->unk_08))->y + offset_y);
        position->z.w.i = (s16) (((MovingPosition *)(((S_8181B1A0_4 *)source)->unk_08))->z + offset_z);
        render = ((ObjectNodeHeader *)effect)->sprite;
        render->scale_y = 0x1000;
        render->scale_x = 0x1000;
        render->color.c.b = 0x80;
        render->color.c.g = 0x80;
        render->color.c.r = 0x80;
        memcpy((u8 *) effect + 0x40, &D_80025908, 12);
        render->source = (void *) (effect + 0x40);
    }
}

/* Advances the timer, ramps target values, and flags completion on timeout or target status. */
void grow_timed_sprite_effect(void *state_data, s32 unused, void *target) {
    u16 timer;
    u8 *state = state_data;

    timer = *(u16 *)(state + 2) + 2;
    textured_effect_update_flag = 1;
    *(u16 *)(state + 2) = timer;
    if ((s16)timer < 40) {
        *(s16 *)((u8 *)target + 0x1C) = (s16)timer * 204;
        *(s16 *)((u8 *)target + 0x1E) =
            (s16)*(u16 *)(state + 2) * 204;
    }
    if ((s16)*(u16 *)(state + 2) >= 120) {
        *(u16 *)(state - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
    if (*(u16 *)((u8 *)target + 0x14) & 0x8000) {
        *(u16 *)(state - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

extern s32 get_sprite_attachment_vector(s32, void *, s16 *, s32);
extern s32 func_8003DF74(s32, void *, s16 *, s32);
extern void initialize_timed_motion_step(s32, s32, void *);
extern void unlink_node(void *);
extern void func_80044A50(void *);
extern void apply_attack_power_and_element_effects(void *, s32, u8, s32, s32, void *, s32);

extern u8 D_800258FC[];
extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
extern s32 D_800814A0[3];
extern u8 effect_sprite_sources[];
extern u8 countdown_sprite_entries[];

/* Updates a projectile effect through travel, impact, particles, and cleanup. */
void advance_projectile_burst_and_impact(void *effect, ObjectPosition *motion, SpriteFrameState *sprite) {
    s16 offset[3];
    PathBlock velocity_table;
    void *source;
    s32 state;
    void *target_graphics;
    ObjectNodeHeader *impact;
    s32 impact_position;
    s32 impact_sprite;
    s32 particle_count_m;
    S_80024BE8_1 *task;
    MovingPosition *origin;
    S_80024BE8_4 *source_sprite;
    void *target;
    u8 *direction_table;
    s32 default_steps;
    s32 tile_distance;
    s32 source_coord;
    s32 direction;
    u16 prev_state;
    u16 source_flags;
    u16 target_height;
    u16 origin_height;

    source = ((S_80024BE8_0 *)effect)->unk_00;
    velocity_table = textured_particle_direction_offsets;
    task = (u8 *)source - 0x20;
    origin = task->unk_08;
    ((S_80024BE8_0 *)effect)->unk_82++;
    state = ((S_80024BE8_0 *)effect)->unk_0A.s;

    switch (state) {
    case 0:
        sprite->color.word = 0x808080;
        sprite->scale_y = 0x400;
        sprite->scale_x = 0x400;
        sprite->clut = 0x7DCF;
        sprite->flags |= 0x100;
        ((S_80024BE8_0 *)effect)->unk_84 = 0;
        select_record_entry_and_value(sprite, effect_sprite_sources, 2);
        source_flags = ((S_80024BE8_3 *)source)->unk_2A;
        textured_effect_update_flag = 1;
        ((S_80024BE8_0 *)effect)->unk_7E.s = (source_flags >> 9) & 7;
        ((S_80024BE8_0 *)effect)->unk_0A.s++;

    case 1:
        source_sprite = task->unk_0C;
        if ((get_sprite_attachment_vector(source_sprite->unk_08, source_sprite, offset, 0) != 0) ||
            (((S_80024BE8_22 *)(task->unk_0C))->unk_14 & 0x8000)) {
            motion->x.w.i = origin->x;
            motion->y.w.i = origin->y;
            origin_height = origin->z;
            motion->z.w.i = origin_height;

            if (!(((S_80024BE8_22 *)(task->unk_0C))->unk_14 & 0x8000)) {
                *(u16 *)&motion->x.w.i += offset[0];
                *(u16 *)&motion->y.w.i += offset[1];
                *(u16 *)&motion->z.w.i += offset[2];
            } else {
                motion->z.w.i = origin_height - 0x40;
            }

            if (*((S_80024BE8_0 *)effect)->unk_04 & 0x80) {
                if (!(((S_80024BE8_0 *)effect)->unk_7A & 4)) {
                    register_node((u8 *)effect - 0x20, project_sprite_chain);
                    sprite->tpage_abr = 0x60;
                    sprite->flags |= 0xC;
                    ((S_80024BE8_0 *)effect)->unk_7A |= 4;
                }

                default_steps = 8;
                target = ((S_80024BE8_3 *)source)->unk_60;
                if (target != 0) {
                    target_height = ((S_80024BE8_7 *)target)->unk_88;
                    direction = ((S_80024BE8_0 *)effect)->unk_7E.s;
                    direction_table = target_height;
                    ((S_80024BE8_0 *)effect)->unk_78.u = direction_table;
                    direction_table = D_8006CCD8;
                    direction <<= 1;
                    direction += (s32)direction_table;
                    target_graphics = ((S_80024BE8_3_pre *)source)[-1].unk_00;
                    direction = *(u8 *)direction;
                    direction_table = (u8 *)(u32)((S_80024BE8_8 *)target_graphics)->unk_24;
                    direction_table = (u8 *)((u8 *)direction_table + direction);
                    ((S_80024BE8_0 *)effect)->unk_A2 = (s32)direction_table;
                    direction = ((S_80024BE8_0 *)effect)->unk_7E.s;
                    direction_table = D_8006CCE8;
                    direction <<= 1;
                    direction += (s32)direction_table;
                    direction_table = (u8 *)(u32)((S_80024BE8_8 *)target_graphics)->unk_25;
                    direction = *(u8 *)direction;
                    direction_table = (u8 *)((u8 *)direction_table + direction);
                    ((S_80024BE8_0 *)effect)->unk_A3 = (s32)direction_table;
                    tile_distance = ((S_80024BE8_3 *)source)->unk_72;
                    source_coord = ((S_80024BE8_8 *)target_graphics)->unk_24;
                    if (tile_distance == source_coord) {
                        tile_distance = ((S_80024BE8_3 *)source)->unk_73;
                        source_coord = ((S_80024BE8_8 *)target_graphics)->unk_25;
                    }
                    tile_distance -= source_coord;
                    if (tile_distance < 0) {
                        tile_distance = -tile_distance;
                    }
                    tile_distance *= 2;
                    tile_distance -= 1;
                    ((S_80024BE8_0 *)effect)->unk_7B = tile_distance;
                } else {
                    u16 target_z;
                    target_z = ((S_80024BE8_3 *)source)->unk_88;
                    ((S_80024BE8_0 *)effect)->unk_7B = default_steps;
                    ((S_80024BE8_0 *)effect)->unk_78.u = target_z - 0x50;
                }

                motion->velocity_x = velocity_table.entries[((S_80024BE8_0 *)effect)->unk_7E.s].x
                << 16;
                motion->velocity_y = velocity_table.entries[((S_80024BE8_0 *)effect)->unk_7E.s].y
                << 16;
                motion->velocity_z =
                    ((((S_80024BE8_0 *)effect)->unk_78.s << 16) - motion->z.v) /
                    ((S_80024BE8_0 *)effect)->unk_7B;
                prev_state = ((S_80024BE8_0 *)effect)->unk_0A.u;
                ((S_80024BE8_0 *)effect)->unk_82 = 0;
                ((S_80024BE8_0 *)effect)->unk_0A.u = prev_state + 1;
                break;
            }
        }
        break;

    case 2:
    {
        void *target_position;
        void *animation;
        s32 color_mode;
        s32 random_intensity;

        if ((check_adjacent_tile_height_clearance(((u16) motion->x.w.i), ((u16) motion->y.w.i),
            motion->z.w.i, ((S_80024BE8_3 *)source)->unk_60) << 16) != 0) {
            ((S_80024BE8_0 *)effect)->unk_0A.s = 8;
            ((S_80024BE8_0 *)effect)->unk_82 = 0;
            sprite->flags |= 0x80;
            break;
        }

        particle_count_m = 0;
        do {
            s32 heading;
            s32 particle_color;
            s32 intensity;
            random_intensity = rand();
            particle_color = 0xF04040;
            intensity = (random_intensity & 0xFF) | 0x80;
            heading = ((S_80024BE8_0 *)effect)->unk_7E.s;
            spawn_scattered_point_particle((u8 *)effect - 0x20, heading, particle_color, intensity, 0, 0, 0);
            particle_count_m++;
        } while (particle_count_m < 4);

        ((S_80024BE8_0 *)effect)->unk_7B--;
        if (((S_80024BE8_0 *)effect)->unk_7B <= 0) {
            unlink_node((u8 *)effect - 0x20);
            color_mode = 4;
            if (((S_80024BE8_3 *)source)->unk_60 != 0) {
                ((S_80024BE8_0 *)effect)->unk_86.u = 0;
                ((S_80024BE8_0 *)effect)->unk_0A.s++;
                target_position = ((S_80024BE8_23_pre *)(((S_80024BE8_3 *)source)->unk_60))[-1].unk_00;
                motion->x.w.i = ((S_80024BE8_9 *)target_position)->unk_02;
                motion->y.w.i = ((S_80024BE8_9 *)target_position)->unk_06;
                motion->z.w.i = ((S_80024BE8_0 *)effect)->unk_78.u;
                source_sprite = (S_80024BE8_4 *)((S_80024BE8_3 *)source)->unk_60;
                ((S_80024BE8_23 *)source_sprite)->unk_1C |= 0x10000000;
                target_graphics = ((S_80024BE8_23_pre *)(((S_80024BE8_3 *)source)->unk_60))[-1].unk_04;
                random_intensity = 0x80;
                ((S_80024BE8_10 *)target_graphics)->unk_0C = random_intensity;
                ((S_80024BE8_10 *)target_graphics)->unk_0D = random_intensity;
                ((S_80024BE8_10 *)target_graphics)->unk_0E = random_intensity;
                initialize_timed_motion_step(color_mode, 8, target_graphics);
                play_sound_if_enabled(AUDIO_PLAY_CD_CUE);

                impact = allocate_flagged_object_node(0x212);
                if (impact != 0) {
                    impact->update_callback = grow_timed_sprite_effect;
                    register_node(impact, draw_linked_sprites_clipped);
                    impact_sprite = (s32)(impact->sprite);
                    ((SpriteFrameState *)impact_sprite)->tpage_abr = 0;
                    ((SpriteFrameState *)impact_sprite)->flags |= 0xC;
                    impact_position = (s32)(impact->position);
                    ((S_80024BE8_13 *)(void *)impact_position)->unk_02 = ((u16) motion->x.w.i);
                    ((S_80024BE8_13 *)(void *)impact_position)->unk_06 = ((u16) motion->y.w.i);
                    ((S_80024BE8_13 *)(void *)impact_position)->unk_08.at00.v = motion->z.v;
                    animation = D_800258FC;
                    impact_sprite = (s32)(impact->sprite);
                    ((SpriteFrameState *)impact_sprite)->source = animation;
                    ((SpriteFrameState *)impact_sprite)->color.c.b = random_intensity;
                    ((SpriteFrameState *)impact_sprite)->color.c.g = random_intensity;
                    ((SpriteFrameState *)impact_sprite)->color.c.r = random_intensity;
                    ((SpriteFrameState *)impact_sprite)->scale_y = 1;
                    ((SpriteFrameState *)impact_sprite)->scale_x = 1;
                    ((SpriteFrameState *)impact_sprite)->flags ^= 0xC;
                    ((S_80024BE8_13 *)(void *)impact_position)->unk_08.at02.v =
                        ((S_80024BE8_23 *)(((S_80024BE8_3 *)source)->unk_60))->unk_88;
                }
                motion->z.w.i = ((S_80024BE8_23 *)(((S_80024BE8_3 *)source)->unk_60))->unk_88;
            } else {
                ((S_80024BE8_0 *)effect)->unk_0A.s = 8;
                ((S_80024BE8_0 *)effect)->unk_82 = 0;
                sprite->color.c.b = 0;
                sprite->color.c.g = 0;
                sprite->color.c.r = 0;
            }
            break;
        }
        {
            motion->x.v += motion->velocity_x;
            motion->y.v += motion->velocity_y;
            motion->z.v += motion->velocity_z;

            random_intensity = rand();
            impact_position = random_intensity & 0xF;
            impact_position -= 8;
            impact_position <<= 16;
            impact_position >>= 16;
            impact_sprite = rand() & 0xF;
            impact_sprite -= 8;
            impact_sprite <<= 16;
            impact_sprite >>= 16;
            create_offset_paletted_sprite(effect, motion, sprite, impact_position, impact_sprite,
                (s16)((rand() & 0xF) - 8));
            impact_position = rand() & 0xF;
            impact_position -= 8;
            impact_position <<= 16;
            impact_position >>= 16;
            impact_sprite = rand() & 0xF;
            impact_sprite -= 8;
            impact_sprite <<= 16;
            impact_sprite >>= 16;
            create_offset_paletted_sprite(effect, motion, sprite, impact_position, impact_sprite,
                (s16)((rand() & 0xF) - 8));
            impact_position = rand() & 0xF;
            impact_position -= 8;
            impact_position <<= 16;
            impact_position >>= 16;
            impact_sprite = rand() & 0xF;
            impact_sprite -= 8;
            impact_sprite <<= 16;
            impact_sprite >>= 16;
            create_offset_paletted_sprite(effect, motion, sprite, impact_position, impact_sprite,
                (s16)((rand() & 0xF) - 8));
            impact_position = rand() & 0xF;
            impact_position -= 8;
            impact_position <<= 16;
            impact_position >>= 16;
            impact_sprite = rand() & 0xF;
            impact_sprite -= 8;
            impact_sprite <<= 16;
            impact_sprite >>= 16;
            create_offset_paletted_sprite(effect, motion, sprite, impact_position, impact_sprite,
                (s16)((rand() & 0xF) - 8));
            impact_position = rand() & 0xF;
            impact_position -= 8;
            impact_position <<= 16;
            impact_position >>= 16;
            impact_sprite = rand() & 0xF;
            impact_sprite -= 8;
            impact_sprite <<= 16;
            impact_sprite >>= 16;
            create_offset_paletted_sprite(effect, motion, sprite, impact_position, impact_sprite,
                (s16)((rand() & 0xF) - 8));
            impact_position = rand() & 0xF;
            impact_position -= 8;
            impact_position <<= 16;
            impact_position >>= 16;
            impact_sprite = rand() & 0xF;
            impact_sprite -= 8;
            impact_sprite <<= 16;
            impact_sprite >>= 16;
            create_offset_paletted_sprite(effect, motion, sprite, impact_position, impact_sprite,
                (s16)((rand() & 0xF) - 8));
            break;
        }
    }

    case 3:
    {
        s32 color_step;
        u16 previous_phase;

        color_step = ((S_80024BE8_0 *)effect)->unk_86.u;
        color_step += 2;
        ((S_80024BE8_0 *)effect)->unk_86.u = color_step;
        target_graphics = ((S_80024BE8_23_pre *)(((S_80024BE8_3 *)source)->unk_60))[-1].unk_04;
        ((S_80024BE8_14 *)target_graphics)->unk_0E = (s16)color_step * 3 - 0x70;
        ((S_80024BE8_14 *)target_graphics)->unk_0D = 0x70 - ((S_80024BE8_0 *)effect)->unk_86.s * 3;
        ((S_80024BE8_14 *)target_graphics)->unk_0C = 0x70 - ((S_80024BE8_0 *)effect)->unk_86.s * 3;
        if (((S_80024BE8_0 *)effect)->unk_86.s >= 0x24) {
            previous_phase = ((S_80024BE8_0 *)effect)->unk_0A.u;
            ((S_80024BE8_0 *)effect)->unk_86.u = 0;
            ((S_80024BE8_0 *)effect)->unk_82 = 0;
            ((S_80024BE8_0 *)effect)->unk_0A.u = previous_phase + 1;
            break;
        }
        break;
    }

    case 4:
    {
        void *animation;
        SpriteFrameState *particle_sprite;
        ObjectPosition *particle_position;
        s32 particle_kind;
        u16 direction_preload;
        s32 animation_mode;
        u16 previous_phase;
        s32 side;
        s32 jitter;
        s32 coord;
        s32 height;
        u16 scale_step;

        particle_count_m = 0;
        do {
            particle_count_m++;
            impact_sprite = rand() & 0x3F;
            impact_sprite -= 0x20;
            impact_sprite <<= 16;
            impact_sprite >>= 16;
            decrement_object_counter((u8 *)effect - 0x20, impact_sprite,
                (s16)((rand() & 0x3F) - 0x20),
                (s16)(-(((S_80024BE8_0 *)effect)->unk_86.s * 2) + 0x10), 0x1E);
        } while (particle_count_m < 2);

        particle_kind = 0x212;
        side = ((S_80024BE8_0 *)effect)->unk_86.u & 3;
        impact = allocate_flagged_object_node(particle_kind);
        if (impact != 0) {
            ((S_80024BE8_15 *)impact)->unk_22 = 0x1E;
            impact->update_callback = create_radial_height_offset_effect;
            register_node(impact, project_sprite_chain);
            particle_sprite = impact->sprite;
            particle_sprite->tpage_abr = 0;
            particle_sprite->flags |= 0xC;
            particle_position = impact->position;
            jitter = rand() & 0xF;
            coord = ((u16) motion->x.w.i);
            coord -= 8;
            coord += jitter;
            particle_position->x.w.i = coord;
            jitter = rand() & 0xF;
            coord = ((u16) motion->y.w.i);
            coord -= 8;
            coord += jitter;
            particle_position->y.w.i = coord;
            if (rand() & 1) {
                particle_sprite->flags |= 1;
            }

            switch (side) {
            case 0:
                particle_position->y.w.i = ((u16) motion->y.w.i) + 8;
                particle_sprite->depth_bias = 7;
                break;
            case 1:
                particle_position->x.w.i = ((u16) motion->x.w.i) - 8;
                particle_sprite->depth_bias = 7;
                break;
            case 2:
                particle_position->x.w.i = ((u16) motion->x.w.i) + 8;
                particle_sprite->depth_bias = 7;
                break;
            case 3:
                particle_position->y.w.i = ((u16) motion->y.w.i) - 8;
                particle_sprite->depth_bias = -7;
                break;
            }

            animation = countdown_sprite_entries;
            height = (motion->z.v);
            animation_mode = 0;
            particle_position->z.v = height;
            {
                SpriteFrameState *scaled_sprite;
                s32 scale;

                particle_sprite = impact->sprite;
                scale = ((S_80024BE8_0 *)effect)->unk_86.s;
                scaled_sprite = particle_sprite;
                scaled_sprite->scale_x = scale * 0xAA;
                scale = ((S_80024BE8_0 *)effect)->unk_86.s;
                scaled_sprite->color.c.b = 0x80;
                scaled_sprite->color.c.g = 0x80;
                scaled_sprite->color.c.r = 0x80;
                scaled_sprite->scale_y = scale * 0xCC;
                select_record_entry_and_value(scaled_sprite, animation, animation_mode);
            }
        }

        scale_step = ((S_80024BE8_0 *)effect)->unk_86.u + 2;
        ((S_80024BE8_0 *)effect)->unk_86.u = scale_step;
        if ((s16)scale_step >= 0x3D) {
            scale_step = 0x28;
            previous_phase = ((S_80024BE8_0 *)effect)->unk_0A.u;
            ((S_80024BE8_0 *)effect)->unk_86.u = scale_step;
            ((S_80024BE8_0 *)effect)->unk_0A.u = previous_phase + 1;
            break;
        }
        break;
    }

    case 5:
    {
        void *target_actor;
        void *current_target;
        s32 target_flag;
        u16 scale_step;

        particle_count_m = 0;
        do {
            particle_count_m++;
            impact_position = rand() & 0x3F;
            impact_position -= 0x20;
            impact_position <<= 16;
            impact_position >>= 16;
            impact_sprite = rand() & 0x3F;
            impact_sprite -= 0x20;
            impact_sprite <<= 16;
            impact_sprite >>= 16;
            decrement_object_counter((u8 *)effect - 0x20, impact_position, impact_sprite,
                (s16)(-0x20 - (rand() & 0x3F)), 0x1E);
        } while (particle_count_m < 2);

        scale_step = ((S_80024BE8_0 *)effect)->unk_86.u - 2;
        ((S_80024BE8_0 *)effect)->unk_86.u = scale_step;
        target_flag = 0x10000000;
        if ((s16)scale_step <= 0) {
            ((S_80024BE8_0 *)effect)->unk_86.u = 0;
            ((S_80024BE8_0 *)effect)->unk_82 = 0;
            ((S_80024BE8_0 *)effect)->unk_0A.s++;
            target_actor = ((S_80024BE8_3 *)source)->unk_60;
            ((S_80024BE8_19 *)target_actor)->unk_1C ^= target_flag;
            current_target = ((S_80024BE8_3 *)source)->unk_60;
            target_graphics = ((S_80024BE8_20_pre *)current_target)[-1].unk_00;
            ((S_80024BE8_21 *)target_graphics)->unk_0C = 0x80;
            ((S_80024BE8_21 *)target_graphics)->unk_0D = 0x80;
            ((S_80024BE8_21 *)target_graphics)->unk_0E = 0x80;
            apply_attack_power_and_element_effects(((S_80024BE8_3 *)source)->unk_60, 0x10, ((S_80024BE8_0 *)effect)->unk_09, 2,
                (s16)(((S_80024BE8_0 *)effect)->unk_7E.u << 9), source, 2);
        }
        break;
    }

    case 6:
    {
        u16 elapsed;

        elapsed = ((S_80024BE8_0 *)effect)->unk_82 + 1;
        ((S_80024BE8_0 *)effect)->unk_82 = elapsed;
        if ((s16)elapsed >= 0x3D) {
            ((S_80024BE8_0 *)effect)->unk_0A.s = 8;
            ((S_80024BE8_0 *)effect)->unk_82 = 0x1E;
        }
        break;
    }

    case 8:
    {
        u16 elapsed;
        s32 active;

        elapsed = ((S_80024BE8_0 *)effect)->unk_82;
        ((S_80024BE8_0 *)effect)->unk_82 = elapsed + 1;
        if ((s16)(elapsed + 1) >= 0x1F) {
            active = textured_effect_update_flag;
            ((S_80024BE8_0 *)effect)->unk_82 = elapsed;
            if (active == 0) {
                g_dungeon_status.active_actor = 0;
                ((ObjectNodeHeader *)((u8 *)effect - 0x20))->flags |= NODE_REMOVE;
                D_800814A0[0] |= 0x8000;
            } else {
                textured_effect_update_flag = 0;
            }
        }
        break;
    }
    }

    {
        u16 animation_tick;

        advance_sprite_animation_and_textures(sprite);
        animation_tick = ((S_80024BE8_0 *)effect)->unk_84;
        ((S_80024BE8_0 *)effect)->unk_84 = animation_tick + 1;
        if ((s16)animation_tick >= 5) {
            select_record_entry_and_value(sprite, effect_sprite_sources, 2);
            ((S_80024BE8_0 *)effect)->unk_84 = 0;
        }
    }
}
