#include "common.h"

extern void func_8004D7E8(void *a0);

/* Wait for a callback while polling is enabled, then invoke it with the data following its slot. */
void func_8004D690(void (**callback_slot)(void *), s32 *poll_enabled, void *poll_context)
{
    void (*callback)(void *);

    while (1) {
        callback = *callback_slot;
        if (callback != (void *)0) {
            callback((void *) (callback_slot + 1));
            return;
        }
        if (*poll_enabled == 0) {
            break;
        }
        func_8004D7E8(poll_context);
    }
}
