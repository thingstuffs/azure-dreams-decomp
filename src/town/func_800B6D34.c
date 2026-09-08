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

/* Sets the record's base value, offset value, and data pointer. */
void func_800B4494(void *record_values, s32 base_value) {
    ((S_800B4494_0 *)((u8 *)record_values - 0x10))->unk_14 = base_value;
    ((S_800B4494_0 *)((u8 *)record_values - 0x10))->unk_10 = (s32) (base_value + 0x20);
    ((S_800B4494_0 *)((u8 *)record_values - 0x10))->unk_00 = &D_800B3E68;
}
