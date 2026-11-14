#include "common.h"
#include "town/scene/script_hooks.h"
#include "m2c_compat.h"
#include "town/scene.h"
#include "town/menu.h"

/* func_koya_tamago_pal_ld: load the hut egg palette. */
s32 scr_func_koya_tamago_pal_ld(void) {
    return store_target_record_value_and_kind(0, 0, 0, 0);
}
