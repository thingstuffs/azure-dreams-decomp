#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
/* extern */
extern M2C_UNK D_800C885C;

typedef struct S_800C88AC_0 {
    u8 pad_00[0x54];
    M2C_UNK * unk_54;
} S_800C88AC_0;   /* arg0 in func_800C88AC */


M2C_UNK func_800C4804(S_800C88AC_0 *, s32, s32);
/* Call func_800C4804 and set the object pointer to D_800C885C. */
void func_800C88AC(S_800C88AC_0 *object, s32 param_1, s32 param_2) {
    func_800C4804(object, param_1, param_2);
    object->unk_54 = &D_800C885C;
}
