#include "common.h"
#include "frontend/card/command_panel.h"
#include "frontend/card.h"

/* Retain the node that owns the command panel. */
void card_dev_set_word(CardDevCommandPanel *panel, struct ObjectNodeHeader *owner) {
    panel->owner = owner;
}
