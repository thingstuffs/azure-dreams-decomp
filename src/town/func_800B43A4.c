#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B1B04_0 {
    s32 unk_00;
    s32 unk_04;
} S_800B1B04_0;   /* arg0 in func_800B1B04 */

/* Store two values in the pair. */
void func_800B1B04(S_800B1B04_0 *pair, s32 first, s32 second) {
    pair->unk_00 = first;
    pair->unk_04 = second;
}
