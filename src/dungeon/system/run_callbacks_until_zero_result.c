#include "common.h"
#include "dungeon/system.h"

typedef s32 (*Func8094D708Callback)(void *, s32);

typedef struct Func8094D708Object {
    u8 pad00[0x10];
    Func8094D708Callback *callbacks;
    s32 field14;
    u8 pad18[2];
    s16 field1A;
} Func8094D708Object;

/* Invokes the object's callbacks in order and returns the index of the first to return zero. */
s32 run_callbacks_until_zero_result(Func8094D708Object *object)
{
    s32 callbackIndex = 0;
    u8 *callbackAddress;
    Func8094D708Callback callback;

    dispatch_packed_value_pairs(object->field14, object->field1A);

    for (;;) {
        void *callbackObject = object;
        callbackAddress = (u8 *)((s32)(callbackIndex << 4) + (long)object->callbacks);
        callback = *(Func8094D708Callback *)callbackAddress;
        if (callback(callbackObject, callbackIndex) == 0)
            return callbackIndex;
        callbackIndex++;
    }
}
