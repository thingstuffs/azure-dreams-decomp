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
} S_80402A1C_0;   /* arg1 in func_80402A1C */

/* Builds four groups of drawing commands sized from the selected layout. */
void *func_80402A1C(void *buffer, S_80402A1C_0 *layout) {
    M2C_UNK command_ids;
    M2C_UNK ids_limit;
    s32 width_extent;
    s32 layout_offset;
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
    u8 *stack_end;

    write_ptr = (u8 *)buffer;
    memcpy(&command_ids, D_80400000 + 0x544, 4);
    do {
        opcode = 0x48;
    } while (0);
    shade = 0x101010;
    id_ptr = (u8 *)&command_ids;
    stack_end = (u8 *)&ids_limit;
    layout_offset = layout->unk_08 * 4;
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
            size_ptr[-1] = (u8)half_width;
            size_ptr[0] = (u8)half_height;
            size_ptr[-0xA] = (u8)opcode;
            *(u32 *)(size_ptr - 7) = shade;
            size_ptr += 0xC;
            write_ptr[0] = *id_ptr;
            write_ptr += 0xC;
            size_ptr[-1] = (u8)outer_half_width;
            size_ptr[0] = (u8)((u32)outer_height >> 1);
            size_ptr[-0xA] = (u8)opcode;
            *(u32 *)(size_ptr - 7) = shade;
            command_id = *id_ptr;
            size_ptr += 0xC;
            write_ptr[0] = command_id;
            write_ptr += 0xC;
            memcpy(write_ptr, D_80410000 - 0x7394, 0x18);
            *(u32 *)(size_ptr - 7) = 0x30BFC0;
            *(u32 *)(size_ptr + 1) = 0x30BFC0;
            *(u32 *)(size_ptr + 5) = 0x30BFC0;
            *(u32 *)(size_ptr + 9) = 0x30BFC0;
            size_ptr[-1] = (u8)half_width;
            size_ptr[0] = (u8)half_height;
            size_ptr += 0x18;
            command_id = *id_ptr;
            id_ptr += 1;
            write_ptr[0] = command_id;
            write_ptr += 0x18;
        } while (0);
    if ((s32)id_ptr < (s32)stack_end)
        goto loop;
    ASM_SET(stack_end);   /* MATCH pin: retail schedule: same instructions, different order without it */
    write_ptr[-0x18] |= 0x80;
    return write_ptr;
}
