#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_8008AD1C(arg0, arg1, arg2);                                /* extern */
M2C_UNK func_8008AE4C();                         /* extern */
s32 func_8008AFB0();      /* extern */

/* Load a resource into the cache or move its existing entry to the front. */
void func_8008B188(s32 resource_flag, M2C_UNK resource_group, M2C_UNK resource_id) {
    s32 entry_index;

    entry_index = func_8008AD1C(resource_flag, resource_group, resource_id);
    if (entry_index < 0) {
        entry_index = func_8008AFB0(resource_flag, resource_group, resource_id, entry_index & 0x7FFFFFFF);
    }
    if (entry_index != 0) {
        func_8008AE4C(entry_index);
    }
}
