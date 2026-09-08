#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8004B1A4();                         /* extern */
s32 func_8004B404();                         /* extern */
s32 func_800B0E18();                        /* extern */

/* Allocates and initializes an object, releasing it if initialization fails. */
s32 func_800B0F30(s32 initializationArg) {
    s32 allocatedObject;
    s32 resultObject;

    allocatedObject = func_8004B404(0x100);
    resultObject = allocatedObject;
    if (allocatedObject != 0) {
        resultObject = allocatedObject;
        if (func_800B0E18(allocatedObject, initializationArg) == 0) {
            func_8004B1A4(allocatedObject);
            resultObject = 0;
        }
    }
    return resultObject;
}
