#include "common.h"

typedef void (*Callback_8001F2F4)();

typedef struct Object_8001F2F4 {
    u8 pad00[0x44];
    s32 callback_index;
} Object_8001F2F4;

typedef struct CallbackTable_8001F2F4 {
    Callback_8001F2F4 entries[4];
} CallbackTable_8001F2F4;

extern CallbackTable_8001F2F4 D_8040076C;

/* Invoke the callback selected by the object's callback index. */
void func_8001F2F4(Object_8001F2F4 *object)
{
    CallbackTable_8001F2F4 callbacks;

    callbacks = D_8040076C;
    callbacks.entries[object->callback_index](object);
}
