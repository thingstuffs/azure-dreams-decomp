#include "modules/town_ovl_6f48d0.h"

void dispatch_town_callback_or_fallback(s32 value0, s32 value1)
{
    void *ptr;
    s32 callbackIndex;

    ptr = D_80016000;

    callbackIndex = ((Rec_D_80016000 *)ptr)->unk_08;
    ptr = ((Rec_D_80016000 *)ptr)->unk_40;
    ptr = (u8 *)ptr + callbackIndex * sizeof(CallbackEntry);
    ptr = *(void **)ptr;

    if (ptr == 0) {
        func_80016128(value0, value1);
        return;
    }
    ((Callback)ptr)();
}
