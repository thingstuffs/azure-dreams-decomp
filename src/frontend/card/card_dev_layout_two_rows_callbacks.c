#include "frontend/card/choice_panel.h"
#include "common.h"
#include "frontend/card.h"
#include "main/data.h"

/* Callback function addresses outside this overlay's own window (0x8000D000-
   0x80022000); they belong to code loaded elsewhere and are only ever stored
   as raw pointers here, never called, so bind them as absolute symbols
   (established .set idiom) rather than declaring undefined func_ externs. */

/* Initializes two child objects and assigns their callbacks. */
void card_dev_layout_two_rows_callbacks(CardDevChoicePanelPrefix *owner) {
    CardMenuDisplayNode *firstChild;

    firstChild = owner->children[0];
    firstChild->block->fields.x = 0x40;
    firstChild->block->fields.y = 0x20;
    firstChild->payload.data = &D_80409110;
    firstChild = owner->children[1];
    firstChild->block->fields.x = 0xC0;
    firstChild->block->fields.y = 0x20;
    firstChild->payload.data = &D_80409128;
}
