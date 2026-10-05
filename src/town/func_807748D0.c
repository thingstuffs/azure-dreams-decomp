#include "common.h"
#include "shared/record_ptrs.h"

typedef void (*Callback)(void);

typedef struct CallbackEntry {
    Callback callback;
    void *data;
} CallbackEntry;

typedef struct Runtime {
    u8 pad0[8];
    s32 callbackIndex;
    u8 padC[0x34];
    CallbackEntry *callbacks;
} Runtime;

extern void func_80016128(s32 value0, s32 value1);

void func_800160D0(s32 value0, s32 value1)
{
    void *ptr;
    s32 callbackIndex;

    ptr = ((Runtime *)D_80016000);

    callbackIndex = ((Runtime *)ptr)->callbackIndex;
    ptr = ((Runtime *)ptr)->callbacks;
    ptr = (u8 *)ptr + callbackIndex * sizeof(CallbackEntry);
    ptr = *(void **)ptr;

    if (ptr == 0) {
        func_80016128(value0, value1);
        return;
    }
    ((Callback)ptr)();
}
