#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80022D60();   /* extern */

/* Initializes a request with selector 0 and mode 1. */
void func_80022E74(M2C_UNK request_id, M2C_UNK request_value) {
    func_80022D60(request_id, 0, 1, request_value);
}
