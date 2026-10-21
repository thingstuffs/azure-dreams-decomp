#include "modules/main_title_callbacks.h"
#include "common.h"
#include "frontend/libcard.h"

s32 create_resource_transition_for_descriptor_check();                          /* extern */

typedef struct S_7FDD19D0_0 {
    u8 pad_00[0x10];
    void (*flag_handler)(void *entry);
} S_7FDD19D0_0;

/* Assigns the object descriptor when the object check succeeds. */
void assign_object_descriptor_on_check(s32 object_data_addr) {
    S_7FDD19D0_0 *object;

    object = object_data_addr - 0x20;
    if (create_resource_transition_for_descriptor_check(object) != 0) {
        object->flag_handler = run_flag_handler_and_set_2000_flags;
    }
}
