#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"


extern void store_recalled_familiar(void *, void *, void *, void *);
extern void unlink_entity_node(void *);
extern void cycle_map_cell_flags(s16 x, s16 y, u16 flags);
extern void update_map_cell_flags_with_item_limit(u8, u8, s32);
extern void decrement_monster_entry_count(s16 requested_id, s16 requested_type);
extern u8 find_entity_slot_by_field_ac(void *);
extern void advance_status_timers(void *);
extern void play_sound_if_enabled(s32);
extern void spend_actor_mp(void *, s32);
extern void display_record_name_message(void *);

extern u8 D_80173B98;


typedef struct S_80176028_0 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
} S_80176028_0;   /* arg2 in advance_actor_transition_state */


typedef struct S_80176028_4 {
    u8 pad_00[0x1C];
    u32 unk_1C;
} S_80176028_4;   /* actor in advance_actor_transition_state */

typedef struct S_80176028_5 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0x26];
    u16 unk_46;
} S_80176028_5;   /* work in advance_actor_transition_state */

typedef struct S_80176028_6 {
    u8 pad_00[0x8C];
    void * unk_8C;
} S_80176028_6;   /* owner in advance_actor_transition_state */

/* Advances the actor transition state and updates shared actor data and tile flags. */
void advance_actor_transition_state(void *owner_data, s32 unused, void *entry_data, void *work_data)
{
    register u8 *owner = owner_data;
    u8 *work = work_data;
    register s32 state = owner[0x9B];
    register u8 *actor = *(u8 **)(work + 0x60);
    s16 type_check;

    switch (state) {
    case 0:
        {
            type_check = 3;
            if ((((S_80176028_0 *)entry_data)->unk_04 == type_check) &&
                (((S_80176028_0 *)entry_data)->unk_14 & 0x1000)) {
                play_sound_if_enabled(0x808);
            }
            if (((S_80176028_0 *)entry_data)->unk_14 & 0xE000) {
                ((u8 *)owner_data)[0x9B]++;
                return;
            }
            return;
        }

    case 1:
        {
            u8 *saved_actor;
            ActorRecord *actor_map;
            u16 saved_index;
            u8 actor_index;
            ObjectPosition *primary_table;
            TileObject *secondary_table;

            saved_index = ((u16)((ActorRecord *)((u8 *)D_800E3D7C))->unk_8A);
            saved_actor = ((ActorRecord *)((u8 *)D_800E3D7C))->target;
            actor_index = find_entity_slot_by_field_ac(actor);
            primary_table = &D_80083780;
            secondary_table = &D_80082E80;
            actor_map = D_800E3D7C;
            owner[0xA9] = actor_index;
            actor_map->unk_8A = actor_index;
            ((ActorRecord *)((u8 *)D_800E3D7C))->target = actor;
            store_recalled_familiar(((u8 *)D_800E3D7C), primary_table, secondary_table, ((u8 *)D_800E3D7C));
            (*(u8 * *)((u8 *)((u8 *)D_800E3D7C) + (0x60))) = saved_actor;
            ((ActorRecord *)((u8 *)D_800E3D7C))->unk_8A = saved_index;
            g_dungeon_status.activity_counts.parts.pending_action_count--;
        }

        ((u8 *)owner_data)[0x9B]++;
        return;

    case 2:
        {
            u8 *map;
            u8 *tile;
            u8 x;
            u8 y;
            s32 tile_mask;

            if (!(((S_80176028_4 *)actor)->unk_1C & 0x00800000)) {
                return;
            }

            map = ((u8 *)D_800E3D7C);
            *(u32 *)(map + 0xAC + owner[0xA9] * 4) = 0;
            *(u32 *)(map + 0xD0 + owner[0xA9] * 4) = 0;
            decrement_monster_entry_count(actor[0x13], 3);
            tile = *(u8 **)(actor - 0x14);
            x = tile[0x24];
            y = tile[0x25];
            tile_mask = (((S_80176028_4 *)actor)->unk_1C & 0x2000) ? 0x300 : 0x3000;
            update_map_cell_flags_with_item_limit(x, y, tile_mask);
            unlink_entity_node(actor);
            (*(u16 *)((u8 *)actor + (-2))) |= 0x8000;
            object_flag_block.flags |= 0x8000;
            {
                u8 *actor_slot;

                actor_slot = ((u8 *)D_800E3D7C) + 0xFA;
                actor_slot[owner[0xA9]] = state;
            }
            owner[0xA8] = owner[0xA9] + 1;
            owner[0x9B]++;
            return;
        }

    case 3:
        {
            register u8 *entry = entry_data;

            spend_actor_mp(work, 0x800);
            ((S_80176028_5 *)work)->unk_1C |= 0x2000;
            update_map_cell_flags_with_item_limit(entry[0x24], entry[0x25], 0x3000);
            cycle_map_cell_flags(entry[0x24], entry[0x25], 0x300);
            work[0x12] = state;
            display_record_name_message(*(void **)(work + 0x60));
            ((S_80176028_5 *)work)->unk_46 &= 0x7FFF;
            ((S_80176028_6 *)owner)->unk_8C = &D_80173B98;
            advance_status_timers(work);
            work[0x6D]--;
        }

        return;
    }
}
