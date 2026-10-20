#include "common.h"

typedef void (*S_80083C68)(void);

extern S_80083C68 runtime_callback_entries[];

/* Calls each callback in D_80083C68 until the null terminator. */
void run_runtime_callbacks(void) {
    S_80083C68 *callback_entry = runtime_callback_entries;

    if (*callback_entry != 0) {
        do {
            (*callback_entry)();
            callback_entry++;
        } while (*callback_entry != 0);
    }
}
