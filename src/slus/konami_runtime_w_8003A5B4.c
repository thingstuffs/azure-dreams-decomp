#include "common.h"

typedef struct Func8003A5B4Entry {
    u8 pad_00[0x48];
    u32 value;
} Func8003A5B4Entry;

typedef struct Func8003A5B4State {
    u8 pad_00[0x1c];
    u8 *read_ptr;
    u8 pad_20[0x60];
    struct Func8003A5B4State *table;
} Func8003A5B4State;

void func_8003A5B4(Func8003A5B4State *arg0) {
    u8 *ptr = arg0->read_ptr;
    u8 opcode = *ptr;

    ptr++;
    arg0->read_ptr = ptr;

    if (((Func8003A5B4Entry *)((u8 *)arg0->table + opcode * 4))->value != 0) {
        u32 value = (u32)ptr[0]
                  + ((u32)ptr[1] << 8)
                  + ((u32)ptr[2] << 16)
                  + ((u32)ptr[3] << 24);
        arg0->read_ptr = (u8 *)value;
    } else {
        arg0->read_ptr = ptr + 4;
    }
}
