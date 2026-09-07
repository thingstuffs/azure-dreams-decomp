#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800C2E84(s32, void *, void *);           /* extern */
M2C_UNK func_800C591C();        /* extern */
extern M2C_UNK D_800D54C4;

typedef struct S_800C5ADC_0 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_800C5ADC_0;   /* arg2 in func_800C5ADC */

void func_800C5ADC(s32 arg0, M2C_UNK arg1, S_800C5ADC_0 *arg2) {
    if (arg2->unk_14 & 0x6000) {
        func_800C2E84(arg0, arg2, &D_800D54C4);
        func_800C591C(arg0, arg1, arg2);
    }
}
