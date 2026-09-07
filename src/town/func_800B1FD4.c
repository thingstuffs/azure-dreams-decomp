#include "common.h"
#include "m2c_compat.h"

typedef struct S_800AF734_0 {
    u8 pad_00[0x98];
    void * unk_98;
    void * unk_9C;
} S_800AF734_0;   /* arg0 in func_800AF734 */

typedef struct S_800AF734_1 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800AF734_1;   /* ((S_800AF734_0 *)arg0)->unk_98 in func_800AF734 */

typedef struct S_800AF734_2 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800AF734_2;   /* ((S_800AF734_0 *)arg0)->unk_9C in func_800AF734 */

typedef struct S_800AF734_3 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800AF734_3;   /* ((S_800AF734_1 *)(((S_800AF734_0 *)arg0)->unk_98))->unk_04 in func_800AF734 */

typedef struct S_800AF734_4 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800AF734_4;   /* ((S_800AF734_2 *)(((S_800AF734_0 *)arg0)->unk_9C))->unk_04 in func_800AF734 */





void func_800AF734(S_800AF734_0 *arg0) {
    ((S_800AF734_3 *)(((S_800AF734_1 *)(arg0->unk_98))->unk_04))->unk_08 = -0x40;
    ((S_800AF734_3 *)(((S_800AF734_1 *)(arg0->unk_98))->unk_04))->unk_0A = 0x30;
    ((S_800AF734_4 *)(((S_800AF734_2 *)(arg0->unk_9C))->unk_04))->unk_08 = 0xC4;
    ((S_800AF734_4 *)(((S_800AF734_2 *)(arg0->unk_9C))->unk_04))->unk_0A = 0x30;
}
