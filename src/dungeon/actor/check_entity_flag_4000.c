#include "common.h"
#include "shared/record_ptrs.h"


typedef struct S_800C8078_0 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x3C];
    s32 unk_54;
} S_800C8078_0;   /* arg0 in check_entity_flag_4000 */

typedef struct S_800C8078_1 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_800C8078_1;

typedef struct S_800C8078_2 {
    u8 pad_00[0x54];
    s32 unk_54;
} S_800C8078_2;

/* Checks flag 0x4000 on the entity or its two global linked entities. */
s32 check_entity_flag_4000(S_800C8078_0 *entity) {
    s32 slot_index;
    S_800C8078_2 *linked_entity;
    void *slot_cursor;

    if (entity->unk_14 & 0x4000) {
        slot_index = 1;
        slot_cursor = (void *)(((u8 *)dungeon_actor_ring_anchor) + 4);
        do {
            linked_entity = ((S_800C8078_1 *)slot_cursor)->unk_AC;
            if ((linked_entity != 0) && ((linked_entity->unk_54 & 0x4000) != 0)) {
                return 1;
            }
            slot_index -= 1;
            slot_cursor -= 4;
        } while (slot_index >= 0);
    } else {
        if ((entity->unk_54 & 0x4000) != 0) {
            return 1;
        }
    }
    return 0;
}
