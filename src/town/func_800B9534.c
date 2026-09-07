#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B6C94_0 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_800B6C94_0;   /* arg0 in func_800B6C94 */

typedef struct S_800B6C94_1 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800B6C94_1;   /* ((S_800B6C94_0 *)arg0)->unk_0C in func_800B6C94 */

typedef struct S_800B6C94_2 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800B6C94_2;   /* ((S_800B6C94_1 *)(((S_800B6C94_0 *)arg0)->unk_0C))->unk_04 in func_800B6C94 */





void func_800B6C94(S_800B6C94_0 *arg0, s16 arg1, s16 arg2) {
    if (arg0 != NULL) {
        ((S_800B6C94_2 *)(((S_800B6C94_1 *)(arg0->unk_0C))->unk_04))->unk_08 = arg1;
        ((S_800B6C94_2 *)(((S_800B6C94_1 *)(arg0->unk_0C))->unk_04))->unk_0A = arg2;
    }
}
