#include "frontend/card/slot_details.h"
#include "common.h"
#include "town/scene.h"

/* Stores the node that owns this card information panel. */
void write_value_through_pointer(CardDevSlotDetails *panel, ObjectNodeHeader *owner) { panel->owner = owner; }
