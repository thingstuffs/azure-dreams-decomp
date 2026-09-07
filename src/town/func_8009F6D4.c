#include "common.h"
#include "m2c_compat.h"

void *func_8003FE78();   /* extern */
M2C_UNK func_8008D084();                            /* extern */
M2C_UNK func_80096DC8();                   /* extern */
extern M2C_UNK D_8009CE80;
extern M2C_UNK D_801006D0;
extern M2C_UNK D_80100900;

typedef struct S_8009CE34_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
} S_8009CE34_0;   /* func_8003FE78(0x11, &D_801006D0, 0x49) in func_8009CE34 */

void func_8009CE34(void) {
    ((S_8009CE34_0 *)(func_8003FE78(0x11, &D_801006D0, 0x49)))->unk_10 = &D_8009CE80;
    func_80096DC8(&D_80100900);
    func_8008D084();
}
