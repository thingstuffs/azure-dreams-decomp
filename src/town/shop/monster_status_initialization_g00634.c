/* Initialize monster status state and entry objects. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B9044, CL:town/func_800B90DC, CL:town/func_800B914C, CL:town/func_800B9168. */
#include "town/shop/monster_status_initialization_g00634.h"
#include "town/shop.h"
#include "town/shop/monster_status_opening_g00633.h"

/* Returns the indexed entry from D_800D17C8. */
SpritePartCommand *get_monster_status_type_data(s32 index) {
    return D_800D17C8[index];
}

/* Initializes the record, resolves its type data, and runs its setup routine. */
void initialize_monster_status_state(ShopFirstCallbackObject *record, struct ActorRecord *actor, s32 type_id) {
    record->slot_index = type_id;
    record->actor = actor;
    record->unk_0C = 0;
    record->opening_step = 0;
    record->first_callback = advance_monster_status_opening;
    record->texture = get_monster_status_type_data(record->slot_index);
    queue_monster_status_reload(record);
}

/* Initialize an object's position, internal links, and resource state. */
void initialize_monster_status_object(ShopFirstCallbackObject *object, struct ActorRecord *actor, s32 resourceIndex, s32 positionX, s32 positionY, s32 positionZ) {
    initialize_positioned_display_templates(&object->display, &object->display_template, &object->display_position, positionX, positionY, positionZ);
    reset_monster_status_links(object);
    initialize_monster_status_state(object, actor, resourceIndex);
}
