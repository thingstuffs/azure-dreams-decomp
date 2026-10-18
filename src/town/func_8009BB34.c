/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/town_handler.h"

void clear_entity_record_fields();                     
extern s8 D_80082668;
extern s32 D_80098078;
extern s32 D_800D0150;

void func_80099294(Rec_func_80094268_arg0 *object, s32 followUpArg, void *ptr2) {
    call_the_handler_selects_nonzero_entry((s32 *) &D_800D0150, object, ptr2);
    D_80082668 = 0;
    object->unk_04.as_pm = &D_80098078;
    object->unk_0A.as_s16 = 4;
    clear_entity_record_fields(followUpArg);
}
