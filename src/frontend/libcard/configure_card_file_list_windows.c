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
    void *field0;
    WinSub *field4;
} WinObj;

/* Initialize window data and configure the four window objects. */
void configure_card_file_list_windows(CardFileListPanel *window_state) {
    void *window_data;
    WinObj *window;

    window_data = window_state->panel_packets;
    card_boot_build_shaded_panel_packets(window_data, 0xF8, 0x48);

    window = (WinObj *)window_state->pointers[3];
    window->field4->w = 0xA0;
    window->field4->h = 0xB0;
    window->field0 = window_data;

    window = (WinObj *)window_state->pointers[0];
    window->field4->w = 0x60;
    window->field4->h = 0x88;
    window->field0 = &D_80079054;

    window = (WinObj *)window_state->pointers[1];
    window->field4->w = 0xD0;
    window->field4->h = 0x88;
    window->field0 = &D_800790B4;

    window = (WinObj *)window_state->pointers[2];
    window->field4->w = 0x20;
    window->field4->h = 0x88;
    window->field0 = &D_80079114;
}
