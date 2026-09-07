#include "common.h"
#include "m2c_compat.h"

typedef struct S_8001F590_0 {
    M2C_UNK * unk_00;
} S_8001F590_0;   /* arg0 in func_8001F590; pointer addresses record offset 0x10 */


M2C_UNK func_80405AE8();                            /* extern */
M2C_UNK func_80400908();                            /* extern */
extern M2C_UNK D_80406368;

void func_8001F590(void *arg0) {
    func_80405AE8(arg0);
    func_80400908();
    ((S_8001F590_0 *)((u8 *)arg0 - 0x10))->unk_00 = &D_80406368;
}
