#include "common.h"
#include "m2c_compat.h"
#include "frontend/libcard.h"
#include "frontend/libcard/message.h"
#include "main/data.h"

/* Initialize four graphics packets with shared colors and halved coordinates. */
void *card_boot_build_shaded_panel_packets(CardShadedPanelPackets *packets, u32 x, u32 y) {
    s32 packet_index;
    u8 *table_entry;
    CardShadedPanelQuad *quad;
    u8 *packet = (u8 *)packets;
    CardPanelBoundary *end;
    s8 opcode;
    s32 main_color;
    s32 dark_color;
    s32 half_x;
    u8 *packet_tags;

    packets->begin.opcode = 0x81;
    packets->begin.command_value = 0x20;
    packets->begin.end = 0;
    packet += sizeof(packets->begin);
    packet_index = 0;
    opcode = 0x38;
    main_color = 0x9CBCBC;
    dark_color = 0x8C9C9C;
    half_x = (s32) ((x >> 0x1F) + x) >> 1;
    x = (s32) ((y >> 0x1F) + y) >> 1;
    packet_tags = D_80027FD0;
    do {
        quad = (CardShadedPanelQuad *)packet;
        table_entry = (u8 *) (packet_index + (long)packet_tags);
        packet_index += 1;
        quad->opcode = opcode;
        quad->color0 = main_color;
        quad->color1 = main_color;
        quad->color2 = main_color;
        quad->color3 = dark_color;
        quad->half_width = half_x;
        quad->half_height = x;
        *packet = *table_entry;
        packet += sizeof(*quad);
    } while (packet_index < 4);
    end = (CardPanelBoundary *)packet;
    end->opcode = 0x81;
    end->command_value = 0x20;
    end->end = 1;
    end->id = 0x80;
    return end + 1;
}
