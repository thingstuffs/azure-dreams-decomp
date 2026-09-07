#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80038538_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
} S_80038538_0;   /* arg0 in func_80038538 */


M2C_UNK func_80053DA8();                     /* extern */
extern M2C_UNK func_80038A10;

void func_80038538(S_80038538_0 *arg0) {
    func_80053DA8(0xB4);
    arg0->unk_10 = &func_80038A10;
}
