/* Actor data references (G00663). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:town/engine:800D58B8. */
#include "town/person/actor_data_references_g00663.h"

/* Set both linked pointers to D_800D58B8. */
void set_linked_data_pointers_variant_1(Rec_func_80094268_arg0 *record) {
    *record->unk_7C.as_ppm = &D_800D58B8;
    ((S_800C6440_2 *)(((Rec_func_80094268_arg0 *)record)->unk_80))->unk_04 = &D_800D58B8;
}

/* Set both object references to D_800D58F4. */
void set_linked_data_pointers_variant_2(S_800C645C_0 *object) {
    *object->unk_7C = &D_800D58F4;
    ((S_800C645C_2 *)(((S_800C645C_1 *)object)->unk_80))->unk_04 = &D_800D58F4;
}

/* Sets the object's linked data pointer to D_800D5930. */
void set_linked_data_pointer_variant_3(S_800C6478_0 *object) {
    ((S_800C6478_1 *)(object->unk_80))->unk_04 = &D_800D5930;
}

/* Check whether both actor data references match D_800D58B8. */
s32 check_actor_data_references_match(S_800C648C_0 *actor) {
    s32 data_addr;

    data_addr = *actor->unk_7C;
    if ((data_addr == (s32)&D_800D58B8) &&
        (((S_800C648C_1 *)(actor->unk_80))->unk_04 == data_addr)) {
        return 1;
    }
    return 0;
}
