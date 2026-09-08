#include "common.h"
#include "m2c_compat.h"

typedef struct S_80020F40_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0x4C];
    s32 unk_50;
} S_80020F40_0;   /* arg0 in func_80020F40; pointer addresses record offset 0x10 */


extern M2C_UNK D_80407E64;

/* Decrement the record's counter and replace its pointer when the counter becomes negative. */
void func_80020F40(void *record_data) {
    s32 counter;

    counter = ((S_80020F40_0 *)((u8 *)record_data - 0x10))->unk_50 - 1;
    ((S_80020F40_0 *)((u8 *)record_data - 0x10))->unk_50 = counter;
    if (counter < 0) {
        ((S_80020F40_0 *)((u8 *)record_data - 0x10))->unk_00 = &D_80407E64;
    }
}
