#include "frontend/card/server_menu.h"
#include "common.h"
#include "frontend/card.h"

/* Store the load screen that created this panel. */
void card_sme_set_word(CardDevMenu4 *panel, struct CardDevLoadNode *owner) {
    panel->owner = owner;
}
