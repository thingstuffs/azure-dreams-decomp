#include "common.h"

typedef void (*Callback_8001F2F4)();

typedef struct Object_8001F2F4 {
    u8 pad00[0x44];
    s32 callback_index;
} Object_8001F2F4;

extern Callback_8001F2F4 D_8040076C[4];

/* Invoke the callback selected by the object's callback index. */
void func_8001F2F4(Object_8001F2F4 *object)
{
    register Callback_8001F2F4 *callback_table ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    Callback_8001F2F4 local_callbacks[4];
    Callback_8001F2F4 first_callback;
    Callback_8001F2F4 second_callback;
    Callback_8001F2F4 third_callback;
    Callback_8001F2F4 fourth_callback;

    if (object->callback_index != 0) {
        callback_table = D_8040076C;
    } else {
        callback_table = D_8040076C;
    }
    first_callback = callback_table[0];
    second_callback = callback_table[1];
    third_callback = callback_table[2];
    local_callbacks[0] = first_callback;
    local_callbacks[1] = second_callback;
    local_callbacks[2] = third_callback;
    fourth_callback = callback_table[3];
    local_callbacks[3] = fourth_callback;
    local_callbacks[object->callback_index](object, third_callback, callback_table);
}
