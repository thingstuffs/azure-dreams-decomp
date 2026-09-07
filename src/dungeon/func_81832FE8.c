#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 rand();                             /* extern */
M2C_UNK func_800A48F0();        /* extern */

typedef struct S_81832FE8_0 {
    u8 pad_00[0x60];
    void * unk_60;
} S_81832FE8_0;   /* arg0 in func_81832FE8 */

typedef struct S_81832FE8_1 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_81832FE8_1;   /* temp_v1 in func_81832FE8 */

void func_81832FE8(S_81832FE8_0 *arg0) {
    s32 temp_a0;
    S_81832FE8_1 *temp_v1;

    temp_v1 = arg0->unk_60;
    if (temp_v1 != NULL) {
        temp_a0 = temp_v1->unk_14;
        if (!(temp_a0 & 0x20) && (temp_a0 & 1)) {
            temp_v1->unk_1C = (s32) (temp_v1->unk_1C | 0x20);
            func_800A48F0(arg0->unk_60, 4, (rand(temp_a0) & 0x3F) | 0x20);
        }
    }
}
