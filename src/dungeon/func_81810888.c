#include "common.h"
#include "m2c_compat.h"

typedef struct S_80025888_0 {
    u8 pad_00[0x4];
    void * unk_04;
    void * unk_08;
} S_80025888_0;   /* arg0 in func_80025888 */

typedef struct S_80025888_1 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80025888_1;   /* ((S_80025888_0 *)arg0)->unk_04 in func_80025888 */

typedef struct S_80025888_2 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80025888_2;   /* ((S_80025888_0 *)arg0)->unk_08 in func_80025888 */

typedef struct S_80025888_3 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80025888_3;   /* ((S_80025888_1 *)(((S_80025888_0 *)arg0)->unk_04))->unk_04 in func_80025888 */

typedef struct S_80025888_4 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80025888_4;   /* ((S_80025888_2 *)(((S_80025888_0 *)arg0)->unk_08))->unk_04 in func_80025888 */





void func_80025888(S_80025888_0 *arg0, s32 arg1) {
    s16 temp_a1;

    temp_a1 = (arg1 * 0x10) - 0x38;
    ((S_80025888_3 *)(((S_80025888_1 *)(arg0->unk_04))->unk_04))->unk_0A = temp_a1;
    ((S_80025888_4 *)(((S_80025888_2 *)(arg0->unk_08))->unk_04))->unk_0A = temp_a1;
}
