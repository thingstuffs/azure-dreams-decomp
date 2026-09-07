#include "common.h"

typedef struct S_800B4AB0_0 {
    void * unk_00;
    u8 pad_04[0x8];
    s32 unk_0C;
    u8 pad_10[0x4C];
    void * unk_5C;
} S_800B4AB0_0;   /* arg0 in func_800B4AB0 */

typedef struct S_800B4AB0_1 {
    u8 pad_00[0x2C];
    s32 unk_2C;
    s32 unk_30;
} S_800B4AB0_1;   /* state in func_800B4AB0 */

typedef struct S_800B4AB0_2 {
    u8 pad_00[0x2C];
    s32 unk_2C;
} S_800B4AB0_2;   /* ((S_800B4AB0_0 *)arg0)->unk_00 in func_800B4AB0 */

typedef struct S_800B4AB0_3 {
    u8 pad_00[0x98];
    void ** unk_98;
    void ** unk_9C;
} S_800B4AB0_3;   /* ((S_800B4AB0_0 *)arg0)->unk_5C in func_800B4AB0 */



extern u8 D_800786DC[];
extern u8 D_800786E8[];

void func_800B4AB0(S_800B4AB0_0 *arg0)
{
    S_800B4AB0_1 *state;

    if (((S_800B4AB0_2 *)(arg0->unk_00))->unk_2C > 0) {
        *((S_800B4AB0_3 *)(arg0->unk_5C))->unk_98 = D_800786DC;
        arg0->unk_0C = arg0->unk_0C & -3;
    } else {
        *((S_800B4AB0_3 *)(arg0->unk_5C))->unk_98 = 0;
        arg0->unk_0C = arg0->unk_0C | 2;
    }

    state = arg0->unk_00;
    if (state->unk_2C < state->unk_30) {
        arg0->unk_0C = arg0->unk_0C & -2;
        *((S_800B4AB0_3 *)(arg0->unk_5C))->unk_9C = D_800786E8;
    } else {
        arg0->unk_0C = arg0->unk_0C | 1;
        *((S_800B4AB0_3 *)(arg0->unk_5C))->unk_9C = 0;
    }
}
