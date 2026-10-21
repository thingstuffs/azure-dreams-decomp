#ifndef SLUS_COMMAND_SLOTS_81554_H
#define SLUS_COMMAND_SLOTS_81554_H

#include "common.h"

extern s32 script_message_command_words[32];
extern s32 message_command_write_index;
extern s32 message_command_start_index;

extern void runtime_register_object_or_fallback_slot(void *object);
extern void set_script_record_buffer(s32 script_addr);
extern void func_8003528C(s32 script_addr);

#endif
