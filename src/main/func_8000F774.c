#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef struct Bytes4 { u8 bytes[4]; } Bytes4;
typedef struct Bytes24 { u8 bytes[24]; } Bytes24;
extern u8 D_800200A0[];
extern u8 D_80027F48[];
extern s32 D_800280B4[];

void *func_80022774(void *arg0, void *arg1)
{
    Bytes4 values;
    s32 i;
    u32 height;
    u32 width;
    u32 first_x;
    u32 first_y;
    s32 width_plus_10;
    u32 height_plus_10;
    u32 fill;
    s32 index;
    unsigned long table_base;
    unsigned long table_offset;
    u8 *record;
    u8 *fields;
    u8 *value;

    record = arg0;
    values = *(Bytes4 *)D_800200A0;
    i = 0;
    table_base = (unsigned long)D_800280B4;
    index = FIELD(arg1, s32, 8);
    table_offset = table_base + index * 0x18;
    width = *(u8 *)(table_offset + 0x16) * 4;
    first_x = (width + 8) >> 1;
    height = *(u8 *)(table_offset + 0x17) * 0x11;
    first_y = (height + 8) >> 1;
    width_plus_10 = width + 10;
    height_plus_10 = height + 10;
    height_plus_10 += width;
    height_plus_10 -= width;
    FIELD(arg1, s32, 0x18) = width + 8;
    FIELD(arg1, s32, 0x1C) = height + 8;
    fields = record + 11;
    do {
        fields[-1] = first_x;
        fields[0] = first_y;
        fields[-10] = 0x48;
        FIELD(fields, u32, -7) = 0x104058;
        fields += 12;
        value = &values.bytes[i];
        i++;
        record[0] = *value;
        record += 12;
        fields[-1] = width_plus_10 / 2;
        fields[0] = height_plus_10 >> 1;
        fields[-10] = 0x48;
        FIELD(fields, u32, -7) = 0x104058;
        fields += 12;
        record[0] = *value;
        record += 12;
        *(Bytes24 *)record = *(Bytes24 *)D_80027F48;
        fill = 0x90D0E0;
        FIELD(fields, u32, -7) = fill;
        FIELD(fields, u32, 1) = fill;
        FIELD(fields, u32, 5) = fill;
        FIELD(fields, u32, 9) = fill;
        fields[-1] = first_x;
        fields[0] = first_y;
        record[0] = *value;
        fields += 24;
        record += 24;
        fill = 0;
    } while (i < 4);
    record[-24] |= 0x80;
    return record;
}
