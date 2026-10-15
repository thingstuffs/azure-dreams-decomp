#include "modules/trap_effects_candidate.h"
#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800C8900();            /* extern */


/* Apply the global-mode mask to the target with a fixed value of 0x10. */
void func_800CD6AC(target)
M2C_UNK target;
{
    M2C_UNK mode_mask;

    mode_mask = 0x40;
    if (D_800E3D40 != 0) {
        mode_mask = 0x400;
    }
    func_800C8900(target, mode_mask, 0x10);
}
