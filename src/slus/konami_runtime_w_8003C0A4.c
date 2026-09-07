#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_8003C0A4_0 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_8003C0A4_0;   /* arg1 in func_8003C0A4 */

typedef struct S_8003C0A4_1 {
    u8 pad_00[0x4];
    s8 unk_04;
} S_8003C0A4_1;   /* arg0 in func_8003C0A4 */


void func_8003C0A4(S_8003C0A4_1 *arg0, S_8003C0A4_0 *arg1) {
    if (arg1->unk_08 != 0) {
        arg0->unk_04 = 1;
    }
}
