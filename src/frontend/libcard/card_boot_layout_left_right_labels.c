#include "common.h"
#include "shared/widget_views.h"
#include "m2c_compat.h"
#include "frontend/libcard.h"
#include "main/data.h"
#include "frontend/libcard/message.h"

typedef struct S_80026C94_0 {
    u8 pad_00[0x60];
    void * unk_60;
    void * unk_64;
} S_80026C94_0;   /* arg0 in card_boot_layout_left_right_labels */

/* Set the positions and data pointers for the left and right entries. */
void card_boot_layout_left_right_labels(S_80026C94_0 *owner) {
    CardCallbackState *left_entry;

    left_entry = owner->unk_60;
    (((CardDisplayNode *)left_entry)->block)->fields.x = 0x40;
    (((CardDisplayNode *)left_entry)->block)->fields.y = 0x20;
    left_entry->callback = &D_80028418;
    left_entry = (owner->unk_64);
    (((CardDisplayNode *)left_entry)->block)->fields.x = 0xC0;
    (((CardDisplayNode *)left_entry)->block)->fields.y = 0x20;
    left_entry->callback = &D_80028430;
}
