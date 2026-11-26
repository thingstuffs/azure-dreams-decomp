#include "common.h"
#include "engine/resource.h"

typedef void (*S_80083C68)(void);

extern void (*runtime_callback_entries[16])(void);

/* Invokes runtime_callback_entries in order until the null terminator. */
void run_frame_callbacks(void) {
    S_80083C68 *callback_entry = runtime_callback_entries;

    if (*callback_entry != 0) {
        do {
            (*callback_entry)();
            callback_entry++;
        } while (*callback_entry != 0);
    }
}
