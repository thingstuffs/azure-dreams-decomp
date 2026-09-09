#include "common.h"
#include "m2c_compat.h"

typedef struct S_8001B3E4_0 {
    u16 unk_00;
} S_8001B3E4_0;   /* arg0 in func_8001B3E4; pointer addresses record offset 0x2 */


M2C_UNK func_80047938(void *, s32, s32);                            /* extern */
M2C_UNK func_804024A4();                      /* extern */

void func_8001B3E4(void *arg0, s32 arg1, s32 arg2) {
    u16 flag;
    func_80047938(arg0, arg1, arg2);
    flag = ((S_8001B3E4_0 *)((u8 *)arg0 - 0x2))->unk_00;
    arg0 = (s8 *) arg0 - 0x20;
    if (flag & 0x2000) {
        func_804024A4(arg0);
    }
}
