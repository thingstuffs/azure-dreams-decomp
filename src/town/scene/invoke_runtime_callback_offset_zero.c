#include "common.h"
#include "town/scene.h"
#include "town/data.h"

/* Link-at-0 devkit image copy of shop_invoke_runtime_callback (src/town/shop/shop_invoke_runtime_callback.c). */

/* Calls overlay_trace_methods - > invoke with 0. */
void invoke_runtime_callback_offset_zero(void) {
    overlay_trace_methods->invoke(0);
}
