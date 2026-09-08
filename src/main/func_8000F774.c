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

/* Builds four groups of display records and stores the padded layout dimensions. */
void *func_80022774(void *buffer, void *layout)
{
    Bytes4 record_flags;
    s32 group_index;
    u32 row_count;
    u32 height;
    u32 width;
    s32 outer_width;
    u32 outer_height;
    u32 fill_color;
    s32 entry_index;
    u8 record_tag;
    u32 texture_data;
    unsigned long table_sum;
    unsigned long entry_addr;
    u8 *record;
    u8 *dimensions;
    u8 *flags;

    record = buffer;
    record_flags = *(Bytes4 *)D_800200A0;
    group_index = 0;
    record_tag = 0x48;
    texture_data = 0x104058;
    table_sum = (unsigned long)D_800280B4;
    table_sum += (unsigned long)record;
    entry_index = ((S_80022774_0 *)layout)->unk_08;
    entry_addr = (entry_index * 0x18 - (unsigned long)record) + table_sum;
    row_count = *(u8 *)(entry_addr + 0x17);
    width = *(u8 *)(entry_addr + 0x16) * 4;
    height = row_count * 0x11 + row_count - row_count;
    outer_width = width + 10;
    ((S_80022774_0 *)layout)->unk_18 = width + 8;
    ((S_80022774_0 *)layout)->unk_1C = height + 8;
    dimensions = record + 11;
    dimensions += height;
    dimensions -= height;
    dimensions += height;
    dimensions -= height;
    do {
        dimensions[-1] = (width + 8) >> 1;
        dimensions[0] = (height + 8) >> 1;
        dimensions[-10] = record_tag;
        (*(u32 *)((u8 *)dimensions + (-7))) = texture_data;
        dimensions += 12;
        fill_color = 0x90D0E0;
        flags = &record_flags.bytes[group_index];
        group_index++;
        record[0] = *flags;
        record += 12;
        dimensions[-1] = outer_width / 2;
        outer_height = height + 10;
        outer_height &= 0xFFFF;
        dimensions[0] = outer_height >> 1;
        dimensions[-10] = record_tag;
        (*(u32 *)((u8 *)dimensions + (-7))) = texture_data;
        dimensions += 12;
        record[0] = *flags;
        record += 12;
        *(Bytes24 *)record = *(Bytes24 *)D_80027F48;
        (*(u32 *)((u8 *)dimensions + (-7))) = fill_color;
        (*(u32 *)((u8 *)dimensions + (1))) = fill_color;
        (*(u32 *)((u8 *)dimensions + (5))) = fill_color;
        (*(u32 *)((u8 *)dimensions + (9))) = fill_color;
        dimensions[-1] = (width + 8) >> 1;
        dimensions[0] = (height + 8) >> 1;
        record[0] = *flags;
        dimensions += 24;
        record += 24;
        fill_color = 0;
    } while (group_index < 4);
    record[-24] |= 0x80;
    return record;
}
