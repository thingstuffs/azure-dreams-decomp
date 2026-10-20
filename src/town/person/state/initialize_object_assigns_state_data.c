#include "common.h"
#include "records/Rec_func_80094268_arg0.h"

s32 scale_random_to_unsigned_halfword_limit();                         /* extern */
#include "town/person/object/initialize_object_entries_api.h"                /* extern */
void run_unhandled_update_and_choose_direction(Rec_func_80094268_arg0 *entity, s32 motion, s32 context, s32 update_arg);


/* Initializes the object, assigns its state data, and sets a value in multiples of 21. */
void initialize_object_assigns_state_data(Rec_func_80094268_arg0 *object, s32 unusedArg, s32 initializationArg) {
    initialize_object_entries((Struct800C5724 *)(object), (s8 *)(initializationArg), (s32 *)(*object->unk_7C.as_ps32));
    object->unk_50.as_pm = &run_unhandled_update_and_choose_direction;
    object->unk_6C.as_s16 = (s16) (((scale_random_to_unsigned_halfword_limit(4) & 0xFFFF) * 0x15) + 0x15);
}
