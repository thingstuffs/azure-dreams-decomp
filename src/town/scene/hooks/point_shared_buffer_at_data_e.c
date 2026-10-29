#include "common.h"
#include "town/scene/script_hooks.h"
#include "m2c_compat.h"
#include "town/scene/hooks.h"

extern M2C_UNK D_800160D0;
extern s32 *D_80016E40;

/* Stores the address of D_800160D0 in D_80016E40. */
void point_shared_buffer_at_data_e(void) {
    D_80016E40 = &D_800160D0;
}
