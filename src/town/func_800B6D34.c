#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B4494_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0xC];
    s32 unk_10;
    s32 unk_14;
} S_800B4494_0;   /* arg0 in func_800B4494; pointer addresses record offset 0x10 */


/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_800B3E68;

void func_800B4494(void *arg0, s32 arg1) {
    ((S_800B4494_0 *)((u8 *)arg0 - 0x10))->unk_14 = arg1;
    ((S_800B4494_0 *)((u8 *)arg0 - 0x10))->unk_10 = (s32) (arg1 + 0x20);
    ((S_800B4494_0 *)((u8 *)arg0 - 0x10))->unk_00 = &D_800B3E68;
}
