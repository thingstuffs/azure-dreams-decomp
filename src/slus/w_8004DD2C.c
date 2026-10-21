#include "slus/command_slots_81554.h"

/* Build a command sequence with a header and terminator, then submit it. */
void submit_script_with_registered_context(void *context)
{
    s32 submit_index;
    s32 entry_value;
    s32 header_index;
    s32 buffer_value;
    s32 write_index;

    write_index = message_command_write_index & 0xF;
    entry_value = write_index;
    buffer_value = 0x15080707;
    message_command_write_index = write_index;
    message_command_start_index = entry_value;
    header_index = write_index;
    entry_value = buffer_value;
    script_message_command_words[write_index] = entry_value;
    message_command_write_index = header_index + 1;
    runtime_register_object_or_fallback_slot(context);

    buffer_value = message_command_write_index;
    write_index = buffer_value;
    entry_value = write_index;
    script_message_command_words[entry_value] = 0x23;
    buffer_value = write_index + 1;
    message_command_write_index = buffer_value;
    submit_index = message_command_start_index;
    set_script_record_buffer((s32)&script_message_command_words[submit_index]);
}
