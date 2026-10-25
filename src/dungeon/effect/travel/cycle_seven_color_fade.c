#include "shared/audio_commands.h"
/* Color-cycling radial bands, rotating spark effects, and movement toward reachable tiles. */
#include "dungeon/effect/travel/cycle_seven_color_fade.h"
#include "shared/sprite_frame_state.h"
void (*const dungeon_18d6800_entry)(B28_818B7F38_S_80025738_0 *, B28_818B7F38_S_80025738_5 *, B28_818B7F38_S_80025738_2 *) = advance_movement_toward_reachable_tile;
#include "dungeon/effect/travel/cycle_seven_color_fade.h"
#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

/* Adds a computed gain to the target's stored value, doubling it when flagged. */
void interpolate_view_parameters(EntityRec *target, s32 gain_param, void *record) {
    s32 base_gain;
    register s32 gain;

    if (try_trigger_target_record_effect(target, 1, record) == 0) {
        base_gain = get_random_scaled_value(gain_param & 0xFF) + 8;
        gain = base_gain;
        if (target->unk_28 & 1) {
            gain = base_gain << 1;
        }
        target->unk_64 = (u16) (((u16)target->unk_64) + gain);
        cap_pending_actor_value_delta(target);
        base_gain = 0x8004;
        create_actor_value_popup(base_gain, target, (s16) ((u16)target->unk_64), 1);
        apply_clamped_actor_value_delta(target);
    }
}
#include "dungeon/effect/travel/cycle_seven_color_fade.h"
#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

   /* Increment counters, reduce the stored value, and propagate status flags. */
void lower_animated_sprite(void *counter_state, B28_818B68B8_S_818B68B8_2 *value_state, SpriteFrameState *status) {
    B28_818B68B8_S_818B68B8_1 *linked_counter;

    linked_counter = ((B28_818B68B8_S_818B68B8_0 *)counter_state)->unk_00;
    linked_counter->unk_14 = (u16) (linked_counter->unk_14 + 1);
    ((B28_818B68B8_S_818B68B8_0 *)counter_state)->unk_04 = (u16) (((B28_818B68B8_S_818B68B8_0 *)counter_state)->unk_04 + 1);
    value_state->unk_08 = (s32) (value_state->unk_08 + 0xFFF60000);
    advance_sprite_animation_and_textures(status);
    if (status->flags & 0x6000) {
        ((B28_818B68B8_S_818B68B8_0_pre *)counter_state)[-1].unk_00 = (u16) (((B28_818B68B8_S_818B68B8_0_pre *)counter_state)[-1].unk_00 | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
}
#include "shared/object_node.h"
#include "dungeon/effect/travel/cycle_seven_color_fade.h"
#include "common.h"
#include "shared/slus_callbacks.h"

#ifndef NULL
#define NULL 0
#endif

extern s32 rand();

extern u8 shared_sprite_entries[];

/* Create an object with randomized rotation and a radial position offset. */
s32 create_colored_offset_sprite(s32 context_value, void *source_state, s32 render_param, s32 ignored_context) {
    s16 offset_angle;
    SpriteFrameState *render_state;
    s32 *object_state;
    ObjectNodeHeader *object;
    B28_818B6954_S_818B6954_1 *object_data;

    object = allocate_flagged_object_node(0x212);
    if (object != NULL) {
        object->update_callback = lower_animated_sprite;
        object_data = (B28_818B6954_S_818B6954_1 *)((u8 *)object + 0x20);
        ((B28_818B6954_S_818B6954_0 *)object)->unk_20 = context_value;
        object_data->unk_04 = 0;
        object_data->unk_06 = 0;
        render_state = object->sprite;
        render_state->color.word = render_param;
        render_state->clut = 0x7DCF;
        render_state->flags |= 0xC;
        render_state->tpage_abr |= 0x20;
        render_state->flags |= 0x100;
        select_record_entry_and_value(render_state, shared_sprite_entries, 0);
        render_state->angle_z = rand() % 0x1000;
        render_state->scale_y = 0xC00;
        render_state->scale_x = 0xC00;
        register_node(object, project_sprite_chain);
        object_state = object->position;
        *(B28_818B6954_Copy24 *)object_state = *(B28_818B6954_Copy24 *)source_state;
        offset_angle = rand() % 0x1000;
        object_state[0] += (rcos(offset_angle) >> 4) * 0x1200;
        object_state[1] += (rsin(offset_angle) >> 4) * 0x1200;
        return (s32)object;
    }
    return 0;
}
#include "dungeon/effect/travel/cycle_seven_color_fade.h"
#include "common.h"
#include "shared/object_flags.h"
   /* Cycle through seven colors with fade-in and fade-out, then mark the effect finished. */
void cycle_seven_color_fade(B28_818B6AFC_FxEffect *effect, s32 render_arg, B28_818B6AFC_FxColorOut *color_out) {
    s32 fade_in_color;
    s16 fade_in_green;
    s32 hold_color;
    s32 fade_out_color;
    s16 fade_out_green;
    s16 frame;
    s32 fade_in_blue;
    s32 fade_work;
    s32 rounded_color;
    s32 channel_bit;
    s32 fade_in_half;
    s32 fade_out_half;
    s32 packed_channel;
    s32 cycle_quotient;
    s32 packed_color;
    s32 frames_left;
    s32 hold_blue;
    s32 hold_half;
    s32 cycle_value;
    s16 fade_in_cycle;
    s16 hold_cycle;
    s16 fade_out_cycle;
    s32 fade_in_tick;
    u16 hold_tick;
    u16 fade_out_tick;
    s32 product_result;
    s8 red;
    s8 green;
    s8 blue;
    B28_818B6AFC_FxRgb *target_color;
    B28_818B6AFC_FxOwner *owner;
    B28_818B6AFC_FxOwner *render_owner;

    owner = effect->owner;
    owner->count += 1;
    effect->frame += 1;
    effect->tick += 1;
    effect->scroll_u += 0x80;
    effect->scroll_v += 0x80;
    frame = effect->frame;
    if (frame < 8) {
        effect->target->flags |= 0x10000000;
        fade_in_tick = effect->tick;
        target_color = ((B28_818B6AFC_FxTargetPre *)(effect->target))[-1].color;
        fade_in_cycle = (s16) fade_in_tick % 7 + 1;
        packed_channel = (s32) ((u32) fade_in_cycle << 16);
        fade_in_color = packed_channel >> 16;
        fade_in_tick = fade_in_color;
        if (fade_in_color < 0) {
            fade_in_tick = fade_in_color + 3;
        }
        channel_bit = fade_in_tick >> 2;
        product_result = channel_bit * ((s16) effect->frame << 3);
        fade_in_half = (fade_in_color + (s32) ((u32) packed_channel >> 31)) >> 1;
        target_color->r = (s8) (product_result - 0x80);
        fade_in_green = (s16) fade_in_half % 2;
        packed_channel = fade_in_half;
        packed_channel *= 2;
        packed_channel = fade_in_color - packed_channel;
        packed_channel = (u32)packed_channel << 16;
        product_result = fade_in_green * ((s16) effect->frame << 3);
        target_color->g = (s8) (product_result - 0x80);
        fade_in_blue = packed_channel >> 16;
        product_result = fade_in_blue * ((s16) effect->frame << 3);
        target_color->b = (s8) (product_result - 0x80);
        product_result = channel_bit * (((s16) effect->frame * 3) << 3);
        color_out->rgb.at00.v = (s8) product_result;
        product_result = fade_in_green * (((s16) effect->frame * 3) << 3);
        color_out->rgb.at01.v = (s8) product_result;
        product_result = fade_in_blue * (((s16) effect->frame * 3) << 3);
        color_out->rgb.at02.v = (s8) product_result;
    } else if (frame < 0x28) {
        effect->target->flags |= 0x10000000;
        hold_tick = effect->tick;
        target_color = ((B28_818B6AFC_FxTargetPre *)(effect->target))[-1].color;
        hold_cycle = (s16) hold_tick % 7 + 1;
        cycle_value = (s32) ((u32) hold_cycle << 16);
        hold_color = cycle_value >> 16;
        rounded_color = hold_color;
        red = (rounded_color / 4) * 0xC0;
        hold_half = (hold_color + (s32) ((u32) cycle_value >> 31)) >> 1;
        color_out->rgb.at00.v = red;
        target_color->r = red;
        green = ((s16) hold_half % 2) * 0xC0;
        hold_blue = (s16) (hold_color - (hold_half * 2));
        color_out->rgb.at01.v = green;
        target_color->g = green;
        blue = hold_blue * 0xC0;
        color_out->rgb.at02.v = blue;
        target_color->b = blue;
        render_owner = effect->owner;
        create_colored_offset_sprite(render_owner, render_arg, color_out->rgb.at00u.v, effect);
    } else {
        union { s32 v; } fade_out_red = {0};

        if (frame < 0x30) {
            effect->target->flags |= 0x10000000;
            fade_out_tick = effect->tick;
            target_color = ((B28_818B6AFC_FxTargetPre *)(effect->target))[-1].color;
            fade_out_cycle = (s16) fade_out_tick % 7 + 1;
            packed_color = (s32) ((u32) fade_out_cycle << 16);
            fade_out_color = packed_color >> 16;
            fade_work = fade_out_color;
            if (fade_out_color < 0) {
                fade_work = fade_out_color + 3;
            }
            fade_out_red.v = fade_work >> 2;
            fade_work = (s16) effect->frame;
            fade_in_color = 0x30;
            fade_work = fade_in_color - fade_work;
            fade_out_half = (fade_out_color + (s32) ((u32) packed_color >> 31)) >> 1;
            product_result = fade_out_red.v * (fade_work << 3);
            target_color->r = (s8) (product_result - 0x80);
            fade_out_green = (s16) fade_out_half % 2;
            packed_channel = (s32) ((u32) (fade_out_color - (fade_out_half * 2)) << 16);
            product_result = fade_out_green * ((fade_in_color - (s16) effect->frame) << 3);
            target_color->g = (s8) (product_result - 0x80);
            channel_bit = packed_channel >> 16;
            product_result = channel_bit * ((fade_in_color - (s16) effect->frame) << 3);
            target_color->b = (s8) (product_result - 0x80);
            frames_left = (s16) effect->frame;
            frames_left = fade_in_color - frames_left;
            product_result = fade_out_red.v * ((frames_left * 3) << 3);
            color_out->rgb.at00.v = (s8) product_result;
            frames_left = (s16) effect->frame;
            frames_left = fade_in_color - frames_left;
            product_result = fade_out_green * ((frames_left * 3) << 3);
            color_out->rgb.at01.v = (s8) product_result;
            frames_left = (s16) effect->frame;
            frames_left = fade_in_color - frames_left;
            product_result = channel_bit * ((frames_left * 3) << 3);
            color_out->rgb.at02.v = (s8) product_result;
        } else {
            effect->target->flags &= 0xEFFFFFFF;
            ((B28_818B6AFC_FxEffectPre *)effect)[-1].flags |= 0x8000;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
    }
}
#include "dungeon/effect/travel/cycle_seven_color_fade.h"
#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/game_work.h"

   /* scratch in func_80024790 */

   /* base in func_80024790 */

   /* packet in func_80024790 */

   /* arg1 in func_80024790 */

/* Projects a textured color-gradient quad and links it into the ordering table if its depth is in range. */
s32 draw_indexed_shaded_quad(s32 texture_index, u8 *color_source)
{
    u8 *render_buffer;
    u8 *packet;
    u8 *scratch;
    s32 texture_u;
    s16 texture_id;
    u32 *ot_read;
    u32 *ot_write;
    u32 depth_index;
    u32 write_depth;
    u32 ot_entry;
    u8 *screen_xy0;
    u8 *screen_xy1;
    u8 *screen_xy2;
    u8 *screen_xy3;
    u8 *depth_cue;
    u8 *transform_flags;

    scratch = (u8 *)0x1F800000;
    render_buffer = g_game_work.draw_buffer;
    ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_00 = render_buffer + 0xB0;
    packet = ((GpuContext *)render_buffer)->packetCursor;
    ((GpuContext *)render_buffer)->packetCursor = packet + 0x34;
    ((B28_818B6F90_S_818B6F90_2 *)packet)->unk_00.at03.v = 0x0C;
    ((B28_818B6F90_S_818B6F90_2 *)packet)->unk_07 = 0x3E;

    texture_id = GetTPage(0, 3, 0x300, 0x100);
    texture_u = (texture_index << 16) >> 13;
    texture_u += 0x80;
    screen_xy0 = scratch + 0x70;
    screen_xy1 = scratch + 0x74;
    screen_xy2 = scratch + 0x78;
    screen_xy3 = scratch + 0x7C;
    depth_cue = scratch + 0x08;
    transform_flags = scratch + 0x0C;

    ((B28_818B6F90_S_818B6F90_2 *)packet)->unk_1A = texture_id;
    ((B28_818B6F90_S_818B6F90_2 *)packet)->unk_0E = 0x7DCF;
    ((B28_818B6F90_S_818B6F90_2 *)packet)->unk_0C = texture_u;
    ((B28_818B6F90_S_818B6F90_2 *)packet)->unk_0D = 0x40;
    ((B28_818B6F90_S_818B6F90_2 *)packet)->unk_18 = texture_u | 7;
    ((B28_818B6F90_S_818B6F90_2 *)packet)->unk_19 = 0x40;
    ((B28_818B6F90_S_818B6F90_2 *)packet)->unk_24 = texture_u | 7;
    ((B28_818B6F90_S_818B6F90_2 *)packet)->unk_25 = 0x7F;
    ((B28_818B6F90_S_818B6F90_2 *)packet)->unk_30 = texture_u;
    ((B28_818B6F90_S_818B6F90_2 *)packet)->unk_31 = 0x7F;
    ((B28_818B6F90_S_818B6F90_2 *)packet)->unk_04 = 0;
    ((B28_818B6F90_S_818B6F90_2 *)packet)->unk_05 = 0;
    ((B28_818B6F90_S_818B6F90_2 *)packet)->unk_06 = 0;
    ((B28_818B6F90_S_818B6F90_2 *)packet)->unk_10 = 0;
    ((B28_818B6F90_S_818B6F90_2 *)packet)->unk_11 = 0;
    ((B28_818B6F90_S_818B6F90_2 *)packet)->unk_12 = 0;

    ((B28_818B6F90_S_818B6F90_2 *)packet)->unk_1C = ((B28_818B6F90_S_818B6F90_3 *)color_source)->unk_0C;
    ((B28_818B6F90_S_818B6F90_2 *)packet)->unk_1D = ((B28_818B6F90_S_818B6F90_3 *)color_source)->unk_0D;
    ((B28_818B6F90_S_818B6F90_2 *)packet)->unk_1E = ((B28_818B6F90_S_818B6F90_3 *)color_source)->unk_0E;
    ((B28_818B6F90_S_818B6F90_2 *)packet)->unk_28 = ((B28_818B6F90_S_818B6F90_3 *)color_source)->unk_0C;
    ((B28_818B6F90_S_818B6F90_2 *)packet)->unk_29 = ((B28_818B6F90_S_818B6F90_3 *)color_source)->unk_0D;
    ((B28_818B6F90_S_818B6F90_2 *)packet)->unk_2A = ((B28_818B6F90_S_818B6F90_3 *)color_source)->unk_0E;

    ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_10 = ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_30 >> 16;
    ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_18 = ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_40 >> 16;
    ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_20 = ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_50 >> 16;
    ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_28 = ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_60 >> 16;

    ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_12 = ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_34 >> 16;
    ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_1A = ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_44 >> 16;
    ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_22 = ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_54 >> 16;
    ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_2A = ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_64 >> 16;

    ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_14 = ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_38 >> 16;
    ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_1C = ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_48 >> 16;
    ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_24 = ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_58 >> 16;
    ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_2C = ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_68 >> 16;

    ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_04.v = RotAverage4(
        scratch + 0x10, scratch + 0x18, scratch + 0x20, scratch + 0x28,
        screen_xy0, screen_xy1, screen_xy2, screen_xy3,
        depth_cue, transform_flags);

    (*(u16 *)((u8 *)packet + (0x08))) = ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_70;
    (*(u16 *)((u8 *)packet + (0x0A))) = ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_72;
    (*(u16 *)((u8 *)packet + (0x14))) = ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_74;
    (*(u16 *)((u8 *)packet + (0x16))) = ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_76;
    (*(u16 *)((u8 *)packet + (0x20))) = ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_78;
    (*(u16 *)((u8 *)packet + (0x22))) = ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_7A;
    ((B28_818B6F90_S_818B6F90_2 *)packet)->unk_2C = ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_7C;
    ((B28_818B6F90_S_818B6F90_2 *)packet)->unk_2E = ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_7E;

    depth_index = ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_04.v2;
    if (depth_index < 0x1E0) {
        ot_read = ((u32 *)((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_00);
        ot_entry = ot_read[depth_index];
        ((B28_818B6F90_S_818B6F90_2 *)packet)->unk_00.at00.v =
            (((B28_818B6F90_S_818B6F90_2 *)packet)->unk_00.at00.v & 0xFF000000) |
            (ot_entry & 0x00FFFFFF);
        write_depth = ((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_04.v2;
        ot_write = ((u32 *)((B28_818B6F90_S_818B6F90_0 *)scratch)->unk_00);
        ot_write[write_depth] =
            (ot_write[write_depth] & 0xFF000000) |
            ((u32)packet & 0x00FFFFFF);
    }

    return 0;
}
#include "dungeon/effect/travel/cycle_seven_color_fade.h"
#include "common.h"

   /* arg0 in draw_two_radial_effect_bands */

   /* arg1 in draw_two_radial_effect_bands */

   /* sc in draw_two_radial_effect_bands */

/* Builds and draws two eight-segment radial bands around the effect center. */
s32 draw_two_radial_effect_bands(B28_818B7264_S_80024A64_0 *effect, B28_818B7264_S_80024A64_1 *center, s32 draw_arg) {
    u8 *scratch;
    s32 first_outer_x;
    s32 first_outer_y;
    s32 first_inner_x;
    s32 first_inner_y;
    u16 outer_radius;
    u16 inner_radius;
    s32 jitter_count;
    s16 tip_radius;
    s32 segment;
    s32 angle_step;
    s32 jittered_outer;
    s32 outer_offset;
    s32 arm_offset;
    s32 arm_radius;
    s32 radial_offset;
    s32 next_segment;
    s32 next_angle;
    s32 jittered_inner;
    s32 jitter_limit;
    s32 scaled;

    scratch = (u8 *)0x1F800000;
    if (effect->unk_06 < 8) {
        s32 growing_z;
        growing_z = center->unk_08 - (effect->unk_06 * 0x180000);
        ((B28_818B7264_S_80024A64_2 *)scratch)->unk_48 = growing_z;
        ((B28_818B7264_S_80024A64_2 *)scratch)->unk_38 = growing_z;
        {
            s32 phase_scale = effect->unk_06;
            s32 inner_scale;
            s32 outer_scale;
            inner_scale = phase_scale * 2;
            outer_scale = (inner_scale + phase_scale) * 2;
            outer_radius = outer_scale;
            inner_radius = inner_scale;
        }
        tip_radius = effect->unk_06 / 2;
        jitter_count = tip_radius + 1;
    } else if (effect->unk_06 < 40) {
        {
            s32 plateau_z = center->unk_08 - (8 * 0x180000);
            ((B28_818B7264_S_80024A64_2 *)scratch)->unk_48 = plateau_z;
            ((B28_818B7264_S_80024A64_2 *)scratch)->unk_38 = plateau_z;
        }
        outer_radius = 8 * 6;
        inner_radius = 8 * 2;
        tip_radius = 8 / 2;
        jitter_count = tip_radius + 1;
    } else if (effect->unk_06 < 48) {
        s32 fading_z;
        jitter_count = 48;
        fading_z = center->unk_08 - ((jitter_count - effect->unk_06) * 0x180000);
        ((B28_818B7264_S_80024A64_2 *)scratch)->unk_48 = fading_z;
        ((B28_818B7264_S_80024A64_2 *)scratch)->unk_38 = fading_z;
        {
            s32 inner_scale;
            s32 tip_value;
            jitter_count -= effect->unk_06;
            inner_scale = jitter_count * 2;
            jitter_count = inner_scale - -jitter_count;
            jitter_count *= 2;
            inner_radius = inner_scale;
            tip_value = (47 - effect->unk_06) / 2;
            outer_radius = jitter_count;
            tip_radius = tip_value;
            jitter_count = tip_value + 1;
        }
    } else {
        jitter_count = 0;
        tip_radius = 0;
        inner_radius = 0;
        outer_radius = 0;
    }

    segment = 0;
    jitter_limit = (s16)jitter_count;
    ((B28_818B7264_S_80024A64_2 *)scratch)->unk_58 = ((B28_818B7264_S_80024A64_2 *)scratch)->unk_68 = center->unk_08;
    do {
        angle_step = segment * 512;
        radial_offset = rand() % jitter_limit;
        {
            s32 wave_x = rsin(effect->unk_0C + angle_step);
            radial_offset = (s16)radial_offset;
            jittered_outer = (s16)outer_radius + radial_offset;
            ((B28_818B7264_S_80024A64_2 *)scratch)->unk_40 = center->unk_00 +
                (((wave_x >> 4) * jittered_outer) << 8);
        }
        ((B28_818B7264_S_80024A64_2 *)scratch)->unk_44 = center->unk_04 +
            (((rcos(effect->unk_0C + angle_step) >> 4) * jittered_outer) << 8);
        {
            s32 wave_x = rsin(effect->unk_0C + angle_step);
            jittered_inner = (s16)inner_radius + radial_offset;
            ((B28_818B7264_S_80024A64_2 *)scratch)->unk_50 = center->unk_00 +
                (((wave_x >> 4) * jittered_inner) << 8);
        }
        ((B28_818B7264_S_80024A64_2 *)scratch)->unk_54 = center->unk_04 +
            (((rcos(effect->unk_0C + angle_step) >> 4) * jittered_inner) << 8);
        next_segment = segment + 1;
        next_angle = next_segment * 512;
        ((B28_818B7264_S_80024A64_2 *)scratch)->unk_30 = ((B28_818B7264_S_80024A64_2 *)scratch)->unk_60 = center->unk_00 +
            (((rsin(effect->unk_0C + next_angle) >> 4) * (s16)tip_radius) << 8);
        ((B28_818B7264_S_80024A64_2 *)scratch)->unk_34 = ((B28_818B7264_S_80024A64_2 *)scratch)->unk_64 = center->unk_04 +
            (((rcos(effect->unk_0C + next_angle) >> 4) * (s16)tip_radius) << 8);
        draw_indexed_shaded_quad((s16)segment, draw_arg);
        segment = next_segment;
    } while (segment < 8);

    segment = 0;
    {
        s32 random_raw = rand();
        s32 div5_magic = 0x66666667;
        union {
            long long full;
            struct { s32 hi; u32 lo; } half;
        } wide_product;
        s32 quotient;
        outer_offset = random_raw;
        wide_product.full = (long long)outer_offset * div5_magic;
        quotient = (wide_product.half.hi >> 1) - (outer_offset >> 31);
        outer_offset = outer_offset - quotient * 5;
    }
    {
        s32 wave_x;
        s32 scaled_x;
        s32 outer_x;
        wave_x = rsin(effect->unk_0E);
        outer_x = center->unk_00 +
            (((wave_x >> 4) * ((s16)outer_radius + (s16)outer_offset)) << 8);
        outer_offset = (s16)outer_radius + (s16)outer_offset;
        ((B28_818B7264_S_80024A64_2 *)scratch)->unk_30 = outer_x;
        first_outer_x = outer_x;
    }
    {
        s32 outer_y;
        outer_y = center->unk_04 +
            (((rcos(effect->unk_0E) >> 4) * outer_offset) << 8);
        ((B28_818B7264_S_80024A64_2 *)scratch)->unk_34 = outer_y;
        first_outer_y = outer_y;
    }
    {
        s32 wave_x = rsin(effect->unk_0E + 512);
        s32 inner_x;
        inner_x = center->unk_00 +
            (((wave_x >> 4) * (s16)inner_radius) << 8);
        ((B28_818B7264_S_80024A64_2 *)scratch)->unk_60 = inner_x;
        first_inner_x = inner_x;
    }
    {
        s32 inner_y = center->unk_04 +
            (((rcos(effect->unk_0E + 512) >> 4) * (s16)inner_radius) << 8);
        ((B28_818B7264_S_80024A64_2 *)scratch)->unk_64 = inner_y;
        first_inner_y = inner_y;
    }
    angle_step = 512;
    do {
        ((B28_818B7264_S_80024A64_2 *)scratch)->unk_40 = ((B28_818B7264_S_80024A64_2 *)scratch)->unk_30;
        ((B28_818B7264_S_80024A64_2 *)scratch)->unk_44 = ((B28_818B7264_S_80024A64_2 *)scratch)->unk_34;
        ((B28_818B7264_S_80024A64_2 *)scratch)->unk_50 = ((B28_818B7264_S_80024A64_2 *)scratch)->unk_60;
        ((B28_818B7264_S_80024A64_2 *)scratch)->unk_54 = ((B28_818B7264_S_80024A64_2 *)scratch)->unk_64;
        if (segment == 7) {
            ((B28_818B7264_S_80024A64_2 *)scratch)->unk_30 = first_outer_x;
            ((B28_818B7264_S_80024A64_2 *)scratch)->unk_34 = first_outer_y;
            ((B28_818B7264_S_80024A64_2 *)scratch)->unk_60 = first_inner_x;
            ((B28_818B7264_S_80024A64_2 *)scratch)->unk_64 = first_inner_y;
        } else {
            {
                s32 random_raw = rand();
                s32 div5_magic = 0x66666667;
                union {
                    long long full;
                    struct { s32 hi; u32 lo; } half;
                } wide_product;
                s32 quotient;
                arm_offset = random_raw;
                wide_product.full = (long long)arm_offset * div5_magic;
                quotient = (wide_product.half.hi >> 1) - (arm_offset >> 31);
                arm_offset = arm_offset - quotient * 5;
            }
            {
                scaled = rsin(effect->unk_0E + (segment * 512)) >> 4;
                arm_radius = (s16)outer_radius + (s16)arm_offset;
                ((B28_818B7264_S_80024A64_2 *)scratch)->unk_30 = center->unk_00 +
                    ((scaled * arm_radius) << 8);
            }
            scaled = rcos(effect->unk_0E + (segment * 512)) >> 4;
            ((B28_818B7264_S_80024A64_2 *)scratch)->unk_34 = center->unk_04 +
                ((scaled * arm_radius) << 8);
            ((B28_818B7264_S_80024A64_2 *)scratch)->unk_60 = center->unk_00 +
                (((rsin(effect->unk_0E + angle_step) >> 4) * (s16)inner_radius) << 8);
            ((B28_818B7264_S_80024A64_2 *)scratch)->unk_64 = center->unk_04 +
                (((rcos(effect->unk_0E + angle_step) >> 4) * (s16)inner_radius) << 8);
        }
        draw_indexed_shaded_quad((s16)segment, draw_arg);
        segment = segment + 1;
        angle_step = angle_step + 512;
    } while (segment < 8);
    return 0;
}
#include "shared/object_node.h"
#include "dungeon/effect/travel/cycle_seven_color_fade.h"
#include "common.h"

extern s32 rand(void);

/* Creates an object from source data and payload, initializing two fields randomly. */
void draw_chained_object_records(B28_818B77D4_Arg0818B77D4 *source, B28_818B77D4_Arg1818B77D4 *payload) {
    B28_818B77D4_Obj818B77D4 *obj;
    B28_818B77D4_Inner818B77D4 *state;
    u16 source_value;

    obj = allocate_flagged_object_node(0x212);
    if (obj != 0) {
        obj->unk10 = cycle_seven_color_fade;
        state = &obj->unk20;
        state->unk0 = source->unk0;
        state->unk6 = 0;
        source_value = source->unk12;
        state->unkA = 0x30;
        state->unk8 = source_value;
        state->unkC = rand() % 0x1000;
        state->unkE = rand() % 0x1000;
        state->unk10 = source->unk18;
        *(B28_818B77D4_Arg1818B77D4 *)obj->unk8 = *payload;
        register_node(obj, draw_two_radial_effect_bands);
    }
}
#include "dungeon/effect/travel/cycle_seven_color_fade.h"
#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"

/* Per-frame update for the four-phase spark effect: drift, tint ramp, hold, then mark the owner finished. */
void update_spark_effect(B28_818B78E8_S818B78E8_Obj *obj, B28_818B78E8_S818B78E8_Vec *motion, SpriteFrameState *gfx) {
    s32 variant_index;
    s16 fade;
    s16 next_tick;
    s16 phase;
    s16 elapsed;
    s16 limit;
    s32 red_state2;
    s32 red;
    s32 fade_offset;
    s32 elapsed_now;
    s32 variant_s16;
    s32 half_variant_b;
    s32 blue_component;
    s32 half_variant;
    s32 shifted;
    s32 vec_x10;
    s32 vec_x14;
    s32 variant;
    s32 tick;
    u16 phase_value;
    B28_818B78E8_S818B78E8_Child *child;

    child = obj->child;
    child->field14 = (u16) (child->field14 + 1);
    tick = obj->field12;
    next_tick = tick + 1;
    obj->field10 = (u16) (obj->field10 + 1);
    obj->field12 = (u16) next_tick;
    shifted = next_tick << 0x10;
    variant = shifted >> 0x10;
    variant %= 7;
    variant_index = variant + 1;
    advance_sprite_animation_and_textures(gfx);
    gfx->angle_z = (u16) (gfx->angle_z + 0x300);
    phase = obj->state;
    switch (phase) {
    case 0:
        vec_x10 = motion->x10;
        vec_x14 = motion->x14;
        motion->x0 = (s32) (motion->x0 + motion->xC);
        motion->x4 = (s32) (motion->x4 + vec_x10);
        motion->x8 = (s32) (motion->x8 + vec_x14);
        elapsed = (s16) obj->field10;
        limit = obj->field14;
        if (elapsed >= limit) {
            phase_value = (u16) obj->state;
            obj->field10 = 0U;
            obj->state = (s16) (phase_value + 1);
        }
        break;

    case 1:
        variant_s16 = (s16) variant_index;
        red = variant_s16;
        gfx->clut = 0;
        gfx->flags = (u16) (gfx->flags & 0xFEFF);
        if (variant_s16 < 0) {
            red = variant_s16 + 3;
        }
        half_variant = variant_s16 / 2;
        red >>= 2;
        red <<= 7;
        fade_offset = ((s16) obj->field10 * 8) - 0x80;

        red -= fade_offset;
        gfx->color.c.r = (s8) red;
        gfx->color.c.g = (s8) (((s32) (((s16) half_variant - (((s32) ((s16) half_variant + ((u32) (half_variant << 0x10) >> 0x1F)) >> 1) * 2)) << 0x10) >> 9) - (s16) (((s16) obj->field10 * 8) - 0x80));
        gfx->color.c.b = (s8) (((s32) ((variant_s16 - (half_variant * 2)) << 0x10) >> 9) - (s16) (((s16) obj->field10 * 8) - 0x80));
        elapsed_now = obj->field10;

        fade = (0x19 - elapsed_now) << 8;
        gfx->scale_y = fade;
        gfx->scale_x = fade;
        if ((s16) obj->field10 >= 0x10) {
            draw_chained_object_records((void *)obj, (void *)motion);
            phase_value = (u16) obj->state;
            obj->field10 = 0U;
            obj->state = (s16) (phase_value + 1);
        }
        break;

    case 2:
        variant_s16 = (s16) variant_index;
        red_state2 = variant_s16;
        if (variant_s16 < 0) {
            red_state2 = variant_s16 + 3;
        }
        half_variant_b = variant_s16 / 2;
        gfx->color.c.r = (s8) ((red_state2 >> 2) << 7);
        blue_component = (s32) ((variant_s16 - (half_variant_b * 2)) << 0x10) >> 9;
        gfx->color.c.g = (s8) ((s32) (((s16) half_variant_b - (((s32) ((s16) half_variant_b + ((u32) (half_variant_b << 0x10) >> 0x1F)) >> 1) * 2)) << 0x10) >> 9);
        gfx->color.c.b = (s8) blue_component;
        if ((s16) obj->field10 >= 0x20) {
            phase_value = (u16) obj->state;
            obj->field10 = 0U;
            obj->state = (s16) (phase_value + 1);
        }
        break;

    case 3:
        if (gfx->flags & 0x6000) {
            *((u16 *)obj - 1) = (u16) (*((u16 *)obj - 1) | 0x8000);
            object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
        }
    }
}
#include "shared/object_node.h"
#include "dungeon/effect/travel/cycle_seven_color_fade.h"
#include "common.h"

   /* obj in spawn_owner_random_variant_effect */

   /* render in spawn_owner_random_variant_effect */

   /* owner in spawn_owner_random_variant_effect */

   /* transform in spawn_owner_random_variant_effect */

   /* dst in spawn_owner_random_variant_effect */

/* Spawn a 0x212 effect object for the owner with a random variant and spin, and copy the transform into it. */
s32 spawn_owner_random_variant_effect(B28_818B7BD0_S_818B7BD0_2 *owner, B28_818B7BD0_S_818B7BD0_3 *transform) {
    s32 roll;
    s32 random;
    s32 adjusted;
    s32 result;
    void *model;
    void *update_handler;
    SpriteFrameState *render;
    B28_818B7BD0_S_818B7BD0_1 *part;
    ObjectNodeHeader *obj;
    B28_818B7BD0_S_818B7BD0_4 *dst;

    obj = allocate_flagged_object_node(0x212);
    if (obj != NULL) {
        update_handler = update_spark_effect;
        part = ((void *)obj) + 0x20;
        obj->update_callback = update_handler;
        ((B28_818B7BD0_S_818B7BD0_0 *)obj)->unk_20 = owner;
        part->unk_0E.s16 = 0;
        part->unk_10 = 0;
        roll = rand();
        model = &seven_color_sprite_data;
        part->unk_12 = (s16)(roll % 7);
        part->unk_14 = (u16) owner->unk_12;
        part->unk_18.at00.v = (s32) owner->unk_18;
        render = obj->sprite;
        render->color.c.b = 0x80;
        render->color.c.g = 0x80;
        render->color.c.r = 0x80;
        render->clut = 0x7E00;
        render->flags = (u16) (render->flags | 0x100);
        select_record_entry_and_value(render, model, 0);
        adjusted = rand();
        random = adjusted;
        if (random < 0) {
            adjusted = random + 0xFFF;
        }
        render->angle_z = (s16) (random % 4096);
        render->scale_y = 0x400;
        render->scale_x = 0x400;
        register_node(obj, draw_linked_sprites_clipped);
        dst = obj->position;
        result = (s32) obj;
        *dst = *(B28_818B7BD0_S_818B7BD0_4 *)transform;
        return result;
    }
    return 0;
}
#include "dungeon/effect/travel/cycle_seven_color_fade.h"
#include "common.h"
#include "shared/object_flags.h"

/* Advance counters, rotation, and position, and set flags when the counter exceeds its limit. */
void advance_spinning_effect_motion(B28_818B7D3C_OwnerState *owner, B28_818B7D3C_VecState *vec, SpriteFrameState *entity)
{
    owner->child->counter++;
    owner->counter++;
    advance_sprite_animation_and_textures(entity);
    entity->angle_z += 0x300;

    vec->x += vec->dx;
    vec->y += vec->dy;
    vec->z += vec->dz;

    if ((s16)owner->counter > owner->limit) {
        ((u16 *)owner)[-1] |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
#include "shared/object_node.h"
#include "dungeon/effect/travel/cycle_seven_color_fade.h"
#include "common.h"

extern s32 rand(void);

/* Spawn a 0x212 effect object owned by `owner`, give it a random 12-bit spin and copy the source transform into it. */
s32 spawn_owned_random_spin_effect(void *owner, B28_818B7E14_DungeonSource *source)
{
    s32 random;
    s32 adjusted;
    B28_818B7E14_DungeonObject *obj;
    SpriteFrameState *render;
    u8 *sub;
    B28_818B7E14_DungeonSource *dst;
    s32 copy0;
    s32 copy0_2;
    s32 copy1;
    s32 copy1_2;
    s32 copy2;
    s32 copy3;

    obj = allocate_flagged_object_node(0x212);
    if (obj != 0) {
        sub = (u8 *)obj + 0x20;
        obj->update = advance_spinning_effect_motion;
        obj->owner = owner;
        *(s16 *)(sub + 0x10) = 0;
        *(u16 *)(sub + 0x14) = *(u16 *)((u8 *)owner + 0x12);
        render = obj->render;
        render->color.c.b = 0x80;
        render->color.c.g = 0x80;
        render->color.c.r = 0x80;
        render->clut = 0x7E00;
        render->flags |= 0x100;
        select_record_entry_and_value(render, seven_color_sprite_data, 0);
        random = rand();
        adjusted = random;
        render->angle_z = (random % 4096);
        render->scale_y = 0x400;
        render->scale_x = 0x400;
        register_node(obj, draw_linked_sprites_clipped);
        dst = (B28_818B7E14_DungeonSource *)obj->data;

        *dst = *source;
        return obj;
    }
    return 0;
}
#include "dungeon/effect/travel/cycle_seven_color_fade.h"
#include "common.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "m2c_compat.h"
extern int abs(int);

   /* Advance movement toward a target or a reachable tile, then finish the timed action. */
void advance_movement_toward_reachable_tile(void *state, void *motion_in, void *render) {
    B28_818B7F38_LocalFrame frame;
    u16 *target_delta_cursor;
    u16 *path_delta_cursor;
    u16 base_z;
    s16 floor_z;
    s32 phase;
    s32 target_dx;
    s16 next_phase;
    s32 target_ticks;
    s32 path_ticks;
    s32 world_y;
    s32 world_x;
    s16 *step_y;
    s32 probe_z;
    s32 current_z;
    s32 index;
    s32 target_dy;
    s32 target_dz;
    u16 source_z;
    u16 last_tile_x;
    u16 saved_y;
    u16 tile_x;
    u16 tile_y;
    s16 grid_x;
    s16 grid_y;
    void *source_data;
    void *destination;
    void *source_header;
    void *owner;
    void *target;
    void *source_position;
    void *tile_data;

    phase = (s32) ((B28_818B7F38_S_80025738_0 *)state)->unk_0A;
    owner = ((B28_818B7F38_S_80025738_0 *)state)->unk_00;
    ((B28_818B7F38_S_80025738_0 *)state)->unk_10 = (u16) (((B28_818B7F38_S_80025738_0 *)state)->unk_10 + 1);
    switch (phase) {
    case 0:
        ((B28_818B7F38_S_80025738_0 *)state)->unk_10 = 0U;
        ((B28_818B7F38_S_80025738_0 *)state)->unk_0A = (s16) ((u16) ((B28_818B7F38_S_80025738_0 *)state)->unk_0A + 1);
        ((B28_818B7F38_S_80025738_0 *)state)->unk_0E = (u16) (((u16) ((B28_818B7F38_S_80025738_1 *)owner)->unk_2A >> 9) & 7);
        ((B28_818B7F38_S_80025738_2 *)render)->unk_0C = 0x808080;
    case 1:
        source_header = owner - 0x20;
        source_data = ((B28_818B7F38_S_80025738_3 *)source_header)->unk_0C;
        if (resolve_record_orientation_or_fallback(((B28_818B7F38_S_80025738_4 *)source_data)->unk_08, source_data, frame.delta, 0) != 0) {
            source_position = ((B28_818B7F38_S_80025738_3 *)source_header)->unk_08;
            ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_00.at02.v = (u16) ((B28_818B7F38_S_80025738_6 *)source_position)->unk_02;
            ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_04.at02.v = (u16) ((B28_818B7F38_S_80025738_6 *)source_position)->unk_06;
        } else {
            if (!(((B28_818B7F38_S_80025738_13 *)(((B28_818B7F38_S_80025738_3 *)source_header)->unk_0C))->unk_14 & 0x8000)) {
                break;
            }
            source_position = ((B28_818B7F38_S_80025738_3 *)source_header)->unk_08;
            ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_00.at02.v = (u16) ((B28_818B7F38_S_80025738_6 *)source_position)->unk_02;
            ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_04.at02.v = (u16) ((B28_818B7F38_S_80025738_6 *)source_position)->unk_06;
        }
        source_z = ((B28_818B7F38_S_80025738_6 *)source_position)->unk_0A;
        ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_08.at02.v = source_z;
        if (!(((B28_818B7F38_S_80025738_13 *)(((B28_818B7F38_S_80025738_3 *)source_header)->unk_0C))->unk_14 & 0x8000)) {
            ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_00.at02.v = (u16) (((B28_818B7F38_S_80025738_5 *)motion_in)->unk_00.at02.v
                + frame.delta[0]);
            ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_04.at02.v = (u16) (((B28_818B7F38_S_80025738_5 *)motion_in)->unk_04.at02.v
                + frame.delta[1]);
            base_z = ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_08.at02.v;
            ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_08.at02.v = base_z + frame.delta[2];
            if (!(*((B28_818B7F38_S_80025738_0 *)state)->unk_04 & 0x80)) {
                break;
            }
            target = ((B28_818B7F38_S_80025738_1 *)owner)->unk_60;
            index = 1;
        } else {
            ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_08.at02.v = source_z - 0x40;
            if (!(*((B28_818B7F38_S_80025738_0 *)state)->unk_04 & 0x80)) {
                break;
            }
            target = ((B28_818B7F38_S_80025738_1 *)owner)->unk_60;
            index = 1;
        }
        if (target != NULL) {
            ((B28_818B7F38_S_80025738_0 *)state)->unk_18 = target;
            destination = ((B28_818B7F38_S_80025738_14_pre *)(((B28_818B7F38_S_80025738_1 *)owner)->unk_60))[-1].unk_00;
            target_dx = ((B28_818B7F38_S_80025738_7 *)destination)->unk_00.at02.v;
            target_dx -= ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_00.at02u.v;
            if (target_dx < 0) {
                target_dx = 0 - target_dx;
            }
            frame.delta[0] = (u16) target_dx;
            target_dy = ((B28_818B7F38_S_80025738_7 *)destination)->unk_04.at02.v;
            target_dy -= ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_04.at02u.v;
            target_dy = abs(target_dy);
            frame.delta[1] = (u16) target_dy;
            target = ((B28_818B7F38_S_80025738_1 *)owner)->unk_60;
            current_z = ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_08.at02u.v;
            target_dz = ((B28_818B7F38_S_80025738_8 *)target)->unk_88;
            target_dz -= current_z;
            target_delta_cursor = (u16 *)((u8 *)&frame.out_x + 2);
            target_dz = abs(target_dz);
            frame.delta[2] = (u16) target_dz;
            ((B28_818B7F38_S_80025738_0 *)state)->unk_12 = target_dx;
            do {
                if (((B28_818B7F38_S_80025738_9 *)target_delta_cursor)->unk_18.s > ((B28_818B7F38_S_80025738_0 *)state)->unk_12) {
                    ((B28_818B7F38_S_80025738_0 *)state)->unk_12 = ((B28_818B7F38_S_80025738_9 *)target_delta_cursor)->unk_18.u;
                }
                index += 1;
                target_delta_cursor += 1;
            } while (index < 3);
            target_ticks = (s32) ((u16) ((B28_818B7F38_S_80025738_0 *)state)->unk_12 << 0x10) >> 0x14;
            ((B28_818B7F38_S_80025738_0 *)state)->unk_12 = (s16) target_ticks;
            if (target_ticks == 0) {
                ((B28_818B7F38_S_80025738_0 *)state)->unk_12 = 1;
            }
            ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_0C = (s32) ((s32) (((B28_818B7F38_S_80025738_7 *)destination)->unk_00.at00.v
                - ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_00.at00.v) / (s16) ((B28_818B7F38_S_80025738_0 *)state)->unk_12);
            ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_10 = (s32) ((s32) (((B28_818B7F38_S_80025738_7 *)destination)->unk_04.at00.v
                - ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_04.at00.v) / (s16) ((B28_818B7F38_S_80025738_0 *)state)->unk_12);
            ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_14 =
                (s32) ((s32) ((((B28_818B7F38_S_80025738_14 *)(((B28_818B7F38_S_80025738_1 *)owner)->unk_60))->unk_88 << 0x10)
                - ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_08.at00.v) / (s16) ((B28_818B7F38_S_80025738_0 *)state)->unk_12);
            spawn_owner_random_variant_effect(state, motion_in);
            next_phase = (u16) ((B28_818B7F38_S_80025738_0 *)state)->unk_0A + 1;
        } else {
            index = 0;
            tile_data = ((B28_818B7F38_S_80025738_3 *)source_header)->unk_0C;
            tile_x = ((B28_818B7F38_S_80025738_10 *)tile_data)->unk_24;
            tile_y = ((B28_818B7F38_S_80025738_10 *)tile_data)->unk_25;
            last_tile_x = tile_x;
            saved_y = tile_y;
            while (index < 8) {
                grid_x = (s16)tile_x;
                grid_y = (s16)tile_y;
                if ((s16)check_layer_offset_height((grid_x << 6) & 0xFFC0, (grid_y << 6) & 0xFFC0, ((B28_818B7F38_S_80025738_1 *)owner)->unk_88,
                    (s16) (((B28_818B7F38_S_80025738_0 *)state)->unk_0E << 9)) != 0) {
                    break;
                }
                source_position = &dir_step_x[(s16) ((B28_818B7F38_S_80025738_0 *)state)->unk_0E];
                probe_z = (u16) ((B28_818B7F38_S_80025738_1 *)owner)->unk_88;
                probe_z -= 0x20;
                probe_z = (u32)probe_z << 16;
                probe_z >>= 16;
                step_y = &dir_step_y[(s16) ((B28_818B7F38_S_80025738_0 *)state)->unk_0E];
                floor_z = sample_terrain_surface_height(((grid_x + *(s16 *)source_position) << 6) + 0x20 & 0xFFE0,
                    ((grid_y + *step_y) << 6) + 0x20 & 0xFFE0, probe_z);
                if (floor_z >= 0x201 || (s16) (floor_z - (u16) ((B28_818B7F38_S_80025738_1 *)owner)->unk_88) < -0x3F) {
                    break;
                }
                index += 1;
                tile_x += dir_step_x[(s16) ((B28_818B7F38_S_80025738_0 *)state)->unk_0E];
                tile_y += dir_step_y[(s16) ((B28_818B7F38_S_80025738_0 *)state)->unk_0E];
                saved_y = tile_y;
                last_tile_x = tile_x;
            }
            destination = &frame.out_x;
            index = 1;
            path_delta_cursor = (u16 *)((u8 *)&frame.out_x + 2);
            world_x = ((last_tile_x << 16) >> 10) + ((dir_step_x[(s16) ((B28_818B7F38_S_80025738_0 *)state)->unk_0E] + 1) << 5);
            ((B28_818B7F38_S_80025738_7 *)destination)->unk_00.at02.v = world_x;
            world_y = ((saved_y << 16) >> 10) + ((dir_step_y[(s16) ((B28_818B7F38_S_80025738_0 *)state)->unk_0E] + 1) << 5);
            ((B28_818B7F38_S_80025738_7 *)destination)->unk_04.at02.v = world_y;
            ((B28_818B7F38_S_80025738_7 *)destination)->unk_08.at02.v = ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_08.at02u.v + 0x20;
            frame.delta[0] = abs(((B28_818B7F38_S_80025738_7 *)destination)->unk_00.at02.v - ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_00.at02u.v);
            frame.delta[1] = abs(((B28_818B7F38_S_80025738_7 *)destination)->unk_04.at02.v - ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_04.at02u.v);
            frame.delta[2] = abs(((B28_818B7F38_S_80025738_7 *)destination)->unk_08.at02.v - ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_08.at02u.v);
            ((B28_818B7F38_S_80025738_0 *)state)->unk_12 = frame.delta[0];
            do {
                if (((B28_818B7F38_S_80025738_11 *)path_delta_cursor)->unk_18.s > ((B28_818B7F38_S_80025738_0 *)state)->unk_12) {
                    ((B28_818B7F38_S_80025738_0 *)state)->unk_12 = ((B28_818B7F38_S_80025738_11 *)path_delta_cursor)->unk_18.u;
                }
                index += 1;
                path_delta_cursor += 1;
            } while (index < 3);
            path_ticks = (s32) ((u16) ((B28_818B7F38_S_80025738_0 *)state)->unk_12 << 0x10) >> 0x14;
            ((B28_818B7F38_S_80025738_0 *)state)->unk_12 = (s16) path_ticks;
            if (path_ticks == 0) {
                ((B28_818B7F38_S_80025738_0 *)state)->unk_12 = 1;
            }
            ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_0C = (s32) ((s32) (((B28_818B7F38_S_80025738_7 *)destination)->unk_00.at00.v
                - ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_00.at00.v) / (s16) ((B28_818B7F38_S_80025738_0 *)state)->unk_12);
            ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_10 = (s32) ((s32) (((B28_818B7F38_S_80025738_7 *)destination)->unk_04.at00.v
                - ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_04.at00.v) / (s16) ((B28_818B7F38_S_80025738_0 *)state)->unk_12);
            ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_14 = (s32) ((s32) (((B28_818B7F38_S_80025738_7 *)destination)->unk_08.at00.v
                - ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_08.at00.v) / (s16) ((B28_818B7F38_S_80025738_0 *)state)->unk_12);
            spawn_owned_random_spin_effect(state, motion_in);
            next_phase = 6;
        }
        ((B28_818B7F38_S_80025738_0 *)state)->unk_0A = next_phase;
        ((B28_818B7F38_S_80025738_0 *)state)->unk_10 = 0U;
        break;
    case 2:
        ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_00.at00.v += ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_0C;
        ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_04.at00.v += ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_10;
        ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_08.at00.v += ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_14;
        if ((s16) ((B28_818B7F38_S_80025738_0 *)state)->unk_10 < ((B28_818B7F38_S_80025738_0 *)state)->unk_12) {
            break;
        }
        play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
        goto advance_phase;
    case 3:
        if ((s16) ((B28_818B7F38_S_80025738_0 *)state)->unk_10 >= 0x10) {
            ((B28_818B7F38_S_80025738_0 *)state)->unk_10 = 0U;
            ((B28_818B7F38_S_80025738_0 *)state)->unk_0A = (s16) ((u16) ((B28_818B7F38_S_80025738_0 *)state)->unk_0A + 1);
        }
        break;
    case 4:
        if ((s16) ((B28_818B7F38_S_80025738_0 *)state)->unk_10 < 0x30) {
            break;
        }
        interpolate_view_parameters(((B28_818B7F38_S_80025738_1 *)owner)->unk_60, ((B28_818B7F38_S_80025738_0 *)state)->unk_09, owner);
advance_phase:
        ((B28_818B7F38_S_80025738_0 *)state)->unk_10 = 0U;
        ((B28_818B7F38_S_80025738_0 *)state)->unk_0A = (s16) ((u16) ((B28_818B7F38_S_80025738_0 *)state)->unk_0A + 1);
        break;
    case 5:
        if (((B28_818B7F38_S_80025738_0 *)state)->unk_14 != 0) {
            break;
        }
        g_dungeon_status.active_actor = 0;
        (*(u16 *)((u8 *)state + -2)) = (u16) ((*(u16 *)((u8 *)state + -2)) | NODE_REMOVE);
        (*(s32 *)&object_flag_block.flags) = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
        break;
    case 6:
        ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_00.at00.v = (s32) (((B28_818B7F38_S_80025738_5 *)motion_in)->unk_00.at00.v
            + ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_0C);
        ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_04.at00.v = (s32) (((B28_818B7F38_S_80025738_5 *)motion_in)->unk_04.at00.v
            + ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_10);
        ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_08.at00.v = (s32) (((B28_818B7F38_S_80025738_5 *)motion_in)->unk_08.at00.v
            + ((B28_818B7F38_S_80025738_5 *)motion_in)->unk_14);
        if ((s16) ((B28_818B7F38_S_80025738_0 *)state)->unk_10 < ((B28_818B7F38_S_80025738_0 *)state)->unk_12) {
            break;
        }
        next_phase = 5;
        ((B28_818B7F38_S_80025738_0 *)state)->unk_0A = next_phase;
        ((B28_818B7F38_S_80025738_0 *)state)->unk_10 = 0U;
    }
    ((B28_818B7F38_S_80025738_0 *)state)->unk_14 = 0;
    return;
}
