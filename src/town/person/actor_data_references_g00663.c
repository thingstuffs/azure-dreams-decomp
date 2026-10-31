/* Actor data references (G00663). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:town/engine:800D58B8. */
#include "town/person/actor_data_references_g00663.h"
#include "town/person.h"

/* Set both linked pointers to D_800D58B8. */
void set_linked_data_pointers_variant_1(Rec_func_80094268_arg0 *record, void *unused_context, struct SpriteFrameState *unused_sprite) {
    /* BYTES: retain the slot callback operands without a variadic prologue. */
    *record->unk_7C.as_ppm = &D_800D58B8;
    ((S_800C6440_2 *)(record->unk_80))->data = &D_800D58B8;
}

/* Set both object references to D_800D58F4. */
void set_linked_data_pointers_variant_2(S_800C645C_0 *object) {
    *object->data_slot = &D_800D58F4;
    ((S_800C645C_2 *)(((S_800C645C_1 *)object)->linked_data))->data = &D_800D58F4;
}

/* Sets the object's linked data pointer to D_800D5930. */
void set_linked_data_pointer_variant_3(S_800C6478_0 *object) {
    ((S_800C6478_1 *)(object->linked_data))->data = &D_800D5930;
}

/* Check whether both actor data references match D_800D58B8. */
s32 check_actor_data_references_match(S_800C648C_0 *actor) {
    s32 data_addr;

    data_addr = *actor->data_slot;
    if ((data_addr == (s32)&D_800D58B8) &&
        (((S_800C648C_1 *)(actor->linked_data))->data == data_addr)) {
        return 1;
    }
    return 0;
}
