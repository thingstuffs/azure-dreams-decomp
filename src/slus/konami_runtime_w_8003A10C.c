#include "common.h"

#include "common.h"

typedef struct {
    u8 pad_00[0x1C];
    u8 *read_ptr;
    u8 pad_20[0x60];
    u8 *values;
} Func8003A10CState;

void func_8003A10C(Func8003A10CState *arg0) {
    u8 *ptr;
    u8 *next;
    u8 *data;
    u8 dst_index;
    u32 src_index;
    u32 address;
    u32 indirect;

    data = arg0->read_ptr;
    dst_index = data[0];
    data = data + 1;
    arg0->read_ptr = data;
    src_index = data[0];
    next = data + 1;
    arg0->read_ptr = next;
    src_index <<= 2;

    address = (s32)data[1] + ((u32)next[1] << 8)
            + ((u32)next[2] << 16) + ((u32)next[3] << 24);
    arg0->read_ptr = data + 5;
    ptr = (u8 *)(address + src_index);

    indirect = (u32)ptr[0] + ((u32)ptr[1] << 8)
             + ((u32)ptr[2] << 16) + ((u32)ptr[3] << 24);
    *(u32 *)(arg0->values + 0x48 + (dst_index * 4)) = *(u32 *)indirect;
}
