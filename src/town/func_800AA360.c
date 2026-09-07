#include "common.h"
#include "m2c_compat.h"

typedef struct S_800A7AC0_0 {
    M2C_UNK * unk_00;
} S_800A7AC0_0;   /* arg0 in func_800A7AC0; pointer addresses record offset 0x10 */


M2C_UNK func_80033CD8();           /* extern */
M2C_UNK func_800C2CB0(); /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_800A7B14;
extern M2C_UNK D_800F838C;

void func_800A7AC0(void *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    ((S_800A7AC0_0 *)((u8 *)arg0 - 0x10))->unk_00 = &D_800A7B14;
    func_800C2CB0(arg0, arg2, &D_800F838C, 0);
    func_80033CD8(arg0, &D_80045340);
}
