#include "common.h"
#include "m2c_compat.h"

typedef struct S_80026398_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0x48];
    s32 unk_4C;
} S_80026398_0;   /* arg0 in func_80026398; pointer addresses record offset 0x10 */


/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_800262BC;

/* Decrement the record's countdown and reset its pointer when it becomes negative. */
void func_80026398(void *record_data) {
    s32 countdown;

    countdown = ((S_80026398_0 *)((u8 *)record_data - 0x10))->unk_4C - 1;
    ((S_80026398_0 *)((u8 *)record_data - 0x10))->unk_4C = countdown;
    if (countdown < 0) {
        ((S_80026398_0 *)((u8 *)record_data - 0x10))->unk_00 = &D_800262BC;
    }
}
