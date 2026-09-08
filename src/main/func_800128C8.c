#include "common.h"

typedef void (*Callback_800128C8)();

typedef struct Object_800128C8 {
    u8 pad00[0x44];
    s32 callback_index;
} Object_800128C8;

extern Callback_800128C8 D_800200A8[4];

// Copy the callback table locally and invoke the callback selected by the object.
void func_800258C8(Object_800128C8 *object)
{
    register u32 callback_table_base ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    Callback_800128C8 *callback_table;
    Callback_800128C8 callbacks[4];
    register Callback_800128C8 copied_callback ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    Callback_800128C8 second_callback;
    Callback_800128C8 third_callback;

    callback_table_base = 0x80020000;
    ASM_KEEP(callback_table_base);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    callback_table = (Callback_800128C8 *)(callback_table_base + 0xA8);
    ASM_KEEP(callback_table);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    copied_callback = callback_table[0];
    second_callback = callback_table[1];
    third_callback = callback_table[2];
    callbacks[0] = copied_callback;
    callbacks[1] = second_callback;
    callbacks[2] = third_callback;
    copied_callback = callback_table[3];
    callbacks[3] = copied_callback;
    callbacks[object->callback_index](object, second_callback, third_callback, callback_table);
}
