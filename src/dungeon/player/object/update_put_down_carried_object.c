#include "engine/graphics.h"
#include "shared/dungeon_actor_callbacks.h"
#include "shared/entity.h"
#include "common.h"
#include "dungeon/player/object/data.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "dungeon/level.h"
#include "dungeon/player/object.h"
#include "dungeon/system.h"

extern s32 held_item_record;
extern s32 saved_held_item_word;


typedef struct S_8008F878_1 {
    u8 pad_00[0x8];
    SpriteAttachment *unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_8008F878_1;   /* arg2 in update_put_down_carried_object */

typedef struct S_8008F878_2 {
    union { void * p; s32 i; } unk_00;   /* accessed as both */
} S_8008F878_2;   /* &D_800DD25C in update_put_down_carried_object */

typedef struct S_8008F878_3 {
    u8 pad_00[0x13];
    s8 unk_13;
} S_8008F878_3;


   /* ((S_8008F878_2 *)(&D_800DD25C))->unk_00.p in update_put_down_carried_object */

/* Initializes an actor action and completes it when the action flags are set. */
void update_put_down_carried_object(PlayerRecord *action, void *unused, S_8008F878_1 *action_data, ActorRecord *actor) {
    u16 query_flags;
    s32 event_id;
    s32 state;
    s32 saved_value;
    S_8008F878_3 *target;
    ActorRecord *target_flags;

    state = action->actor.action_phase;
    if (state != 1) {
        if (state >= 2) {
            return;
        }
        if (state == 0) {
            if (find_flagged_record_by_id(action_data->unk_08, 0) == 0) {
                target = action->unk_124;
                ((S_8008F878_2 *)(&player_put_down_target))->unk_00.p = target;
                if (target->unk_13 <= 0) {
                    ((S_8008F878_2 *)(&player_put_down_target))->unk_00.i = 0;
                }
                target_flags = action->unk_124;
                target_flags->flags1C = (s32) (target_flags->flags1C & 0xFFF7FFFF);
                actor->flags1C = (s32) (actor->flags1C & 0xFFEFFFFF);
                get_offset_map_cell_value_and_flags(action_data->unk_24, action_data->unk_25, (actor->facing >> 9) & 7, &query_flags);
                event_id = 0x50C;
                if (query_flags & 0x400) {
                    event_id = 0x517;
                }
                play_sound_if_enabled(event_id);
                saved_value = (*&held_item_record);
                (*&held_item_record) = 0;
                saved_held_item_word = saved_value;
                action->actor.action_phase++;
            }
        }
    } else {
        if (action_data->unk_14 & 0x6000) {
            action->actor.action_phase = 2U;
            g_dungeon_status.flags = (u16) (g_dungeon_status.flags | 0x412);
            process_unflagged_linked_entries_alt(actor->next_actor_header);
            process_unflagged_linked_entries(actor->next_actor_header);
            if (((S_8008F878_2 *)(&player_put_down_target))->unk_00.p != NULL) {
                ((ActorRecord *)(((S_8008F878_2 *)(&player_put_down_target))->unk_00.p))->pending_turn_updates = 0;
            }
            action->actor.unk_8C.run = handle_player_input;
            g_dungeon_status.activity_counts.parts.pending_action_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1);
        }
    }
}
