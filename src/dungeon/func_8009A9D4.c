#include "common.h"
#include "m2c_compat.h"

typedef struct S_800A0134_0 {
    u8 pad_00[0x88];
    u16 unk_88;
} S_800A0134_0;   /* arg0 in func_800A0134 */

typedef struct S_800A0134_1 {
    u8 pad_00[0x88];
    u16 unk_88;
} S_800A0134_1;   /* arg1 in func_800A0134 */

s16 func_800A0134(S_800A0134_0 *arg0, S_800A0134_1 *arg1) {
    return (s16) (arg0->unk_88 - arg1->unk_88);
}
