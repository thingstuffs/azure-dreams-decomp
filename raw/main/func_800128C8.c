#include "common.h"

typedef void (*Callback_800128C8)();

typedef struct Object_800128C8 {
    u8 pad00[0x44];
    s32 callback_index;
} Object_800128C8;

extern Callback_800128C8 D_800200A8[4];

void func_800258C8(Object_800128C8 *object)
{
    register u32 high ASM_REG("$2");
    register Callback_800128C8 *source ASM_REG("$7");
    Callback_800128C8 callbacks[4];
    register Callback_800128C8 scratch ASM_REG("$3");
    Callback_800128C8 callback1;
    Callback_800128C8 callback2;

    high = 0x80020000;
    ASM_KEEP(high);
    source = (Callback_800128C8 *)(high + 0xA8);
    ASM_KEEP(source);
    scratch = source[0];
    callback1 = source[1];
    callback2 = source[2];
    callbacks[0] = scratch;
    callbacks[1] = callback1;
    callbacks[2] = callback2;
    scratch = source[3];
    callbacks[3] = scratch;
    callbacks[object->callback_index](object, callback1, callback2, source);
}
