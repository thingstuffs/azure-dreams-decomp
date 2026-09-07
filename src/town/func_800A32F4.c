#include "common.h"
#include "m2c_compat.h"

void *func_800A0988();                              /* extern */

typedef struct S_800A0A54_0 {
    u8 pad_00[0x88];
    s16 unk_88;
} S_800A0A54_0;   /* temp_v0 in func_800A0A54 */

void func_800A0A54(M2C_UNK arg0, s16 arg1) {
    S_800A0A54_0 *temp_v0;

    temp_v0 = func_800A0988();
    if (temp_v0 != NULL) {
        temp_v0->unk_88 = arg1;
    }
}
