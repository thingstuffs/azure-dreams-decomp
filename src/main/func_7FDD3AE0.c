#include "common.h"
#include "m2c_compat.h"

typedef struct S_7FDD3AE0_1 {
    u8 pad_00[0x4];
    void * unk_04;
} S_7FDD3AE0_1;   /* arg0 in func_7FDD3AE0 */

typedef struct S_7FDD3AE0_2 {
    u8 pad_00[0x16];
    s16 unk_16;
} S_7FDD3AE0_2;   /* ((S_7FDD3AE0_1 *)arg0)->unk_04 in func_7FDD3AE0 */


typedef struct S_7FDD3AE0_0 {
    u16 unk_00;
} S_7FDD3AE0_0;   /* arg0 in func_7FDD3AE0; pointer addresses record offset 0x2 */


extern s32 D_800814A0[];

void func_7FDD3AE0(void *arg0) {
    if (((S_7FDD3AE0_2 *)(((S_7FDD3AE0_1 *)arg0)->unk_04))->unk_16 & 0x8000) {
        ((S_7FDD3AE0_0 *)((u8 *)arg0 - 0x2))->unk_00 = (u16) (((S_7FDD3AE0_0 *)((u8 *)arg0 - 0x2))->unk_00 | 0x8000);
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }
}
