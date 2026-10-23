#include "common.h"
#include "shared/object_index_slots.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

#include "town/player/call_the_handler_selects_nonzero_entry_api.h"  /* extern */
#include "town/player/object/entity_record_fields.h"                     /* extern */
extern void D_80097DE8();
extern s32 D_800D0178;


/* Initializes the object, assigns its handler table, and clears two global flags. */
void initialize_indexed_object_and_clear_flags(Rec_func_80094268_arg0 *object, s32 setupValue, s32 initializationValue) {
    clear_entity_record_fields((struct EntityRec *)(setupValue));
    call_the_handler_selects_nonzero_entry(&D_800D0178, object, (void *)(initializationValue));
    object->unk_04.as_pm = &D_80097DE8;
    object_index_slots[1].unk_00 = 0;
    object_index_slots[1].unk_01 = 0;
}
