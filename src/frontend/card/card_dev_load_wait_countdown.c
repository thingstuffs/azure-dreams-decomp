#include "common.h"
#include "m2c_compat.h"

typedef struct S_8001FB74_0 {
    s32 * unk_00;
    u8 pad_04[0x48];
    s32 unk_4C;
} S_8001FB74_0;   /* arg0 in card_dev_load_wait_countdown; pointer addresses record offset 0x10 */


extern M2C_UNK D_80406AA8;

/* Decrement the record counter and replace its pointer when the counter becomes negative. */
void card_dev_load_wait_countdown(void *record_data) {
    s32 counter;

    counter = ((S_8001FB74_0 *)((u8 *)record_data - 0x10))->unk_4C - 1;
    ((S_8001FB74_0 *)((u8 *)record_data - 0x10))->unk_4C = counter;
    if (counter < 0) {
        ((S_8001FB74_0 *)((u8 *)record_data - 0x10))->unk_00 = &D_80406AA8;
    }
}
