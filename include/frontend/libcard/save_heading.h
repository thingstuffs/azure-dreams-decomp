#ifndef FRONTEND_LIBCARD_SAVE_HEADING_H
#define FRONTEND_LIBCARD_SAVE_HEADING_H
#include "frontend/libcard/display_node.h"
/* Four display pointers initialized in the 0x180-byte save-heading body, and the two text buffers that
 * card_boot_bind_save_heading points the value and heading nodes at. */
typedef struct CardSaveHeadingDisplayPrefix {
    u8 pad_00[0x4];
    u8 value_text[0x78]; /* value node payload; card_boot_initialize_save_heading_layout fills it through func_80027080 */
    u8 heading_text[0x74]; /* heading node payload; format_save_heading_text decodes the save heading here */
    CardMenuDisplayNode *left;
    CardMenuDisplayNode *right;
    CardMenuDisplayNode *value;
    CardMenuDisplayNode *heading;
} CardSaveHeadingDisplayPrefix;
#endif
