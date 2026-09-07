#include "common.h"
#include "m2c_compat.h"

#define M2C_BREAK() 0

/* cfail-repair: tf7-phase1-cache-v3 */
extern void func_800C2E84(void *arg0, M2C_UNK arg1, void *arg2);
extern u8 D_80082660[][8];
extern M2C_UNK D_800CB2DC;
extern M2C_UNK D_800D6910;

typedef struct S_800CB348_0 {
    u8 pad_00[0x54];
    M2C_UNK * unk_54;
    u8 pad_58[0x8];
    s32 unk_60;
    u8 pad_64[0x8];
    s16 unk_6C;
} S_800CB348_0;   /* arg0 in func_800CB348 */

void func_800CB348(void *arg0, M2C_UNK unused, M2C_UNK arg2) {
    func_800C2E84(arg0, arg2, &D_800D6910);
    D_80082660[((S_800CB348_0 *)arg0)->unk_60][0] = 0;
    ((S_800CB348_0 *)arg0)->unk_54 = &D_800CB2DC;
    ((S_800CB348_0 *)arg0)->unk_6C = 6;
}
