#include "common.h"
#include "m2c_compat.h"

void clear_referenced_object_active_flag();                            /* extern */
s32 get_script_flag_mask();                             /* extern */
extern s16 D_8001B8AA;

/* Call clear_referenced_object_active_flag when the current check returns zero, then return one. */
s32 call_handler_when_check_clear(void) {
    if (get_script_flag_mask(D_8001B8AA) == 0) {
        clear_referenced_object_active_flag();
    }
    return 1;
}
