#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80018BD0();                     /* extern */

/* Processes IDs 0xFB7 and 0xFB8, then returns zero. */
s32 process_ids_zero(void) {
    func_80018BD0(0xFB7);
    func_80018BD0(0xFB8);
    return 0;
}
