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

extern u8 D_800200A0[];

void *func_80022A30(void *arg0)
{
    Bytes4 values;
    s32 i;
    s32 first_x;
    s32 first_y;
    s32 kind;
    u32 address;
    s32 second_x;
    s32 second_y;
    u8 *record;
    Fields *fields;
    u8 *value;

    record = arg0;
    values = *(Bytes4 *)D_800200A0;
    i = 0;
    first_x = 5;
    first_y = first_x;
    kind = 0x48;
    address = 0x104058;
    second_x = 6;
    second_y = second_x;
    fields = (Fields *)(record + 4);
    do {
        fields->x = first_x;
        fields->y = first_y;
        ((u8 *)fields)[-3] = kind;
        fields->address = address;
        fields++;
        value = &values.bytes[i];
        i++;
        record[0] = *value;
        record += 12;
        fields->x = second_x;
        fields->y = second_y;
        ((u8 *)fields)[-3] = kind;
        fields->address = address;
        fields++;
        record[0] = *value;
        record += 12;
    } while (i < 4);
    record[-24] |= 0x80;
    return record;
}
