#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_804054E8();                      /* extern */
M2C_UNK func_80405900();                      /* extern */

typedef struct S_8001EA00_0 {
    u8 pad_00[0x9C];
    s32 unk_9C;
} S_8001EA00_0;   /* arg0 in func_8001EA00 */

void func_8001EA00(void *arg0, s32 arg1) {
    void *temp_s0;

    if (arg0 != NULL) {
        ((S_8001EA00_0 *)arg0)->unk_9C = arg1;
        temp_s0 = arg0 + 0x20;
        func_80405900(temp_s0);
        func_804054E8(temp_s0);
    }
}
