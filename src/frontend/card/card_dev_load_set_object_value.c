#include "common.h"
#include "m2c_compat.h"
#include "frontend/card.h"
#include "frontend/card/load.h"

/* Retain the request node for return to the card chooser. */
void card_dev_load_set_object_value(CardDevLoadSlotScreen *screen, struct ObjectNodeHeader *request) {
    screen->request = request;
}
