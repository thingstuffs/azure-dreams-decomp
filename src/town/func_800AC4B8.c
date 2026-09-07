#include "common.h"
#include "m2c_compat.h"

typedef struct S_800A9C18_0 {
    u8 pad_00[0x35C4];
    u8 unk_35C4;
} S_800A9C18_0;   /* temp_a0 in func_800A9C18 */

void func_800A9C18(s32 arg0) {
    u8 temp_v0;
    S_800A9C18_0 *temp_a0;
    void *temp_v1;

    temp_v1 = (void *) 0x80010000;
    temp_a0 = (arg0 * 4) + temp_v1;
    temp_v0 = temp_a0->unk_35C4 + 1;
    temp_a0->unk_35C4 = temp_v0;
    if ((u32) (temp_v0 & 0xFF) >= 4U) {
        temp_a0->unk_35C4 = 3U;
    }
}
