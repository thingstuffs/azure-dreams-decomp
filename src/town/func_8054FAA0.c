#include "common.h"
#include "m2c_compat.h"

typedef struct S_8054FAA0_0 {
    u8 pad_00[0x20];
    void * unk_20;
} S_8054FAA0_0;   /* D_80016000 in func_8054FAA0 */

typedef struct S_8054FAA0_1 {
    u8 pad_00[0x230];
    M2C_UNK (*unk_230)(s32);
} S_8054FAA0_1;   /* ((S_8054FAA0_0 *)D_80016000)->unk_20 in func_8054FAA0 */

extern S_8054FAA0_0 *D_80016000;
extern M2C_UNK D_800179FC;
extern s16 D_80017AA0;

void func_8054FAA0(void) {
    ((S_8054FAA0_1 *)(D_80016000->unk_20))->unk_230(*((M2C_UNK *)((s8 *)&D_800179FC + D_80017AA0 * 4)));
}
