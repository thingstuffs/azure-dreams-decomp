#include "common.h"
#include "shared/town_handler_entries.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/town_handler.h"

#include "town/player/object/entity_record_fields.h"                     /* extern */
extern s8 D_80082668;
extern M2C_UNK D_80098078;


/* Initialize the object's state and run the follow-up setup. */
void initialize_object_with_value_800(Rec_func_80094268_arg0 *object, s32 setupContext, void *ptr2) {
    call_the_handler_selects_nonzero_entry((s32 *) D_800D01E0, object, ptr2);
    D_80082668 = 0;
    object->unk_10.as_s16 = 0x800;
    object->unk_04.as_pm = &D_80098078;
    object->unk_0A.as_s16 = 4;
    clear_entity_record_fields((struct EntityRec *)(setupContext));
}
