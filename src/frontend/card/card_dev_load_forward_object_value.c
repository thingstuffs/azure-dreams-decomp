#include "common.h"
#include "m2c_compat.h"
#include "frontend/card.h"
#include "frontend/card/load.h"


/* Pass the load screen and request to its initializer. */
void card_dev_load_forward_object_value(CardDevLoadSlotScreen *screen, struct ObjectNodeHeader *request) {
    card_dev_load_set_object_value(screen, request);
}
