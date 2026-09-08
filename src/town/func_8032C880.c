#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8001ACE8();                     /* extern */
s32 func_8001ADE0();                         /* extern */

/* Process ID 0xD51 and return its preceding query result. */
s32 func_80017080(void) {
    s32 query_result;

    query_result = func_8001ADE0(0xD51);
    func_8001ACE8(0xD51);
    return query_result;
}
