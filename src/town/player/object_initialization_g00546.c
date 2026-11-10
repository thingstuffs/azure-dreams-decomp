/* Initialize player object counters and fields. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:town/engine:800D01E0. */
#include "town/player/object_initialization_g00546.h"
#include "town/player.h"
#include "town/player/object.h"

/* Initialize the object and pass the setup value to the next initialization step. */
void initialize_object_with_count_four(TownObjectRecord *object, ObjectPosition *setupValue, void *ptr2) {
    call_the_handler_selects_nonzero_entry(D_800D01E0, object, ptr2);
    town_action_reset_byte = 0;
    object->unk_04 = &tick_countdown_and_initialize_target;
    object->unk_10 = 0;
    object->unk_0A = 4;
    clear_entity_record_fields((setupValue));
}

/* Initialize the object's state and run the follow-up setup. */
void initialize_object_with_value_800(TownObjectRecord *object, ObjectPosition *setupContext, void *ptr2) {
    call_the_handler_selects_nonzero_entry(D_800D01E0, object, ptr2);
    town_action_reset_byte = 0;
    object->unk_10 = 0x800;
    object->unk_04 = &target_action_update_address;
    object->unk_0A = 4;
    clear_entity_record_fields((setupContext));
}
