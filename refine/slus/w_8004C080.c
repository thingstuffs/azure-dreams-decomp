#include "common.h"

typedef struct S_8004C080_0 {
    u8 pad_00[0x1];
    u8 unk_01;
    u8 pad_02[0x2];
    union { struct { s32 v; } at00; struct { s16 v; } at00u; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 unk_08;
    u8 unk_09;
    u8 unk_0A;
    u8 unk_0B;
} S_8004C080_0;   /* command in func_8004C080 */

typedef struct S_8004C080_1 {
    u8 pad_00[0x3];
    s8 unk_03;
    union { struct { s32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_04;   /* overlapping accesses */
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    s32 unk_1C;
    s32 unk_20;
} S_8004C080_1;   /* packet in func_8004C080 */

typedef struct S_8004C080_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_8004C080_2;   /* record in func_8004C080 */



typedef struct Tint8004C080 {
    u8 r;
    u8 g;
    u8 b;
    u8 cd;
} Tint8004C080;

extern s32 func_8004C010(u8 *dst, Tint8004C080 *tint);
extern void *func_8004BDDC(Tint8004C080 *tint0, Tint8004C080 *tint1,
                           u8 *packet, void *record, u8 *command);
extern void SetTexWindow(void *packet, s16 *values);
extern void SetDrawMode(void *packet, s32 a1, s32 a2, s32 a3, s32 a4);
extern void *func_8004B954(Tint8004C080 *tint0, Tint8004C080 *tint1,
                           u8 *packet, void *record, u8 *command,
                           s32 *count, s32 mode);

/* Apply command colors or draw settings to a GPU packet and return the next record. */
void *func_8004C080(Tint8004C080 *tint0, Tint8004C080 *tint1,
                    u8 *packet, void *record, u8 *command, s32 *count)
{
    u8 opcode;
    s32 primitive_type;
    s32 length_or_code;
    s32 extended_type;
    u8 *packet_color;
    s16 tex_window[4];

    opcode = ((S_8004C080_0 *)command)->unk_01;
    primitive_type = opcode & 0xFC;

    if (primitive_type == 0x28) {
        packet_color = packet + 4;
        ((S_8004C080_1 *)packet)->unk_04.at00.v = ((S_8004C080_0 *)command)->unk_04.at00.v;
        func_8004C010(packet_color, tint0);
        func_8004C010(packet_color, tint1);
        ((S_8004C080_1 *)packet)->unk_03 = 5;
        ((S_8004C080_1 *)packet)->unk_0C = ((S_8004C080_1 *)packet)->unk_10;
        ((S_8004C080_1 *)packet)->unk_10 = ((S_8004C080_1 *)packet)->unk_18;
        ((S_8004C080_1 *)packet)->unk_14 = ((S_8004C080_1 *)packet)->unk_20;
        ((S_8004C080_1 *)packet)->unk_04.at03.v = ((S_8004C080_0 *)command)->unk_01;
        goto done;
    }

    if (primitive_type == 0x48) {
        packet_color = packet + 4;
        ((S_8004C080_1 *)packet)->unk_04.at00.v = ((S_8004C080_0 *)command)->unk_04.at00.v;
        func_8004C010(packet_color, tint0);
        func_8004C010(packet_color, tint1);
        ((S_8004C080_1 *)packet)->unk_03 = 5;
        ((S_8004C080_1 *)packet)->unk_14 = 0x55555555;
        ((S_8004C080_1 *)packet)->unk_04.at03.v = ((S_8004C080_0 *)command)->unk_01;
        ((S_8004C080_1 *)packet)->unk_08 = ((S_8004C080_1 *)packet)->unk_10;
        ((S_8004C080_1 *)packet)->unk_0C = ((S_8004C080_1 *)packet)->unk_20;
        ((S_8004C080_1 *)packet)->unk_10 = ((S_8004C080_1 *)packet)->unk_18;
        goto done;
    }

    if (primitive_type == 0x38) {
        packet_color = packet + 4;
        ((S_8004C080_1 *)packet)->unk_04.at00.v = ((S_8004C080_0 *)command)->unk_04.at00.v;
        func_8004C010(packet_color, tint0);
        func_8004C010(packet_color, tint1);
        record = (u8 *)record + 0xC;
        length_or_code = 8;
        packet_color = packet + 0xC;
        ((S_8004C080_1 *)packet)->unk_03 = length_or_code;
        ((S_8004C080_1 *)packet)->unk_04.at03.v = primitive_type;
        ((S_8004C080_1 *)packet)->unk_04.at03.v = ((S_8004C080_0 *)command)->unk_01;
        ((S_8004C080_1 *)packet)->unk_0C = ((S_8004C080_2 *)record)->unk_00;
        func_8004C010(packet_color, tint0);
        func_8004C010(packet_color, tint1);
        packet_color = packet + 0x14;
        ((S_8004C080_1 *)packet)->unk_14 = ((S_8004C080_2 *)record)->unk_04;
        func_8004C010(packet_color, tint0);
        func_8004C010(packet_color, tint1);
        packet_color = packet + 0x1C;
        ((S_8004C080_1 *)packet)->unk_1C = ((S_8004C080_2 *)record)->unk_08;
        func_8004C010(packet_color, tint0);
        func_8004C010(packet_color, tint1);
        goto done;
    }

    if (primitive_type == 0x3C) {
        record = func_8004BDDC(tint0, tint1, packet, record, command);
        goto done;
    }

    if (!(opcode & 0x80)) {
        goto done;
    }

    length_or_code = opcode & 0x7F;
    if (length_or_code == 0) {
        tex_window[0] = ((S_8004C080_0 *)command)->unk_08;
        tex_window[1] = ((S_8004C080_0 *)command)->unk_09;
        tex_window[2] = ((S_8004C080_0 *)command)->unk_0A + 1;
        tex_window[3] = ((S_8004C080_0 *)command)->unk_0B + 1;
        SetTexWindow(packet, tex_window);
        goto done;
    }

    extended_type = length_or_code & 0x7C;
    if (length_or_code == 1) {
        SetDrawMode(packet, 1, ((S_8004C080_0 *)command)->unk_04.at02.v,
                      ((S_8004C080_0 *)command)->unk_04.at00u.v, 0);
        goto done;
    }

    if (extended_type == 0x30) {
        record = func_8004B954(tint0, tint1, packet, record, command, count, 1);
        goto done;
    }
    if (extended_type == 0x20) {
        record = func_8004B954(tint0, tint1, packet, record, command, count, 0);
    }
done:
    return record;
}
