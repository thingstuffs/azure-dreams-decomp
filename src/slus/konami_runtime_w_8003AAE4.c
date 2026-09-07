#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_8003AAE4_0 {
    u8 pad_00[0xAC];
    s16 unk_AC;
    s16 unk_AE;
} S_8003AAE4_0;   /* base in func_8003AAE4 */


extern u8 D_80082A38[];

void func_8003AAE4(s16 arg0, s16 arg1) {
    u8 *base;

    base = D_80082A38;
    ((S_8003AAE4_0 *)base)->unk_AC = arg0;
    ((S_8003AAE4_0 *)base)->unk_AE = arg1;
}
