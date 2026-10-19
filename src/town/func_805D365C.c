#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/vector.h"



extern IntVector3 D_80019AE0;

/* Builds a record with two 16.16 values and a zero third value, then invokes the context callbacks. */
void func_805D365C(void) {
    Rec_D_80016000 *context;
    IntVector3 *output;
    s32 source_value2;

    context = D_80016000;
    D_80019AE0.x = ((TownPositionState *)context->unk_1C)->x << 16;
    source_value2 = ((TownPositionState *)context->unk_1C)->y;
    output = &D_80019AE0;
    output->z = 0;
    output->y = source_value2 << 16;
    ((void (*)(s32))context->unk_20->callback_208)(0);
    D_80016000->unk_20->callback_224(output);
}
