#include "common.h"

/* Copy of shop_invoke_runtime_callback (src/town/func_80878640.c) in the devkit image at file 0x800800. */

typedef struct RuntimeCallbacks {
    u8 pad_00[0x60];
    void (*invoke)(s32 code);
} RuntimeCallbacks;

extern RuntimeCallbacks *D_8070100C;

/* Invoke the runtime callback at offset 0x60 with zero. */
void copy_shop_runtime_callback_devkit(void) {
    D_8070100C->invoke(0);
}
