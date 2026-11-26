#include "common.h"
#include "frontend/card.h"
#include "frontend/card/server_menu.h"
#include "frontend/card/server_imports.h"

/* Pass the words of slot-window entries 1-3 to the resident helper and clear them, then clear entry 4's word. */
void card_dev_clear_slot_window_words(CardDevMenu10 *window)
{
    s32 i;

    for (i = 0; i < 3; i++) {
        func_80051FBC(window->entries[i + 1]->display.payload.word);
        window->entries[i + 1]->display.payload.word = 0;
    }
    window->entries[4]->display.payload.word = 0;
}
