#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80400E34();                            /* extern */
M2C_UNK allocate_or_reuse_effect_and_install_callback();                /* extern */
extern s8 D_8008CA34;

/* Set the global flag, prepare state, and process the target in mode 1. */
void process_memory_target_mode_one(s32 target) {
    D_8008CA34 = 1;
    func_80400E34();
    allocate_or_reuse_effect_and_install_callback(target, 1);
}
