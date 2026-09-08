#include "common.h"
#include "m2c_compat.h"

typedef struct S_800252A4_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0x48];
    s32 unk_4C;
} S_800252A4_0;   /* arg0 in func_800252A4; pointer addresses record offset 0x10 */


extern M2C_UNK D_80025230;

/* Decrement the record's countdown and set its pointer when the countdown becomes negative. */
void func_800252A4(void *record_data) {
    s32 countdown;

    countdown = ((S_800252A4_0 *)((u8 *)record_data - 0x10))->unk_4C - 1;
    ((S_800252A4_0 *)((u8 *)record_data - 0x10))->unk_4C = countdown;
    if (countdown < 0) {
        ((S_800252A4_0 *)((u8 *)record_data - 0x10))->unk_00 = &D_80025230;
    }
}
