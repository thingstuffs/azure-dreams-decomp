#include "common.h"

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

extern Runtime *D_80016000;
extern void func_80016120(void) __attribute__((noreturn));
extern void func_80016130(void);

void func_8047E0D8(void)
{
    Callback callback;

    callback = D_80016000->callbacks[D_80016000->callbackIndex].callback;
    if (callback == 0) {
        func_80016130();
        func_80016120();
    }
    callback();
}
