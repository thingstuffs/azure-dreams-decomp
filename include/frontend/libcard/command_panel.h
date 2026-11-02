#ifndef FRONTEND_LIBCARD_COMMAND_PANEL_H
#define FRONTEND_LIBCARD_COMMAND_PANEL_H
#include "frontend/libcard/display_node.h"
/* Observed command-panel prefix. Each column has four pointer slots; these
 * callbacks access the first three. The constructor owns a larger buffer. */
typedef struct CardCommandPanelBody {
    u8 pad_00[0x7C];
    u8 row_offsets[3];
    u8 pad_7F;
    s32 animation_frames;
    s32 animation_tick;
    s32 selected_entry;
    s32 previous_selection;
    u8 pad_90[0x110];
    CardMenuDisplayNode *heading;
    CardMenuDisplayNode *marker;
    CardMenuDisplayNode *left[4];
    CardMenuDisplayNode *right[4];
    CardMenuDisplayNode *highlight[4];
    CardMenuDisplayNode *labels[4];
} CardCommandPanelBody;
#endif
