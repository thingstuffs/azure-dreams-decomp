#include "common.h"
#include "shared/town_handler_entries.h"
#include "shared/object_index_slots.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/town_handler.h"

#include "town/player/object/entity_record_fields.h"                     /* extern */
extern void D_8009AA2C();


/* Clears the object's indexed flag and updates its state and handler. */
void reset_indexed_object_and_set_handler(Rec_func_80094268_arg0 *object, s32 context, void *ptr2) {
    call_the_handler_selects_nonzero_entry((s32 *) D_800D00A8, object, ptr2);
    object_index_slots[object->unk_40].unk_00 = 0;
    object->unk_0A.as_s16 = 0xA;
    clear_entity_record_fields((struct EntityRec *)(context));
    object->unk_04.as_pm = &D_8009AA2C;
}
