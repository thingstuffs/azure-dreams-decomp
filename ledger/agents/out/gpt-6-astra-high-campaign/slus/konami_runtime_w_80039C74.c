#include "common.h"

#include "common.h"

typedef struct Func80039C74State {
    u8 pad_00[0x1C];
    u8 *read_ptr;
} Func80039C74State;

extern s32 func_80033B2C(s32 arg0);

/* Jump the event script to the encoded address if the signed operand check returns zero. */
void func_80039C74(Func80039C74State *state) {
    u8 *operand_ptr = state->read_ptr;
    s32 operand = operand_ptr[0] + (operand_ptr[1] << 8);

    state->read_ptr = operand_ptr + 2;
    if (func_80033B2C((s16)operand) == 0) {
        u8 *target_ptr = state->read_ptr;

        state->read_ptr = (u8 *)(target_ptr[0] + (target_ptr[1] << 8) +
                                  (target_ptr[2] << 16) + (target_ptr[3] << 24));
    } else {
        state->read_ptr += 4;
    }
}
