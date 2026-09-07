#include "common.h"
#include "m2c_compat.h"

typedef struct S_80026370_0 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80026370_0;   /* arg0 in func_80026370 */

typedef struct S_80026370_1 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80026370_1;   /* ((S_80026370_0 *)arg0)->unk_04 in func_80026370 */

typedef struct S_80026370_2 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_80026370_2;   /* ((S_80026370_1 *)(((S_80026370_0 *)arg0)->unk_04))->unk_04 in func_80026370 */





void func_80026370(S_80026370_0 *arg0, s32 arg1) {
    ((S_80026370_2 *)(((S_80026370_1 *)(arg0->unk_04))->unk_04))->unk_08 = (s16) ((arg1 * 8) - 0x18);
}
