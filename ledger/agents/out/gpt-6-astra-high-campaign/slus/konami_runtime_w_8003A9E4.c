#include "common.h"

typedef struct Decoder {
    u8 pad_001C[0x1C];
    u8 *read_ptr;
    u8 pad_0080[0x60];
    s32 *table;
} Decoder;

/* Multiply the first event-script variable by the second and store the result in the first. */
void func_8003A9E4(Decoder *script) {
    u8 *read_ptr = script->read_ptr;
    u8 left_index = *read_ptr;
    u8 right_index;
    s32 *variables;

    read_ptr++;
    script->read_ptr = read_ptr;
    right_index = *read_ptr;
    read_ptr++;
    script->read_ptr = read_ptr;

    variables = script->table;
    variables[left_index + 18] *= variables[right_index + 18];
}
