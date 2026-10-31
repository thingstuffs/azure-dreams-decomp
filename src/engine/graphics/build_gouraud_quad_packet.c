#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "shared/gpu_packets.h"
#include "engine/graphics.h"

typedef struct S_8004BDDC_0 {
    u8 pad_00[0x3];
    s8 unk_03;
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 unk_07;
    s16 unk_08;
    s16 unk_0A;
    u8 unk_0C;
    u8 unk_0D;
    u16 unk_0E;
    union { struct { s32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_10;   /* overlapping accesses */
    union {
        struct { s32 v; } at00;
        struct { s16 v; } at00u;
        struct { u8 pad[0x2]; s16 v; } at02;
    } unk_14;   /* overlapping accesses */
    union {
        struct { s32 v; } at00;
        struct { s8 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
        struct { u8 pad[0x2]; u16 v; } at02;
    } unk_18;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_1C;   /* overlapping accesses */
    union {
        struct { s32 v; } at00;
        struct { s16 v; } at00u;
        struct { u8 pad[0x2]; s16 v; } at02;
    } unk_20;   /* overlapping accesses */
    u8 unk_24;
    s8 unk_25;
    u8 pad_26[0x2];
    union { struct { s32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_28;   /* overlapping accesses */
    s32 unk_2C;
    s8 unk_30;
    s8 unk_31;
} S_8004BDDC_0;   /* arg2 in build_gouraud_quad_packet */

typedef struct S_8004BDDC_1 {
    u8 pad_00[0x1];
    u8 unk_01;
    u8 pad_02[0x2];
    u16 unk_04;
    u16 unk_06;
    u8 unk_08;
    u8 unk_09;
    u8 unk_0A;
    u8 unk_0B;
} S_8004BDDC_1;   /* arg4 in build_gouraud_quad_packet */

   /* Build a textured Gouraud quad packet with tinted vertex colors and adjusted UV bounds. */
void *build_gouraud_quad_packet(void *tint_a, void *tint_b, void *packet_arg, void *record, void *command_arg) {
    S_8004BDDC_1 *command = command_arg;
    S_8004BDDC_0 *packet = packet_arg;
    PacketColorWords *color_record;
    s8 u_end;
    s8 v_end;
    void *color_1;
    void *color_2;
    void *color_3;
    void *color_0;

    packet->unk_2C = (s32) packet->unk_20.at00.v;
    packet->unk_20.at00.v = (s32) packet->unk_18.at00.v;
    packet->unk_14.at00.v = (s32) packet->unk_10.at00.v;
    color_record = record;
    if ((command->unk_08 + command->unk_0A) >= 0x100) {
        command->unk_0A--;
    }
    if ((command->unk_09 + command->unk_0B) >= 0x100) {
        command->unk_0B--;
    }
    color_record = (void *) ((u8 *) color_record + 0xC);
    color_1 = packet_arg + 0x10;
    packet->unk_10.at00.v = (s32) color_record->unk_00;
    packet->unk_04 = (u8) packet->unk_10.at03.v;
    multiply_rgb_tint_saturated(color_1, tint_a);
    multiply_rgb_tint_saturated(color_1, tint_b);
    color_2 = packet_arg + 0x1C;
    packet->unk_1C.at00.v = (s32) color_record->unk_04;
    packet->unk_05 = (u8) packet->unk_1C.at03.v;
    multiply_rgb_tint_saturated(color_2, tint_a);
    multiply_rgb_tint_saturated(color_2, tint_b);
    color_3 = packet_arg + 0x28;
    packet->unk_28.at00.v = (s32) color_record->unk_08;
    packet->unk_06 = (u8) packet->unk_28.at03.v;
    multiply_rgb_tint_saturated(color_3, tint_a);
    multiply_rgb_tint_saturated(color_3, tint_b);
    color_0 = packet_arg + 4;
    multiply_rgb_tint_saturated(color_0, tint_a);
    multiply_rgb_tint_saturated(color_0, tint_b);
    packet->unk_03 = 0xC;
    packet->unk_07 = (u8) command->unk_01;
    packet->unk_0C = (u8) command->unk_08;
    packet->unk_0E = (u16) command->unk_06;
    packet->unk_0D = (u8) command->unk_09;
    if ((packet->unk_14.at00u.v < packet->unk_08) ||
        (packet->unk_08 != packet->unk_20.at00u.v)) {
        command->unk_0A = (u8) (command->unk_0A - 1);
    }
    u_end = command->unk_08 + command->unk_0A;
    packet->unk_30 = u_end;
    packet->unk_18.at00u.v = u_end;
    packet->unk_18.at01.v = (u8) command->unk_09;
    packet->unk_18.at02.v = (u16) command->unk_04;
    packet->unk_24 = (u8) command->unk_08;
    if ((packet->unk_20.at02.v < packet->unk_0A) ||
        (packet->unk_0A != packet->unk_14.at02.v)) {
        command->unk_0B = (u8) (command->unk_0B - 1);
    }
    v_end = command->unk_09 + command->unk_0B;
    packet->unk_31 = v_end;
    packet->unk_25 = v_end;
    return color_record;
}
