#include "common.h"

typedef void (*Callback_800128C8)(void *);

typedef struct Object_800128C8 {
    u8 pad00[0x44];
    s32 callback_index;
} Object_800128C8;

typedef struct CallbackTable {
    Callback_800128C8 cb[4];
} CallbackTable;

extern CallbackTable D_800200A8;

// Copy the callback table locally and invoke the callback selected by the object.
void func_800258C8(Object_800128C8 *object)
{
    CallbackTable callbacks;

    callbacks = D_800200A8;
    callbacks.cb[object->callback_index](object);
}
