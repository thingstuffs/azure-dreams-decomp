#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80035060_0 {
    u8 pad_00[0x3];
    s8 unk_03;
} S_80035060_0;   /* arg0 in func_80035060 */


void func_80035060(S_80035060_0 *arg0, s8 arg1) {
    arg0->unk_03 = arg1;
}
