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
void func_800C88AC(S_800C88AC_0 *arg0, s32 arg1, s32 arg2) {
    func_800C4804(arg0, arg1, arg2);
    arg0->unk_54 = &D_800C885C;
}
