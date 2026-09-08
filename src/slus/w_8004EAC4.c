#include "common.h"

extern s32 func_8004E9EC(u8 *arg0, s32 arg1);
extern char *strncpy(char *dest, const char *src, u32 n);

/* Writes a two-character code to a slot, terminates it if needed, and returns the slot. */
char *func_8004EAC4(u8 *buffer, char *code, s32 slot_index) {
    s32 needs_terminator;
    char *slot;

    needs_terminator = func_8004E9EC(buffer, slot_index);
    slot = (char *)(buffer + slot_index * 2);
    strncpy(slot, code, 2);
    if (needs_terminator != 0) {
        slot[2] = 0;
    }
    return slot;
}
