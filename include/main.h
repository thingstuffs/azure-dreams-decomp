#ifndef MAIN_H
#define MAIN_H
/* Prototypes of the functions defined in src/main/ (one true prototype each; maintained by tools/headers). */

#include "common.h"

struct S_80025B38_0;

/* func_8000D924.c */
void card_boot_select_channel_mode(s32 mode_enabled, s32 *unused_repeat_counts);

/* func_8000D984.c */
void card_boot_recheck_selected_channel(void);

/* func_8000D9C4.c */
void card_boot_toggle_channel(void);

/* func_8000DA0C.c */
void card_boot_reset_operation_and_drain_events(void);

/* func_8000DA30.c */
s32 card_boot_latch_hardware_status_one(void);

/* func_8000DA44.c */
s32 card_boot_latch_hardware_status_two(void);

/* func_8000DA58.c */
s32 card_boot_latch_hardware_status_three(void);

/* func_8000DA6C.c */
s32 card_boot_latch_hardware_status_four(void);

/* func_8000DA80.c */
void card_boot_open_events(void);

/* func_8000DEA0.c */
void card_boot_init_server(void);

/* func_8000DF18.c */
void card_boot_close_events(void);

/* func_8000E0E0.c */
s32 card_boot_get_operation_state(void);

/* func_8000E0F0.c */
s32 card_advance_selected_operation(void);

/* func_8000E21C.c */
s32 card_boot_poll_state_two_transition(void);

/* func_8000E298.c */
s32 card_poll_selected_operation_state(void);

/* func_8000E37C.c */
s32 consume_pending_event_flag(void);
s32 func_8002137C(void);

/* func_8000E3A0.c */
s32 card_boot_reset_operation_return_five(void);

/* func_8000E3C4.c */
s32 card_boot_request_info(s32 card_channel);

/* func_8000E410.c */
s32 card_boot_poll_software_events(void);

/* func_8000E4A4.c */
void card_boot_drain_software_events(void);

/* func_8000E4FC.c */
s32 card_boot_take_hardware_status(void);

/* func_8000E538.c */
void card_boot_drain_hardware_events(void);

/* func_8000E594.c */
s32 card_boot_dispatch_event_callbacks(void);

/* func_8000E68C.c */
s32 card_boot_debounce_card_status_events(void);

/* func_8000E7D4.c */
s32 *card_boot_debounce_card_presence(void);

/* func_8000E904.c */
void func_80021904(void);
void no_op_card_stub(void);

/* func_8000E90C.c */
s32 card_boot_has_selected_channel(void);

/* func_8000EB98.c */
s32 card_boot_read_file_units_128(s32 path, s32 buffer, s32 read_size, s32 block_offset);

/* func_8000EC4C.c */
s32 card_boot_write_file_units_128(s32 path, s32 buffer, s32 unit_count, s32 unit_offset, s32 skip_create);

/* func_8000ED38.c */
s32 card_boot_get_slot_marker(s32 entry_index);

/* func_8000ED54.c */
s32 card_boot_load_slot_metadata(s32 slot);

/* func_8000EDF4.c */
void card_boot_cache_save_header(s32 entry_index, void *source);

/* func_8000EEB8.c */
void card_boot_store_save_xor_checksum(void *buffer);

/* func_8000F0DC.c */
void card_boot_refresh_directory_summary(void);

/* func_8000F138.c */
s32 card_boot_get_remaining_block_summary(void);

/* func_8000F160.c */
s32 card_boot_count_cached_slots(void);

/* func_8000F19C.c */
s32 card_boot_erase_slot_file(s32 file_index);

/* func_8000F23C.c */
void card_boot_erase_temporary_file(void);

/* func_80012B38.c */
void card_boot_set_slot_menu_request(struct S_80025B38_0 *object, s32 value);

#endif
