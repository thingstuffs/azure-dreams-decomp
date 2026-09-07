#include "common.h"
#include "m2c_compat.h"

extern void *D_800DCF64;

typedef struct S_800A6104_0 {
    u8 pad_00[0x20];
    s32 unk_20;
} S_800A6104_0;   /* D_800DCF64 in func_800A6104 */

typedef struct S_800A6104_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x4];
    s16 unk_0C;
} S_800A6104_1;   /* temp_v1 in func_800A6104 */

void func_800A6104(void) {
    S_800A6104_1 *temp_v1;

    if (D_800DCF64 != NULL) {
        ((S_800A6104_0 *)D_800DCF64)->unk_20 = 0xFFFFFF;
        temp_v1 = D_800DCF64 + 0x20;
        temp_v1->unk_04 = 0x40;
        temp_v1->unk_0C = 1;
    }
}
