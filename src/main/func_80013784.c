#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80026920();                         /* extern */
M2C_UNK func_80027AFC();                    /* extern */

typedef struct S_80026784_0 {
    u8 pad_00[0x20];
    s32 unk_20;
    s32 unk_24;
} S_80026784_0;   /* arg0 in func_80026784 */

void func_80026784(void *arg0) {
    func_80026920(arg0 - 0x20);
    func_80027AFC(((S_80026784_0 *)arg0)->unk_20, ((S_80026784_0 *)arg0)->unk_24);
}
