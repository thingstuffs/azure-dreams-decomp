#include "shared/dungeon_actor_callbacks.h"
#include "shared/entity.h"
#include "common.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"

s32 find_flagged_record_by_id();                    /* extern */
void process_unflagged_linked_entries();                         /* extern */
void process_unflagged_linked_entries_alt(s32);                         /* extern */
s16 get_offset_map_cell_value_and_flags(s16, s16, s16, u16 *);          /* extern */
s32 play_sound_if_enabled(s32);                     /* extern */
extern s32 held_item_record;
extern void *player_put_down_target;
extern s32 saved_held_item_word;

typedef struct S_8008F878_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
    u8 pad_9C[0x88];
    void * unk_124;
} S_8008F878_0;   /* arg0 in update_put_down_carried_object */

typedef struct S_8008F878_1 {
    u8 pad_00[0x8];
    s32 unk_08;
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

typedef struct S_8008F878_5 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    u16 unk_2A;
    u8 pad_2C[0x30];
    s32 unk_5C;
} S_8008F878_5;   /* arg3 in update_put_down_carried_object */

   /* ((S_8008F878_2 *)(&D_800DD25C))->unk_00.p in update_put_down_carried_object */

/* Initializes an actor action and completes it when the action flags are set. */
void update_put_down_carried_object(S_8008F878_0 *action, void *unused, S_8008F878_1 *action_data, S_8008F878_5 *actor) {
    u16 query_flags;
    s32 event_id;
    s32 state;
    s32 saved_value;
    S_8008F878_3 *target;
    ActorRecord *target_flags;

    state = action->unk_9B;
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
                actor->unk_1C = (s32) (actor->unk_1C & 0xFFEFFFFF);
                get_offset_map_cell_value_and_flags(action_data->unk_24, action_data->unk_25, ((u16) actor->unk_2A >> 9) & 7, &query_flags);
                event_id = 0x50C;
                if (query_flags & 0x400) {
                    event_id = 0x517;
                }
                play_sound_if_enabled(event_id);
                saved_value = (*(s32 *)&held_item_record);
                (*(s32 *)&held_item_record) = 0;
                saved_held_item_word = saved_value;
                action->unk_9B++;
            }
        }
    } else {
        if (action_data->unk_14 & 0x6000) {
            action->unk_9B = 2U;
            g_dungeon_status.flags = (u16) (g_dungeon_status.flags | 0x412);
            process_unflagged_linked_entries_alt(actor->unk_5C);
            process_unflagged_linked_entries(actor->unk_5C);
            if (((S_8008F878_2 *)(&player_put_down_target))->unk_00.p != NULL) {
                ((ActorRecord *)(((S_8008F878_2 *)(&player_put_down_target))->unk_00.p))->pending_turn_updates = 0;
            }
            action->unk_8C = handle_player_input;
            g_dungeon_status.activity_counts.parts.pending_action_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1);
        }
    }
}
