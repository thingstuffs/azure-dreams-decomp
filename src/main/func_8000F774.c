#include "common.h"


typedef struct Bytes4 { u8 bytes[4]; } Bytes4;
typedef struct Bytes24 { u8 bytes[24]; } Bytes24;
extern u8 D_800200A0[];
extern u8 D_80027F48[];
extern s32 D_800280B4[];


typedef struct S_80022774_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0xC];
    s32 unk_18;
    s32 unk_1C;
} S_80022774_0;   /* arg1 in func_80022774 */

void *func_80022774(void *arg0, void *arg1)
{
    Bytes4 values;
    s32 i;
    u32 height;
    u32 height17;
    u32 width;
    s32 width_plus_10;
    u32 second_y;
    u32 fill;
    s32 index;
    u8 tag;
    u32 tex;
    unsigned long table_base;
    unsigned long table_offset;
    u8 *record;
    u8 *fields;
    u8 *value;

    record = arg0;
    values = *(Bytes4 *)D_800200A0;
    i = 0;
    tag = 0x48;
    tex = 0x104058;
    table_base = (unsigned long)D_800280B4;
    table_base += (unsigned long)record;
    index = ((S_80022774_0 *)arg1)->unk_08;
    table_offset = (index * 0x18 - (unsigned long)record) + table_base;
    height = *(u8 *)(table_offset + 0x17);
    width = *(u8 *)(table_offset + 0x16) * 4;
    height17 = height * 0x11 + height - height;
    width_plus_10 = width + 10;
    ((S_80022774_0 *)arg1)->unk_18 = width + 8;
    ((S_80022774_0 *)arg1)->unk_1C = height17 + 8;
    fields = record + 11;
    fields += height17;
    fields -= height17;
    fields += height17;
    fields -= height17;
    do {
        fields[-1] = (width + 8) >> 1;
        fields[0] = (height17 + 8) >> 1;
        fields[-10] = tag;
        (*(u32 *)((u8 *)fields + (-7))) = tex;
        fields += 12;
        fill = 0x90D0E0;
        value = &values.bytes[i];
        i++;
        record[0] = *value;
        record += 12;
        fields[-1] = width_plus_10 / 2;
        second_y = height17 + 10;
        second_y &= 0xFFFF;
        fields[0] = second_y >> 1;
        fields[-10] = tag;
        (*(u32 *)((u8 *)fields + (-7))) = tex;
        fields += 12;
        record[0] = *value;
        record += 12;
        *(Bytes24 *)record = *(Bytes24 *)D_80027F48;
        (*(u32 *)((u8 *)fields + (-7))) = fill;
        (*(u32 *)((u8 *)fields + (1))) = fill;
        (*(u32 *)((u8 *)fields + (5))) = fill;
        (*(u32 *)((u8 *)fields + (9))) = fill;
        fields[-1] = (width + 8) >> 1;
        fields[0] = (height17 + 8) >> 1;
        record[0] = *value;
        fields += 24;
        record += 24;
        fill = 0;
    } while (i < 4);
    record[-24] |= 0x80;
    return record;
}
