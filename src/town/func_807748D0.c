#include "shared/town_root.h"
#include "common.h"
#include "shared/record_ptrs.h"

typedef void (*Callback)(void);

typedef struct CallbackEntry {
    Callback callback;
    void *data;
} CallbackEntry;

extern void func_80016128(s32 value0, s32 value1);

void func_800160D0(s32 value0, s32 value1)
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
