#include "slus/list_cursor_e0.h"

/* Removes the first matching value from the zero-terminated list and backs up its append cursor. */
void remove_runtime_callback(s32 value) {
    s32 *entry = runtime_callback_entries;
    if (*entry != 0) {
        do {
            if (*entry == value) {
                runtime_callback_write_cursor--;
                for (;;) {
                    *entry = entry[1];
                    entry++;
                    if (*entry == 0) {
                        return;
                    }
                }
            }
            entry++;
        } while (*entry != 0);
    }
}
