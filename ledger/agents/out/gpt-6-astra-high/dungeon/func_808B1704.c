#include "common.h"

typedef s32 (*Func8094D708Callback)(void *, s32);

typedef struct Func8094D708Object {
    u8 pad00[0x10];
    Func8094D708Callback *callbacks;
    s32 field14;
    u8 pad18[2];
    s16 field1A;
} Func8094D708Object;

extern void func_800166A0(s32, s16);

/* Invokes the object's callbacks in order and returns the index of the first to return zero. */
s32 func_808B1704(Func8094D708Object *object)
{
    s32 callbackIndex = 0;
    u8 *callbackAddress;
    Func8094D708Callback callback;

    func_800166A0(object->field14, object->field1A);

L_CALLBACK:
{
    register void *callbackObject ASM_REG("$4") = object;   /* MATCH pin: keeps a statement from moving across a call/branch */
    callbackAddress = (u8 *)(callbackIndex << 4);
    callbackAddress = (u8 *)((s32)callbackAddress + (s32)object->callbacks);
    callback = *(Func8094D708Callback *)callbackAddress;
    if (callback(callbackObject, callbackIndex) == 0)
        return callbackIndex;
    callbackIndex++;
    goto L_CALLBACK;
}
}
