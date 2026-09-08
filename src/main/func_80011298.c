#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80023E14();                         /* extern */
M2C_UNK func_800240EC();                         /* extern */
M2C_UNK func_80024160();                         /* extern */

/* Runs three update routines on the data of a non-null object. */
void func_80024298(s32 object_addr) {
    s32 object_data;

    if (object_addr != 0) {
        object_data = object_addr + 0x20;
        func_800240EC(object_data);
        func_80024160(object_data);
        func_80023E14(object_data);
    }
}
