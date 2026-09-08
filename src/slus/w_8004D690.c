#include "common.h"

/* func_8004D7E8: matched callee (gcc 2.8.1), src/w_8004D7E8.c */
extern void func_8004D7E8(void *a0);

/* Wait for a callback while polling is enabled, then invoke it with the data following its slot. */
void func_8004D690(void (**callback_slot)(void *), s32 *poll_enabled, void *poll_context)
{
    void (*callback)(void *);

check_callback:
    callback = *callback_slot;
    if (callback != (void *)0) {
        callback((void *) (callback_slot + 1));
        return;
    }
    if (*poll_enabled != 0) {
        func_8004D7E8(poll_context);
        goto check_callback;
    }
}
