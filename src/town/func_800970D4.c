/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

#include "town/player/call_the_handler_selects_nonzero_entry_api.h"
#include "slus.h"
extern s32 D_80093524;
extern s32 D_800D0188;

/* Plays sound 0x500, selects D_800D0188, and installs D_80093524 with count 0x1E. */
void init_linked_position_action(Rec_func_80094268_arg0 *record, s32 unused, s32 setup_value) {
    SD_Call(0x500);
    call_the_handler_selects_nonzero_entry(&D_800D0188, record, (void *)(setup_value));
    record->unk_00.as_pm = &D_80093524;
    record->unk_0A.as_s16 = 0x1E;
}
