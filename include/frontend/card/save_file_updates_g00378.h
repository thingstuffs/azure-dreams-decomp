#ifndef FRONTEND_CARD_SAVE_FILE_UPDATES_G00378_H
#define FRONTEND_CARD_SAVE_FILE_UPDATES_G00378_H
/* Save file updates; G00378; inferred-strong; CL/PD joins as listed below, no proven or weak cut crossed */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:main/func_8000EB98, CL:main/func_8000EC4C, CL:main/func_8000EDF4, CL:main/func_8000EEB8, CL:main/func_8000EEE0. */

#include "common.h"
#include "modules/main_server_ship.h"

extern void rename(void *old_name, void *new_name);

/* Functions defined in this translation unit. */
s32 card_boot_verify_save_xor_checksum(void *save_data);
s32 card_boot_write_save_via_temporary_path(s32 slot, void *data);
s32 card_boot_load_save_and_clear_marker(s32 entry_index, void *data, s32 update_entry);

#endif
