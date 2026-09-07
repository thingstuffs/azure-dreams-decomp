#include "common.h"
#include "m2c_compat.h"

typedef struct S_80024274_0 {
    u8 pad_00[0x224];
    s32 unk_224;
    u8 pad_228[0x58];
    s32 * unk_280;
} S_80024274_0;   /* temp_v1 in func_80024274 */

void func_80024274(s32 arg0) {
    S_80024274_0 *temp_v1;

    if (arg0 != 0) {
        temp_v1 = arg0 + 0x20;
        temp_v1->unk_224 = 0x606868;
        *temp_v1->unk_280 = 0;
    }
}
