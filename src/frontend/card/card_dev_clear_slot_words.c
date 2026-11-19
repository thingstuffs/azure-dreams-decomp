#include "frontend/card/slot_details.h"
#include "common.h"
#include "frontend/card/server_imports.h"

/* Releases and clears the three text words, then clears the detail and icon words. */
void card_dev_clear_slot_words(CardDevSlotDetails *object)
{
    s32 i;

    for (i = 0; i < 3; i++) {
        func_80051FBC(object->entries[4 + i]->display.payload.word);
        object->entries[4 + i]->display.payload.word = 0;
    }
    for (i = 0; i < 4; i++) {
        object->entries[7 + i]->display.payload.word = 0;
    }
    for (i = 0; i < 10; i++) {
        object->entries[11 + i]->display.payload.word = 0;
    }
}
