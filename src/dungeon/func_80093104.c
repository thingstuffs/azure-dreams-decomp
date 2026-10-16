#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
typedef struct Ent Ent;

typedef struct S_80098864_0 {
    s32 unk_00;
    u8 pad_04[0x3A];
    s16 unk_3E;
    u8 pad_40[0x34];
    void * unk_74;
} S_80098864_0;   /* arg1 in dungeonProcessRecordAndUpdateLinkedState; pointer addresses record offset 0x14 */

typedef struct S_80098864_1 {
    u8 pad_00[0x60];
    s32 unk_60;
} S_80098864_1;   /* temp_a0 in dungeonProcessRecordAndUpdateLinkedState */



#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

void dungeonClearSlotAndUpdateLinkedState();
void copyItemCategoryDamage();
s32 dungeonResolveAttackDamageAndEffects();
Ent *dungeonPrepareDirectionalAttack();

/* Processes a record and updates its linked state on success. */
s32 dungeonProcessRecordAndUpdateLinkedState(s32 request, void *record_data) {
    s32 record_id;
    S_80098864_1 *linked_record;

    dungeonStatus.unk_0A--;
    record_id = ((S_80098864_0 *)((u8 *)record_data - 0x14))->unk_00;
    copyItemCategoryDamage(record_data, request);
    dungeonPrepareDirectionalAttack(record_data, record_id, ((S_80098864_0 *)((u8 *)record_data - 0x14))->unk_3E, 0, 0);
    if (dungeonResolveAttackDamageAndEffects(record_data, record_id, ((S_80098864_0 *)((u8 *)record_data - 0x14))->unk_3E, 0) == 0) {
        return 0;
    }
    linked_record = ((S_80098864_0 *)((u8 *)record_data - 0x14))->unk_74;
    if (linked_record != 0) {
        linked_record->unk_60 = (s32) ((s32)D_800E3D7C);
    }
    dungeonClearSlotAndUpdateLinkedState(request);
    return 1;
}
