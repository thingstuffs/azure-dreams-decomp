#include "common.h"

void flag_object_for_removal(unsigned short *object);
s32 create_callback_pair_default();                         /* extern */
s32 format_item_value_and_flag_marker();                        /* extern */

/* Allocates and initializes an object, releasing it if initialization fails. */
s32 allocate_and_initialize_shop_object(s32 initializationArg) {
    s32 allocatedObject;
    s32 resultObject;

    allocatedObject = create_callback_pair_default(0x100);
    resultObject = allocatedObject;
    if (allocatedObject != 0) {
        resultObject = allocatedObject;
        if (format_item_value_and_flag_marker(allocatedObject, initializationArg) == 0) {
            flag_object_for_removal(allocatedObject);
            resultObject = 0;
        }
    }
    return resultObject;
}
