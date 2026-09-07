#include "common.h"

typedef struct Decoder {
    u8 pad_001C[0x1C];
    u8 *read_ptr;
    u8 pad_0080[0x60];
    s32 *table;
} Decoder;

void func_8003A9E4(Decoder *ctx) {
    u8 *ptr = ctx->read_ptr;
    u8 left_index = *ptr;
    u8 right_index;
    s32 *table;

    ptr++;
    ctx->read_ptr = ptr;
    right_index = *ptr;
    ptr++;
    ctx->read_ptr = ptr;

    table = ctx->table;
    table[left_index + 18] *= table[right_index + 18];
}
