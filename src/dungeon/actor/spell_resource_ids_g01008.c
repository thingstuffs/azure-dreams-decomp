#include "shared/entity.h"
/* Spell resource ids g01008.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01008 - CL:dungeon/func_800A3C30, CL:dungeon/func_800A40CC, PD:dungeon/engine:800DD8E7.
 */
struct ObjectPosition;
#include "shared/object_node.h"
#include "dungeon/effect.h"
#include "dungeon/actor/spell_resource_ids_g01008.h"
#include "shared/object_flags.h"

/*
 * Looks up the spell resource and, when the player-linked flag is set, substitutes 0x33, 0x3A, and
 * 0x42 for IDs 0x32, 0x39, and 0x40.
 */
s32 resolve_spell_effect_resource_id(s16 index) {
    s32 compare;

    index = spell_resource_ids[index];
    if (((Inner *)dungeon_actor_ring_anchor->unk_4C)->flag != 0) {
        compare = index;
        if (compare == 0x32) {
            return 0x33;
        }
        if (compare == 0x39) {
            return 0x3A;
        }
        if (compare == 0x40) {
            return 0x42;
        }
    }
    return index;
}

/* Maps special tile codes to mode-dependent values, otherwise returning the tile index. */

s16 resolve_alternate_spell_id(s32 tile_index)
{
    s16 index;
    u8 *tile;
    s32 tile_code;

    index = tile_index;
    tile = spell_resource_ids + (s16)tile_index;
    tile_code = *tile;

    if (*(*(u8 **)(((u8 *)dungeon_actor_ring_anchor) + 0x4C) + 1) != 0) {
        if (tile_code == 0x32) {
            return 7;
        }
        if (tile_code == 0x39) {
            return 8;
        }
        if (tile_code == 0x40) {
            return 9;
        }
    } else {
        if (tile_code == 0x32) {
            return 1;
        }
        if (tile_code == 0x39) {
            return 2;
        }
        if (tile_code == 0x40) {
            return 3;
        }
    }

    return index;
}

/* Creates an effect for an actor, sets its position and scale, and builds its message. */
void *create_actor_spell_effect(void *actor, void *record_data, s16 mode, void *context) {
    u8 *effect_record = record_data;
    void *message;
    const unsigned char *name_text;
    s32 effect_data;
    s32 text_context;
    void *new_text_context;
    s32 direction_offset;
    s32 effect_mode;
    u16 effect_flags;
    s32 global_flags;
    u8 variant;
    s16 effect_id;
    ObjectPosition *effect_position;
    S_800A94A0_7 *actor_state;
    ObjectNodeHeader *effect;
    S_800A94A0_3 *effect_state;
    void *linked_object;
    MovingPosition *actor_position;
    TileObject *map_state;

    actor_state = ((S_800A94A0_0 *)((u8 *)actor - 0x18))->unk_04;
    effect = allocate_list_node(0x12, &scene_object_list_anchor.next);
    if (effect != NULL) {
        effect_mode = ((s32) mode << 0x10) >> 0x10;
        {
            s32 mode_arg = effect_mode;
            u8 entry_variant;
            effect_id = effect_record[0];
            entry_variant = effect_record[1];
            current_spell_effect_variant = entry_variant;
            effect_data = load_spell_effect_code((u8) effect_id, mode_arg, ((S_800A94A0_0 *)((u8 *)actor - 0x18))->unk_2B);
        }
        if (effect_data == 0) {
            effect_flags = effect->flags | 0x8000;
            global_flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
            effect->flags = effect_flags;
            object_flag_block.flags = global_flags;
            return NULL;
        }
        effect->update_callback = effect_data;
        effect_state = ((void *)effect )+ 0x20;
        ((S_800A94A0_2 *)effect)->unk_20 = actor;
        effect_state->unk_04 = context;
        effect_state->unk_08 = effect_id;
        active_spell_parameters[0] = effect_id;
        variant = effect_record[1];
        effect_state->unk_09 = variant;
        active_spell_parameters[1] = variant;
        if (mode == 0) {
            actor_position = ((S_800A94A0_0 *)((u8 *)actor - 0x18))->unk_00;
            effect_position = effect->position;
            effect_position->x.w.i = (u16) actor_position->x;
            effect_position->y.w.i = (u16) actor_position->y;
            effect_position->z.w.i = (u16) actor_position->z;
            text_context = rand();
            if (!((u16) *((s16 *)&system_update_flags) & 1)) {
                linked_object = ((S_800A94A0_0 *)((u8 *)actor - 0x18))->unk_78;
                if (linked_object != NULL) {
                    get_tile_chebyshev_distance(((S_800A94A0_0 *)((u8 *)actor - 0x18))->unk_04,
                        ((S_800A94A0_6 *)((u8 *)linked_object - 0x14))->unk_00);
                    select_nearby_target_and_initialize_slot(effect, effect_position, 8, 0x300);
                } else {
                    select_nearby_target_and_initialize_slot(effect, effect_position, 8, 0x300);
                }
            } else {
                select_nearby_target_and_initialize_slot(effect, effect_position, 8, 0x300);
            }
            /* BYTES: retail evidence: the test's operands survive (the arm compiled away); reconstructed as a conditional update of a local nothing reads in the retail build - any dead local set reproduces the bytes (lane r118_fable_f4; decision 45, docs/evidence/r97_decisions.md) */
            if (text_context) {
                effect_mode = 0;
            }
        } else {
            map_state = &reference_tile_object;
            if (!(actor_state->unk_14 & 0x8000)) {
                if (!(map_state->sprite_flags & 0x8000)) {
                    process_nearby_object_midpoint(map_state, actor_state, dungeon_actor_ring_anchor->ground_height,
                        ((S_800A94A0_0 *)((u8 *)actor - 0x18))->unk_A0, 8, 0x300);
                    goto set_effect_scale;
                }
            }
            direction_offset = ((u16) ((S_800A94A0_9 *)(((u8 *)dungeon_actor_ring_anchor)))->unk_2A >> 8) & 0xE;
            setup_object_within_planar_range(actor - 0x20, (map_state->tile_position.parts.tile_x << 6) + ((s32) (*(u16 *)((u8 *)direction_x_offsets + direction_offset)
                << 0x10) >> 0x11) + 0x20, (map_state->tile_position.parts.tile_y << 6) + ((s32) (*(u16 *)((u8 *)direction_y_offsets
                + direction_offset) << 0x10) >> 0x11) + 0x20, dungeon_actor_ring_anchor->ground_height, 8, 0x300);
        }
set_effect_scale:
        if ((mode << 0x10) != 0) {
            spend_actor_mp(actor, alternate_spell_mp_costs[effect_id] << 6);
        } else {
            spend_actor_mp(actor, spell_mp_costs[effect_id] << 8);
        }
        if ((effect != NULL) && ((s8) ((S_800A94A0_0 *)((u8 *)actor - 0x18))->unk_2B > 0)) {
            new_text_context = get_unused_text_buffer();
            message = append_entity_display_text(actor, new_text_context);
            message = expand_text_control_codes(D_800E1C58, message);
            if (((u32)(u16)mode << 0x10) != 0) {
                effect_id = resolve_alternate_spell_id(effect_id);
                name_text = item_action_definitions[effect_id].alternate_name;
                message = expand_text_control_codes(name_text, message);
            } else {
                name_text = item_action_definitions[effect_id].normal_name;
                message = expand_text_control_codes(name_text, message);
            }
            clear_byte_and_advance(expand_text_control_codes(D_80089080, message));
            display_text_with_fullwidth_adjustment(new_text_context);
            return effect;
        }
    }
    return effect;
}

/* Updates selection data and starts a message when the selection changes. */
/* Requests changed spell-effect code from CD, sets its sound cue, and returns the loaded entry when ready. */
s32 load_spell_effect_code(selection_id, alternate_table, unused)
    s16 selection_id, alternate_table;
    s32 unused; {
    register s32 changed;
    s32 change_result;
    u32 index_hi;
    s32 doubled_index;
    s32 *selection_entry;
    s32 *selection_table;
    s32 *resource_data;
    s32 *message_data;
    s32 message_offset;
    s32 entry_offset;
    s32 state_value;

    resource_data = (s32 *)0x80024000;
    if (spell_resource_load_state == 0) {
        changed = 0;
        if ((selection_id != (spell_effect_selector_cache & 0x3F)) ||
            ((((u8)spell_effect_selector_cache >> 6) & 1) != alternate_table)) {
            changed = 1;
        }
        change_result = changed;
        if (change_result != 0) {
            if (alternate_table != 0) {
                message_offset = ((s16)resolve_spell_effect_resource_id(selection_id) * 0xC) + 0x607F;
            } else {
                message_offset = ((selection_id - 1) * 0xC) + 0x607F;
            }
            message_data = D_800E58B0;
            pack_tagged_resource_descriptor(0xC, resource_data, message_data, message_offset);
            Control_CD(6, message_data, 0);
            Control_CD(0xFF, set_byte_one, &spell_resource_load_state);
            spell_effect_selector_cache = selection_id | (alternate_table << 6);
        }

        if (alternate_table != 0) {
            selection_table = D_800DDAB8;
            index_hi = resolve_alternate_spell_id(selection_id) << 16;
            doubled_index = index_hi >> 15;
            state_value = cd_cue_base[0];
        } else {
            selection_table = spell_audio_cues;
            index_hi = selection_id << 16;
            doubled_index = index_hi >> 15;
            state_value = cd_cue_base[0];
        }
        entry_offset = (s32)(doubled_index << 16) >> 14;
        selection_entry = (s32 *)(entry_offset + (unsigned long)selection_table);
        sound_set_cd_cue_parameters(0, state_value, selection_entry[0], selection_entry[1]);
        Control_CD(0x15, (void *)read_stream_cue_start_offset(), 0);

        change_result = changed;
        if (change_result != 0) {
            spell_resource_load_state = 2;
            return 0;
        }
    } else {
        if (spell_resource_load_state != 1) {
            return 0;
        }
        spell_resource_load_state = 0;
    }
    return resource_data[0];
}
