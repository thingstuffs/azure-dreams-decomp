#include "common.h"
#include "frontend/card.h"

/* Stores a value at the destination. */
void card_background_set_word(CardBackgroundBody *object, ObjectNodeHeader *owner) {
    object->owner = owner;
}
