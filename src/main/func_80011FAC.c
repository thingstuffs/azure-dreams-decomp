#include "common.h"
#include "m2c_compat.h"

typedef struct S_80024FAC_0 {
    M2C_UNK * unk_00;
} S_80024FAC_0;   /* arg0 in func_80024FAC; pointer addresses record offset 0x10 */


s32 func_8002168C();                                /* extern */
M2C_UNK func_800231E4();                     /* extern */
M2C_UNK func_80024F7C(void *);                            /* extern */
extern M2C_UNK D_8002593C;

void func_80024FAC(void *arg0) {
    func_80024F7C(arg0);
    if (func_8002168C() >= 4) {
        func_800231E4(0);
        ((S_80024FAC_0 *)((u8 *)arg0 - 0x10))->unk_00 = &D_8002593C;
    }
}
