#include "common.h"

extern void restore_view_slot(void *a0);

/* Wait for a callback while polling is enabled, then invoke it with the data following its slot. */
void run_view_slot_callback(void (**callback_slot)(void *), s32 *poll_enabled, void *poll_context)
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
        restore_view_slot(poll_context);
    }
}
