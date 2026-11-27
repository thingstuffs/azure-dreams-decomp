#include "common.h"
#include "frontend/libcard.h"
#include "frontend/libcard/message.h"
#include "main/data.h"

typedef struct {
    u8 pad[8];
    s16 w;
    s16 h;
} WinSub;

typedef struct {
    void *packet_data;
    WinSub *block;
} WinObj;

/* Initialize window data and configure the four window objects. */
void configure_card_file_list_windows(CardFileListPanel *window_state) {
    CardShadedPanelPackets *window_data;
    WinObj *window;

    window_data = &window_state->panel_packets;
    card_boot_build_shaded_panel_packets(window_data, 0xF8, 0x48);

    window = (WinObj *)window_state->pointers[3];
    window->block->w = 0xA0;
    window->block->h = 0xB0;
    window->packet_data = window_data;

    window = (WinObj *)window_state->pointers[0];
    window->block->w = 0x60;
    window->block->h = 0x88;
    window->packet_data = &D_80079054;

    window = (WinObj *)window_state->pointers[1];
    window->block->w = 0xD0;
    window->block->h = 0x88;
    window->packet_data = &D_800790B4;

    window = (WinObj *)window_state->pointers[2];
    window->block->w = 0x20;
    window->block->h = 0x88;
    window->packet_data = &D_80079114;
}
