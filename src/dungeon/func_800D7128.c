#include "common.h"



#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef s32 M2C_UNK;

M2C_UNK func_800DC82C();
extern s32 D_800E5910;

typedef struct S_800DC888_0 {
    u8 pad_00[0x38];
    s32 * unk_38;
} S_800DC888_0;   /* temp_a0 in func_800DC888 */

// Advances the stored cycle index modulo three and applies the new index.
void func_800DC888(void) {
    s32 *cycleIndexToWrap;
    s32 *cycleIndexToIncrement;
    s32 incrementedIndex;
    S_800DC888_0 *cycleState;

    cycleState = D_800E5910 + 0x20;
    cycleIndexToIncrement = cycleState->unk_38;
    *cycleIndexToIncrement += 1;
    cycleIndexToWrap = cycleState->unk_38;
    incrementedIndex = *cycleIndexToWrap;
    *cycleIndexToWrap = incrementedIndex % 3;
    func_800DC82C(cycleState, incrementedIndex % 3, cycleIndexToWrap);
}
