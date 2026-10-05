#include "common.h"
#include "shared/object_index_slots.h"

typedef void (*Callback)(s32, void *, void *);

extern s32 func_800352FC(void);
extern s32 *D_800D0508[];
extern s32 *D_800FE5D8[3];

void func_80097DE8(s32 value, void *ptr, void *ptr2, void *unused) {
    u8 *state;
    Callback callback;
    s8 status;

    if (func_800352FC() == 0) {
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
