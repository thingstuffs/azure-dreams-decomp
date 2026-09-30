#include "common.h"

typedef struct { u8 bytes[4]; } Bytes4;
typedef struct {
    u8 value;
    u8 kind;
    u8 pad_02[2];
    u32 address;
    u8 pad_08[2];
    u8 x;
    u8 y;
} Fields;

extern u8 D_80400544[];

/* Initializes four pairs of records from D_80400544 and marks the final pair. */
void *func_8001BCD4(void *buffer)
{
    Bytes4 values;
    s32 i;
    u32 width;
    u32 height;
    s32 outer_width;
    u32 outer_height;
    Fields *record;

    record = buffer;
    values = *(Bytes4 *)D_80400544;
    width = 2;
    height = 2;
    outer_width = width + 10;
    i = 0;
    do {
        record->x = (width + 8) >> 1;
        record->y = (height + 8) >> 1;
        record->kind = 0x48;
        record->address = 0x101010;
        record->value = values.bytes[i];
        record++;
        record->x = outer_width / 2;
        outer_height = height + 10;
        outer_height &= 0xFFFF;
        record->y = outer_height >> 1;
        record->kind = 0x48;
        record->address = 0x101010;
        record->value = values.bytes[i];
        record++;
        i++;
    } while (i < 4);
    record[-2].value |= 0x80;
    return record;
}
