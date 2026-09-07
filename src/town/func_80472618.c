#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_8001A418();                 /* extern */

typedef struct S_80472618_0 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_80472618_0;   /* arg0 in func_80472618 */

typedef struct S_80472618_1 {
    u8 pad_00[0xC];
    s16 unk_0C;
} S_80472618_1;   /* temp_a1 in func_80472618 */

void func_80472618(S_80472618_0 *arg0, s32 arg1) {
    S_80472618_1 *temp_a1;

    temp_a1 = (arg1 * 0x10) + arg0->unk_10;
    func_8001A418(temp_a1->unk_0C, temp_a1);
}
