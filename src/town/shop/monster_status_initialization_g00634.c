/* Initialize monster status state and entry objects (G00634). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B9044, CL:town/func_800B90DC, CL:town/func_800B914C, CL:town/func_800B9168. */
#include "town/shop/monster_status_initialization_g00634.h"
#include "town/shop.h"

/* Returns the indexed entry from D_800D17C8. */
s32 get_monster_status_type_data(s32 index) {
    return *(s32 *)((u8 *)&D_800D17C8 + ((index) * 4));
}

/* Initializes the record, resolves its type data, and runs its setup routine. */
void initialize_monster_status_state(Rec_func_800B683C_arg0 *record, s32 context, s32 type_id) {
    record->unk_08 = type_id;
    record->unk_04 = context;
    record->unk_0C = 0;
    record->unk_0E = 0;
    record->unk_00 = &D_800B66E8;
    record->unk_14 = get_monster_status_type_data(record->unk_08);
    invalidate_cached_state_and_queue_read(record);
}

/* Initialize an object's position, internal links, and resource state. */
void initialize_entry_object(void *object, s32 entityId, s32 resourceIndex, s32 positionX, s32 positionY, s32 positionZ) {
    initialize_positioned_display_templates((u8 *)object + 0x88, (u8 *)object + 0x60, (u8 *)object + 0x70, positionX, positionY, positionZ);
    clear_linked_entry_state(object);
    initialize_monster_status_state((Rec_func_800B683C_arg0 *)object, entityId, resourceIndex);
}
