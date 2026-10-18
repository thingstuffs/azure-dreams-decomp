#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/town_handler.h"

extern M2C_UNK D_80090C68;
extern M2C_UNK D_800D0078;


/* Initialize the record, set its first pointer to D_80090C68, and store code 0x54. */
void initialize_scene_action_record(Rec_func_80094268_arg0 *record, void *ptr, void *ptr2) {
    call_the_handler_selects_nonzero_entry((s32 *) &D_800D0078, record, ptr2);
    record->unk_00.as_pm = &D_80090C68;
    record->unk_0A.as_s16 = 0x54;
}
