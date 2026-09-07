#include "common.h"

typedef void (*Callback_8001F2F4)();

typedef struct Object_8001F2F4 {
    u8 pad00[0x44];
    s32 callback_index;
} Object_8001F2F4;

extern Callback_8001F2F4 D_8040076C[4];

void func_8001F2F4(Object_8001F2F4 *object)
{
    register Callback_8001F2F4 *source ASM_REG("$6");   /* MATCH pin: retail register colouring depends on it */
    Callback_8001F2F4 callbacks[4];
    Callback_8001F2F4 callback0;
    Callback_8001F2F4 callback1;
    Callback_8001F2F4 callback2;
    Callback_8001F2F4 callback3;

    if (object->callback_index != 0) {
        source = D_8040076C;
    } else {
        source = D_8040076C;
    }
    callback0 = source[0];
    callback1 = source[1];
    callback2 = source[2];
    callbacks[0] = callback0;
    callbacks[1] = callback1;
    callbacks[2] = callback2;
    callback3 = source[3];
    callbacks[3] = callback3;
    callbacks[object->callback_index](object, callback2, source);
}
