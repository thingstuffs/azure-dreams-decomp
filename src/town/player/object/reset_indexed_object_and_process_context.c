#include "common.h"
#include "shared/town_handler_entries.h"
#include "shared/object_index_slots.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/town_handler.h"

#include "town/player/object/entity_record_fields.h"                     /* extern */
extern M2C_UNK D_80098078;


/* Clears the object's indexed flag and resets its state before processing the context. */
void reset_indexed_object_and_process_context(Rec_func_80094268_arg0 *object, s32 context, void *ptr2) {
    call_the_handler_selects_nonzero_entry((s32 *) D_800D0120, object, ptr2);
    D_80082660[object->unk_40].unk_00 = 0;
    object->unk_04.as_pm = &D_80098078;
    object->unk_0A.as_s16 = 6;
    clear_entity_record_fields((struct EntityRec *)(context));
}
