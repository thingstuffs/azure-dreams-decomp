#include "frontend/card/server_menu.h"
#include "common.h"
#include "frontend/card.h"
#include "frontend/card/server_imports.h"


/* Pass the object's referenced value to func_80051FBC. */
void card_sme_fade_entry(CardDevMenu4 *panel) {
    func_80051FBC(panel->entries[3]->display.payload.word);
}
