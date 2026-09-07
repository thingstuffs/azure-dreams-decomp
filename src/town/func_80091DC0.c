#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
typedef struct S_8008F520_0 {
    u8 pad_00[0x36];
    s8 unk_36;
} S_8008F520_0;   /* arg0 in func_8008F520 */

typedef struct S_8008F520_1 {
    s32 unk_00;
    u8 pad_04[0x8];
    s32 unk_0C;
} S_8008F520_1;   /* arg1 in func_8008F520 */

void func_8008F520(S_8008F520_0 *arg0, S_8008F520_1 *arg1, s32 arg2) {
    arg0->unk_36 = 1;
    arg1->unk_00 = arg2;
    arg1->unk_0C = 0;
}
