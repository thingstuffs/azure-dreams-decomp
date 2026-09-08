#include "common.h"

typedef void (*S_80083C68)(void);

extern S_80083C68 D_80083C68[];

/* Calls each callback in D_80083C68 until the null terminator. */
void func_800411AC(void) {
    S_80083C68 *callback_entry = D_80083C68;

    if (*callback_entry != 0) {
        do {
            (*callback_entry)();
            callback_entry++;
        } while (*callback_entry != 0);
    }
}
