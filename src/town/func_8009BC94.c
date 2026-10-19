/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "shared/town_handler_entries.h"
#include "shared/object_index_slots.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/town_handler.h"

void clear_entity_record_fields();                     
extern s32 D_80098608;

void func_800993F4(Rec_func_80094268_arg0 *object, s32 context, void *ptr2) {
    call_the_handler_selects_nonzero_entry((s32 *) D_800D00A8, object, ptr2);
    D_80082660[object->unk_40].unk_00 = 0;
    object->unk_0A.as_s16 = 0xA;
    clear_entity_record_fields(context);
    object->unk_04.as_pm = &D_80098608;
}
