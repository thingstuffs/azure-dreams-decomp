/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

extern s32 func_80049E1C();
extern M2C_UNK func_800B1F10();
extern M2C_UNK func_800B1F48();

typedef struct S_800B2068_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x8];
    s32 unk_18;
} S_800B2068_0;   /* arg0 in func_800B2068 */

typedef struct S_800B2068_1 {
    s32 unk_00;
    u8 pad_04[0x4];
    s32 unk_08;
    s32 unk_0C;
} S_800B2068_1;   /* temp_s0 in func_800B2068 */

void func_800B2068(void *arg0) {
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_a1_3;
    s32 temp_ret;
    S_800B2068_1 *temp_s0;

    temp_s0 = arg0 + ((((S_800B2068_0 *)arg0)->unk_0C * 0x10) + 0x1C);
    temp_ret = func_80049E1C(temp_s0->unk_08 - 1, 1, temp_s0->unk_0C);
    temp_s0->unk_08 = temp_ret;
    temp_s0->unk_00 = (s32) (temp_ret / 10);
    temp_a1 = ((S_800B2068_0 *)arg0)->unk_0C;
    func_800B1F48(*((s32 *)arg0 + temp_a1), temp_a1);
    temp_a1_2 = ((S_800B2068_0 *)arg0)->unk_0C;
    func_800B1F10(*((s32 *)arg0 + temp_a1_2), temp_a1_2);
    temp_a1_3 = ((S_800B2068_0 *)arg0)->unk_18;
    func_800B1F10(*((s32 *)arg0 + temp_a1_3), temp_a1_3);
}
