#include "common.h"

typedef struct Func8003A500Entry {
    u8 pad_00[0x48];
    s32 value;
} Func8003A500Entry;

typedef struct Func8003A500State {
    u8 pad_00[0x1c];
    u8 *read_ptr;
    u8 pad_20[0x60];
    struct Func8003A500State *table;
    s32 result;
} Func8003A500State;

void func_8003A500(Func8003A500State *arg0) {
    u8 *ptr = arg0->read_ptr;
    u8 first = *ptr;
    u8 second;
    ptr++;
    arg0->read_ptr = ptr;
    second = *ptr;
    ptr++;
    arg0->read_ptr = ptr;

    arg0 = arg0->table;
    arg0->result = ((Func8003A500Entry *)((u8 *)arg0 + first * 4))->value
                 - ((Func8003A500Entry *)((u8 *)arg0 + second * 4))->value;
}
