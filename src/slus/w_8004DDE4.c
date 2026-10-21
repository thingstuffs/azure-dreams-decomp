#include "slus/command_slots_81554.h"

/* Build and submit a command buffer using the supplied data. */
void build_object_registration_script(void *data)
{
    message_command_write_index &= 0xF;
    message_command_start_index = message_command_write_index;
    script_message_command_words[message_command_write_index++] = 0x15080707;
    runtime_register_object_or_fallback_slot(data);
    script_message_command_words[message_command_write_index++] = 0x20C11;
    script_message_command_words[message_command_write_index++] = 1;
    set_script_record_buffer((s32)&script_message_command_words[message_command_start_index]);
}
