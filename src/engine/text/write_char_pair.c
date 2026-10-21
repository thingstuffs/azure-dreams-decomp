#include "common.h"
#include "engine/text.h"
#include "sdk/libc.h"

/* Writes a two-character code to a slot, terminates it if needed, and returns the slot. */
char *write_char_pair(u8 *buffer, char *code, s32 slot_index) {
    s32 needs_terminator;
    char *slot;

    needs_terminator = fill_string_tail_and_detect_zero(buffer, slot_index);
    slot = (char *)(buffer + slot_index * 2);
    strncpy(slot, code, 2);
    if (needs_terminator != 0) {
        slot[2] = 0;
    }
    return slot;
}
