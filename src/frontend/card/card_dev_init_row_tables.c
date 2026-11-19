#include "common.h"
#include "m2c_compat.h"
#include "frontend/card.h"
#include "frontend/card/command_panel.h"
#include "main/data.h"
#include "frontend/card/server_imports.h"


/* Initializes an object's value and four sets of shared and per-entry pointers. */
void card_dev_init_row_tables(CardDevCommandPanel *panel) {
    s32 slot_index;
    void *shared_data_a;
    void *shared_data_b;
    void *object_data;

    panel->marker->payload.word = func_80056F14(4);
    panel->resource_entry->payload.data = &D_80082FF4;
    slot_index = 0;
    shared_data_a = &D_80083060;
    shared_data_b = &D_8008306C;
    object_data = panel->highlight_packets;
    for (; slot_index < 4; slot_index++) {
        panel->left[slot_index]->payload.data = shared_data_a;
        panel->right[slot_index]->payload.data = shared_data_b;
        panel->middle[slot_index]->payload.data = object_data;
        panel->lower[slot_index]->payload.data = panel->labels[slot_index];
    }
}
