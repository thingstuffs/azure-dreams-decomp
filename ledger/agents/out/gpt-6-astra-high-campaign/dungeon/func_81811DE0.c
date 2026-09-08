#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80025040();  /* extern */
s32 func_8004B404();                         /* extern */

/* Configure resource 0x91 with the supplied value and data if it is available. */
void func_80026DE0(s32 setup_value, M2C_UNK setup_data) {
    s32 resource;

    resource = func_8004B404(0x91);
    if (resource != 0) {
        func_80025040(resource, setup_value, setup_data, 0x48);
    }
}
