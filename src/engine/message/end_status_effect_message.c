#include "shared/actor_property_flags.h"
#include "shared/monster_ids.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_status_ids.h"
#include "shared/object_node.h"
#include "slus/jtbl_80042BDC.h"
#include "shared/object_flags.h"

#include "common.h"

/* Rodata owner: the row's switch emits its jump table(s) into this object's .rodata,
 * placed at the retail address by config/slus_modules.json (assets/800.bin carve). */

#include "slus/jtbl_80042BDC.h"
#include "engine/message.h"

/* Applies status-ending changes to actor flags, form and tile occupancy, with messages when enabled. */
void end_status_effect_message(S_80042BDC *ent, s16 action) {
    S_80042BDC *spawn_result;
    S_80042BDC *spawn_result_2;
    u8 *message_ctx;
    S_80042BDC_child *child;
    s32 action_index;
    action_index = (s16)(action - 1);
    switch (action_index) {
    case STATUS_SLEEP - 1:
        ent->x1C &= ~ACTOR_ASLEEP;
        if (ent->x14 & ACTOR_PARTY_MEMBER) {
            message_ctx = get_unused_text_buffer();
            clear_byte_and_advance(expand_text_control_codes(status_end_action_1_text, append_entity_display_text(ent, message_ctx)));
            display_text_with_fullwidth_adjustment(message_ctx);
        }
        break;
    case STATUS_CONFUSION - 1:
        ent->x1C &= ~ACTOR_CONFUSED;
        if (ent->x14 & ACTOR_PARTY_MEMBER) {
            message_ctx = get_unused_text_buffer();
            clear_byte_and_advance(expand_text_control_codes(status_end_action_2_text, append_entity_display_text(ent, message_ctx)));
            display_text_with_fullwidth_adjustment(message_ctx);
        }
        break;
    case STATUS_BLIND - 1:
        ent->x1C &= ~ACTOR_BLIND;
        if (ent->x14 & ACTOR_PARTY_MEMBER) {
            message_ctx = get_unused_text_buffer();
            clear_byte_and_advance(expand_text_control_codes(status_end_action_3_text, append_entity_display_text(ent, message_ctx)));
            display_text_with_fullwidth_adjustment(message_ctx);
        }
        if (ent->x13 != 0) {
            refresh_actor_proximity_state(ent);
        }
        break;
    case STATUS_PARALYSIS - 1:
        ent->x1C &= ~ACTOR_PARALYZED;
        if (ent->x14 & ACTOR_PARTY_MEMBER) {
            message_ctx = get_unused_text_buffer();
            clear_byte_and_advance(expand_text_control_codes(status_end_action_4_text, append_entity_display_text(ent, message_ctx)));
            display_text_with_fullwidth_adjustment(message_ctx);
        }
        break;
    case STATUS_POISON - 1:
        ent->x1C &= ~ACTOR_POISONED;
        if (ent->x14 & ACTOR_PARTY_MEMBER) {
            message_ctx = get_unused_text_buffer();
            clear_byte_and_advance(expand_text_control_codes(status_end_action_5_text, append_entity_display_text(ent, message_ctx)));
            display_text_with_fullwidth_adjustment(message_ctx);
        }
        break;
    case STATUS_MAGIC_BIND - 1:
        ent->x1C &= ~ACTOR_MAGIC_BOUND;
        if (ent->x14 & ACTOR_PARTY_MEMBER) {
            message_ctx = get_unused_text_buffer();
            clear_byte_and_advance(expand_text_control_codes(status_end_action_6_text, append_entity_display_text(ent, message_ctx)));
            display_text_with_fullwidth_adjustment(message_ctx);
        }
        break;
    case STATUS_SPEED - 1:
        if (ent->x14 & ACTOR_PARTY_MEMBER) {
            message_ctx = get_unused_text_buffer();
            clear_byte_and_advance(expand_text_control_codes(status_end_action_7_text, append_entity_display_text(ent, message_ctx)));
            display_text_with_fullwidth_adjustment(message_ctx);
        }
        break;
    case STATUS_CURSE - 1:
        ent->x1C &= ~ACTOR_CURSED;
        break;
    case STATUS_ANGER - 1:
        ent->x1C &= ~ACTOR_ANGRY;
        if (ent->x14 & ACTOR_PARTY_MEMBER) {
            message_ctx = get_unused_text_buffer();
            clear_byte_and_advance(expand_text_control_codes(status_end_action_9_text, append_entity_display_text(ent, message_ctx)));
            display_text_with_fullwidth_adjustment(message_ctx);
        }
        break;
    case STATUS_FROG - 1:
    {
        s32 spawn_mode;
        int is_registered;
        int tile_mask;
        s16 has_owner;
        Ctor_80042BDC create_entity;
        u32 entity_flags;

        if (ent->x13 == MONSTER_FROG || ent->x13 == 0) {
            create_colored_effect_with_event((u8 *)ent - 0x20, 0x20A0A0, 0x613);
        }
        if (ent->x13 != 0) {
            spawn_mode = 1;
            if (ent->x13 == MONSTER_FROG) {
            child = *(S_80042BDC_child * *)&((ObjectNodeHeader *)((u8 *)ent - 0x20))->sprite;
            entity_flags = ent->x14;
            ent->x13 = ent->xA8;
            if (entity_flags & 0x4000) {
                spawn_mode = 3;
            }
            {
                S_80042BDC *resource = find_or_retain_sprite_resource_slot(ent->x13, spawn_mode);
                tile_mask = 0x3000;
                {
                    ent->x1C |= ((u32)(0x10000));
                }
                spawn_result = resource;
            }
            is_registered = (ent->x14 >> 14) & 1;
            {
                int tile_x = child->x24;
                int tile_y = child->x25;
                if (ent->x1C & ACTOR_PLAYER_SIDE) {
                    tile_mask = 0x300;
                }
                update_map_cell_flags_with_item_limit(tile_x, tile_y, tile_mask);
            }
            set_code_for_entity_mode(ent);

            create_entity = load_monster_resource_data(ent->x13, spawn_result, 1);
            drain_cd_command_queue();
            spawn_result_2 = create_entity(is_registered, child->x24, child->x25, ent->x88);

            spawn_result_2->x14 = 0;
            spawn_result_2->x1C = 0;
            has_owner = (ent->x1C >> 19) & 1;
            copy_entity_record(spawn_result_2, ent);
            update_owner_class_bits(spawn_result_2);

            if (g_dungeon_status.flags & 0x1000) {
                if (ent->x71 > (s16)ent->x8A) {
                    g_dungeon_status.activity_counts.parts.pending_movement_count -= (ent->x71 - ent->x8A);
                }
            }
            update_actor_status_and_mp(spawn_result_2);
            spawn_result_2->x1C &= ~0x10000;

            if (ent->x14 & ACTOR_PARTY_MEMBER) {
                u8 *slot_base;
                u8 *slot_data;
                int entity_index;
                spawn_mode = find_entity_slot_by_field_ac(ent);
                slot_base = (u8 *)((s16)spawn_mode * 4 + (unsigned long)((u8 *)dungeon_actor_ring_anchor));
                slot_data = *(u8 **)(slot_base + 0xD0);
                entity_index = *(u8 *)(slot_data + 3) & 0x1F;
                familiar_record_slots[entity_index] = spawn_result_2;
                *(S_80042BDC **)(slot_base + 0xAC) = spawn_result_2;
            }

            {
                int attach_owner = has_owner;
                if (attach_owner) {
                    S_80042BDC *owned_ent = spawn_result_2;
                    u8 *owner_data;
                    owner_data = ((u8 *)dungeon_actor_ring_anchor);
                    *(S_80042BDC **)(owner_data + 0x124) = spawn_result_2;
                    spawn_result_2->x60 = owner_data;
                    spawn_result_2->x1C |= ACTOR_LIFTED;
                    /*
                     * BUG: the lifted replacement shares Koh's tile. This lift setup clears that tile again
                     * after the constructor marked it occupied. Reattach without clearing Koh's occupancy.
                     * Found and documented by the Azure Dreams community
                     * (adrando.com/guide/bugs.html).
                     */
                    begin_actor_move_to_target_facing(owned_ent, ((ObjectNodeHeader *)((u8 *)spawn_result_2 - 0x20))->position,
                        ((ObjectNodeHeader *)((u8 *)spawn_result_2 - 0x20))->sprite, spawn_result_2);
                    update_actor_transform_from_parent(spawn_result_2, ((ObjectNodeHeader *)((u8 *)spawn_result_2 - 0x20))->position,
                        ((ObjectNodeHeader *)((u8 *)spawn_result_2 - 0x20))->sprite, spawn_result_2);
                } else {
                    if (spawn_result_2->x25 == 0) {
                        g_dungeon_status.activity_counts.parts.pending_action_count += 1;
                        spawn_result_2->x1C &= ~ACTOR_MP_EMPTY;
                    }
                }
            }
            ent->x14 |= 0x20000000;
            detach_record_and_update_slot_state(ent);
            unlink_entity_node(ent);
            ((ObjectNodeHeader *)((u8 *)ent - 0x20) )->flags|= NODE_REMOVE;
            D_800814A0 |= OBJECT_REMOVE_PENDING;
            ent = spawn_result_2;
        }
        }
L_print4B:
        if (ent->x14 & ACTOR_PARTY_MEMBER) {
            message_ctx = get_unused_text_buffer();
            clear_byte_and_advance(expand_text_control_codes(status_end_action_10_text, append_entity_display_text(ent, message_ctx)));
            display_text_with_fullwidth_adjustment(message_ctx);
        }
        break;
    }
    case STATUS_NO_TILE_OCCUPANCY - 1:
        child = *(S_80042BDC_child * *)&((ObjectNodeHeader *)((u8 *)ent - 0x20))->sprite;
        cycle_map_cell_flags(child->x24, child->x25, (ent->x1C & ACTOR_PLAYER_SIDE) ? 0x300 : 0x3000);
        try_move_actor_to_valid_position(ent, ((ObjectNodeHeader *)((u8 *)ent - 0x20))->position, child, ent);
        break;
    case STATUS_PLAYER_SIDE - 1:
        child = *(S_80042BDC_child * *)&((ObjectNodeHeader *)((u8 *)ent - 0x20))->sprite;
        update_map_cell_flags_with_item_limit(child->x24, child->x25, (ent->x1C & ACTOR_PLAYER_SIDE) ? 0x300 : 0x3000);
        ent->x1C &= ~ACTOR_PLAYER_SIDE;
        cycle_map_cell_flags(child->x24, child->x25, (ent->x1C & ACTOR_PLAYER_SIDE) ? 0x300 : 0x3000);
        break;
    case STATUS_BRAINWASH - 1:
        if (ent->x14 & ACTOR_PARTY_MEMBER) {
            message_ctx = get_unused_text_buffer();
            clear_byte_and_advance(expand_text_control_codes(status_end_action_12_text, append_entity_display_text(ent, message_ctx)));
            display_text_with_fullwidth_adjustment(message_ctx);
        }
        child = *(S_80042BDC_child * *)&((ObjectNodeHeader *)((u8 *)ent - 0x20))->sprite;
        update_map_cell_flags_with_item_limit(child->x24, child->x25, (ent->x1C & ACTOR_PLAYER_SIDE) ? 0x300 : 0x3000);
        ent->x1C |= ACTOR_PLAYER_SIDE;
        cycle_map_cell_flags(child->x24, child->x25, (ent->x1C & ACTOR_PLAYER_SIDE) ? 0x300 : 0x3000);
        break;
    case 25:
        child = *(S_80042BDC_child * *)&((ObjectNodeHeader *)((u8 *)ent - 0x20))->sprite;
        ent->x98 &= 0x7FFF;
        update_map_cell_flags_with_item_limit(child->x24, child->x25, (ent->x1C & ACTOR_PLAYER_SIDE) ? 0x300 : 0x3000);
        if (ent->x98 & 0x4000) {
            ent->x1C |= ACTOR_PLAYER_SIDE;
        }
        cycle_map_cell_flags(child->x24, child->x25, (ent->x1C & ACTOR_PLAYER_SIDE) ? 0x300 : 0x3000);
        child->x12 = ent->xA6;
        break;
    case STATUS_NO_MP_DRAIN - 1:
        if (ent->x14 & ACTOR_PARTY_MEMBER) {
            message_ctx = get_unused_text_buffer();
            clear_byte_and_advance(expand_text_control_codes(status_end_action_32_text, append_entity_display_text(ent, message_ctx)));
            display_text_with_fullwidth_adjustment(message_ctx);
        }
        break;
    case 20:
    case 21:
    case 22:
        if (ent->x14 & ACTOR_PARTY_MEMBER) {
            message_ctx = get_unused_text_buffer();
            clear_byte_and_advance(expand_text_control_codes(status_end_action_21_to_23_text, append_entity_display_text(ent, message_ctx)));
            display_text_with_fullwidth_adjustment(message_ctx);
        }
        break;
    case STATUS_FIRE_PROTECT - 1:
        if (ent->x14 & ACTOR_PARTY_MEMBER) {
            message_ctx = get_unused_text_buffer();
            clear_byte_and_advance(expand_text_control_codes(status_end_action_18_text, append_entity_display_text(ent, message_ctx)));
            display_text_with_fullwidth_adjustment(message_ctx);
        }
        break;
    case STATUS_WATER_PROTECT - 1:
        if (ent->x14 & ACTOR_PARTY_MEMBER) {
            message_ctx = get_unused_text_buffer();
            clear_byte_and_advance(expand_text_control_codes(status_end_action_19_text, append_entity_display_text(ent, message_ctx)));
            display_text_with_fullwidth_adjustment(message_ctx);
        }
        break;
    case STATUS_WIND_PROTECT - 1:
        if (ent->x14 & ACTOR_PARTY_MEMBER) {
            message_ctx = get_unused_text_buffer();
            clear_byte_and_advance(expand_text_control_codes(status_end_action_20_text, append_entity_display_text(ent, message_ctx)));
            display_text_with_fullwidth_adjustment(message_ctx);
        }

    }

    apply_entity_effects(ent);
}
