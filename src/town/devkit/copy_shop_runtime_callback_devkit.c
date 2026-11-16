#include "common.h"
#include "town/devkit.h"
#include "town/devkit/runtime_callback_owner_data.h"

/* Copy of shop_invoke_runtime_callback (src/town/func_80878640.c) in the devkit image at file 0x800800. */

/* Invoke the runtime callback at offset 0x60 with zero. */
void copy_shop_runtime_callback_devkit(void) {
    devkit_runtime_callback_owner[0]->invoke(0);
}
