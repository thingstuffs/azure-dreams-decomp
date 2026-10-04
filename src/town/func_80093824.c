#include "common.h"
#include "m2c_compat.h"

/* extern */
void func_80093D48();      /* extern */

typedef struct S_80090F84_0 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80090F84_0;   /* arg2 in func_80090F84 */


void func_80090A74(s32 *, s32, S_80090F84_0 *);
/* Run the fallback handler if the value stays unchanged and either 0x6000 flag is set. */
void func_80090F84(s32 *value, s32 context, S_80090F84_0 *record) {
    s32 previous_value;

    previous_value = *value;
    func_80090A74(value, context, record);
    if ((previous_value == *value) && (record->unk_14 & 0x6000)) {
        func_80093D48(value, context, record);
    }
}
