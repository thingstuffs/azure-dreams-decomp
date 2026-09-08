#include "common.h"
#include "m2c_compat.h"

typedef struct S_800242D8_0 {
    u8 unk_00;
    u8 unk_01;
    u8 pad_02[0x2];
    s16 unk_04;
    s16 unk_06;
} S_800242D8_0;   /* arg0 in func_800242D8 */

typedef struct S_800242D8_1_pre {
    s8 unk_00;
} S_800242D8_1_pre;   /* the 0x1 bytes before var_v1 in func_800242D8, addressed as var_v1[-1] */

typedef struct S_800242D8_1 {
    s8 unk_00;
} S_800242D8_1;   /* var_v1 in func_800242D8 */


__asm__(".set D_80027FD0, 0x80027FD0");
extern u8 D_80027FD0[];

/* Initialize four graphics packets with shared colors and halved coordinates. */
void *func_800242D8(u8 *packet, u32 x, u32 y) {
    s32 packet_index;
    u8 *table_entry;
    void *field_cursor;
    s8 opcode;
    s32 main_color;
    s32 dark_color;
    register u8 *packet_tags ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 half_x;
    s32 half_y;

    ((S_800242D8_0 *)packet)->unk_01 = 0x81;
    ((S_800242D8_0 *)packet)->unk_04 = 0x20;
    ((S_800242D8_0 *)packet)->unk_06 = 0;
    packet = packet + 0xC;
    packet_index = 0;
    opcode = 0x38;
    main_color = 0x9CBCBC;
    dark_color = 0x8C9C9C;
    half_x = (s32) ((x >> 0x1F) + x) >> 1;
    half_y = (s32) ((y >> 0x1F) + y) >> 1;
    __asm__("lui $2, %%hi(D_80027FD0)\n\taddiu %0, $2, %%lo(D_80027FD0)" : "=r"(packet_tags));
    field_cursor = packet + 0xB;
    do {
        table_entry = (u8 *) (packet_index + (s32) packet_tags);
        packet_index += 1;
        (*(s8 *)((u8 *)field_cursor + -0xA)) = opcode;
        (*(s32 *)((u8 *)field_cursor + -7)) = main_color;
        (*(s32 *)((u8 *)field_cursor + 1)) = main_color;
        (*(s32 *)((u8 *)field_cursor + 5)) = main_color;
        (*(s32 *)((u8 *)field_cursor + 9)) = dark_color;
        ((S_800242D8_1_pre *)field_cursor)[-1].unk_00 = half_x;
        ((S_800242D8_1 *)field_cursor)->unk_00 = half_y;
        field_cursor += 0x18;
        *packet = *table_entry;
        packet += 0x18;
    } while (packet_index < 4);
    ((S_800242D8_0 *)packet)->unk_01 = 0x81;
    ((S_800242D8_0 *)packet)->unk_04 = 0x20;
    ((S_800242D8_0 *)packet)->unk_06 = 1;
    ((S_800242D8_0 *)packet)->unk_00 = 0x80;
    return packet + 0xC;
}
