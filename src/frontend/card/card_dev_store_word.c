#include "common.h"
#include "frontend/card.h"

/* Stores a value at the destination address. */
void card_dev_store_word(struct ObjectNodeHeader **dest, struct ObjectNodeHeader *owner) {
    *dest = owner;
}
