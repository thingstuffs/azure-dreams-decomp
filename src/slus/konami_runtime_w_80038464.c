#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80038464_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
    u8 pad_14[0x70];
    s8 unk_84;
} S_80038464_0;   /* arg0 in func_80038464 */


extern M2C_UNK func_80038478;

void func_80038464(S_80038464_0 *arg0) {
    arg0->unk_84 = 0;
    arg0->unk_10 = &func_80038478;
}
