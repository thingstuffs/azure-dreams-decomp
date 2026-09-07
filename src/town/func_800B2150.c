/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_800AF8B0_1 {
    void * unk_00;
} S_800AF8B0_1;   /* arg0 in func_800AF8B0 */

typedef struct S_800AF8B0_2 {
    u8 pad_00[0x18];
    s32 unk_18;
    u8 pad_1C[0x4];
    s32 unk_20;
} S_800AF8B0_2;   /* ((S_800AF8B0_1 *)arg0)->unk_00 in func_800AF8B0 */




M2C_UNK func_800B05DC(); /* extern */

typedef struct S_800AF8B0_0 {
    u8 pad_00[0x10];
    s32 unk_10;
    u8 pad_14[0x4];
    s32 unk_18;
} S_800AF8B0_0;   /* arg0 in func_800AF8B0 */

void func_800AF8B0(S_800AF8B0_0 *arg0) {
    M2C_UNK var_a2;
    s32 var_a3;

    var_a3 = ((S_800AF8B0_2 *)(((S_800AF8B0_1 *)arg0)->unk_00))->unk_18 % 10;
    var_a2 = -0xB4;
    if ((var_a3 / 5) != 0) {
        var_a2 = 0x28;
    }
    arg0->unk_10 = 0;
    func_800B05DC(arg0->unk_18, ((S_800AF8B0_2 *)(((S_800AF8B0_1 *)arg0)->unk_00))->unk_18, var_a2, ((var_a3 % 5) * 0x18) - 0x80, ((s32 *)((S_800AF8B0_2 *)(((S_800AF8B0_1 *)arg0)->unk_00))->unk_20)[((S_800AF8B0_2 *)(((S_800AF8B0_1 *)arg0)->unk_00))->unk_18]);
}
