#include "common.h"
#include "m2c_compat.h"

extern u8 D_80410000[];
extern u8 D_80400000[];
extern u8 D_80408ADC[];

typedef struct S_80402A1C_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0xC];
    u32 unk_18;
    u32 unk_1C;
} S_80402A1C_0;   /* arg1 in card_boot_build_four_layout_command_groups */

typedef struct LayoutCommand {
    u8 id;
    u8 opcode;
    u8 pad_02[2];
    u32 shade;
    u8 pad_08[2];
    u8 half_width;
    u8 half_height;
} LayoutCommand;

typedef struct LayoutQuadColors {
    u8 pad_00[4];
    u32 first;
    u8 pad_08[4];
    u32 second;
    u32 third;
    u32 fourth;
} LayoutQuadColors;

/* Builds four groups of drawing commands sized from the selected layout. */
void *card_boot_build_four_layout_command_groups(void *buffer, S_80402A1C_0 *layout) {
    M2C_UNK command_ids;
    M2C_UNK ids_limit;
    s32 width_extent;
    s32 layout_offset;
    s32 layout_index;
    s32 height_extent;
    s32 outer_height;
    u32 height;
    u32 width;
    u32 half_height;
    u32 half_width;
    s32 outer_half_width;
    u32 opcode;
    u32 shade;
    u8 *id_ptr;
    u8 command_id;
    u8 *size_ptr;
    u8 *write_ptr;
    u8 * stack_end;

    write_ptr = (u8 *)buffer;
    memcpy(&command_ids, D_80400000 + 0x544, 4);
    do {
        opcode = 0x48;
        shade = 0x101010;
        id_ptr = (u8 *)&command_ids;
        layout_index = layout->unk_08;
        stack_end = (u8 *)&ids_limit;
    } while (0);
    layout_offset = layout_index * 4;
    size_ptr = write_ptr + 0xB;
    width_extent = D_80408ADC[layout_offset] * 0xC;
    width = width_extent + 8;
    height_extent = D_80408ADC[layout_offset + 1] * 0x11;
    half_width = width >> 1;
    layout->unk_18 = width;
    height = height_extent + 8;
    half_height = height >> 1;
    width_extent += 0xA;
    outer_half_width = (s32)width_extent >> 1;
    do {
        do {
            outer_height = height_extent + 0xA;
        } while (0);
    } while (0);
    layout->unk_1C = height;
loop:
    do {
        ((LayoutCommand *)(size_ptr - 0xB))->half_width = (u8)half_width;
        ((LayoutCommand *)(size_ptr - 0xB))->half_height = (u8)half_height;
        ((LayoutCommand *)(size_ptr - 0xB))->opcode = (u8)opcode;
        ((LayoutCommand *)(size_ptr - 0xB))->shade = shade;
        size_ptr += 0xC;
        ((LayoutCommand *)write_ptr)->id = *id_ptr;
        write_ptr += 0xC;
        ((LayoutCommand *)(size_ptr - 0xB))->half_width = (u8)outer_half_width;
        ((LayoutCommand *)(size_ptr - 0xB))->half_height = (u8)((u32)outer_height >> 1);
        ((LayoutCommand *)(size_ptr - 0xB))->opcode = (u8)opcode;
        ((LayoutCommand *)(size_ptr - 0xB))->shade = shade;
        command_id = *id_ptr;
        size_ptr += 0xC;
        ((LayoutCommand *)write_ptr)->id = command_id;
        write_ptr += 0xC;
        memcpy(write_ptr, D_80410000 - 0x7394, 0x18);
        ((LayoutCommand *)(size_ptr - 0xB))->shade = 0x30BFC0;
        ((LayoutQuadColors *)(size_ptr - 0xB))->second = 0x30BFC0;
        ((LayoutQuadColors *)(size_ptr - 0xB))->third = 0x30BFC0;
        ((LayoutQuadColors *)(size_ptr - 0xB))->fourth = 0x30BFC0;
        ((LayoutCommand *)(size_ptr - 0xB))->half_width = (u8)half_width;
        ((LayoutCommand *)(size_ptr - 0xB))->half_height = (u8)half_height;
        size_ptr += 0x18;
        command_id = *id_ptr;
        id_ptr += 1;
        ((LayoutCommand *)write_ptr)->id = command_id;
        write_ptr += 0x18;
    } while (0);
    if ((s32)id_ptr < (s32)stack_end)
        goto loop;
    ((LayoutCommand *)(write_ptr - 0x18))->id |= 0x80;
    return write_ptr;
}
