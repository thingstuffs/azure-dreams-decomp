#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80035820_0 {
    s32 unk_00;
    u8 pad_04[0x4C];
    u16 unk_50;
    u8 pad_52[0x22];
    s32 unk_74;
} S_80035820_0;   /* arg0 in func_80035820 */


M2C_UNK func_80033C84();                         /* extern */
M2C_UNK func_80034EB4();                         /* extern */
M2C_UNK func_80035090();                      /* extern */
M2C_UNK func_8003FFF0();                      /* extern */
M2C_UNK func_80044A50();                      /* extern */

/* Run handlers for a type-0x101 record and its enclosing object. */
void func_80035820(void *record) {
    void *object_base;

    if (((S_80035820_0 *)record)->unk_50 == 0x101) {
        func_80034EB4(((S_80035820_0 *)record)->unk_74);
        func_80033C84(((S_80035820_0 *)record)->unk_00);
        func_80035090(record + 0x54);
        object_base = record - 0x20;
        func_80044A50(object_base);
        func_8003FFF0(object_base);
    }
}
