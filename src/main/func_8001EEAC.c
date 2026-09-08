#include "common.h"
#include "m2c_compat.h"

typedef struct S_8001EEAC_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0x48];
    s32 unk_4C;
} S_8001EEAC_0;   /* arg0 in func_8001EEAC; pointer addresses record offset 0x10 */


extern M2C_UNK D_80405DE0;

/* Decrement the record's countdown and switch its pointer when the count goes negative. */
void func_8001EEAC(void *record_data) {
    s32 countdown;

    countdown = ((S_8001EEAC_0 *)((u8 *)record_data - 0x10))->unk_4C - 1;
    ((S_8001EEAC_0 *)((u8 *)record_data - 0x10))->unk_4C = countdown;
    if (countdown < 0) {
        ((S_8001EEAC_0 *)((u8 *)record_data - 0x10))->unk_00 = &D_80405DE0;
    }
}
