#include "common.h"
#include "frontend/card/slot_marker.h"
#include "frontend/card.h"

/* Clears the ten values referenced by the pointer array at offset 0x1D8. */
void card_dev_clear_ten_values(CardDevMenu10 *window) {
    s32 index;

    index = 0;
    do {
        window->entries[index]->display.payload.word = 0;
    } while (++index < 10);
}
