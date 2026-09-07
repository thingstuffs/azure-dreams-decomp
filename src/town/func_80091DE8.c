#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
typedef struct S_8008F548_0 {
    u8 pad_00[0x38];
    s8 unk_38;
} S_8008F548_0;   /* arg0 in func_8008F548 */

typedef struct S_8008F548_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x8];
    s32 unk_10;
} S_8008F548_1;   /* arg1 in func_8008F548 */

void func_8008F548(S_8008F548_0 *arg0, S_8008F548_1 *arg1, s32 arg2) {
    arg0->unk_38 = 1;
    arg1->unk_04 = arg2;
    arg1->unk_10 = 0;
}
