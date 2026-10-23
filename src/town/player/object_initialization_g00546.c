/* Initialize player object counters and fields (G00546). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:town/engine:800D01E0. */
#include "town/player/object_initialization_g00546.h"

/* Initialize the object and pass the setup value to the next initialization step. */
void initialize_object_with_count_four(Rec_func_80094268_arg0 *object, s32 setupValue, void *ptr2) {
    call_the_handler_selects_nonzero_entry((s32 *) D_800D01E0, object, ptr2);
    town_action_reset_byte = 0;
    object->unk_04.as_pm = &tick_countdown_and_initialize_target;
    object->unk_10.as_s16 = 0;
    object->unk_0A.as_s16 = 4;
    clear_entity_record_fields((struct EntityRec *)(setupValue));
}

/* Initialize the object's state and run the follow-up setup. */
void initialize_object_with_value_800(Rec_func_80094268_arg0 *object, s32 setupContext, void *ptr2) {
    call_the_handler_selects_nonzero_entry((s32 *) D_800D01E0, object, ptr2);
    town_action_reset_byte = 0;
    object->unk_10.as_s16 = 0x800;
    object->unk_04.as_pm = &target_action_update_address;
    object->unk_0A.as_s16 = 4;
    clear_entity_record_fields((struct EntityRec *)(setupContext));
}
