#include "common.h"
#include "engine/camera.h"

/* Wait for a callback while polling is enabled, then invoke it with the data following its slot. */
void run_view_slot_callback(void (**callback_slot)(void *), s32 *poll_enabled, s32 slot_selector)
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
        restore_view_slot(slot_selector);
    }
}
