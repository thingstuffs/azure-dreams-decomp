#include "shared/object_node_flags.h"
#include "shared/audio_commands.h"
/* Moving attack visuals, linked particle creation, and timed view parameter updates. */
#include "shared/entity.h"
#include "shared/object_node.h"
#include "dungeon/effect/motion/interpolate_view_parameters.h"
#include "shared/object_flags.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/effect/motion/interpolate_view_parameters.h"
/* Selector entry invokes this complete native state machine. */
void (*const D_80024000)(Row_81917C08_ActionState *action, Row_81917C08_EffectMotion *motion, Row_81917C08_EffectVisual *visual) = build_inverted;

/* Eases the camera toward its tracked object, blends the vertical view offset, and damps horizontal
   view offsets. */
void interpolate_view_parameters(void *tracker) {
    s16 blend_ticks;
    s16 next_ticks;
    Row_81916800_S_81916800_2 *target_values;
    GameView *blend_state;
    u8 *countdown;
    u8 *third_pending;

    blend_ticks = (*(s16 *)((u8 *)tracker + 0x24));
    blend_state = &g_game_work.view;
    if (blend_ticks > 0) {
        blend_state->view_offset.parts.view_offset_z = (u16) ((u16)blend_state->view_offset.parts.view_offset_z) + ((s32) ((*(s16 *)((u8 *)tracker + 0x26))
            - blend_state->view_offset.parts.view_offset_z) / blend_ticks);
    }
    next_ticks = (u16) (*(s16 *)((u8 *)tracker + 0x24)) - 1;
    (*(s16 *)((u8 *)tracker + 0x24)) = next_ticks;
    if (next_ticks < -0x80) {
        (*(s16 *)((u8 *)tracker + 0x24)) = -0x80;
    }
    countdown = ((u8 *)camera_transition_timer);
    if (((Row_81916800_S_81916800_1 *)countdown)->unk_00.u != 0) {
        ((Row_81916800_S_81916800_1 *)countdown)->unk_00.s = (s8) (((Row_81916800_S_81916800_1 *)countdown)->unk_00.u - 1);
    }
    (*(u16 *)((u8 *)tracker + 4)) = (u16) ((Row_81916800_S_81916800_4 *)(*(void **)((u8 *)tracker + 0xC)))->unk_02;
    target_values = (*(void **)((u8 *)tracker + 0xC));
    (*(u16 *)((u8 *)tracker + 6)) = (u16) target_values->unk_06;
    (*(u16 *)((u8 *)tracker + 8)) = (u16) target_values->unk_0A;
    blend_state->camera_position.parts.camera_position_x = (u16) ((u16)blend_state->camera_position.parts.camera_position_x) + ((s32) ((s16) (*(u16 *)((u8 *)tracker + 4))
        - blend_state->camera_position.parts.camera_position_x) >> 2);
    blend_state->camera_position.parts.camera_position_y = (u16) ((u16)blend_state->camera_position.parts.camera_position_y) + ((s32) ((s16) (*(u16 *)((u8 *)tracker + 6))
        - blend_state->camera_position.parts.camera_position_y) >> 2);
    third_pending = D_80025B1C;
    if (((Row_81916800_S_81916800_3 *)third_pending)->unk_00.u != 0) {
        blend_state->camera_position.parts.camera_position_z = (u16) ((u16)blend_state->camera_position.parts.camera_position_z) + ((s32) ((s16) (*(u16 *)((u8 *)tracker + 8))
            - blend_state->camera_position.parts.camera_position_z) >> 2);
    }
    ((Row_81916800_S_81916800_3 *)third_pending)->unk_00.s = (s8) (blend_state->camera_position.parts.camera_position_z != (s16) (*(u16 *)((u8 *)tracker + 8)));
    blend_state->view_offset.parts.view_offset_x = (u16) ((s32) (((u16)blend_state->view_offset.parts.view_offset_x) << 0x10) >> 0x12);
    blend_state->view_offset.parts.view_offset_y = (u16) ((s32) (((u16)blend_state->view_offset.parts.view_offset_y) << 0x10) >> 0x12);
}

/* Sets camera tracking mode 12, its target and timing, installs the tracking callback, and returns
   change flags. */
s32 begin_view_parameter_transition(s32 unused, s32 request_id, s32 request_value, s16 request_param) {
    GameView *state = &g_game_work.view;
    Row_8191696C_S_8191696C_state *dispatch = (Row_8191696C_S_8191696C_state *)&state->slot[0].unk_04;
    void *payload_start = (void *)((u8 *)&state->slot[0].unk_04 + 4);
    s16 saved_value;
    s32 prev_request_id;
    s32 change_flags;

    prev_request_id = dispatch->unkC4;
    dispatch->unkC4 = request_id;
    dispatch->unkE0 = 0;
    dispatch->field_B8 = payload_start;
    saved_value = request_value;
    change_flags = prev_request_id != request_id;
    if (dispatch->unkCC != 9) {
        change_flags |= 2;
    }
    dispatch->unkCC = 0xC;
    dispatch->unkD0 = 0;
    dispatch->unkDE = request_param;
    state->slot[0].callback = view_interpolation_update_address;
    if (change_flags & 1) {
        ((s8 *)camera_transition_timer)[0] = saved_value;
    }
    dispatch->unkDC = request_value;
    return change_flags;
}

/* Moves an animated sprite along its heading with decreasing speed and a fixed vertical step until its
   duration ends. */
void advance_motion_counters_position_set_completion_flags_past_lifetime(void *motion, void *position, s32 update_context)
{
    s32 y_step;
    void *motion_state;
    void *page;
    void *owner;
    owner = *((void **) (((s8 *) motion) + 0));
    *((u16 *) (((s8 *) owner) + 0x14)) = (u16) ((*((u16 *) (((s8 *) owner) + 0x14))) + 1);
    *((u16 *) (((s8 *) motion) + 4)) = (u16) ((*((u16 *) (((s8 *) motion) + 4))) + 1);
    advance_sprite_animation_and_textures(update_context);
    *((s32 *) (((s8 *) position) + 0)) = (s32) ((*((s32 *) (((s8 *) position) + 0)))
        + ((rcos(*((s16 *) (((s8 *) motion) + 0xA))) >> 4) * (((*((s16 *) (((s8 *) motion) + 8)))
        - ((s16) (*((u16 *) (((s8 *) motion) + 4))))) << 8)));
    y_step = (rsin(*((s16 *) (((s8 *) motion) + 0xA))) >> 4) * (((*((s16 *) (((s8 *) motion) + 8)))
        - ((s16) (*((u16 *) (((s8 *) motion) + 4))))) << 8);
    *((s32 *) (((s8 *) position) + 8)) = (s32) ((*((s32 *) (((s8 *) position) + 8))) + 0xFFFE0000);
    motion_state = motion;
    *((s32 *) (((s8 *) position) + 4)) = (s32) ((*((s32 *) (((s8 *) position) + 4))) + y_step);
    if (((s16) (*((u16 *) (((s8 *) motion_state) + 4)))) > (*((s16 *) (((s8 *) motion_state) + 6)))) {
        *((u16 *) (((s8 *) motion_state) + (-2))) = (u16) ((*((u16 *) (((s8 *) motion_state) + (-2)))) | 0x8000);
        page = (void *) 0x80080000;
        *((s32 *) (((s8 *) page) + 0x14A0)) = (s32) ((*((s32 *) (((s8 *) page) + 0x14A0))) | 0x8000);
    }
}
/* MECHANISM: The seed preserves the 0x20 frame and the long-lived s1/s0 argument bases.
   A literal 0x80080000 page local held by ASM_KEEP emits the branch-delay lui in v1.
   Both flag RMW accesses use +0x14A0 from that base, closing all three addressing words. */

/* Creates a blue-tinted sprite with copied motion, two eight-step counters, and facing copied from the
   source. */
void *create_an_initializes_visual_state_copies_initial_data(s32 object_id, void *initial_data, Row_81916AEC_S_800242EC_2 *source)
{
    SpriteFrameState *visual;
    ObjectNodeHeader *object;
    Row_81916AEC_S_800242EC_1 *state;
    Row_81916AEC_Copy6 *object_data;
    void *result;

    object = allocate_flagged_object_node(0x212);
    if (object != NULL) {
        state = (u8 *)object + 0x20;
        object->update_callback = &D_800241E4;
        ((Row_81916AEC_S_800242EC_0 *)object)->unk_20 = object_id;
        state->unk_04 = 0;
        state->unk_06 = 8;
        state->unk_08 = 8;
        state->unk_0A = source->unk_2A;
        visual = object->sprite;
        visual->color.c.g = 0x30;
        visual->color.c.r = 0x30;
        visual->color.c.b = 0xC0;
        visual->clut = 0x7DCF;
        visual->flags |= 0xC;
        visual->tpage_abr |= 0x20;
        visual->flags |= 0x100;
        select_record_entry_and_value(visual, &shared_sprite_entries, 0);
        visual->scale_y = 0x1000;
        visual->scale_x = 0x1000;
        register_node(object, project_sprite_chain);
        object_data = *(Row_81916AEC_Copy6 * *)&object->position;
        result = object;
        *object_data = *(Row_81916AEC_Copy6 *)initial_data;
        return object;
    }
    return NULL;
}

/* Queues a translucent screen polygon with a countdown-dependent edge and removes the controller when
   the count ends. */
void create_counted_sprite_effect(void *context, s32 unused, Row_81916C1C_Arg81916C1C *countdown)
{
    Row_81916C1C_Inner81916C1C *tick_state;
    Row_81916C1C_State81916C1C *render_state;
    Row_81916C1C_Prim81916C1C *prim;
    s32 step;
    s8 x_value;
    s8 remaining;

    tick_state = *(Row_81916C1C_Inner81916C1C **)context;
    tick_state->counter++;
    render_state = g_game_work.draw_buffer;
    prim = render_state->next;
    render_state->next = prim + 1;
    prim->x3 = 0x140;
    prim->x2 = 0;
    prim->y2 = 0;
    prim->y3 = 0xE0;
    step = countdown->count;
    prim->y0 = 0xC0;
    x_value = -0x40 - step * 0x30;
    prim->x1 = x_value;
    prim->x0 = x_value;
    SetTile(prim, step);
    prim->flags |= 2;
    AddPrim((u8 *)g_game_work.draw_buffer + 0xB0, prim);
    remaining = (u8)countdown->count - 1;
    countdown->count = remaining;
    if ((remaining << 24) == 0) {
        *(u16 *)((u8 *)context - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

void create_a_type_hex_212_initializes_handler_mode(s32 initial_value) {
    Row_81916D2C_S_8002452C_0 *object;

    object = allocate_flagged_object_node(0x212);
    if (object != NULL) {
        object->unk_10 = &D_8002441C;
        ((ObjectNodeHeader *)object)->sprite->frame_ticks = 4;
        object->unk_20 = initial_value;
    }
}

/* Advances sprite animation and, when it finishes, removes the child and increments the owner's
   completion counter. */
void update_the_target_records_counts_flags_status(void *object_slot, void *unused, SpriteFrameState *target)
{
    void *post_object;
    void *pre_object;

    pre_object = *(void **)object_slot;
    *(u16 *)((u8 *)pre_object + 0x14) += 1;
    advance_sprite_animation_and_textures(target);
    if (target->flags & 0x6000) {
        u16 object_count;
        u16 slot_flags;
        s32 global_flags;

        slot_flags = *(u16 *)((u8 *)object_slot - 2);
        post_object = *(void **)object_slot;
        *(u16 *)((u8 *)object_slot - 2) = slot_flags | 0x8000;
        global_flags = object_flag_block.flags;
        object_count = *(u16 *)((u8 *)post_object + 0x18);
        object_flag_block.flags = global_flags | 0x8000;
        *(u16 *)((u8 *)post_object + 0x18) = object_count + 1;
    }
}

/* Creates a gray animated sprite with copied motion and the owner's link for completion bookkeeping. */
void *create_an_default_rendering_settings_copies_initial_data(s32 *owner_data, Row_81916E00_Copy24 *initial_data) {
    s32 owner_value;
    SpriteFrameState *render_state;
    Row_81916E00_S_80024600_0 *object;
    Row_81916E00_Copy24 *object_data;

    object = allocate_list_node(0x212, (s8 *) owner_data - 0x20);
    if (object != NULL) {
        object->unk_10 = &D_8002457C;
        owner_value = *owner_data;
        render_state = object->unk_0C;
        object->unk_24 = 0;
        object->unk_20 = owner_value;
        render_state->color.word = 0x808080;
        render_state->clut = 0x7DCF;
        render_state->flags = (u16) (render_state->flags | 0xC);
        render_state->tpage_abr = (u16) (render_state->tpage_abr | 0x60);
        render_state->flags = (u16) (render_state->flags | 0x100);
        select_record_entry_and_value(render_state, &rotating_particle_sprite_entries, 0);
        render_state->scale_y = 0x1000;
        render_state->scale_x = 0x1000;
        register_node(object, project_sprite_chain);
        object_data = object->unk_08;
        *object_data = *initial_data;
        return object;
    } else {
        return NULL;
    }
}

/* Advances a point along the radial direction given by two angles and increments the owner's update
   counter. */
void advance_the_counter_offset_position_using_two_angles(Row_81916F10_S_80024710_0 *object, Row_81916F10_S_80024710_2 *position) {
    s32 angle_scale_x;
    s32 angle_scale_y;
    Row_81916F10_S_80024710_1 *state;

    state = object->unk_00;
    state->unk_14 = (u16) (state->unk_14 + 1);
    angle_scale_x = rsin(object->unk_0E);
    position->unk_00 = (s32) (position->unk_00 + ((angle_scale_x >> 4) * (rsin(object->unk_10) >> 4) * 0x1C));
    angle_scale_y = rsin(object->unk_0E);
    position->unk_04 = (s32) (position->unk_04 + ((angle_scale_y >> 4) * (rcos(object->unk_10) >> 4) * 0x1C));
    position->unk_08 = (s32) (position->unk_08 + ((rcos(object->unk_0E) >> 4) * 0x1C00));
}

/* Creates a randomly rotated sprite behind the source along its radial direction, with size and color
   set by step. */
void *create_radial_effect_from_source(void *source, Row_81917004_Copy24 *origin, s16 size_step)
{
    s16 saved_step = size_step;
    ObjectNodeHeader *effect;
    SpriteFrameState *part;
    Row_81917004_Copy24 *position;
    u8 *effect_state;
    s32 scale_step;
    s32 direction_factor;
    s32 direction_factor_2;
    s32 scaled_factor;
    s32 random_value;
    s16 part_scale;
    s32 alloc_kind;
    void *alloc_source;
    s32 step_word;

    alloc_kind = 0x212;
    alloc_source = (u8 *)source - 0x20;
    effect = allocate_list_node(alloc_kind, alloc_source);
    if (effect != NULL) {
        effect->update_callback = &D_80024710;
        ((Row_81917004_S_80024804_0 *)effect)->unk_20 = ((Row_81917004_S_80024804_1 *)source)->unk_00;

        step_word = (s32)saved_step << 16;
        part = effect->sprite;
        part->color.c.g = -0x60 - ((step_word >> 16) << 6);
        part->color.c.r = -0x60 - ((step_word >> 16) << 6);
        part->color.c.b = 0xC0;
        part->clut = 0x7DCF;
        part->source = &D_80025B10;

        part->flags |= 0x000C;
        part->tpage_abr |= 0x0020;
        part->flags |= 0x0100;

        random_value = rand();
        effect_state = (u8 *)effect + 0x20;
        part->angle_z = random_value % 0x1000;

        part_scale = ((step_word >> 16) << 8) + 0x500;
        part->scale_y = part_scale;
        part->scale_x = part_scale;
        register_node(effect, project_sprite_chain);

        position = *(Row_81917004_Copy24 * *)&effect->position;
        *position = *origin;

        ((Row_81917004_S_80024804_3 *)effect_state)->unk_0E.u = ((Row_81917004_S_80024804_1 *)source)->unk_0E;
        ((Row_81917004_S_80024804_3 *)effect_state)->unk_10.u = ((Row_81917004_S_80024804_1 *)source)->unk_10;

        direction_factor = rsin(((Row_81917004_S_80024804_3 *)effect_state)->unk_0E.s);
        position->word[0] -= (scaled_factor = direction_factor >> 4) *
            (rsin(((Row_81917004_S_80024804_3 *)effect_state)->unk_10.s) >> 4) * ((step_word >> 16) + 2) * 8;

        direction_factor_2 = rsin(((Row_81917004_S_80024804_3 *)effect_state)->unk_0E.s);
        position->word[1] -= (scaled_factor = direction_factor_2 >> 4) *
            (rcos(((Row_81917004_S_80024804_3 *)effect_state)->unk_10.s) >> 4) * ((step_word >> 16) + 2) * 8;

        position->word[2] -=
            ((rcos(((Row_81917004_S_80024804_3 *)effect_state)->unk_0E.s) >> 4) * ((step_word >> 16) + 2)) << 11;
        return effect;
    }

    return NULL;
}

/* Retires three child nodes, resets the sprite, scatters its position on a sphere, and creates a new
   child. */
void initialize_the_s_visual_state_apply_random_spherical_position_offset(void *object, Rec_func_80024600_arg1 *position, SpriteFrameState *visual) {
    s16 azimuth;
    s16 polar_angle;
    s32 radial_x;
    s32 radial_y;
    s32 rotation_rand;
    s32 polar_rand;
    s32 azimuth_rand;
    s32 node_index;
    s32 azimuth_biased;
    s32 rotation_quotient;
    s32 polar_quotient;
    s32 *flags_base;
    void **node_slot;
    Row_81917234_S_80024A34_0 *node;

    node_index = 0;
    flags_base = (s32 *)(u32)0x80080000;
    node_slot = (void **)object;
    do {
        if ((node = node_slot[5]) != NULL) {
            u32 node_flags;
            s32 global_flags;
            node_flags = node->unk_1E;
            global_flags = flags_base[0x528];
            node_flags |= 0x8000;
            global_flags = global_flags | 0x8000;
            node->unk_1E = node_flags;
            flags_base[0x528] = global_flags;
        }
        node_index += 1;
        node_slot += 1;
    } while (node_index < 3);
    select_record_entry_and_value(visual, rising_sprite_entries, 0);
    visual->color.c.b = 0xC0;
    visual->color.c.g = 0xC0;
    visual->color.c.r = 0xC0;
    visual->scale_y = 0x800;
    visual->scale_x = 0x800;
    visual->flags = (u16) (visual->flags | 0xC);
    visual->tpage_abr = (u16) (visual->tpage_abr | 0x20);
    rotation_quotient = rand();
    rotation_rand = rotation_quotient;
    if (rotation_rand < 0) {
        rotation_quotient = (s32) (rotation_rand + 0xFFF);
    }
    rotation_quotient >>= 0xC;
    visual->angle_z = (s16) (rotation_rand - (rotation_quotient << 0xC));
    polar_rand = rand();
    polar_quotient = polar_rand;
    polar_quotient = polar_rand / 4096;
    polar_angle = (polar_rand % 4096);
    azimuth_rand = rand();
    azimuth_biased = azimuth_rand;
    azimuth = (azimuth_rand % 4096);
    radial_x = rsin(polar_angle);
    position->unk_00 = (s32) (position->unk_00 + ((radial_x >> 4) * (rsin(azimuth) >> 4) * 0x10));
    radial_y = rsin(polar_angle);
    position->unk_04 = (s32) (position->unk_04 + ((radial_y >> 4) * (rcos(azimuth) >> 4) * 0x10));
    position->unk_08 = (s32) (position->unk_08 + ((rcos(polar_angle) >> 4) << 0xC));
    create_an_default_rendering_settings_copies_initial_data(object, position);
}

/* Moves a rotating sprite along its radial direction, then scatters, expands, and fades it at its
   travel limit. */
void advance_radial_effect_state(void *motion, void *position, SpriteFrameState *effect) {
    s32 direction_scale;
    s32 sin_a;
    s32 sin_b;
    s32 sin_c;
    s32 target_x;
    s32 current_x;
    s32 next_x;
    s32 next_distance;
    s16 past_target;
    u16 size;
    u8 intensity;
    void *object;
    ObjectFlagBlock *global_flags;
    s16 state;

    object = ((Row_8191740C_S_80024C0C_0 *)motion)->unk_00;
    ((Row_8191740C_S_80024C0C_1 *)object)->unk_14++;
    state = ((Row_8191740C_S_80024C0C_0 *)motion)->unk_04.s;
    switch (state) {
    case 0:
        effect->angle_z += 0x200;
        sin_a = rsin(((Row_8191740C_S_80024C0C_0 *)motion)->unk_0E);
        direction_scale = (sin_a >> 4) * (rsin(((Row_8191740C_S_80024C0C_0 *)motion)->unk_10) >> 4);
        ((Rec_func_80024600_arg1 *)position)->unk_00 += direction_scale * 0x1C;
        sin_b = rsin(((Row_8191740C_S_80024C0C_0 *)motion)->unk_0E);
        direction_scale = (sin_b >> 4) * (rcos(((Row_8191740C_S_80024C0C_0 *)motion)->unk_10) >> 4);
        ((Rec_func_80024600_arg1 *)position)->unk_04 += direction_scale * 0x1C;
        ((Rec_func_80024600_arg1 *)position)->unk_08 += (rcos(((Row_8191740C_S_80024C0C_0 *)motion)->unk_0E) >> 4) * 0x1C00;
        sin_c = rsin(((Row_8191740C_S_80024C0C_0 *)motion)->unk_0E);
        direction_scale = (sin_c >> 4) * (rsin(((Row_8191740C_S_80024C0C_0 *)motion)->unk_10) >> 4);
        current_x = ((Rec_func_80024600_arg1 *)position)->unk_00;
        state = ((Row_8191740C_S_80024C0C_0 *)motion)->unk_12;
        next_x = current_x + direction_scale * 0x1C;
        if (state != 0) {
            target_x = ((Rec_func_80024600_arg1 *)position)->unk_0C;
            past_target = target_x < current_x;
        } else {
            target_x = ((Rec_func_80024600_arg1 *)position)->unk_0C;
            past_target = current_x < target_x;
        }
        if (past_target) {
            s32 distance;

            distance = current_x - target_x;
            distance = abs(distance);
            next_distance = next_x - target_x;
            next_distance = abs(next_distance);
            if (next_distance < distance) {
                return;
            }
        }
        initialize_the_s_visual_state_apply_random_spherical_position_offset(motion, position, effect);
        ((Row_8191740C_S_80024C0C_0 *)motion)->unk_04.u++;
        break;
    case 1:
        if (effect->color.c.r != 0) {
            intensity = effect->color.c.b - 0x20;
            effect->color.c.b = intensity;
            effect->color.c.g = intensity;
            effect->color.c.r = intensity;
        }
        size = effect->scale_y + 0x400;
        effect->scale_y = size;
        effect->scale_x = size;
        advance_sprite_animation_and_textures(effect);
        advance_sprite_animation_and_textures(effect);
        if (effect->flags & 0x6000) {
            object = ((Row_8191740C_S_80024C0C_0 *)motion)->unk_00;
            ((Row_8191740C_S_80024C0C_1 *)object)->unk_16++;
            global_flags = &object_flag_block;
            (*(u16 *)((u8 *)motion + (-2))) |= 0x8000;
            global_flags->flags |= 0x8000;
        }
        break;
    }
}

/* Creates a sprite aimed from the supplied position toward the owner's saved coordinates and adds
   three trail sprites. */
void *create_an_oriented_effect_between_position_owner(void *owner, Rec_func_80024E80_arg1 *start_pos) {
    ObjectNodeHeader *effect;
    Row_81917680_S_80024E80_2 *state;
    SpriteFrameState *render;
    Row_81917680_S_80024E80_4 *endpoints;
    s32 dx;
    s32 dy;
    s32 dz;
    s32 slot_index;
    u8 *slot_ptr;
    s32 random_angle;

    effect = allocate_list_node(0x212, (u8 *)owner - 0x20);
    if (effect != 0) {
        effect->update_callback = D_80024C0C;
        state = (u8 *)effect + 0x20;
        ((Row_81917680_S_80024E80_0 *)effect)->unk_20 = ((Row_81917680_S_80024E80_1 *)owner)->unk_00;
        state->unk_04 = 0;

        render = effect->sprite;
        render->color.c.b = 0x80;
        render->color.c.g = 0x80;
        render->color.c.r = 0x80;
        render->clut = 0x7DCF;
        render->source = D_800DE39C;
        render->flags |= 0x100;

        random_angle = rand();
        render->angle_z = random_angle % 0x1000;
        render->scale_y = 0x400;
        render->scale_x = 0x400;

        register_node(effect, project_sprite_chain);

        endpoints = effect->position;
        *(Row_81917680_SixWords *)endpoints = *(Row_81917680_SixWords *)start_pos;
        endpoints->unk_0C = ((Row_81917680_S_80024E80_1 *)owner)->unk_20;
        endpoints->unk_10 = ((Row_81917680_S_80024E80_1 *)owner)->unk_24;
        endpoints->unk_14 = ((Row_81917680_S_80024E80_1 *)owner)->unk_28;

        dx = ((Row_81917680_S_80024E80_1 *)owner)->unk_20 - start_pos->unk_00.at00_s32.v;
        dy = ((Row_81917680_S_80024E80_1 *)owner)->unk_24 - start_pos->unk_04.at00_s32.v;
        dz = ((Row_81917680_S_80024E80_1 *)owner)->unk_28 - start_pos->unk_08.at00_s32.v;

        state->unk_0E = ratan2(
            SquareRoot12((((dx >> 12) * (dx >> 12)) +
                           ((dy >> 12) * (dy >> 12))) << 4),
            dz >> 4);
        state->unk_10 = ratan2(dx >> 4, dy >> 4);

        if (dx < 0) {
            state->unk_12 = 1;
        }

        slot_index = 0;
        slot_ptr = state;
        do {
            ((Row_81917680_S_80024E80_6 *)slot_ptr)->unk_14 = create_radial_effect_from_source(state, endpoints, (s16)slot_index);
            slot_index++;
            slot_ptr += 4;
        } while (slot_index < 3);

        return effect;
    }
    return 0;
}

/* Grows and brightens an orbiting sprite, waits for its indexed delay, then replaces it with a
   directed effect. */
void advance_the_effect_phase_brightness_scale_position_until_lifetime_ends(void *effect, void *transform, SpriteFrameState *visual) {
    s32 scale;
    s16 phase;
    u8 brightness;
    void *owner;

    owner = ((Row_81917894_S_80025094_0 *)effect)->unk_00;
    ((Row_81917894_S_80025094_1 *)owner)->unk_14 = (u16) (((Row_81917894_S_80025094_1 *)owner)->unk_14 + 1);
    advance_sprite_animation_and_textures(visual);
    ((Row_81917894_S_80025094_0 *)effect)->unk_06.u = (u16) (((Row_81917894_S_80025094_0 *)effect)->unk_06.u + 1);
    visual->angle_z = (u16) (visual->angle_z + 0x200);
    phase = ((Row_81917894_S_80025094_0 *)effect)->unk_04.s;

    switch (phase) {
    case 0:
    {
        u16 radius;

        if (((Row_81917894_S_80025094_0 *)effect)->unk_06.u & 1) {
            radius = ((Row_81917894_S_80025094_0 *)effect)->unk_0A + 2;
        } else {
            radius = ((Row_81917894_S_80025094_0 *)effect)->unk_0A + 1;
        }
        ((Row_81917894_S_80025094_0 *)effect)->unk_0A = radius;
    }
        brightness = visual->color.c.b + 3;
        visual->color.c.b = brightness;
        visual->color.c.g = brightness;
        visual->color.c.r = brightness;
        scale = ((Row_81917894_S_80025094_0 *)effect)->unk_06.s << 5;
        visual->scale_y = scale;
        visual->scale_x = scale;
        ((Rec_func_80024E80_arg1 *)transform)->unk_08.at02_u16.v =
            (u16) (((Rec_func_80024E80_arg1 *)transform)->unk_08.at02_u16.v - 2);
    case 1:
        if ((s16) ((Row_81917894_S_80025094_0 *)effect)->unk_06.u >= 0x20) {
            ((Row_81917894_S_80025094_0 *)effect)->unk_06.u = 0U;
            ((Row_81917894_S_80025094_0 *)effect)->unk_04.u =
                (u16) (((Row_81917894_S_80025094_0 *)effect)->unk_04.u + 1);
        }
        break;
    case 2:
        if ((s16) ((Row_81917894_S_80025094_0 *)effect)->unk_06.u >=
            ((Row_81917894_S_80025094_0 *)effect)->unk_08) {
            create_an_oriented_effect_between_position_owner(effect, transform);
            (*(u16 *)((u8 *)effect + (-2))) =
                (u16) (((Row_81917894_S_80025094_0_pre *)effect)[-1].unk_00 | NODE_REMOVE);
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
            return;
        }
        break;
    }

    ((Rec_func_80024E80_arg1 *)transform)->unk_00.at02_s16.v = (s16) (((Rec_func_80024E80_arg1 *)transform)->unk_0E
        + ((s32) ((rcos(((Row_81917894_S_80025094_0 *)effect)->unk_0C) >> 4) * (s16) ((Row_81917894_S_80025094_0 *)effect)->unk_0A)
           >> 8));
    ((Rec_func_80024E80_arg1 *)transform)->unk_04.at02_s16.v = (s16) (((Rec_func_80024E80_arg1 *)transform)->unk_12
        + ((s32) ((rsin(((Row_81917894_S_80025094_0 *)effect)->unk_0C) >> 4) * (s16) ((Row_81917894_S_80025094_0 *)effect)->unk_0A)
           >> 8));
}

/* Creates a randomly rotated attached sprite with copied motion and staggered phase and timing from
   its index. */
s32 create_an_attached_effect_copied_transform_data_randomized_angle(void *object, Row_81917A70_Copy24 *src_transform, s16 effect_index) {
    s32 first_word;
    s32 second_word;
    s32 random_value;
    s32 adjusted_random;
    Row_81917A70_S_80025270_1 *state;
    ObjectPosition *transform;
    ObjectNodeHeader *effect;
    s16 saved_index;
    effect = allocate_list_node(0x212, (u8 *)object - 0x20);
    if (effect != NULL) {
        saved_index = effect_index;
        state = ((void *)effect) + 0x20;
        effect->update_callback = &D_80025094;
        ((Row_81917A70_S_80025270_0 *)effect)->unk_20 = (s32)object;
        state->unk_08 = (s16) (saved_index * 7);
        state->unk_04 = 0;
        state->unk_06 = 0;
        state->unk_0A = 0;
        state->unk_0C = (s16) (saved_index * 0x600);
        state->unk_20 = src_transform->wordC;
        state->unk_24 = src_transform->word10;
        state->unk_28 = src_transform->word14;
        object = effect->sprite;
        ((Rec_D_80082E80 *)object)->unk_0C.at02_s8.v = 0x20;
        ((Rec_D_80082E80 *)object)->unk_0C.at01_s8.v = 0x20;
        ((Rec_D_80082E80 *)object)->unk_0C.at00_s8.v = 0x20;
        ((Rec_D_80082E80 *)object)->unk_12.at00_s16.v = 0x7DCF;
        ((Rec_D_80082E80 *)object)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)object)->unk_14.at00_u16.v | 0xC);
        ((Rec_D_80082E80 *)object)->unk_10.as_u16 = (u16) (((Rec_D_80082E80 *)object)->unk_10.as_u16 | 0x20);
        ((Rec_D_80082E80 *)object)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)object)->unk_14.at00_u16.v | 0x100);
        select_record_entry_and_value(object, &D_800DEB70, 0);
        adjusted_random = rand();
        random_value = adjusted_random;
        if (random_value < 0) {
            adjusted_random = random_value + 0xFFF;
        }
        ((Rec_D_80082E80 *)object)->unk_1A.as_s16 = (s16) (random_value % 4096);
        ((Rec_D_80082E80 *)object)->unk_1C.at02_s16.v = 0x400;
        ((Rec_D_80082E80 *)object)->unk_1C.at00_s16.v = 0x400;
        register_node(effect, project_sprite_chain);
        transform = *(Row_81917A70_Copy24 * *)&effect->position;
        *(Row_81917A70_Copy24 *)transform = *src_transform;
        first_word = transform->x.v;
        second_word = transform->y.v;
        transform->velocity_x = first_word;
        transform->velocity_y = second_word;
        return (s32)effect;
    }
    return 0;
}

/* Stages an effect's launch and particle burst, moves it to the target, and applies damage after child
   completion. */
void build_inverted(Row_81917C08_ActionState *action, Row_81917C08_EffectMotion *motion, Row_81917C08_EffectVisual *visual)
{
    EntityRec *actor;
    EntityRec *target;
    ObjectNodeHeader *node;
    Row_81917C08_EffectMotion *target_motion;
    ObjectPosition *actor_motion;
    SpriteFrameState *actor_visual;
    SpriteFrameState *scan_visual;
    Row_81917C08_EffectMotion destination;
    s16 offset[3];
    s16 dest_tile_y;
    u16 tile_x, tile_y;
    s32 steps;
    s32 height;
    s16 dest_tile_x;

    action->ticks++;
    actor = action->actor;
    switch (action->phase) {
    case 0:
        action->ticks = 0;
        action->completed_a = 0;
        action->completed_b = 0;
        action->phase++;
        action->direction = ((u16)actor->facing >> 9) & 7;
        visual->color = 0x808080;
        begin_view_parameter_transition((ObjectNodeHeader *)actor - 1, motion, 8, 0x300);
        /* The initial movement work is shared with phase 1. */
    case 1:
        node = (ObjectNodeHeader *)actor - 1;
        actor_visual = node->sprite;
        if (!resolve_record_orientation_or_fallback(actor_visual->source, actor_visual, offset, 0)) {
            if (!( node->sprite->flags & 0x8000))
                break;
        }
        actor_motion = node->position;
        motion->x.w.i = actor_motion->x.w.i;
        motion->y.w.i = actor_motion->y.w.i;
        motion->z.w.i = actor_motion->z.w.i;
        if (!(node->sprite->flags & 0x8000)) {
            motion->x.w.i += offset[0];
            motion->y.w.i += offset[1];
            motion->z.w.i += offset[2];
        } else {
            motion->z.w.i -= 0x40;
        }
        if (!(*action->flags & 0x80))
            break;
        steps = 0;
        target = actor->target;
        if (target) {
            target_motion = ((ObjectNodeHeader *)target - 1)->position;
            motion->next_x = target_motion->x.v;
            motion->next_y = target_motion->y.v;
            motion->next_z = target_motion->z.v - (entity_height_offsets[((u8 *)actor->target)[0x13]] << 15);
        } else {
            scan_visual = node->sprite;
            tile_x = scan_visual->tile_x;
            tile_y = scan_visual->tile_y;
            dest_tile_x = tile_x;
            dest_tile_y = tile_y;
            do {
                if (check_layer_offset_height((s16)tile_x * 0x40, (s16)tile_y * 0x40,
                                 actor->unk_88, action->direction << 9))
                    break;
                height = sample_terrain_surface_height(((s16)tile_x + dir_step_x[action->direction]) * 0x40 + 0x20,
                                     ((s16)tile_y + dir_step_y[action->direction]) * 0x40 + 0x20,
                                     actor->unk_88 - 0x20);
                if ((s16)height > 0x200 || (s16)(height - actor->unk_88) < -0x3F)
                    break;
                steps++;
                tile_x += (u16)dir_step_x[action->direction];
                tile_y += (u16)dir_step_y[action->direction];
                dest_tile_y = tile_y;
                dest_tile_x = tile_x;
            } while (steps < 8);
            target_motion = &destination;
            target_motion->x.w.i = (dest_tile_x * 64) + ((dir_step_x[action->direction] + 1) * 32);
            target_motion->y.w.i = (dest_tile_y * 64) + ((dir_step_y[action->direction] + 1) * 32);
            target_motion->z.w.i = motion->z.w.i;
            motion->next_x = target_motion->x.v;
            motion->next_y = target_motion->y.v;
            motion->next_z = motion->z.v - 0x200000;
        }
        create_an_initializes_visual_state_copies_initial_data(action, motion, actor);
        action->ticks = 0;
        action->phase++;
        break;
    case 2:
        motion->x.v += ((rcos(actor->facing) >> 4) * (8 - action->ticks)) << 8;
        motion->y.v += ((rsin(actor->facing) >> 4) * (8 - action->ticks)) << 8;
        motion->z.v -= 0x20000;
        if (action->ticks == 5) {
            play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
            for (steps = 0; steps < 8; steps++)
                create_an_attached_effect_copied_transform_data_randomized_angle(action, motion, (s16)steps);
        }
        if (action->ticks >= 9) {
            action->ticks = 0;
            action->phase++;
            break;
        }
        action->pending = 0;
        return;
    case 3:
        if (action->ticks < 0xD)
            motion->z.v -= 0x20000;
        if (action->ticks < 0x3C)
            break;
        create_a_type_hex_212_initializes_handler_mode(action);
        target = actor->target;
        if (target) {
            target_motion = ((ObjectNodeHeader *)target - 1)->position;
            motion->next_x = (target_motion->x.v - motion->x.v) / 32;
            motion->next_y = (target_motion->y.v - motion->y.v) / 32;
            motion->next_z = (target_motion->z.v -
                (entity_height_offsets[((u8 *)actor->target)[0x13]] << 15) - motion->z.v) / 32;
        } else {
            motion->next_x = (motion->next_x - motion->x.v) / 32;
            motion->next_y = (motion->next_y - motion->y.v) / 32;
            motion->next_z = (motion->next_z - motion->z.v) / 32;
        }
        action->ticks = 0;
        action->phase++;
        break;
    case 4:
        motion->x.v += motion->next_x;
        motion->y.v += motion->next_y;
        motion->z.v += motion->next_z;
        if (action->ticks >= 0x20) {
            action->ticks = 0;
            action->phase++;
            break;
        }
        action->pending = 0;
        return;
    case 5:
        if (action->completed_a < 8 || action->completed_b < 8)
            break;
        if (actor->target)
            apply_attack_power_and_element_effects(actor->target, 0x18, action->event_id, 2,
                         action->direction << 9, actor, 1);
        action->ticks = 0;
        action->phase++;
        break;
    case 6:
        if (!action->pending) {
            D_8008346C.value = 0;
            ((ObjectNodeHeader *)action)[-1].flags |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
        break;
    }
    action->pending = 0;
}
