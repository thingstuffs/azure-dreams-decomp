#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_800160D0;
extern s32 *D_80016E40;

/* Point D_80016E40 at D_800160D0. */
void point_shared_buffer_at_data_e(void) {
    D_80016E40 = &D_800160D0;
}
