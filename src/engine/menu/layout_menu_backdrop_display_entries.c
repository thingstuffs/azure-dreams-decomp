#include "common.h"
#include "engine/menu.h"

/* Initialize seven slots with coordinate pairs and pointers to embedded buffers. */
void layout_menu_backdrop_display_entries(SevenEntryMenuBackdropBody *host)
{
    SevenEntryMenuBackdropEntry *slot;
    void *shared_buffer;
    s16 right_x;
    s16 bottom_y;

    slot = host->view.layout.entries[0];
    slot->coordinates->x = 6;
    slot->coordinates->y = 0x10;
    slot->buffer = (u8 *)host + 8;

    slot = host->view.layout.entries[5];
    slot->coordinates->x = 0;
    slot->coordinates->y = 0;
    slot->buffer = (u8 *)host + 0x80;

    slot = host->view.layout.entries[6];
    slot->coordinates->x = 0x68;
    slot->coordinates->y = 0;
    slot->buffer = (u8 *)host + 0xF8;

    slot = host->view.layout.entries[1];
    right_x = 0xA0;
    bottom_y = 0x70;
    slot->coordinates->x = right_x;
    shared_buffer = (u8 *)host + 0x170;
    slot->coordinates->y = bottom_y;
    slot->buffer = shared_buffer;

    slot = host->view.layout.entries[2];
    slot->coordinates->x = 0;
    slot->coordinates->y = bottom_y;
    slot->buffer = shared_buffer;

    slot = host->view.layout.entries[3];
    slot->coordinates->x = right_x;
    slot->coordinates->y = 0;
    slot->buffer = shared_buffer;

    slot = host->view.layout.entries[4];
    slot->coordinates->x = 0;
    slot->coordinates->y = 0;
    slot->buffer = shared_buffer;
}
