#include "common.h"

typedef s32 (*Func8094D708Callback)(void *, s32);

typedef struct Func8094D708Object {
    u8 pad00[0x10];
    Func8094D708Callback *callbacks;
    s32 field14;
    u8 pad18[2];
    s16 field1A;
} Func8094D708Object;

extern void pass_2(s32, s16);
/* Notify the object, then run its callbacks in order until one returns zero; return that index. */
s32 run_callbacks_until_zero(Func8094D708Object *object) {
    s32 i;
    Func8094D708Callback *base;
    u8 *address;
    void *call_arg;
    Func8094D708Callback callback;

    pass_2(object->field14, object->field1A);
    for (i = 0;; i++) {
        call_arg = object;
        base = object->callbacks;
        address = (u8 *)(i << 4);
        callback = *(Func8094D708Callback *)((u8 *)((u8 *)((s32)address + (s32)base)));
        if (callback(call_arg, i) == 0) {
            return i;
        }
    }
}
