#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_8003571C_0 {
    void * unk_00;
    u8 pad_04[0x64];
    M2C_UNK * unk_68;
} S_8003571C_0;   /* arg0 in func_8003571C */

typedef struct S_8003571C_1 {
    u8 pad_00[0x8];
    u16 unk_08;
} S_8003571C_1;   /* temp_v0 in func_8003571C */

typedef struct S_8003571C_2 {
    u8 pad_00[0x8];
    u16 unk_08;
} S_8003571C_2;   /* temp_v1 in func_8003571C */


extern M2C_UNK func_80035760;

void func_8003571C(S_8003571C_0 *arg0) {
    S_8003571C_1 *temp_v0;
    S_8003571C_2 *temp_v1;

    temp_v0 = arg0->unk_00;
    temp_v0->unk_08 = (u16) (temp_v0->unk_08 - 0xA0);
    temp_v1 = arg0->unk_00;
    if ((s16) temp_v1->unk_08 < 0) {
        temp_v1->unk_08 = 0U;
        arg0->unk_68 = &func_80035760;
    }
}
