#include "common.h"

void func_800B1960(s32, s32, s32, s32, s32); /* extern */
void func_800B19F8(s32); /* extern */
void func_800B1B04(s32, s32); /* extern */

/* Set up the object, update its embedded records, and finalize it. */
void func_800B1B10(s32 object_addr, s32 setup_value, s32 update_value_1, s32 update_value_2) {
    func_800B1B04(object_addr, setup_value);
    func_800B1960(object_addr + 0x38, object_addr + 0x10, object_addr + 0x20, update_value_1, update_value_2);
    func_800B19F8(object_addr);
}
