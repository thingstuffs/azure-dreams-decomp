#include "common.h"
extern u8 D_80082660[];

typedef void (*Callback)(s32, void *, void *);

extern s32 func_800352FC(s32, void *, void *, void *);
extern s32 *D_800D0508[];
extern s32 *D_800FE5D8[3];

void func_80097DE8(s32 arg0, void *arg1, void *arg2, void *arg3) {
    u8 *state;
    Callback callback;
    s8 status;

    if (func_800352FC(arg0, arg1, arg2, arg3) == 0) {
        ((Callback)D_800FE5D8[0])(arg0, arg1, arg2);
        return;
    }
    state = D_80082660;
    status = *(s8 *)(state + 8);
    if (status >= 2) {
        ((Callback)D_800D0508[status])(arg0, arg1, arg2);
        return;
    }
    if (status < 0) {
        callback = (Callback)D_800FE5D8[0];
        *(s8 *)(state + 8) = 0;
        callback(arg0, arg1, arg2);
    }
}
