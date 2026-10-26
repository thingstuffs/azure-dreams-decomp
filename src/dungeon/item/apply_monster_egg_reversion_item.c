#include "shared/actor_status_ids.h"
#include "shared/dungeon_item_entries.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dungeon_moving_views.h"
#include "dungeon/item/message.h"

typedef struct S_800BE6F0_0_pre {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0xE];
    u16 unk_16;
} S_800BE6F0_0_pre;   /* the 0x18 bytes before arg0 in apply_monster_egg_reversion_item, addressed as arg0[-1] */


typedef struct S_800BE6F0_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800BE6F0_1;   /* record1 in apply_monster_egg_reversion_item */

   /* record2 in apply_monster_egg_reversion_item */

typedef struct S_800BE6F0_5 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800BE6F0_5;   /* state_base2 in apply_monster_egg_reversion_item */


s32 get_entity_effect_value();
#include "dungeon/player/item.h"
struct EntityLinkNode;
s32 clear_slot_and_update_linked_state();
void * get_unused_text_buffer(); /* Unprototyped: zero, one or three arguments; retail replaces all incoming arguments. */
u8 * append_typed_formatted_value();
void unlink_entity_node(struct EntityLinkNode *node);
void update_map_cell_flags_with_item_limit(s32 x, s32 y, u16 flags);
void * detach_record_and_update_slot_state(void *record);
s32 display_text_with_fullwidth_adjustment();
s32 place_actor_item();
s32 display_item_status_message();
s32 release_entity_slot_and_update_flags();
s32 generate_random_value(void);
s32 clear_selected_item_flag_400();
void * create_effect_or_fallback(u32 x, u32 y, s32 z, void *effect_data);

extern u8 D_80089360[];
extern u8 D_800E1095[0x1E];
extern u8 D_800E10B3[];

/* Handles entity removal, displays its message, and updates dungeon state. */
s32 apply_monster_egg_reversion_item(void *entity, DungeonItemEntry *source, s16 reason)
{
    u8 spawn_data[4];
    void *text_buffer;
    void *text_end;
    s32 entity_index;
    void *linked_entity;
    s32 tile_mask;
    u8 entity_type;
    s32 spawn_type;
    u8 tile_x;
    u8 tile_y;
    S_800BE6F0_1 *position;
    MovingTile *map_position;
    s32 *entity_table;
    s32 cleared_selection;
    u8 *entity_base;

    if (entity == ((u8 *)dungeon_actor_ring_anchor)) {
        ((PlayerRecord *)entity)->pending_item_action = source;
        begin_deferred_item_action(entity, ((u8 *)(&view_reference_entity)), ((u8 *)(&reference_tile_object)), entity);
        return 0;
    }

    if ((u32)entity <= 0x9FFFFFFF) {
        display_item_status_message(entity, source, reason);
    }

    if (((ActorRecord *)entity)->flags14 & ACTOR_PARTY_MEMBER) {
        text_buffer = get_unused_text_buffer();
        if ((u32)(((ActorRecord *)entity)->species - 3) < 0x2B) {
            text_end = append_entity_display_text(entity, text_buffer);
            text_end = expand_text_control_codes(D_800E1095, text_end);
        } else {
            text_end = append_entity_display_text(entity, text_buffer);
            text_end = expand_text_control_codes(D_800E10B3, text_end);
            text_end = append_typed_formatted_value(source, text_end);
            text_end = expand_text_control_codes(D_80089360, text_end);
        }
        clear_byte_and_advance(text_end);
        display_text_with_fullwidth_adjustment(text_buffer);
    }

    entity_type = ((ActorRecord *)entity)->species;
    if ((u32)(entity_type - 3) < 0x2B) {
        spawn_data[0] = entity_type;
        spawn_type = ((ActorRecord *)entity)->species;
        if ((spawn_type == 3) || (spawn_type == 5) || (spawn_type == 7) ||
            (spawn_type == 9) || (spawn_type == 0xB) || (spawn_type == 0xD) ||
            (spawn_type == 0xF) || (spawn_type == 0x11) || (spawn_type == 0x13)) {
            spawn_data[0]++;
        }
        spawn_data[1] = 0x12;
        spawn_data[2] = (generate_random_value() & 0xF) + 0xA;
        spawn_data[3] = 0;
        clear_selected_item_flag_400(spawn_data);

        position = ((S_800BE6F0_0_pre *)entity)[-1].unk_00;
        create_effect_or_fallback(
            position->unk_02,
            position->unk_06,
            position->unk_0A,
            spawn_data);

        spawn_type = (s32)g_dungeon_status.pending_display_owner;
        if (spawn_type == (s32)((u8 *)entity - 0x20)) {
            cleared_selection = spawn_type & 0x7FFFFFFF;
            g_dungeon_status.pending_display_owner = (void *)cleared_selection;
        }

        linked_entity = detach_record_and_update_slot_state(entity);
        if (linked_entity != 0) {
            entity_index = release_entity_slot_and_update_flags(linked_entity, 0);
            if (entity_index < 0x40) {
                entity_table = (s32 *)0x80010980;
                entity_base = (u8 *)0x80010000;
                entity_base[entity_index * 0x54 + 0xA93] = 0;
                entity_table[entity_index] = 0;
            }
        }

        if ((get_entity_effect_value(entity, STATUS_NO_TILE_OCCUPANCY) << 16) == 0) {
            map_position = ((S_800BE6F0_0_pre *)entity)[-1].unk_04;
            tile_x = map_position->tile_x;
            tile_y = map_position->tile_y;
            tile_mask = 0x3000;
            if (((ActorRecord *)entity)->flags1C & ACTOR_PLAYER_SIDE) {
                tile_mask = 0x300;
            }
            /*
             * BUG: a lifted familiar shares Koh's tile. Roche removes the familiar but this clear also removes
             * Koh's occupancy; preserve the shared tile.
             * Found and documented by the Azure Dreams community
             * (adrando.com/guide/bugs.html).
             */
            update_map_cell_flags_with_item_limit(tile_x, tile_y, tile_mask);
        }

        unlink_entity_node(entity);
        ((S_800BE6F0_0_pre *)entity)[-1].unk_16 |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    } else {
        place_actor_item(entity, source);
        return 1;
    }
    clear_slot_and_update_linked_state(source);
    g_dungeon_status.activity_counts.parts.pending_action_count--;
    return 1;
}

/* 2.7.2-cdk-G0: symbols by name; the cdk cell splits each address itself. */
