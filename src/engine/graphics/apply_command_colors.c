#include "common.h"
#include "shared/gpu_packets.h"
#include "engine/graphics.h"
#include "sdk/libgpu.h"

typedef struct S_8004C080_0 {
    u8 pad_00[0x1];
    u8 unk_01;
    u8 pad_02[0x2];
    union {
        struct { s32 v; } at00;
        struct { s16 v; } at00u;
        struct { u8 pad[0x2]; u16 v; } at02;
    } unk_04;   /* overlapping accesses */
    u8 unk_08;
    u8 unk_09;
    u8 unk_0A;
    u8 unk_0B;
} S_8004C080_0;   /* command in apply_command_colors */

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
} S_8004C080_1;   /* packet in apply_command_colors */

   /* record in apply_command_colors */




extern void SetTexWindow(void *packet, s16 *values);

/* Apply command colors or draw settings to a GPU packet and return the next record. */
void *apply_command_colors(void *tint0, void *tint1,
                    u8 *packet_arg, void *record, u8 *command_arg, s32 *count)
{
    S_8004C080_0 *command = command_arg;
    S_8004C080_1 *packet = packet_arg;
    u8 opcode;
    s32 primitive_type;
    s32 length_or_code;
    s32 extended_type;
    u8 *packet_color;
    s16 tex_window[4];

    opcode = command->unk_01;
    primitive_type = opcode & 0xFC;

    if (primitive_type == 0x28) {
        packet_color = packet_arg + 4;
        packet->unk_04.at00.v = command->unk_04.at00.v;
        multiply_rgb_tint_saturated(packet_color, tint0);
        multiply_rgb_tint_saturated(packet_color, tint1);
        packet->unk_03 = 5;
        packet->unk_0C = packet->unk_10;
        packet->unk_10 = packet->unk_18;
        packet->unk_14 = packet->unk_20;
        packet->unk_04.at03.v = command->unk_01;
    } else if (primitive_type == 0x48) {
        packet_color = packet_arg + 4;
        packet->unk_04.at00.v = command->unk_04.at00.v;
        multiply_rgb_tint_saturated(packet_color, tint0);
        multiply_rgb_tint_saturated(packet_color, tint1);
        packet->unk_03 = 5;
        packet->unk_14 = 0x55555555;
        packet->unk_04.at03.v = command->unk_01;
        packet->unk_08 = packet->unk_10;
        packet->unk_0C = packet->unk_20;
        packet->unk_10 = packet->unk_18;
    } else if (primitive_type == 0x38) {
        packet_color = packet_arg + 4;
        packet->unk_04.at00.v = command->unk_04.at00.v;
        multiply_rgb_tint_saturated(packet_color, tint0);
        multiply_rgb_tint_saturated(packet_color, tint1);
        record = (u8 *)record + 0xC;
        length_or_code = 8;
        packet_color = packet_arg + 0xC;
        packet->unk_03 = length_or_code;
        packet->unk_04.at03.v = primitive_type;
        packet->unk_04.at03.v = command->unk_01;
        packet->unk_0C = ((PacketColorWords *)record)->unk_00;
        multiply_rgb_tint_saturated(packet_color, tint0);
        multiply_rgb_tint_saturated(packet_color, tint1);
        packet_color = packet_arg + 0x14;
        packet->unk_14 = ((PacketColorWords *)record)->unk_04;
        multiply_rgb_tint_saturated(packet_color, tint0);
        multiply_rgb_tint_saturated(packet_color, tint1);
        packet_color = packet_arg + 0x1C;
        packet->unk_1C = ((PacketColorWords *)record)->unk_08;
        multiply_rgb_tint_saturated(packet_color, tint0);
        multiply_rgb_tint_saturated(packet_color, tint1);
        return record;
    } else if (primitive_type == 0x3C) {
        record = build_gouraud_quad_packet(tint0, tint1, packet, record, command);
    } else if (!(opcode & 0x80)) {
        return record;
    } else {
        length_or_code = opcode & 0x7F;
        if (length_or_code == 0) {
            tex_window[0] = command->unk_08;
            tex_window[1] = command->unk_09;
            tex_window[2] = command->unk_0A + 1;
            tex_window[3] = command->unk_0B + 1;
            SetTexWindow(packet, tex_window);
        } else {
            extended_type = length_or_code & 0x7C;
            if (length_or_code == 1) {
                SetDrawMode(packet, 1, command->unk_04.at02.v,
                            command->unk_04.at00u.v, 0);
            } else if (extended_type == 0x30) {
                record = build_elliptical_triangle_fan(tint0, tint1, packet, record, command, count, 1);
            } else if (extended_type == 0x20) {
                record = build_elliptical_triangle_fan(tint0, tint1, packet, record, command, count, 0);
            }
        }
    }
    return record;
}
