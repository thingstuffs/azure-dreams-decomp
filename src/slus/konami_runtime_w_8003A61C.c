#include "common.h"

typedef struct Func8003A61CEntry {
    u8 pad_00[0x48];
    s32 value;
} Func8003A61CEntry;

typedef struct Func8003A61CState {
    u8 pad_00[0x1c];
    u8 *read_ptr;
    u8 pad_20[0x60];
    struct Func8003A61CState *table;
} Func8003A61CState;

// Jump to the encoded address if the selected table value is nonpositive; otherwise skip it.
void func_8003A61C(Func8003A61CState *state) {
    u8 *operand_ptr = state->read_ptr;
    u8 table_index = *operand_ptr;
    operand_ptr++;
    state->read_ptr = operand_ptr;

    if (((Func8003A61CEntry *)((u8 *)state->table + table_index * 4))->value <= 0) {
        u32 jump_address = (u32)operand_ptr[0]
                         + ((u32)operand_ptr[1] << 8)
                         + ((u32)operand_ptr[2] << 16)
                         + ((u32)operand_ptr[3] << 24);
        state->read_ptr = (u8 *)jump_address;
    } else {
        state->read_ptr = operand_ptr + 4;
    }
}
