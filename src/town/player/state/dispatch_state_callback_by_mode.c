#include "common.h"
#include "shared/object_index_slots.h"

typedef void (*Callback)(s32, void *, void *);

extern s32 service_script_controller(void);
extern s32 *D_800D0508[];
extern s32 *D_800FE5D8[3];

void dispatch_state_callback_by_mode(s32 value, void *ptr, void *ptr2, void *unused) {
    u8 *state;
    Callback callback;
    s8 status;

    if (service_script_controller() == 0) {
        ((Callback)D_800FE5D8[0])(value, ptr, ptr2);
        return;
    }
    state = D_80082660;
    status = *(s8 *)(state + 8);
    if (status >= 2) {
        ((Callback)D_800D0508[status])(value, ptr, ptr2);
        return;
    }
    if (status < 0) {
        callback = (Callback)D_800FE5D8[0];
        *(s8 *)(state + 8) = 0;
        callback(value, ptr, ptr2);
    }
}
