#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_8003A288_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_8003A288_0;   /* arg0 in func_8003A288 */


void func_8003A288(S_8003A288_0 *arg0) {
    arg0->unk_1C = (s32) (arg0->unk_1C + 1);
}
