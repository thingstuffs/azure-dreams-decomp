#ifndef MAIN_SERVER_SHIP_H
#define MAIN_SERVER_SHIP_H
#include "common.h"

/* Runtime/storage views. This diagnostic header makes no allocation claim. */
typedef struct MainCardPair { s32 a; s32 b; } MainCardPair;
#include "modules/main_server_callbacks.h"
typedef struct CallbackSet { card_event_callback_fn value[5]; } CallbackSet;
typedef struct CallbackWork { CallbackSet first; s32 pad; CallbackSet second; } CallbackWork;
typedef struct MainCardDirectoryEntry { u8 name[0x18]; s32 size; u8 tail[0xC]; } MainCardDirectoryEntry;
#include "frontend/card.h"
extern u8 card_event_error_format[];
extern u8 card_server_filename[];
extern CallbackSet card_software_handlers;
extern CallbackSet D_80020048;
extern u8 D_80020084[];
extern s32 boot_card_paths[];
extern u8 D_80027F20[];
extern u8 boot_card_slot_names[];
extern s32 card_status_repeats[];
extern s32 card_last_status[];
extern s32 card_presence_repeats[];
extern s32 card_last_presence_event[];
extern s32 card_sw_done_event[];
extern s32 card_sw_error_event[];
extern s32 card_sw_timeout_event[];
extern s32 card_sw_new_event[];
extern s32 card_hw_done_event[];
extern s32 card_hw_error_event[];
extern s32 card_hw_timeout_event[];
extern s32 card_hw_new_event[];
extern MainCardDirectoryEntry boot_card_directory[15];
extern MainCardPair card_operation_state;
extern s32 card_selected_channel_alias[];
extern MainCardPair card_filtered_status;
extern MainCardPair card_presence_flags;
extern s32 card_event_backend_mode[];
extern s32 card_hardware_status[];
extern MainCardPair card_slot_completion_flags;
extern s32 card_remaining_block_counts[];
extern s32 card_directory_counts[];

extern void _card_wait(s32 channel);
extern s32 func_8006A024(s32 event);
extern s32 func_8006A084(void);
extern s32 func_8006A094(void);
extern void printf(void *format, ...);
extern void exit(s32 status) __attribute__((noreturn));
extern void strcpy(void *dest, s32 source);
extern void strcat(void *dest, void *source);
#include "sdk/libapi.h"

/* Complete member contracts, one prototype per line. */
void card_boot_select_channel_mode(s32 mode_enabled, s32 *unused_repeat_counts);
void card_boot_reset_operation_and_drain_events(void);
s32 card_boot_latch_hardware_status_one(void);
s32 card_boot_latch_hardware_status_two(void);
s32 card_boot_latch_hardware_status_three(void);
s32 card_boot_latch_hardware_status_four(void);
void card_boot_open_events(void);
s32 func_8002137C(void);
s32 card_boot_request_info(s32 card_channel);
s32 card_boot_poll_software_events(void);
void card_boot_drain_software_events(void);
s32 card_boot_take_hardware_status(void);
void card_boot_drain_hardware_events(void);
s32 card_boot_dispatch_event_callbacks(void);
s32 *card_boot_debounce_card_presence(void);
void func_80021904(void);
s32 count_entries_matching_search_path(void);
s32 card_boot_calc_remaining_8k_blocks(s32 entry_count);
s32 card_boot_has_directory_name_prefix(s32 count, u8 *text);
void card_boot_build_slot_path(s32 dest, s32 suffix_index);
s32 card_boot_read_file_units_128(void *path, void *buffer, s32 read_size, s32 block_offset);
s32 card_boot_write_file_units_128(void *path, void *buffer, s32 unit_count, s32 unit_offset, s32 skip_create);
s32 card_boot_get_slot_marker(s32 entry_index);
void card_boot_cache_save_header(s32 entry_index, void *source);
void card_boot_store_save_xor_checksum(void *buffer);
s32 card_boot_verify_save_xor_checksum(void *save_data);
s32 card_boot_write_save_via_temporary_path(s32 slot, void *data);
void card_boot_load_save_and_clear_marker(s32 entry_index, void *data, s32 update_entry);
#include "modules/main_server_ship_interfaces.h"
#endif
