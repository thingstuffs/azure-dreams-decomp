#include "common.h"
#include "town/player/object_initialization_g00546.h"
#include "shared/town_handler_entries.h"
#include "shared/object_index_slots.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/town_handler.h"
#include "town/player/object.h"

#include "town/player/object/entity_record_fields.h"                     /* extern */


/* Clears the object's indexed flag and resets its state before processing the context. */
void reset_indexed_object_and_process_context(Rec_func_80094268_arg0 *object, s32 context, void *ptr2) {
    call_the_handler_selects_nonzero_entry(counted_action_handler_table, object, ptr2);
    object_index_slots[object->unk_40].unk_00 = 0;
    object->unk_04.as_pm = &target_action_update_address;
    object->unk_0A.as_s16 = 6;
    clear_entity_record_fields((struct EntityRec *)(context));
}
