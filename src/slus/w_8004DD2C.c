#include "slus/command_slots_81554.h"

/* Build a command sequence with a header and terminator, then submit it. */
void submit_script_with_registered_context(void *context)
{
    s32 submit_index;
    s32 entry_value;
    s32 header_index;
    s32 buffer_value;
    s32 write_index;

    write_index = D_80081554 & 0xF;
    entry_value = write_index;
    buffer_value = 0x15080707;
    D_80081554 = write_index;
    D_80081558 = entry_value;
    header_index = write_index;
    entry_value = buffer_value;
    script_message_command_words[write_index] = entry_value;
    D_80081554 = header_index + 1;
    runtime_register_object_or_fallback_slot(context);

    buffer_value = D_80081554;
    write_index = buffer_value;
    entry_value = write_index;
    script_message_command_words[entry_value] = 0x23;
    buffer_value = write_index + 1;
    D_80081554 = buffer_value;
    submit_index = D_80081558;
    set_script_record_buffer((s32)&script_message_command_words[submit_index]);
}
