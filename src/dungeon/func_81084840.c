#include "common.h"
#include "m2c_compat.h"

typedef struct S_80172040_0 {
    u8 pad_00[0x9A];
    s8 unk_9A;
    s8 unk_9B;
} S_80172040_0;   /* arg0 in func_80172040 */

void func_80172040(S_80172040_0 *arg0) {
    arg0->unk_9A = 0x10;
    arg0->unk_9B = 0;
}
