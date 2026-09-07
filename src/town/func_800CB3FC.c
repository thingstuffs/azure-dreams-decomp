#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_800C8BB4;
extern M2C_UNK D_800D6374;

typedef struct S_800C8B5C_0 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_800C8B5C_0;   /* arg1 in func_800C8B5C */

typedef struct S_800C8B5C_1 {
    u8 pad_00[0x50];
    M2C_UNK * unk_50;
    u8 pad_54[0x3C];
    s16 unk_90;
} S_800C8B5C_1;   /* arg0 in func_800C8B5C */

void func_800C8B5C(S_800C8B5C_1 *arg0, S_800C8B5C_0 *arg1) {
    arg1->unk_14 = (s32) *(M2C_UNK *)((u8 *)&D_800D6374 + ((arg0->unk_90) * 4));
    arg0->unk_50 = &D_800C8BB4;
}
