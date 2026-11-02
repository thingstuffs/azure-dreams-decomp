#ifndef FRONTEND_LIBCARD_DISPLAY_NODE_H
#define FRONTEND_LIBCARD_DISPLAY_NODE_H
#include "common.h"
#include "shared/menu_display.h"
/* Data/word payload prefix used by frontend display nodes. No stride or
 * complete allocation size is inferred from this view. */
typedef struct CardDetailDisplayNode {
    union { void *data; s32 word; } payload;
    MenuDisplayBlock *block;
} CardMenuDisplayNode;
typedef CardMenuDisplayNode CardDetailDisplayNode;
#endif
