#include "common.h"

#include "common.h"

typedef struct D80082A38 {
    u8 pad0[0x48];
    s32 field48;
    s32 field4C;
    u8 pad50[0x5C];
    s16 fieldAC;
    s16 fieldAE;
} D80082A38;

extern D80082A38 D_80082A38;

void func_8003AAF8(void) {
    D80082A38 *base;
    s32 value0;
    s32 value1;

    base = &D_80082A38;
    value0 = base->fieldAC;
    value1 = base->fieldAE;
    base->field48 = value0;
    base->field4C = value1;
}
