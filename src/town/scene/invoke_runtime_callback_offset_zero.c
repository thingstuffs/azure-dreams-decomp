#include "common.h"

/* Link-at-0 devkit image copy of shop_invoke_runtime_callback (src/town/func_80878640.c). */

typedef struct RuntimeCallbacks {
    u8 pad_00[0x60];
    void (*invoke)(s32 code);
} RuntimeCallbacks;

extern RuntimeCallbacks *overlay_trace_methods;

/* Invoke the runtime callback at offset 0x60 with zero. */
void invoke_runtime_callback_offset_zero(void) {
    overlay_trace_methods->invoke(0);
}
