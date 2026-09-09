#include "common.h"
#include "m2c_compat.h"

typedef struct S_80025B60_0 {
    M2C_UNK * unk_00;
} S_80025B60_0;   /* arg0 in func_80025B60; pointer addresses record offset 0x10 */


M2C_UNK func_80020984();                            /* extern */
M2C_UNK func_80025030(void *);                            /* extern */
extern M2C_UNK D_8002593C;

void func_80025B60(void *arg0) {
    func_80025030(arg0);
    func_80020984();
    ((S_80025B60_0 *)((u8 *)arg0 - 0x10))->unk_00 = &D_8002593C;
}
