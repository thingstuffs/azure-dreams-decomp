#include "modules/main_title_callbacks.h"
#include "common.h"

s32 func_8004EE30();                          /* extern */

typedef struct S_7FDD19D0_0 {
    u8 pad_00[0x10];
    void (*flag_handler)(void *entry);
} S_7FDD19D0_0;   /* temp_s0 in mainAssignObjectDescriptorOnCheck */

/* Assigns the object descriptor when the object check succeeds. */
void mainAssignObjectDescriptorOnCheck(s32 object_data_addr) {
    S_7FDD19D0_0 *object;

    object = object_data_addr - 0x20;
    if (func_8004EE30(object) != 0) {
        object->flag_handler = mainRunFlagHandlerAndSet2000Flags;
    }
}
