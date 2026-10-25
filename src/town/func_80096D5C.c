/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "shared/town_handler_entries.h"
#include "records/Rec_func_80094268_arg0.h"

#include "town/player/call_the_handler_selects_nonzero_entry_api.h"
#include "slus.h"
extern s32 D_80092698;

/* Plays sound 0x511, selects counted_action_handler_table, and installs D_80092698 with count six. */
void initialize_action_object_with_counter(Rec_func_80094268_arg0 *record, s32 unused, s32 setup_value) {
    SD_Call(0x511);
    call_the_handler_selects_nonzero_entry(counted_action_handler_table, record, (void *)(setup_value));
    record->unk_00.as_pm = &D_80092698;
    record->unk_0A.as_s16 = 6;
}
