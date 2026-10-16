#include "common.h"

/* Copy of townShopInvokeRuntimeCallback (src/town/func_80878640.c) in the devkit image at file 0x800800. */

typedef struct RuntimeCallbacks {
    u8 pad_00[0x60];
    void (*invoke)(s32 code);
} RuntimeCallbacks;

extern RuntimeCallbacks *D_8070100C;

/* Invoke the runtime callback at offset 0x60 with zero. */
void func_80700FC4(void) {
    D_8070100C->invoke(0);
}
