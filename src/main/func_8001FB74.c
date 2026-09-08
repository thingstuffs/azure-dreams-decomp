#include "common.h"
#include "m2c_compat.h"

typedef struct S_8001FB74_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0x48];
    s32 unk_4C;
} S_8001FB74_0;   /* arg0 in func_8001FB74; pointer addresses record offset 0x10 */


extern M2C_UNK D_80406AA8;

/* Decrement the record counter and replace its pointer when the counter becomes negative. */
void func_8001FB74(void *record_data) {
    s32 counter;

    counter = ((S_8001FB74_0 *)((u8 *)record_data - 0x10))->unk_4C - 1;
    ((S_8001FB74_0 *)((u8 *)record_data - 0x10))->unk_4C = counter;
    if (counter < 0) {
        ((S_8001FB74_0 *)((u8 *)record_data - 0x10))->unk_00 = &D_80406AA8;
    }
}
