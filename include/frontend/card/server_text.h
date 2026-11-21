#ifndef FRONTEND_CARD_SERVER_TEXT_H
#define FRONTEND_CARD_SERVER_TEXT_H
#include "common.h"

extern s32 card_first_flg;
extern const char card_server_assert_format[];
extern const char dev_server_filename[];
extern const char card_first_flg_label[];
extern const char card_counter_label[];

/* Each initializer uses its own assertion format and source filename. */
extern const char card_message_assert_format[];
extern const char card_message_assert_filename[];
extern const char card_options_assert_format[];
extern const char card_options_assert_filename[];
extern const char card_window_slot_assert_format[];
extern const char card_window_slot_assert_filename[];
extern const char card_background_assert_format[];
extern const char card_background_assert_filename[];
extern const char card_info_assert_format[];
extern const char card_info_assert_filename[];
extern const char card_sme_assert_format[];
extern const char card_sme_assert_filename[];

/* The two NUL-terminated memory-card device prefixes, ordered by channel. */
extern const char *dev_card_paths[2];
extern const char *dev_card_slot_names[];

/* Formats and string tables for the devkit card status diagnostics. */
extern const char dev_card_channel_format[];
extern const char dev_card_operation_state_format[];
extern const char dev_card_event_mode_format[];
extern const char dev_card_hardware_status_format[];
extern const char dev_card_channel_zero_status_format[];
extern const char dev_card_channel_one_status_format[];
extern const char dev_card_index_and_status_format[];
extern const char dev_card_first_status_format[];
extern const char dev_card_second_status_format[];
extern const char *dev_card_slot_status_names[];
extern const char *dev_card_channel_status_names[];

extern const char dev_card_invalid_data_message[];

extern const char dev_card_directory_wildcard[];

extern const char dev_card_save_file_prefix[];

#endif
