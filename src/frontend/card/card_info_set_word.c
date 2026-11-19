#include "frontend/card/slot_details.h"
#include "common.h"
#include "frontend/card.h"

/* Stores the node that owns this card information panel. */
void card_info_set_word(CardDevSlotDetails *panel, ObjectNodeHeader *owner) {
    panel->owner = owner;
}
