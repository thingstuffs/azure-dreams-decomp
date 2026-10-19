/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "shared/town_handler_entries.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/town_handler.h"

extern s8 D_80082668;
extern s32 D_8009803C;

void func_80098EC0(Rec_func_80094268_arg0 *record, void *ptr, void *ptr2) {
    call_the_handler_selects_nonzero_entry((s32 *) D_800D0180, record, ptr2);
    D_80082668 = 0;
    record->unk_04.as_pm = &D_8009803C;
    record->unk_0A.as_s16 = 0x15;
}
