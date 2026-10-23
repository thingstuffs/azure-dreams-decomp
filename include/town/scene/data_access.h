#ifndef INCLUDE_TOWN_SCENE_DATA_ACCESS_H
#define INCLUDE_TOWN_SCENE_DATA_ACCESS_H

#include "common.h"

s32 *get_scene_entry_data_a(void);
s32 *get_scene_entry_data_b(void);
s32 *get_scene_entry_data_c(void);
s32 *get_scene_entry_data_d(void);
s32 *get_scene_entry_data_e(void);
s32 get_null_scene_entry_data(void);
u8 *get_scene_entry_bytes(void);
void initialize_scene_entry_data_a(void);
void initialize_scene_entry_data_b(void);
void initialize_scene_entry_data_c(void);
void request_scene_rescan_a(void);
void request_scene_rescan_b(void);
void request_scene_rescan_c(void);
void request_scene_rescan_d(void);
void request_scene_rescan_e(void);
void set_scene_handler_value_a(s32 handler_value);
void set_scene_handler_value_b(s32 handler_value);
void set_scene_handler_value_c(s32 handler_value);
void set_scene_handler_value_d(s32 handler_value);
void set_scene_handler_value_e(s32 handler_value);
void set_scene_handler_value_f(s32 handler_value);

#endif
