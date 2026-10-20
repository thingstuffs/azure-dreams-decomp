#ifndef MODULES_MAIN_SERVER_SHIP_INTERFACES_H
#define MODULES_MAIN_SERVER_SHIP_INTERFACES_H

#include "common.h"

/* Shared MAIN card-server contracts used by the frontend. */
void card_boot_recheck_selected_channel(void);
void card_boot_toggle_channel(void);
void card_boot_init_server(void);
void card_boot_close_events(void);
s32 card_boot_get_operation_state(void);
s32 card_boot_debounce_card_status_events(void);
void no_op_card_stub(void);
s32 card_boot_has_selected_channel(void);
s32 card_boot_format_card_and_wait(s32 card_slot);
s32 card_boot_load_slot_metadata(s32 slot);
void card_boot_refresh_directory_summary(void);
s32 card_boot_get_remaining_block_summary(void);
s32 card_boot_count_cached_slots(void);
s32 card_boot_erase_slot_file(s32 file_index);
void card_boot_erase_temporary_file(void);

#endif
