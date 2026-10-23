#include "shared/audio_commands.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
/* Status application, shaded particles, terrain-seeking motion, and rotating target effects. */
#include "dungeon/effect/particle/view_parameter_transition.h"
#include "modules/dungeon_native_abi.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/gpu_packets.h"
#include "shared/game_work.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "shared/entity_height_offsets.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"

void (*const dungeon_188e800_entry)(MovingColorWork *, u8 *, u8 *) = update_moving_effect_particles_and_cleanup;
const u8 no_effect_target_prefix[48] = {0x82,0x73,0x82,0x88,0x82,0x85,0x82,0x92,0x82,0x85,0x81,0x40,0x82,0x97,0x82,0x81,0x82,0x93,0x81,0x40,0x82,0x8e,0x82,0x8f,0x81,0x40,0x82,0x85,0x82,0x86,0x82,0x86,0x82,0x85,0x82,0x83,0x82,0x94,0x81,0x40,0x82,0x8f,0x82,0x8e,0x81,0x40,0x0,0x0};
const u8 D_80024034[4] = {0x81,0x44,0x0,0x0};
const s16 D_80024038[8][2] = {{32,0},{32,32},{0,32},{-32,32},{-32,0},{-32,-32},{0,-32},{32,-32}};




extern s32 get_unused_text_buffer(void);
extern s32 expand_text_control_codes(u8 *src, u8 *dst);
extern void clear_byte_and_advance(s8 *byte_ptr);
extern s32 append_entity_display_text(void *record, u8 *out);
extern void adjust_source_value_and_finalize(void *, void *);
extern s32 try_trigger_target_record_effect(void *, s32);
extern s32 set_or_clear_actor_status_slot(void *, s32, s8);
extern void display_text_with_fullwidth_adjustment(s8 *text);
extern s32 get_random_scaled_value(s16 input_value);

extern const u8 no_effect_target_prefix[48];
extern const u8 D_80024034[4];
extern s32 D_800E1C64;



/* Applies effect 0x12 to an eligible entity and handles messages for flagged entities. */
extern s32 RotTransPers(void *, void *, void *, void *);
extern s32 GetTPage(s32, s32, s32, s32);
extern void SetDrawMode(void *, s32, s32, s32, s32);
extern s32 rand(void);
extern s16 D_80025308;
extern s32 rand(void);
extern s32 begin_view_parameter_transition(PointRecord *, ObjectPosition *);
extern void create_randomized_transform_effect();
extern s16 D_80025308;
s32 rsin(s16);                          /* extern */
s32 rcos(s16);                          /* extern */
extern int abs(int);
extern void *memcpy(void *, const void *, u32);
extern s32 get_sprite_attachment_vector();
extern void project_sprite_chain(void);
extern s32 rand(void);
extern s32 check_adjacent_tile_height_clearance();
extern s32 rsin();
extern s32 rcos();
extern void select_record_entry_and_value();
extern const s16 D_80024038[8][2];
extern void *D_80024058[9];
extern u8 D_800252FC[12];
extern s16 D_80025308;
extern u8 ribbon_sprite_entries[];

/* Attempts status slot 0x12 with a randomized value and displays the result when the target's message
   flag is set. */
void apply_random_actor_value_adjustment(S_func_8186E800_0 *entity, s32 effect_param, void *context)
{
    s32 message_end;
    s32 message_start;

    if (try_trigger_target_record_effect(entity, 1) == 0) {
        /*
         * Original bug: set_or_clear_actor_status_slot returns a slot index (0..3), or -1 on
         * failure. Testing it as nonzero misreports slot 0 as failure and -1 as success.
         * Slot-0 success instead prints the no-effect message; rejected insertion prints success.
         * try_apply_confusion_status uses the nonnegative success test.
         */
        if ((set_or_clear_actor_status_slot(entity, STATUS_FIRE_PROTECT,
                           (s8)(get_random_scaled_value(effect_param & 0xFF) + 2)) << 16) != 0) {
            if (entity->unk_14 & ACTOR_PARTY_MEMBER) {
                adjust_source_value_and_finalize(entity, &D_800E1C64);
                return;
            }
        } else if (entity->unk_14 & ACTOR_PARTY_MEMBER) {
            message_end = get_unused_text_buffer();
            message_start = message_end;
            message_end = expand_text_control_codes(&no_effect_target_prefix, message_end);
            message_end = append_entity_display_text(entity, message_end);
            message_end = expand_text_control_codes(&D_80024034, message_end);
            clear_byte_and_advance(message_end);
            display_text_with_fullwidth_adjustment(message_start);
        }
    }
}


/* Retail 8186E96C (begin_view_parameter_transition): projects each linked point and queues a brightness-scaled shaded point
 * followed by a draw-mode packet for it. */
s32 begin_view_parameter_transition(PointRecord *start_node, ObjectPosition *start_coords)
{
    GpuContext **state_ptr;
    Scratch8002416C *scratch;
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
    scratch = (Scratch8002416C *)0x1F800000;

    scratch->cursor = render_state->packetCursor;
    scratch->ot = (u32 *)&render_state->orderTag;

    for (;;) {
        coord_x = (u16)coords->x.w.i;
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

        prev_entry = ((ObjectNodeHeader *)node - 1)->chain_next;
        node = (PointRecord *)(prev_entry + 1);
        if (prev_entry == 0) {
            break;
        }
        coords = prev_entry->position;
    }

    final_state = *state_ptr;
    final_state->packetCursor = scratch->cursor;
    return 0;
}




/* Raise the position toward the queried height and set flags when the countdown expires. */
void create_randomized_transform_effect(u8 *state, UnkArg1 *position)
{
    u16 countdown;

    D_80025308 = 1;
    if ((s16)position->value.half.unkA <
        (s16)sample_terrain_surface_height(position->unk2, position->unk6,
                      (s16)(position->value.half.unkA + 2))) {
        position->value.unk8 += 0x20000 + (rand() & 0xFFF);
    }

    countdown = *(u16 *)(state + 0x32) - 8;
    *(u16 *)(state + 0x32) = countdown;
    if ((s32)(countdown << 16) <= 0) {
        *(u16 *)(state - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}


/* Retail 8186EC88 (spawn_parent_attached_effect): spawn an effect object under the parent node, placed at the parent's
 * position plus a random jitter (0..31 per axis) and the given offsets (minus half the jitter range). */
void spawn_parent_attached_effect(ObjectNodeHeader *parent, s16 field_34, s32 field_28, s16 field_52, s16 offset_x,
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
        spawned->update_callback = (void *)create_randomized_transform_effect;
        jitter_x = rand() & 0x1F;
        position_x = ((ObjectPosition *)source_obj->position)->x.w.i;
        dest_x = spawned->position;
        position_x += jitter_x;
        bias_x = offset_x - 0x10;
        position_x += bias_x;
        dest_x->x.w.i = position_x;

        jitter_y = rand() & 0x1F;
        position_y = ((ObjectPosition *)source_obj->position)->y.w.i;
        dest_y = spawned->position;
        position_y += jitter_y;
        bias_y = offset_y - 0x10;
        position_y += bias_y;
        dest_y->y.w.i = position_y;

        jitter_z = rand();
        jitter_z &= 0x1F;
        position_z = ((ObjectPosition *)source_obj->position)->z.w.i;
        fields = (PointRecord *)(spawned + 1);
        dest_z = spawned->position;
        position_z += jitter_z;
        bias_z = offset_z - 0x10;
        position_z += bias_z;
        dest_z->z.w.i = position_z;
        fields->unk_14 = field_34;
        fields->brightness = saved_field_52;
        register_node(spawned, (s32)begin_view_parameter_transition);
        fields->color = saved_field_28;
    }
}

   /* arg1 in func_8186EDA8 */

   /* arg0 in func_8186EDA8; pointer addresses record offset 0x2 */


/* cfail-repair: tf7-phase1-cache-v3 */





typedef struct RotatingStatusPrefix { u16 flags; } RotatingStatusPrefix;

/* Updates a rotating dungeon effect through delay, contraction, fade, and completion. */
void advance_rotating_fading_effect(DungeonState *anim, S_8186EDA8_0 *position, DungeonEffect *input_effect) {
    s16 phase;
    s16 fade_angle;
    s16 shrink_angle;
    s16 radius;
    s32 radius_step;
    u16 delay_timer;
    u16 finish_timer;
    u8 fade_level;
    DungeonEffect *effect = input_effect;
    s32 first_angle = anim->angle;


    position->unk_00 = (s32) (anim->base0 + (anim->count * rsin((*(u16 *)&D_80025308 = 1,
        first_angle)) * 0x10));
    position->unk_04 = (s32) (anim->base1 + (anim->count * rcos(anim->angle) * 0x10));
    advance_sprite_animation_and_textures(effect);
    phase = anim->state;
    switch (phase) {
    case 0:
        delay_timer = anim->timer - 1;
        anim->timer = delay_timer;
        if ((delay_timer << 0x10) <= 0) {
            anim->state = (s16) ((u16) anim->state + 1);
        }
        break;
    case 1:
        shrink_angle = (u16) anim->angle - anim->angle2;
        anim->angle = shrink_angle;
        if (shrink_angle < 0) {
            anim->angle = (s16) (shrink_angle + 0x1000);
        }
        if ((s16) anim->angle2 < 0x7F8) {
            anim->angle2 = (u16) (anim->angle2 + 8);
        }
        radius = anim->count;
        if (radius >= 0x41) {
            if (radius >= 0x65) {
                radius_step = 3;
            } else if (radius >= 0x47) {
                radius_step = 2;
            } else if (radius >= 0x33) {
                radius_step = 2;
            } else {
                radius_step = 1;
            }
            anim->count = (s16) ((u16) anim->count
                - radius_step);
            effect->x1C -= 0x46;
            effect->y1E -= 0x46;
            effect->c += 4;
            effect->d += 4;
            effect->e += 4;
            break;
        }
        anim->timer = 0x28U;
        anim->state = (s16) ((u16) anim->state
            + 1);
        break;
    case 2:
        fade_angle = (u16) anim->angle - anim->angle2;
        anim->angle = fade_angle;
        if (fade_angle < 0) {
            anim->angle = (s16) (fade_angle + 0x1000);
        }
        if ((s16) anim->angle2 < 0x100) {
            anim->angle2 = (u16) (anim->angle2 + 8);
        }
        radius = anim->count;
        if (radius >= 0x1B) {
            anim->count = (s16) (radius - 1);
        }
        fade_level = effect->c;
        if (fade_level >= 2U) {
            effect->c = (u8) (fade_level - 2);
            effect->d -= 2;
            effect->e -= 2;
        }
        if (effect->c == 0) {
            anim->timer = 0U;
            anim->state = (s16) ((u16) anim->state + 1);
        }
        effect->x1C -= 0x14;
        effect->y1E += 0xC8;
        break;
    case 3:
        finish_timer = anim->timer - 1;
        anim->timer = finish_timer;
        if ((finish_timer << 0x10) <= 0) {
            ((RotatingStatusPrefix *)anim)[-1].flags = (u16) (((RotatingStatusPrefix *)anim)[-1].flags
                | 0x8000);
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
        break;
    }
    if (effect->flags14 & 0x8000) {
        ((RotatingStatusPrefix *)anim)[-1].flags = (u16) (((RotatingStatusPrefix *)anim)[-1].flags | 0x8000);
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
    return;

}


#define S8_AT(p, o)  (*(s8 *)((u8 *)(p) + (o)))
#define U8_AT(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PTR_AT(p, o) (*(u8 **)((u8 *)(p) + (o)))





/* Updates a moving effect, its particles, target color animation, and cleanup. */
void update_moving_effect_particles_and_cleanup(MovingColorWork *effect_data, u8 *effect_pos, u8 *effect_display) {
    s16 origin_offset[4];
    OffsetPair direction_offsets[8];
    u8 *display = effect_display;
    u8 *owner;
    u8 *entity;
    u8 *source;
    u8 *copy_page;
    u8 *copy_source;
    void **jump_table;
    s32 state;

    owner = effect_data->owner;
    copy_page = (u8 *)0x80020000;
    *(AggU32 *)direction_offsets = *(AggU32 *)&D_80024038;
    state = effect_data->state;
    entity = owner - 0x20;
    source = PTR_AT(entity, 0x08);
    switch (state) {
    case 0:
        S32_AT(display, 0x0C) = 0x00808080;
        U16_AT(display, 0x1E) = 0x1000;
        U16_AT(display, 0x1C) = 0x1000;
        copy_page = (u8 *)0x80020000;
        copy_source = D_800252FC;
        memcpy(effect_data->sprite_data.bytes, copy_source, 12);
        PTR_AT(display, 0x08) = effect_data->sprite_data.bytes;
        {
            u32 owner_bits = U16_AT(owner, 0x2A);

            D_80025308 = 1;
            effect_data->direction = (owner_bits >> 9) & 7;
            effect_data->state++;
        }

    case 1:
    {
        u8 *record = PTR_AT(entity, 0x0C);
        s32 has_origin;

        has_origin = get_sprite_attachment_vector(PTR_AT(record, 0x08), record, origin_offset, 0);
        if (has_origin == 0 && !(U16_AT(PTR_AT(entity, 0x0C), 0x14) & 0x8000)) {
            break;
        }

        U16_AT(effect_pos, 0x02) = U16_AT(source, 0x02);
        U16_AT(effect_pos, 0x06) = U16_AT(source, 0x06);
        state = U16_AT(source, 0x0A);
        U16_AT(effect_pos, 0x0A) = state;

        if (!(U16_AT(PTR_AT(entity, 0x0C), 0x14) & 0x8000)) {
            U16_AT(effect_pos, 0x02) += (u16)origin_offset[0];
            U16_AT(effect_pos, 0x06) += (u16)origin_offset[1];
            U16_AT(effect_pos, 0x0A) += (u16)origin_offset[2];
            {
                u8 *task = (u8 *)effect_data - 0x20;

                if (!(effect_data->flags & 4)) {
                    register_node(task, (s32)project_sprite_chain);
                    U16_AT(display, 0x10) = 0x20;
                    U8_AT(display, 0x0E) = 0x14;
                    U8_AT(display, 0x0D) = 0x14;
                    U8_AT(display, 0x0C) = 0x14;
                    U16_AT(display, 0x14) |= 0x0C;
                    effect_data->flags |= 4;
                }
            }
        } else {
            U16_AT(effect_pos, 0x0A) = (u16)(state - 0x40);
            {
                u8 *task = (u8 *)effect_data - 0x20;

                if (!(effect_data->flags & 4)) {
                    register_node(task, (s32)project_sprite_chain);
                    U16_AT(display, 0x10) = 0x20;
                    U8_AT(display, 0x0E) = 0x14;
                    U8_AT(display, 0x0D) = 0x14;
                    U8_AT(display, 0x0C) = 0x14;
                    U16_AT(display, 0x14) |= 0x0C;
                    effect_data->flags |= 4;
                }
            }
        }

        if (!(effect_data->animation->flags & 0x80)) {
            break;
        }

        {
            u32 target = (u32)PTR_AT(owner, 0x60);
            if (target != 0) {
                u8 *sprite;
                s32 delta;

                {

                    u32 table;

                    copy_source = PTR_AT((u8 *)target, -0x18);
                    table = (u32)entity_height_offsets;
                    target = U8_AT((u8 *)target, 0x13);
                    target += table;
                    table = U8_AT((u8 *)target, 0x00);
                    target = U16_AT(copy_source, 0x0A);
                    table += 0x20;
                    target -= table;

                    table = (u32)((u8 *)dir_step_x);
                    effect_data->target_height.s = target;
                    target = effect_data->direction;
                    sprite = PTR_AT(owner, -0x14);
                    target <<= 1;
                    target += table;
                    table = U8_AT(sprite, 0x24);
                    target = U8_AT((u8 *)target, 0x00);
                    table += target;
                    effect_data->next_tile_x = table;

                    table = (u32)((u8 *)dir_step_y);
                    target = effect_data->direction;
                    target <<= 1;
                    target += table;
                    table = U8_AT(sprite, 0x25);
                    target = U8_AT((u8 *)target, 0x00);
                    table += target;
                    effect_data->next_tile_y = table;
                }

                {
                    s32 owner_axis = S8_AT(owner, 0x72);
                    u32 sprite_axis = U8_AT(sprite, 0x24);

                    if (owner_axis != sprite_axis) {
                    } else {
                        owner_axis = S8_AT(owner, 0x73);
                        sprite_axis = U8_AT(sprite, 0x25);
                    }
                    delta = owner_axis - sprite_axis;
                }
                delta = abs(delta);
                effect_data->flight_ticks.u = (u8)((delta * 2) - 1);
            } else {
                s32 height = U16_AT(owner, 0x88);
                effect_data->flight_ticks.u = 0x20;
                effect_data->target_height.s = (s16)(height - 0x50);
            }

        }
        S32_AT(effect_pos, 0x0C) = direction_offsets[effect_data->direction].x << 16;
        S32_AT(effect_pos, 0x10) = (u16)direction_offsets[effect_data->direction].y << 16;
        S32_AT(effect_pos, 0x14) = ((effect_data->target_height.s << 16) -
            S32_AT(effect_pos, 0x08)) / effect_data->flight_ticks.s;
        {
            s8 timer = effect_data->flight_ticks.s;
            s16 timer_copy;
            s32 duration_squared;

            timer_copy = timer;
            duration_squared = timer * timer_copy;
            effect_data->timer.s = 0;
            effect_data->state++;
            effect_data->initial_ticks = effect_data->flight_ticks.s;
            effect_data->ticks_squared = duration_squared;
        }
        break;
    }

    case 2:
    {
        for (entity = 0; (s32)entity < 4; entity++) {
            {
                s32 random = rand();
                u8 *task;
                s32 particle_color;
                s32 particle_param;

                task = (u8 *)effect_data - 0x20;
                particle_color = 0x002020E0;
                random &= 0xFF;
                particle_param = random | 0x80;
                spawn_parent_attached_effect(task, effect_data->direction, particle_color, particle_param, 0, 0, 0);
            }
        }

        if (effect_data->sprite_phase == 0) {
            effect_data->sprite_phase = 1;
            effect_data->sprite_data.fields.unk_9C += 0x18;
        } else {
            effect_data->sprite_phase = 0;
            effect_data->sprite_data.fields.unk_9C -= 0x18;
        }

        {
            s32 timer = effect_data->initial_ticks;
            s32 remaining = effect_data->flight_ticks.s;
            timer -= remaining;
            U8_AT(display, 0x0C) = (((timer * timer) * 7) << 5) /
                effect_data->ticks_squared + 0x14;
        }
        {
            s32 timer = effect_data->initial_ticks;
            s32 remaining = effect_data->flight_ticks.s;
            timer -= remaining;
            U8_AT(display, 0x0D) = ((timer * timer) << 7) /
                effect_data->ticks_squared + 0x14;
        }
        {
            s32 timer = effect_data->initial_ticks;
            s32 remaining = effect_data->flight_ticks.s;
            timer -= remaining;
            U8_AT(display, 0x0E) = ((timer * timer) << 7) /
                effect_data->ticks_squared + 0x14;
        }

        if ((check_adjacent_tile_height_clearance(U16_AT(effect_pos, 0x02), U16_AT(effect_pos, 0x06),
                S16_AT(effect_pos, 0x0A), PTR_AT(owner, 0x60)) << 16) != 0) {
            effect_data->state = 8;
            effect_data->timer.s = 0;
            U8_AT(display, 0x0E) = 0;
            U8_AT(display, 0x0D) = 0;
            U8_AT(display, 0x0C) = 0;
            break;
        }

        effect_data->flight_ticks.u--;
        if (effect_data->flight_ticks.s <= 0) {
            if (PTR_AT(owner, 0x60) != 0) {

                effect_data->state = 3;
                effect_data->timer.s = 0;
                copy_source = PTR_AT(PTR_AT(owner, 0x60), -0x18);
                U16_AT(effect_pos, 0x02) = U16_AT(copy_source, 0x02);
                U16_AT(effect_pos, 0x06) = U16_AT(copy_source, 0x06);
                U16_AT(effect_pos, 0x0A) = effect_data->target_height.u;
                play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
                break;
            }

            effect_data->state = 8;
            effect_data->timer.s = 0;
            U8_AT(display, 0x0E) = 0;
            U8_AT(display, 0x0D) = 0;
            U8_AT(display, 0x0C) = 0;
            break;
        }

        S32_AT(effect_pos, 0x00) += S32_AT(effect_pos, 0x0C);
        S32_AT(effect_pos, 0x04) += S32_AT(effect_pos, 0x10);
        S32_AT(effect_pos, 0x08) += S32_AT(effect_pos, 0x14);
        break;
    }

    case 3:
    {
        if (effect_data->sprite_phase == 0) {
            effect_data->sprite_phase = 1;
            effect_data->sprite_data.fields.unk_9C += 0x18;
        } else {
            effect_data->sprite_phase = 0;
            effect_data->sprite_data.fields.unk_9C -= 0x18;
        }

        source = (u8 *)allocate_flagged_object_node(0x212);
        if (source != 0) {
            s32 trig;

            entity = source + 0x20;
            {
                u16 spawn_count = effect_data->timer.u;
                S16_AT(entity, 0x0A) = 0x80;
                S16_AT(entity, 0x02) = 8 - spawn_count;
            }
            {
                s32 spawn_counter = effect_data->timer.s;
                S16_AT(entity, 0x0C) = spawn_counter << 9;
            }
            copy_source = PTR_AT(PTR_AT(owner, 0x60), -0x18);
            S32_AT(entity, 0x4C) = S32_AT(copy_source, 0x00);
            S32_AT(entity, 0x50) = S32_AT(copy_source, 0x04);
            S32_AT(source, 0x10) = (s32)advance_rotating_fading_effect;
            register_node(source, project_sprite_chain);

            {
                u8 *spawn_display = PTR_AT(source, 0x0C);
                U16_AT(spawn_display, 0x10) = 0x20;
                U16_AT(spawn_display, 0x14) |= 0x0C;
            }
            display = PTR_AT(source, 0x08);

            trig = rsin(S16_AT(entity, 0x0C));
            S32_AT(display, 0x00) = S32_AT(entity, 0x4C) +
                (S16_AT(entity, 0x0A) * trig * 0x10);
            trig = rcos(S16_AT(entity, 0x0C));
            S32_AT(display, 0x04) = S32_AT(entity, 0x50) +
                (S16_AT(entity, 0x0A) * trig * 0x10);
            S32_AT(display, 0x08) = S32_AT(effect_pos, 0x08) +
                (entity_height_offsets[U8_AT(PTR_AT(owner, 0x60), 0x13)] << 16);

            {
                u8 *spawn_display = PTR_AT(source, 0x0C);
                U16_AT(spawn_display, 0x1E) = 0x1000;
                U16_AT(spawn_display, 0x1C) = 0x1000;
                U8_AT(spawn_display, 0x0E) = 0x14;
                U8_AT(spawn_display, 0x0D) = 0x14;
                U8_AT(spawn_display, 0x0C) = 0x14;
                select_record_entry_and_value(spawn_display, ribbon_sprite_entries, 0);
            }
        }

        effect_data->timer.s++;
        if (effect_data->timer.s == 8) {
            effect_data->state = 4;
            effect_data->timer.s = 0;
        }
        break;
    }

    case 4:
    {
        s32 fade_frame;
        u8 *target_display;

        effect_data->timer.u++;
        fade_frame = effect_data->timer.s;
        if (fade_frame < 20) {
            U8_AT(display, 0x0C) = ((20 - effect_data->timer.s) * 0xE0) / 20;
            U8_AT(display, 0x0D) = ((20 - effect_data->timer.s) * 0x80) / 20;
            U8_AT(display, 0x0E) = ((20 - effect_data->timer.s) * 0x80) / 20;

            if (effect_data->sprite_phase == 0) {
                effect_data->sprite_phase = 1;
                effect_data->sprite_data.fields.unk_9C += 0x18;
            } else {
                effect_data->sprite_phase = 0;
                effect_data->sprite_data.fields.unk_9C -= 0x18;
            }

            for (entity = 0; (s32)entity < 4; entity++) {
                {
                    s32 random = rand();
                    u8 *task;
                    s32 particle_color;
                    s32 particle_param;

                    task = (u8 *)effect_data - 0x20;
                    particle_color = 0x002020E0;
                    random &= 0xFF;
                    particle_param = random | 0x80;
                    spawn_parent_attached_effect(task, effect_data->direction, particle_color, particle_param, 0, 0, 0);
                }
            }
        }

        if (effect_data->timer.s >= 50) {
            u8 *target = PTR_AT(owner, 0x60);

            S32_AT(target, 0x1C) |= 0x10000000;
            target_display = PTR_AT(target, -0x14);
            if (effect_data->timer.s >= 76) {
                U8_AT(target_display, 0x0E) += 3;
                U8_AT(target_display, 0x0D) += 3;
                U8_AT(target_display, 0x0C) -= 4;
            } else {
                U8_AT(target_display, 0x0E) -= 3;
                U8_AT(target_display, 0x0D) -= 3;
                U8_AT(target_display, 0x0C) += 4;
            }
        }

        if (effect_data->timer.s >= 101) {
            u8 *target = PTR_AT(owner, 0x60);
            target_display = PTR_AT(target, -0x14);

            S32_AT(target, 0x1C) &= 0xEFFFFFFF;
            U8_AT(target_display, 0x0E) = 0x80;
            U8_AT(target_display, 0x0D) = 0x80;
            U8_AT(target_display, 0x0C) = 0x80;
            apply_random_actor_value_adjustment(PTR_AT(owner, 0x60), effect_data->variant, owner);
            effect_data->state = 8;
            effect_data->timer.s = 0x1E;
        }
        break;
    }

    case 8:
    {
        u16 old_frame = effect_data->timer.u;
        s16 next_frame = (s16)(old_frame + 1);

        effect_data->timer.u = (u16)next_frame;
        if (next_frame >= 31) {
            {
                s32 effect_active = D_80025308;
                effect_data->timer.u = old_frame;
                if (effect_active == 0) {
                    g_dungeon_status.active_actor = 0;
                    ((RotatingStatusPrefix *)effect_data)[-1].flags |= NODE_REMOVE;
                    object_flag_block.flags |= OBJECT_REMOVE_PENDING;
                } else {
                    D_80025308 = 0;
                }
            }
        }
    }

    default:
        break;
    }
}
