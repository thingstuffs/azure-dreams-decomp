#include "common.h"
#include "m2c_compat.h"

/* extern */

typedef struct S_80173588_0 {
    u8 pad_00[0xA2];
    s16 unk_A2;
} S_80173588_0;   /* arg0 in func_80173588 */


M2C_UNK func_800AB538(S_80173588_0 *, void *, void *);
void func_80173588(S_80173588_0 *arg0, void *arg1, void *arg2) {
    func_800AB538(arg0, arg1, arg2);
    arg0->unk_A2 = 0;
}
