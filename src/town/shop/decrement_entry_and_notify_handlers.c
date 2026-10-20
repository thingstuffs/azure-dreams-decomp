/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800B1DCC_arg0.h"

s32 advance_index_with_directional_clamp(s32, s32, s32);
void dispatch_indexed_handler(void *, s32);
void dispatch_indexed_handler_alt(void *, s32);


typedef struct S_800B2068_1 {
    s32 unk_00;
    u8 pad_04[0x4];
    s32 unk_08;
    s32 unk_0C;
} S_800B2068_1;

/* Decrement the selected entry value, update its quotient, and invoke entry callbacks. */
void decrement_entry_and_notify_handlers(void *state) {
    s32 selected_index;
    s32 refresh_index;
    s32 related_index;
    s32 updated_value;
    S_800B2068_1 *entry;

    entry = state + ((((Rec_func_800B1DCC_arg0 *)state)->unk_0C * 0x10) + 0x1C);
    updated_value = advance_index_with_directional_clamp(entry->unk_08 - 1, 1, entry->unk_0C);
    entry->unk_08 = updated_value;
    entry->unk_00 = (s32) (updated_value / 10);
    selected_index = ((Rec_func_800B1DCC_arg0 *)state)->unk_0C;
    dispatch_indexed_handler_alt((void *)(*((s32 *)state + selected_index)), selected_index);
    refresh_index = ((Rec_func_800B1DCC_arg0 *)state)->unk_0C;
    dispatch_indexed_handler((void *)(*((s32 *)state + refresh_index)), refresh_index);
    related_index = ((Rec_func_800B1DCC_arg0 *)state)->unk_18;
    dispatch_indexed_handler((void *)(*((s32 *)state + related_index)), related_index);
}
