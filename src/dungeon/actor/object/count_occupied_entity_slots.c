#include "common.h"
#include "shared/record_ptrs.h"
#include "m2c_compat.h"
#include "dungeon/actor/object.h"


typedef struct S_800C82B8_0 {
    u8 pad_00[0xAC];
    s32 unk_AC;
} S_800C82B8_0;

typedef struct S_800C82B8_1 {
    u8 pad_00[0x54];
    s32 unk_54;
} S_800C82B8_1;   /* arg0 in count_occupied_entity_slots */

/* Counts the two occupied slots when the current entity has flag 8 set. */
s32 count_occupied_entity_slots(void *entity) {
    s32 slot_index;
    s32 active_count;
    void *slot_base;

    active_count = 0;
    if (entity == dungeon_actor_ring_anchor) {
        slot_index = 1;
        slot_base = entity + 4;
        do {
            /*
             * BUG: this counts familiar slots but tests Koh's talent flags. Test each familiar instead; their
             * Strength increased bonus is otherwise lost.
             * Found and documented by the Azure Dreams community
             * (adrando.com/guide/bugs.html).
             */
            if ((((S_800C82B8_0 *)slot_base)->unk_AC != 0) && (((S_800C82B8_1 *)entity)->unk_54 & 8)) {
                active_count += 1;
            }
            slot_index -= 1;
            slot_base -= 4;
        } while (slot_index >= 0);
    }
    return active_count;
}
