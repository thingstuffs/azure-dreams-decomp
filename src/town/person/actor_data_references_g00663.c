/* Actor data references. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:town/engine:800D58B8. */
#include "town/person/actor_data_references_g00663.h"
#include "town/person.h"

/* Set both linked pointers to D_800D58B8. */
void set_linked_data_pointers_variant_1(TownObjectRecord *record, ObjectPosition *unused_context, struct SpriteFrameState *unused_sprite) {
    /* BYTES: retain the slot callback operands without a variadic prologue. */
    *record->animation_tables.as_pps32 = &D_800D58B8;
    record->descriptor->entries[1] = &D_800D58B8;
}

/* Set both object references to D_800D58F4. */
void set_linked_data_pointers_variant_2(TownObjectRecord *object) {
    *object->animation_tables.as_pps32 = &D_800D58F4;
    object->descriptor->entries[1] = &D_800D58F4;
}

/* Sets the object's linked data pointer to D_800D5930. */
void set_linked_data_field_pointer(TownObjectRecord *object) {
    object->descriptor->entries[1] = &D_800D5930;
}

/* Check whether both actor data references match D_800D58B8. */
s32 check_actor_data_references_match(TownObjectRecord *actor) {
    s32 *data_addr;

    data_addr = *actor->animation_tables.as_pps32;
    if ((data_addr == &D_800D58B8) &&
        (actor->descriptor->entries[1] == data_addr)) {
        return 1;
    }
    return 0;
}
