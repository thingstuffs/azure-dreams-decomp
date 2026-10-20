#include "common.h"

extern u32 service_script_controller(void);
extern void select_object_value_with_idle_fallback(void);

/* Set the object callback when service_script_controller returns nonzero. */
void set_object_callback_when_active(void *object, s32 value_1, s32 value_2, s32 value_3) {
    if (service_script_controller() != 0) {
        *(void **)((u8 *)object + 0x24) = select_object_value_with_idle_fallback;
    }
}
