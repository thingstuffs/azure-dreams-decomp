#include "common.h"
#include "town/scene/script_hooks.h"
#include "m2c_compat.h"
#include "town/scene.h"

s32 store_record_value_and_table_lookup(); /* Slot contract: loading images do not establish one callee contract. */ /* extern */

/* func_koya_tamago_pal_ld: load the hut egg palette. */
s32 scr_func_koya_tamago_pal_ld(void) {
    return store_record_value_and_table_lookup(0, 0, 0, 0);
}
