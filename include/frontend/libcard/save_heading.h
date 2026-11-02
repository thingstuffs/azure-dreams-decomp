#ifndef FRONTEND_LIBCARD_SAVE_HEADING_H
#define FRONTEND_LIBCARD_SAVE_HEADING_H
#include "frontend/libcard/display_node.h"
/* Four display pointers initialized in the 0x180-byte save-heading body. */
typedef struct CardSaveHeadingDisplayPrefix {
    u8 pad_00[0xF0];
    CardMenuDisplayNode *left;
    CardMenuDisplayNode *right;
    CardMenuDisplayNode *value;
    CardMenuDisplayNode *heading;
} CardSaveHeadingDisplayPrefix;
#endif
