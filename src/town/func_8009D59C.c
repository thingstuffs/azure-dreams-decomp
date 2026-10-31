/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "shared/object_index_slots.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/town_handler.h"

#include "town/player/object/entity_record_fields.h"
#include "town/player/object.h"
extern s32 D_8009AD70;
extern s32 D_800D0198;

/*
 * Selects D_800D0198, clears the indexed object slot and entity motion fields, and installs
 * D_8009AD70 with count 0x14.
 */
void initialize_object_handler_and_countdown(Rec_func_80094268_arg0 *object, s32 context, void *ptr2) {
    call_the_handler_selects_nonzero_entry(&D_800D0198, object, ptr2);
    object_index_slots[object->unk_40].unk_00 = 0;
    object->unk_0A.as_s16 = 0x14;
    clear_entity_record_fields((struct EntityRec *)(context));
    object->unk_04.as_pm = &D_8009AD70;
}
