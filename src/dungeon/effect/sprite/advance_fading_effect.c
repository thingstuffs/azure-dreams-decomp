#include "shared/audio_commands.h"
/* Linked line travel, directional sprite rings, timed fades, and nearby status effects. */
#include "shared/object_node.h"
#include "dungeon/effect/sprite/advance_fading_effect.h"
#include "shared/object_flags.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/actor.h"
#include "shared/game_work.h"
#include "dungeon/effect/sprite.h"
void (*const dungeon_ovl_188298c_entry)(ovl_188298c_818632E4_Controller *ctrl, ovl_188298c_818632E4_Motion *motion, void *render_data) = move_to_linked_object_and_apply_arrival_effects;

/* Attempts a status effect on compatible, eligible actors within two tiles of the supplied center. */
void apply_status_to_nearby_actors(s32 x, s32 y, void *kind, s32 flags) {
    u8 *actor = dungeon_actor_ring_anchor;
    x = (s16)x;
    y = (s16)y;
    flags = ((u8)flags >> 2) + 0x10;
    do {
        if ((s16)check_entity_interaction_compatibility(kind, actor) != 0) {
            u8 *header = *(u8 * *)&((ObjectNodeHeader *)((u8 *)actor - 0x20))->sprite;
            if (abs(header[0x24] - x) < 3 && abs(header[0x25] - y) < 3 && (s16)check_entity_eligibility(actor) != 0) {
                s32 amount = flags + (generate_random_value() & 3);
                s32 mode = 0x10;
                if (current_spell_effect_variant == 0xFF) mode = 0xFF;
                try_apply_status_effect(actor, mode, amount);
            }
        }
        actor = *(u8 **)(actor + 0x5C) + 0x20;
    } while (actor != dungeon_actor_ring_anchor);
}

/* Expands and fades a sprite, restarts at frame 4 after its first completed animation, and removes it
   after the second. */
void advance_fading_effect(ovl_188298c_8186298C_Arg0Ent *state, void *unused, ovl_188298c_8186298C_Arg2Ent *effect)
{
    u16 size;
    u8 brightness;

    state->unk00->unk14++;
    size = effect->unk1E + 0x400;
    brightness = effect->unk0E - 4;
    effect->unk1E = size;
    effect->unk1C = size;
    effect->unk0E = brightness;
    effect->unk0D = brightness;
    effect->unk0C = brightness;
    advance_sprite_animation_and_textures(effect);

    if (effect->unk14 & 0x6000) {
        if (state->unk04 != 0) {
            *(u16 *)((u8 *)state - 2) |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
            return;
        } else {
            select_record_entry_and_value(effect, rising_sprite_entries, 4);
            state->unk04 = 1;
        }
    }
}

/* Creates a gray sprite at the source's horizontal coordinates with a randomized vertical offset. */
void spawn_jittered_type_212_effect(s32 owner, void *source)
{
    s32 roll;
    void *render;
    int white;
    ObjectNodeHeader *obj;
    obj = allocate_flagged_object_node(0x212);
    if (obj != 0) {
        *((s32 *) (((s8 *) obj) + 0x20)) = owner;
        obj->update_callback = (void *)advance_fading_effect;
        render = obj->sprite;
        *((s8 *) (((s8 *) obj) + 0x24)) = 0;
        white = 0x80;
        *((s8 *) (((s8 *) render) + 0xE)) = white;
        *((s8 *) (((s8 *) render) + 0xD)) = white;
        *((s8 *) (((s8 *) render) + 0xC)) = white;
        select_record_entry_and_value(render, rising_sprite_entries, 0);
        *((s16 *) (((s8 *) render) + 0x1E)) = 0x1000;
        *((s16 *) (((s8 *) render) + 0x1C)) = 0x1000;
        *((s16 *) (((s8 *) render) + 0x12)) = 0x7E0B;
        *((u16 *) (((s8 *) render) + 0x10)) = (u16) ((*((u16 *) (((s8 *) render) + 0x10))) | 0x60);
        *((u16 *) (((s8 *) render) + 0x14)) = (u16) ((*((u16 *) (((s8 *) render) + 0x14))) | 0x10C);
        register_node(obj, project_sprite_chain);
        render = obj->position;
        rand();
        *((u16 *) (((s8 *) render) + 2)) = (u16) (*((u16 *) (((s8 *) source) + 2)));
        *((u16 *) (((s8 *) render) + 6)) = (u16) (*((u16 *) (((s8 *) source) + 6)));
        roll = rand();
        *((s16 *) (((s8 *) render) + 0xA)) = (s16) (((*((u16 *) (((s8 *) source) + 0xA))) - 0x40) - (roll % 16));
    }
}

/* Advances sprite animation, spawns a child at update 10, and removes the effect when its animation
   finishes. */
void advance_counter_and_propagate_target_flags(void *state, s32 context, SpriteFrameState *target) {
    u16 update_count;
    ovl_188298c_81862B74_S_81862B74_1 *linked_object;

    linked_object = ((ovl_188298c_81862B74_S_81862B74_0 *)state)->unk_00;
    linked_object->unk_14 = (u16) (linked_object->unk_14 + 1);
    advance_sprite_animation_and_textures(target);
    update_count = ((ovl_188298c_81862B74_S_81862B74_0 *)state)->unk_04 + 1;
    ((ovl_188298c_81862B74_S_81862B74_0 *)state)->unk_04 = update_count;
    if ((s16) update_count == 0xA) {
        spawn_jittered_type_212_effect(((ovl_188298c_81862B74_S_81862B74_0 *)state)->unk_00, context);
    }
    if (target->flags & 0x6000) {
        ((ovl_188298c_81862B74_S_81862B74_0_pre *)state)[-1].unk_00 = (u16) (((ovl_188298c_81862B74_S_81862B74_0_pre *)state)[-1].unk_00 | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
}

/* Creates a center sprite or sprites along eight radial tile directions, stopping each direction at
   blocked terrain. */
void create_radius_directional_effects(s32 effect_param, void *origin_arg, s16 radius_arg, u8 *blocked_dirs) {
    s16 target_y;
    s16 target_x;
    s32 source_y;
    s32 source_x;
    s32 direction;
    ovl_188298c_81862C28_S_81862C28_1 *effect_data;
    ovl_188298c_81862C28_S_81862C28_0 *effect;
    s16 tile_x;
    s16 tile_dy;
    s16 origin_z;

    if (radius_arg == 0) {
        effect = allocate_flagged_object_node(0x212);
        if (effect != 0) {
            effect_data = effect->unk_0C;
            effect->unk_10 = advance_counter_and_propagate_target_flags;
            effect->unk_20 = effect_param;
            effect->unk_24 = 0;
            effect_data->unk_0E = 0x80;
            effect_data->unk_0D = 0x80;
            effect_data->unk_0C = 0x80;
            select_record_entry_and_value(effect_data, countdown_sprite_entries, 0);
            effect_data->unk_1C = 0x1000;
            effect_data->unk_1E = 0x3000;
            effect_data->unk_12 = 0x7E0B;
            effect_data->unk_10 |= 0x20;
            effect_data->unk_14 |= 0x10C;
            register_node(effect, project_sprite_chain);
            effect_data = effect->unk_08;
            effect_data->unk_02.s = ((ovl_188298c_81862C28_S_81862C28_2 *)origin_arg)->unk_02.s;
            effect_data->unk_06.s = ((ovl_188298c_81862C28_S_81862C28_2 *)origin_arg)->unk_06.s;
            effect_data->unk_0A = ((ovl_188298c_81862C28_S_81862C28_2 *)origin_arg)->unk_0A.s;
        }
    } else {
        for (direction = 0; direction < 8; direction++) {
            effect_data = blocked_dirs + direction;
            if (effect_data->unk_00 == 0) {
                source_x = ((ovl_188298c_81862C28_S_81862C28_2 *)origin_arg)->unk_02.u;
                tile_x = (source_x / 64) + ((u16)dir_step_x[direction] * (u16)radius_arg);
                source_y = ((ovl_188298c_81862C28_S_81862C28_2 *)origin_arg)->unk_06.u;
                tile_dy = (source_y / 64) + (u16)dir_step_y[direction] * (u16)radius_arg;
                origin_z = ((ovl_188298c_81862C28_S_81862C28_2 *)origin_arg)->unk_0A.u;
                target_x = ((tile_x << 0x10) >> 0xA) + 0x20;
                target_y = ((tile_dy << 0x10) >> 0xA) + 0x20;
                if ((check_left_tile_and_center_height(target_x & 0xFFE0, target_y & 0xFFE0, origin_z) << 0x10) != 0) {
                    effect_data->unk_00 = 1;
                    continue;
                }
                effect = allocate_flagged_object_node(0x212);
                if (effect != 0) {
                    effect_data = effect->unk_0C;
                    effect->unk_10 = advance_counter_and_propagate_target_flags;
                    effect->unk_20 = effect_param;
                    effect->unk_24 = 0;
                    effect_data->unk_0E = 0x40;
                    effect_data->unk_0D = 0x40;
                    effect_data->unk_0C = 0x40;
                    select_record_entry_and_value(effect_data, countdown_sprite_entries, 0);
                    effect_data->unk_1C = 0x1000;
                    effect_data->unk_1E = 0x1800;
                    effect_data->unk_12 = 0x7E0B;
                    effect_data->unk_10 |= 0x20;
                    effect_data->unk_14 |= 0x10C;
                    register_node(effect, project_sprite_chain);
                    effect_data = effect->unk_08;
                    effect_data->unk_02.u = target_x;
                    effect_data->unk_06.u = target_y;
                    effect_data->unk_0A = ((ovl_188298c_81862C28_S_81862C28_2 *)origin_arg)->unk_0A.s;
                    effect_data->unk_0A = get_surface_height_at_record(effect_data);
                }
            }
        }
    }
}

/* Returns the end-minus-start difference as a 32-bit value. */
static __inline__ s32 first_delta_s32_s32(s32 end, s32 start)
{
    return end - start;
}

/* Interpolates and projects a shaded line, then links it into the depth ordering table. */
s32 project_and_queue_shaded_line(void *line, void *unused_render_context)
{
    u8 *line_or_red;
    u8 *scratch = (u8 *)0x1F800000;
    u8 *packet;
    void *projection_out_a;
    void *projection_out_b;
    ovl_188298c_81862ED8_PackedDelta delta;
    s32 mask_or_phase;
    s32 phase_or_depth;
    s32 multiplier;
    u8 *line_bytes = line;
    s32 y;
    s32 first_z;
    s32 second_z;
    s32 depth_or_tag;
    s32 depth_sum;
    u32 *ordering_table;
    u8 *render_ctx = g_game_work.draw_buffer;

    ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_18 = (u32 *)(render_ctx + 0xB0);
    packet = ((GpuContext *)render_ctx)->packetCursor;
    line_or_red = line_bytes;
    ((GpuContext *)render_ctx)->packetCursor = packet + 0x14;

    ((ovl_188298c_81862ED8_S_800246D8_2 *)packet)->unk_00.at03.v = 4;
    ((ovl_188298c_81862ED8_S_800246D8_2 *)packet)->unk_07 = 0x50;

    ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_64 = ((ovl_188298c_81862ED8_S_800246D8_3 *)line_or_red)->unk_22;
    ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_66 = ((ovl_188298c_81862ED8_S_800246D8_3 *)line_or_red)->unk_26;
    ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_68 = ((ovl_188298c_81862ED8_S_800246D8_3 *)line_or_red)->unk_2A;
    ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_6C = ((ovl_188298c_81862ED8_S_800246D8_3 *)line_or_red)->unk_3A;
    ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_6E = ((ovl_188298c_81862ED8_S_800246D8_3 *)line_or_red)->unk_3E;
    ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_70 = ((ovl_188298c_81862ED8_S_800246D8_3 *)line_or_red)->unk_42;

    phase_or_depth = ((ovl_188298c_81862ED8_S_800246D8_3 *)line_or_red)->unk_10 - 1;
    switch (phase_or_depth) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    {
        s32 x0;
        s32 mask;
        s32 y0;
        s32 z0;
        s32 step_x;
        s32 step_y;
        s32 end_z;

        delta.word = first_delta_s32_s32(((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_6C, (x0 = ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_64))
        << 16;
        delta.word >>= 3;
        delta.word *= ((ovl_188298c_81862ED8_S_800246D8_3 *)line_or_red)->unk_10 + 1;

        y0 = ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_66;
        mask = 0xFFFF0000;
        step_x = (delta.word & mask) >> 16;
        delta.half.high = ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_6E - y0;
        delta.word &= mask;
        ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_6C = x0 + step_x;
        delta.word >>= 3;
        delta.word *= ((ovl_188298c_81862ED8_S_800246D8_3 *)line_or_red)->unk_10 + 1;

        end_z = ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_70;
        z0 = ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_68;
        step_y = delta.half.high;
        delta.half.high = end_z - z0;
        delta.word &= mask;
        ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_6E = y0 + step_y;
        delta.word >>= 3;
        delta.word *= ((ovl_188298c_81862ED8_S_800246D8_3 *)line_or_red)->unk_10 + 1;
        z0 += delta.half.high;
        ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_70 = z0;
    }
        {
            s32 level;

            mask_or_phase = ((ovl_188298c_81862ED8_S_800246D8_3 *)line_or_red)->unk_10;
            multiplier = 15;
            level = mask_or_phase + 1;
            line_or_red = (u8 *)(level * multiplier);
            multiplier = 23;
            y = level * multiplier;
            level = 0x40;
            ((ovl_188298c_81862ED8_S_800246D8_2 *)packet)->unk_04 = level;
            ((ovl_188298c_81862ED8_S_800246D8_2 *)packet)->unk_05 = level;
            ((ovl_188298c_81862ED8_S_800246D8_2 *)packet)->unk_06 = level;
            level -= (7 - mask_or_phase) * 8;
            multiplier = (s32)line_or_red + 0x40;
            ((ovl_188298c_81862ED8_S_800246D8_2 *)packet)->unk_0D = level;
            ((ovl_188298c_81862ED8_S_800246D8_2 *)packet)->unk_0C = multiplier;
            multiplier = y + 0x40;
            ((ovl_188298c_81862ED8_S_800246D8_2 *)packet)->unk_0E = multiplier;
        }
        break;
    case 7:
        ((ovl_188298c_81862ED8_S_800246D8_2 *)packet)->unk_04 = 0x40;
        ((ovl_188298c_81862ED8_S_800246D8_2 *)packet)->unk_05 = 0x40;
        ((ovl_188298c_81862ED8_S_800246D8_2 *)packet)->unk_06 = 0x40;
        ((ovl_188298c_81862ED8_S_800246D8_2 *)packet)->unk_0C = 0x7F;
        ((ovl_188298c_81862ED8_S_800246D8_2 *)packet)->unk_0D = 0;
        ((ovl_188298c_81862ED8_S_800246D8_2 *)packet)->unk_0E = 0xFF;
        break;
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    {
        s32 x0;
        s32 mask;
        s32 y0;
        s32 z0;
        s32 step_x;
        s32 step_y;
        s32 end_z;

        delta.word = first_delta_s32_s32(((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_6C, (x0 = ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_64))
        << 16;
        delta.word >>= 3;
        delta.word *= ((ovl_188298c_81862ED8_S_800246D8_3 *)line_or_red)->unk_10 - 7;

        y0 = ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_66;
        mask = 0xFFFF0000;
        step_x = (delta.word & mask) >> 16;
        delta.half.high = ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_6E - y0;
        delta.word &= mask;
        ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_64 = x0 + step_x;
        delta.word >>= 3;
        delta.word *= ((ovl_188298c_81862ED8_S_800246D8_3 *)line_or_red)->unk_10 - 7;

        end_z = ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_70;
        z0 = ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_68;
        step_y = delta.half.high;
        delta.half.high = end_z - z0;
        delta.word &= mask;
        ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_66 = y0 + step_y;
        delta.word >>= 3;
        delta.word *= ((ovl_188298c_81862ED8_S_800246D8_3 *)line_or_red)->unk_10 - 7;
        z0 += delta.half.high;
        ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_68 = z0;
    }
        {
            s32 k;
            s32 k23;

            y = ((ovl_188298c_81862ED8_S_800246D8_3 *)line_or_red)->unk_10;
            k = 15;
            mask_or_phase = y - 7;
            line_or_red = (u8 *)(mask_or_phase * k);
            k23 = 23;
            mask_or_phase *= k23;
            ((ovl_188298c_81862ED8_S_800246D8_2 *)packet)->unk_0D = 0;
            ((ovl_188298c_81862ED8_S_800246D8_2 *)packet)->unk_05 = (k - y) * 8;
            multiplier = 0x7F;
            ((ovl_188298c_81862ED8_S_800246D8_2 *)packet)->unk_0C = multiplier;
            multiplier = 0xFF;
            ((ovl_188298c_81862ED8_S_800246D8_2 *)packet)->unk_0E = multiplier;
            multiplier = (s32)line_or_red + 0x40;
            ((ovl_188298c_81862ED8_S_800246D8_2 *)packet)->unk_04 = multiplier;
            multiplier = mask_or_phase + 0x40;
            ((ovl_188298c_81862ED8_S_800246D8_2 *)packet)->unk_06 = multiplier;
        }
        break;
    }

    projection_out_a = scratch + 0x84;
    projection_out_b = scratch + 0x88;
    first_z = RotTransPers((void *)((u32)scratch | 0x64),
                            (void *)((u32)scratch | 0xD8), projection_out_a, projection_out_b);
    ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_F4 = first_z;
    second_z = RotTransPers((void *)((u32)scratch | 0x6C),
                             (void *)((u32)scratch | 0xDC), projection_out_a, projection_out_b);
    ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_F8 = second_z;

    ((ovl_188298c_81862ED8_S_800246D8_2 *)packet)->unk_08 = ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_D8;
    ((ovl_188298c_81862ED8_S_800246D8_2 *)packet)->unk_0A = ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_DA;
    ((ovl_188298c_81862ED8_S_800246D8_2 *)packet)->unk_10 = ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_DC;
    ((ovl_188298c_81862ED8_S_800246D8_2 *)packet)->unk_12 = ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_DE;

    depth_sum = ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_F4;
    depth_sum += ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_F8;
    depth_or_tag = (s32)(depth_sum + ((u32)depth_sum >> 31)) >> 1;
    ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_B4 = depth_or_tag;
    if ((u32)depth_or_tag < 0x1E0U) {
        u32 entry_addr;
        u32 *ot_base;
        s32 low_mask;
        low_mask = 0x00FFFFFF;
        entry_addr = depth_or_tag << 2;
        ot_base = ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_18;
        depth_or_tag = 0xFF000000;
        entry_addr += (u32)ot_base;
        ((ovl_188298c_81862ED8_S_800246D8_2 *)packet)->unk_00.at00.v =
            (((ovl_188298c_81862ED8_S_800246D8_2 *)packet)->unk_00.at00.v & depth_or_tag) |
            (*(u32 *)entry_addr & low_mask);

        phase_or_depth = ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_B4;
        ordering_table = ((ovl_188298c_81862ED8_S_800246D8_0 *)scratch)->unk_18;
        ordering_table[phase_or_depth] =
            (ordering_table[phase_or_depth] & depth_or_tag) |
            ((u32)packet & low_mask);
    }

    return 0;
}

/*
 * Moves a line effect to a linked actor or forward tile, emits radial sprites, and applies a
 * nearby status effect.
 *
 * MECHANISM: The 0x28 frame holds s3=scratchpad, s2=packet, and s1/s0 call bases. Each
 * interpolation arm keeps its coordinates, steps and mask in arm-local variables (single-lifetime
 * quantities for local-alloc), while delta and line_or_red stay function-wide; the masked step_x
 * read gives the mask the extra reference that orders it ahead of y0.
 */
void move_to_linked_object_and_apply_arrival_effects(ovl_188298c_818632E4_Controller *ctrl, ovl_188298c_818632E4_Motion *motion, void *render_data)
{
    u8 *root;
    ovl_188298c_818632E4_RootPrefix *prefix;
    ovl_188298c_818632E4_Lookup *lookup;
    SpriteFrameState *lookup_2;
    ovl_188298c_818632E4_Motion *root_motion;

    u8 *linked_root;
    u8 *slot;
    GteShortVector delta;
    u16 final_x;
    u16 final_y;
    s32 step;
    s32 diff;
    s32 start_coord;
    s32 floor_height;
    u16 cell_x;
    u16 cell_y;
    u16 start_z;
    s32 state;
    u32 elapsed;

    elapsed = (u16)ctrl->timer;
    state = ctrl->state;
    root = ctrl->root;
    ctrl->timer = elapsed + 1;
    switch (state) {
    case 0:
        ctrl->timer = 0;
        ctrl->state++;
        ctrl->angle = (*(u16 *)(root + 0x2A) >> 9) & 7;
        step = 7;
        slot = (u8 *)ctrl + 7;
        do {
            slot[22] = 0;
            step--;
            slot--;
        } while (step >= 0);
        ((s32 *)render_data)[3] = 0x00808080;

    case 1:
        prefix = (ovl_188298c_818632E4_RootPrefix *)(root - 0x20);
        if (resolve_record_orientation_or_fallback(prefix->lookup->source, prefix->lookup, &delta, 0) == 0) {
            if (!(prefix->lookup->flags & 0x8000)) {
                break;
            }
        }

        root_motion = prefix->motion;
        motion->x.h.hi = root_motion->x.h.hi;
        motion->y.h.hi = root_motion->y.h.hi;
        start_z = root_motion->z.h.hi;
        motion->z.h.hi = start_z;
        if (!(prefix->lookup->flags & 0x8000)) {
            motion->x.h.hi += delta.vx;
            motion->y.h.hi += delta.vy;
            motion->z.h.hi += delta.vz;
        } else {
            motion->z.h.hi = start_z - 64;
        }
        if (!(*ctrl->flags & 0x80)) {
            break;
        }

        ctrl->saved = *motion;
        linked_root = *(u8 **)(root + 0x60);
        if (linked_root != 0) {
            prefix = (ovl_188298c_818632E4_RootPrefix *)*(ovl_188298c_818632E4_Motion **)(linked_root - 0x18);

            start_coord = motion->x.h.hi;
            delta.vx = __builtin_abs(((ovl_188298c_818632E4_Motion *)prefix)->x.h.hi - start_coord);

            delta.vy = __builtin_abs(((ovl_188298c_818632E4_Motion *)prefix)->y.h.hi - motion->y.h.hi);

            linked_root = *(u8 **)(root + 0x60);
            start_coord = motion->z.h.hi;
            delta.vz = __builtin_abs(*(s16 *)(linked_root + 0x88) - start_coord);

            linked_root = *(u8 **)(root + 0x60);
            lookup = *(ovl_188298c_818632E4_Lookup **)(linked_root - 0x14);
            ctrl->cell_x = lookup->cell_x;
            ctrl->cell_y = lookup->cell_y;

            ctrl->target[0].val = ((ovl_188298c_818632E4_Motion *)prefix)->x.val;
            ctrl->target[1].val = ((ovl_188298c_818632E4_Motion *)prefix)->y.val;
            diff = *(u16 *)(*(u8 **)(root + 0x60) + 0x88);
            ctrl->target[2].h.lo = 0;
            ctrl->target[2].h.hi = diff;

            motion->dx.val = (ctrl->target[0].val - motion->x.val) / 15;
            motion->dy.val = (ctrl->target[1].val - motion->y.val) / 15;
            motion->dz.val = (ctrl->target[2].val - motion->z.val) / 15;
        } else {
            step = 0;
            lookup_2 = prefix->lookup;
            cell_x = lookup_2->tile_x;
            cell_y = lookup_2->tile_y;
            final_x = cell_x;
            final_y = cell_y;

            do {
                if ((s16)check_layer_offset_height(((s16)cell_x << 6) & 0xFFC0,
                                       ((s16)cell_y << 6) & 0xFFC0,
                                       *(s16 *)(root + 0x88),
                                       (s16)(ctrl->angle << 9)) != 0) {
                    break;
                }

                {
                    s16 *x_step;
                    s16 *y_step;
                    s32 probe_z;
                    s32 direction;
                    u16 root_z;

                    direction = (s16)ctrl->angle;
                    root_z = *(u16 *)(root + 0x88);
                    lookup = &dir_step_x[direction];
                    x_step = lookup;
                    probe_z = (s16)(root_z - 32);
                    y_step = &dir_step_y[direction];
                    floor_height = sample_terrain_surface_height((((s16)cell_x + *x_step) << 6) + 32 & 0xFFE0,
                                                 (((s16)cell_y + *y_step) << 6) + 32 & 0xFFE0,
                                                 probe_z);
                }
                if ((s16)floor_height >= 513) {
                    break;
                }
                if ((s16)(floor_height - *(u16 *)(root + 0x88)) < -63) {
                    break;
                }

                {
                    s32 direction;

                    direction = (s16)ctrl->angle;
                    step++;
                    cell_x += dir_step_x[direction];
                    cell_y += dir_step_y[direction];
                    final_x = cell_x;
                    final_y = cell_y;
                }
            } while (step < 8);

            {

                prefix = (ovl_188298c_818632E4_RootPrefix *)ctrl->target;
                ((ovl_188298c_818632E4_Fixed32 *)prefix)[2].val = 0;
                ((ovl_188298c_818632E4_Fixed32 *)prefix)[1].val = 0;
                ctrl->target[0].val = 0;
                ((ovl_188298c_818632E4_Fixed32 *)prefix)[0].h.hi = ((final_x << 16) >> 10) + 32;
                ((ovl_188298c_818632E4_Fixed32 *)prefix)[1].h.hi = ((final_y << 16) >> 10) + 32;
                ((ovl_188298c_818632E4_Fixed32 *)prefix)[2].h.hi = -1024;
                ((ovl_188298c_818632E4_Fixed32 *)prefix)[2].h.hi = sample_terrain_surface_height((u16)((ovl_188298c_818632E4_Fixed32 *)prefix)[0].h.hi,
                                               (u16)((ovl_188298c_818632E4_Fixed32 *)prefix)[1].h.hi, -1024);
                if ((s16)((ovl_188298c_818632E4_Fixed32 *)prefix)[2].h.hi >= 513) {
                    ((ovl_188298c_818632E4_Fixed32 *)prefix)[2].h.hi = motion->z.h.hi + 32;
                }
            }

            motion->dx.val = (ctrl->target[0].val - motion->x.val) / 15;
            motion->dy.val = (ctrl->target[1].val - motion->y.val) / 15;
            motion->dz.val = (ctrl->target[2].val - motion->z.val) / 15;
            ctrl->cell_x = final_x;
            ctrl->cell_y = final_y;
        }
        ctrl->timer = 0;
        ctrl->state++;
        play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
        break;

    case 2:
        motion->x.val += motion->dx.val;
        motion->y.val += motion->dy.val;
        motion->z.val += motion->dz.val;
        project_and_queue_shaded_line(ctrl, render_data);
        if (ctrl->timer < 15) {
            break;
        }
        ctrl->timer = 0;
        ctrl->state++;
        create_radius_directional_effects(ctrl, motion, 0, &ctrl->slots[0]);
        break;

    case 3:
    {
        u32 effect_tick;

        effect_tick = (u16)ctrl->timer;
        if ((effect_tick & 7) == 0) {
            create_radius_directional_effects(ctrl, motion, (s16)effect_tick >> 3, &ctrl->slots[0]);
        }
    }
        if (ctrl->timer < 24) {
            break;
        }
        ctrl->timer = 0;
        ctrl->state++;
        break;

    case 4:
        if (ctrl->timer < 36) {
            break;
        }
        apply_status_to_nearby_actors(ctrl->cell_x, ctrl->cell_y, root, ctrl->kind);
        ctrl->timer = 0;
        ctrl->state++;
        break;

    case 5:
        if (ctrl->active == 0) {
            g_dungeon_status.active_actor = 0;
            *(u16 *)((u8 *)ctrl - 2) |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }

    default:
        break;
    }

    ctrl->active = 0;
}
