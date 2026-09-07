#include "common.h"

#include "common.h"

typedef struct {
    u8 pad_00[0x1C];
    u8 *read_ptr;
    u8 pad_20[0x60];
    u8 *values;
} Func8003A904State;

void func_8003A904(Func8003A904State *arg0) {
    u8 *data;
    u8 *next;
    u8 *ptr;
    u8 *base;
    u32 dst_index;
    u32 src_index;
    u32 table_index;
    u32 address_byte_2;
    u32 value;

    data = arg0->read_ptr;
    dst_index = data[0];
    base = arg0->values;
    data = data + 1;
    arg0->read_ptr = data;
    src_index = data[0];
    next = data + 1;
    arg0->read_ptr = next;

    table_index = *(u32 *)(base + (src_index * 4) + 0x48);
    address_byte_2 = next[2];
    table_index <<= 2;
    ptr = (u8 *)((u32)data[1] + ((u32)next[1] << 8)
               + (address_byte_2 << 16) + ((u32)next[3] << 24)
               + table_index);
    arg0->read_ptr = data + 5;

    value = ptr[0];
    *(u32 *)(base + (dst_index * 4) + 0x48) = value;
    value += (u32)ptr[1] << 8;
    *(u32 *)(base + (dst_index * 4) + 0x48) = value;
    value += (u32)ptr[2] << 16;
    *(u32 *)(base + (dst_index * 4) + 0x48) = value;
    value += (u32)ptr[3] << 24;
    *(u32 *)(base + (dst_index * 4) + 0x48) = value;
}
