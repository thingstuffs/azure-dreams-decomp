#include "common.h"

typedef struct { u8 bytes[4]; } Bytes4;
typedef struct {
    u32 address;
    u8 pad_04[2];
    u8 x;
    u8 y;
    u8 next_value;
    u8 next_kind;
    u8 pad_0A[2];
} Fields;

extern u8 D_80400544[];

void *func_8001BCD4(void *arg0)
{
    Bytes4 values;
    s32 first_x;
    s32 first_y;
    s32 kind;
    register u32 address ASM_REG("$5");
    s32 second_x;
    u32 height_source;
    u8 *record;
    u8 *value;
    u8 *end;
    Fields *fields;

    record = arg0;
    values = *(Bytes4 *)D_80400544;
    first_x = 5;
    first_y = 5;
    kind = 0x48;
    address = 0x101010;
    second_x = 6;
    height_source = sizeof(Fields);
    value = values.bytes;
    end = values.bytes + 4;
    fields = (Fields *)(record + 4);
    do {
        fields->x = first_x;
        fields->y = first_y;
        ((u8 *)fields)[-3] = kind;
        fields->address = address;
        record[0] = *value;
        fields++;
        record += sizeof(Fields);
        address++;
        address--;
        height_source++;
        height_source--;
        fields->x = second_x;
        fields->y = height_source >> 1;
        ((u8 *)fields)[-3] = kind;
        fields->address = address;
        fields++;
        record[0] = *value;
        value++;
        record += sizeof(Fields);
    } while ((long)value < (long)end);
    record[-24] |= 0x80;
    return record;
}
