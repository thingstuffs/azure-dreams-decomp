#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
typedef struct S_800B4978_0 {
    void * unk_00;
    u8 pad_04[0x58];
    s32 unk_5C;
} S_800B4978_0;   /* arg0 in func_800B4978 */

typedef struct S_800B4978_1 {
    u8 pad_00[0x40];
    s32 unk_40;
} S_800B4978_1;   /* temp_a1 in func_800B4978 */

void func_800B4978(S_800B4978_0 *arg0) {
    void *temp_a1;

    temp_a1 = arg0->unk_00;
    func_800B2FF8(arg0->unk_5C + 0x18, temp_a1 + 0x2C, ((S_800B4978_1 *)temp_a1)->unk_40);
}
