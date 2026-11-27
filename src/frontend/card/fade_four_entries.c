#include "common.h"
#include "frontend/card.h"
#include "frontend/card/message_display.h"
#include "frontend/card/server_imports.h"

/* Release the draw handle in each of the four text entries. */
void fade_four_entries(CardDevDialogDisplay *dialog) {
    MenuDisplayNode *item;
    s32 index = 0;

    do {
        item = dialog->entries[index];
        index++;
        func_80051FBC(item->draw_commands);
    } while (index < 4);
}
