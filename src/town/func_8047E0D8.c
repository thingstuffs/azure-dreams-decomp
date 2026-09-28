#include "common.h"
#include "shared/record_ptrs.h"

typedef void (*Callback)(void);

typedef struct {
    Callback callback;
    s32 unused;
} CallbackEntry;

typedef struct {
    u8 pad0[8];
    s32 callbackIndex;
    u8 padC[0x34];
    CallbackEntry *callbacks;
} Runtime;

extern void func_80016120(void) __attribute__((noreturn));
extern void func_80016130(s32 arg0, s32 arg1);

void func_8047E0D8(s32 arg0, s32 arg1)
{
    Callback callback;

    callback = ((Runtime *)D_80016000)->callbacks[((Runtime *)D_80016000)->callbackIndex].callback;
    if (callback == 0) {
        func_80016130(arg0, arg1);
        func_80016120();
    }
    callback();
}
