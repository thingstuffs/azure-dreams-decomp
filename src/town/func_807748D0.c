#include "common.h"

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

extern Runtime *D_80016000;
extern void func_80016128(s32 arg0, s32 arg1);
extern void func_80016118(void) __attribute__((noreturn));

void func_807748D0(s32 arg0, s32 arg1)
{
    void *callback;
    s32 callbackIndex;

    callback = D_80016000;
    
    callbackIndex = ((Runtime *)callback)->callbackIndex;
    callback = ((Runtime *)callback)->callbacks;
    callback = (u8 *)callback + callbackIndex * sizeof(CallbackEntry);
    callback = *(void **)callback;
    
    if (callback == 0) {
        func_80016128(arg0, arg1);
        func_80016118();
    }
    ((Callback)callback)();
}
