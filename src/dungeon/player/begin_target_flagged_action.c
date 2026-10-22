
struct ObjectPosition;
#include "common.h"
#include "shared/record_ptrs.h"
#include "dungeon/player.h"

extern u8 D_80081471;
extern u8 held_item_kind_alias;
extern u8 D_800E04BA[];
extern u8 D_800E04E6[];

extern void display_formatted_context_message(void *data_ptr);
extern void adjust_source_value_and_finalize(s32 value, void *data_ptr);
extern void select_nearby_target_and_initialize_slot(s32 slot_id,struct ObjectPosition *target, s32 target_id, s16 slot_value);
extern s16 get_special_table_data_index(s32 actor_value);
extern void append_packed_action_record(void *object_ptr, s32 action_code, s32 payload, s8 extra_byte);

/* Start the actor action and apply its target effect unless a blocking flag is set. */
s32 begin_target_flagged_action(void *actor, s32 action_arg, s32 unused, void *target) {
    if ((held_item_kind_alias != 0) || (D_80081471 != 0)) {
        if (D_80081471 != 0) {
            display_formatted_context_message(D_800E04BA);
            return 0;
        }
        adjust_source_value_and_finalize(((s32)dungeon_actor_ring_anchor), D_800E04E6);
        return 0;
    }
    *(s32 *)((u8 *)target + 0x1C) |= 0x100000;
    *(s32 *)((u8 *)actor + 0x124) = 0;
    *(s8 *)((u8 *)actor + 0x9A) = 0x22;
    *(s8 *)((u8 *)actor + 0x9B) = 0;
    *(s32 *)((u8 *)actor + 0x8C) = 0;
    select_nearby_target_and_initialize_slot((u8 *)actor - 0x20, action_arg, 8, 0x300);
    append_packed_action_record(target, 0x48, get_special_table_data_index(*(s32 *)((u8 *)actor + 0xBC)), 0);
    return 1;
}
