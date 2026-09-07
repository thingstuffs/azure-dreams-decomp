#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_8003AF58_0 {
    u8 pad_00[0x14];
    union { s32 s; void * u; } unk_14;   /* accessed as both */
} S_8003AF58_0;   /* var_a0 in func_8003AF58 */

typedef struct S_8003AF58_1 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_8003AF58_1;   /* arg1 in func_8003AF58 */


void func_8003AF58(void *arg0, S_8003AF58_1 *arg1) {
    S_8003AF58_0 *var_a0;

    var_a0 = arg0;
    if (var_a0->unk_14.s != 0) {
        do {
            var_a0 = var_a0->unk_14.u;
        } while (var_a0->unk_14.s != 0);
    }
    var_a0->unk_14.u = arg1;
    arg1->unk_14 = 0;
}
