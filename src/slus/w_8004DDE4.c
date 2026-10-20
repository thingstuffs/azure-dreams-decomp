#include "slus/command_slots_81554.h"

/* Build and submit a command buffer using the supplied data. */
void build_object_registration_script(void *data)
{
    D_80081554 &= 0xF;
    D_80081558 = D_80081554;
    script_message_command_words[D_80081554++] = 0x15080707;
    runtime_register_object_or_fallback_slot(data);
    script_message_command_words[D_80081554++] = 0x20C11;
    script_message_command_words[D_80081554++] = 1;
    set_script_record_buffer((s32)&script_message_command_words[D_80081558]);
}
