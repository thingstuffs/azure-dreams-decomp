#include "common.h"
#include "shared/town_handler_entries.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

#include "town/player/call_the_handler_selects_nonzero_entry_api.h"  /* extern */
void store_the_valid_shared_angle_in_offset_hex_10(Rec_func_80094268_arg0 *);                            /* extern */
extern M2C_UNK D_80092320;


/* Reset and initialize the record with its handler and a count of six. */
void func_800943B8(Rec_func_80094268_arg0 *record, s32 unused, s32 setup_value) {
    store_the_valid_shared_angle_in_offset_hex_10(record);
    call_the_handler_selects_nonzero_entry(D_800D0108, record, (void *)(setup_value));
    record->unk_00.as_pm = &D_80092320;
    record->unk_0A.as_s16 = 6;
}
