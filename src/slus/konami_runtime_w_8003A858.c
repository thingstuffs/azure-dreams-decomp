#include "common.h"

#include "common.h"

typedef struct {
    u8 pad_00[0x1C];
    u8 *read_ptr;
    u8 pad_20[0x60];
    u32 *values;
} Func8003A858State;

void func_8003A858(Func8003A858State *arg0) {
    u8 *data;
    u8 *next;
    u8 dst_index;
    u8 src_index;
    u32 src_offset;
    u32 address;

    data = arg0->read_ptr;
    dst_index = data[0];
    data = data + 1;
    arg0->read_ptr = data;
    src_index = data[0];
    next = data + 1;
    arg0->read_ptr = next;
    src_offset = (u32)src_index << 2;

    address = (u32)data[1] + ((u32)next[1] << 8)
            + ((u32)next[2] << 16) + ((u32)next[3] << 24);
    arg0->read_ptr = data + 5;
    {
        u32 *values = arg0->values;
        u8 *ptr;

        values[dst_index + 18] = *(u8 *)(address + src_offset);
        ptr = (u8 *)(address + src_offset);
        values[dst_index + 18] += (u32)ptr[1] << 8;
        values[dst_index + 18] += (u32)ptr[2] << 16;
        values[dst_index + 18] += (u32)ptr[3] << 24;
    }
}
