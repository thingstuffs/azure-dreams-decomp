#include "common.h"

void func_8004B1A4(unsigned short *object);
s32 func_8004B404();                         /* extern */
s32 format_item_value_and_flag_marker();                        /* extern */

/* Allocates and initializes an object, releasing it if initialization fails. */
s32 allocate_and_initialize_shop_object(s32 initializationArg) {
    s32 allocatedObject;
    s32 resultObject;

    allocatedObject = func_8004B404(0x100);
    resultObject = allocatedObject;
    if (allocatedObject != 0) {
        resultObject = allocatedObject;
        if (format_item_value_and_flag_marker(allocatedObject, initializationArg) == 0) {
            func_8004B1A4(allocatedObject);
            resultObject = 0;
        }
    }
    return resultObject;
}
