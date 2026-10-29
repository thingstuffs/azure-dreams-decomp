#include "common.h"
#include "shared/dungeon_item_entries.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "dungeon/player/item.h"
#include "dungeon/player/state.h"
#include "dungeon/effect/screen.h"
typedef struct Ent Ent;

typedef struct S_80098864_0 {
    s32 unk_00;
    u8 pad_04[0x3A];
    s16 unk_3E;
    u8 pad_40[0x34];
    void * unk_74;
} S_80098864_0;   /* arg1 in process_record_and_update_linked_state; pointer addresses record offset 0x14 */

typedef struct S_80098864_1 {
    u8 pad_00[0x60];
    s32 unk_60;
} S_80098864_1;

Ent *prepare_directional_attack();

/* Processes a record and updates its linked state on success. */
s32 process_record_and_update_linked_state(DungeonItemEntry *request, void *record_data) {
    s32 record_id;
    S_80098864_1 *linked_record;

    g_dungeon_status.activity_counts.parts.pending_action_count--;
    record_id = ((S_80098864_0 *)((u8 *)record_data - 0x14))->unk_00;
    copy_item_category_damage(record_data, request);
    prepare_directional_attack(record_data, record_id, ((S_80098864_0 *)((u8 *)record_data - 0x14))->unk_3E, 0, 0);
    if (resolve_attack_damage_and_effects(record_data, record_id, ((S_80098864_0 *)((u8 *)record_data - 0x14))->unk_3E, 0) == 0) {
        return 0;
    }
    linked_record = ((S_80098864_0 *)((u8 *)record_data - 0x14))->unk_74;
    if (linked_record != 0) {
        linked_record->unk_60 = (s32) ((s32)dungeon_actor_ring_anchor);
    }
    clear_slot_and_update_linked_state(request);
    return 1;
}
