#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800AD7F8_arg0.h"


typedef struct S_800AD7F8_1 {
    u8 pad_00[0x3];
    u8 unk_03;
} S_800AD7F8_1;   /* temp_a0 in func_800AD7F8 */

void func_800AD7F8(Rec_func_800AD7F8_arg0 *arg0) {
    u8 temp_v1;
    S_800AD7F8_1 *temp_a0;

    temp_a0 = (arg0->unk_04 * 4) + arg0->unk_20;
    temp_v1 = temp_a0->unk_03;
    if (!(temp_v1 & 0x80)) {
        temp_a0->unk_03 = (u8) (temp_v1 ^ 0x20);
    }
}
