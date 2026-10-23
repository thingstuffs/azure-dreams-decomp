#include "common.h"
#include "town/scene/entry_requests.h"
#include "m2c_compat.h"
void func_800179A0(void);                            /* extern */
extern M2C_UNK D_800190BC;

/* Calls func_800179A0 and returns the address of D_800190BC. */
s32 *run_scene_helper_and_get_result(void) {
    func_800179A0();
    return &D_800190BC;
}
