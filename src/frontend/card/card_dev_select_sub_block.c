#include "common.h"
#include "frontend/card.h"
#ifndef NULL
#define NULL 0
#endif
/* Point the object's two handler slots at one of two sub-blocks, chosen by a flag word. */
void card_dev_select_sub_block(CardBackgroundBody *object) {
    s32 *flag_ptr = object->selection_flag;
    if (flag_ptr != NULL) {
        s32 flag = *flag_ptr;
        if (flag != 0) {
            u8 *alt_block = object->selected_packets;
            object->entries[5].display.payload.data = NULL;
            object->entries[6].display.payload.data = alt_block;
            return;
        }
        object->entries[5].display.payload.data = object->alternate_packets;
        object->entries[6].display.payload.data = NULL;
    }
}
