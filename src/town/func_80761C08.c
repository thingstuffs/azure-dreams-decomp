#include "common.h"

extern s32 apply_selected_entry_values(s32, s32);
/* Calls func_80016C6C with record, entry_index and returns its result. */
s32 invoke_system_callback_29(s32 record, s32 entry_index) { return apply_selected_entry_values(record, entry_index); }
