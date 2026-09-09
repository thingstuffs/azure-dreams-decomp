#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80700C54(s32, s32, s32, s32);                            /* extern */
extern s32 D_80700A18[];
__asm__(".set D_80700A18, 0x80700A18");

/* Run the indexed operation and return its table value. */
s32 func_8087FF98(s32 table_index, s32 call_input, s32 call_param, s32 call_extra) {
    func_80700C54(table_index, call_input, call_param, call_extra);
    return D_80700A18[table_index];
}
