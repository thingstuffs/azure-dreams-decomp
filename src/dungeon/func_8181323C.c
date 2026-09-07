#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_80028050();       /* extern */
M2C_UNK func_800280FC();                 /* extern */
M2C_UNK func_80028210();                            /* extern */

typedef struct S_8002823C_0 {
    u8 pad_00[0x88];
    s32 unk_88;
} S_8002823C_0;   /* arg0 in func_8002823C */

void func_8002823C(void *arg0) {
    func_80028210();
    func_80028050(arg0, arg0 + 0x78, arg0 + 0x50, arg0 + 0x60);
    func_800280FC(arg0, ((S_8002823C_0 *)arg0)->unk_88);
}
