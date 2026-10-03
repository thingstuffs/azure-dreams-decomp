#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"



s32 func_8001ADE0();                         /* extern */


/* Invoke the callback with code 8 when checks 0x1200 and 0x1201 both return zero. */
void func_80018860(void) {
    if ((func_8001ADE0(0x1200) == 0) && (func_8001ADE0(0x1201) == 0)) {
        D_80016000->unk_20->callback_1E8(8);
    }
}
