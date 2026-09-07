#include "common.h"
#include "m2c_compat.h"

typedef struct S_80026398_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0x48];
    s32 unk_4C;
} S_80026398_0;   /* arg0 in func_80026398; pointer addresses record offset 0x10 */


/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_800262BC;

void func_80026398(void *arg0) {
    s32 temp_v0;

    temp_v0 = ((S_80026398_0 *)((u8 *)arg0 - 0x10))->unk_4C - 1;
    ((S_80026398_0 *)((u8 *)arg0 - 0x10))->unk_4C = temp_v0;
    if (temp_v0 < 0) {
        ((S_80026398_0 *)((u8 *)arg0 - 0x10))->unk_00 = &D_800262BC;
    }
}
