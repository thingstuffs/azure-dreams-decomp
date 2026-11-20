#ifndef ENGINE_MESSAGE_DATA_H
#define ENGINE_MESSAGE_DATA_H

#include "common.h"

struct ScriptController;
extern struct ScriptController runtime_script_state;
extern u8 message_window_state_data[];
extern const char message_window_primary_sync_data[0x10];
extern const char message_window_tail_sync_data[0x10];
extern const char message_window_detail_sync_data[0x10];
struct MessageWindowImage;
extern struct MessageWindowImage message_window_object_template;
extern u8 message_window_audio_sync_data[];
extern u8 person_motion_tag[];
extern u8 *message_control_string_table[];

#endif
