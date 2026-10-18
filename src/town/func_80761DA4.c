#include "common.h"
#include "m2c_compat.h"
void func_80017724(s32);                     /* extern */
s32 get_indexed_table_entry();                         /* extern */
s32 func_80017990();                         /* extern */
extern M2C_UNK D_80017AB8;
extern s32 *D_80017B6C;

/* Set the active data pointer and process entries for the two checks for index 7. */
void func_80761DA4(void) {
    D_80017B6C = &D_80017AB8;
    if (get_indexed_table_entry(7) != 0) {
        func_80017724(0x9DE);
    }
    if (func_80017990(7) != 0) {
        func_80017724(0x9DD);
    }
}
