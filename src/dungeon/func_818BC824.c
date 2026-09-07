#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_8009D218(s32, s32);                 /* extern */
M2C_UNK func_800AD4D0();                      /* extern */
M2C_UNK func_800AD568();                      /* extern */
M2C_UNK func_800B4C7C(); /* extern */

typedef struct S_818BC824_0 {
    u8 pad_00[0x64];
    u16 unk_64;
} S_818BC824_0;   /* arg0 in func_818BC824 */

void func_818BC824(S_818BC824_0 *arg0) {
    if (func_8009D218((s32)arg0, 2) == 0) {
        arg0->unk_64 = (u16) (arg0->unk_64 + 0x200);
        func_800AD568(arg0);
        func_800B4C7C(0x8004, arg0, (s16) arg0->unk_64, 1);
        func_800AD4D0(arg0);
    }
}
