#include "slus/command_slots_81554.h"

extern void flag_script_list_nonempty(void);

/* Marks the current registration slot, advances the slot counter, and calls two helpers. */
void func_8004E130(void)
{
    s32 slot_index;
    s32 *slot;

    slot_index = message_command_write_index & 0xF;
    slot = &script_message_command_words[slot_index];
    message_command_write_index = slot_index;
    message_command_start_index = slot_index;
    *slot = 1;
    message_command_write_index = slot_index + 1;
    set_script_record_buffer((s32)slot);
    flag_script_list_nonempty();
}
