#include "common.h"
#include "m2c_compat.h"

s32 func_800352FC(s32, M2C_UNK, M2C_UNK, s32);                                /* extern */
M2C_UNK func_80093D48();       /* extern */

/* Run the fallback handler when the request check returns zero. */
void func_80093638(s32 request, M2C_UNK request_data, M2C_UNK request_param, s32 check_param) {
    if (func_800352FC(request, request_data, request_param, check_param) == 0) {
        func_80093D48(request, request_data, request_param);
    }
}
