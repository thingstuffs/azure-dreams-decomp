#ifndef FRONTEND_LIBCARD_COMMAND_PANEL_H
#define FRONTEND_LIBCARD_COMMAND_PANEL_H
#include "frontend/libcard/display_node.h"
/* Observed command-panel prefix. Each column has four pointer slots; these
 * callbacks access the first three. The constructor owns a larger buffer. */
typedef struct CardCommandPanelBody {
    struct ObjectNodeHeader *owner;
    u8 highlight_packets[0x78];
    u8 row_offsets[3];
    u8 pad_7F;
    s32 animation_frames;
    s32 animation_tick;
    s32 selected_entry;
    s32 previous_selection;
    u8 label_text[3][0x48];
    MenuDisplayBlock display_block;
    DisplayPositionWords display_vector;
    DisplayPositionWords node_vector;
    MenuDisplayNode display;
    CardMenuDisplayNode *heading;
    CardMenuDisplayNode *marker;
    CardMenuDisplayNode *left[4];
    CardMenuDisplayNode *right[4];
    CardMenuDisplayNode *highlight[4];
    CardMenuDisplayNode *labels[4];
} CardCommandPanelBody;
#endif
