#include "frontend/card.h"
#include "frontend/libcard/card_chooser.h"

/* Retain the request node and selector read by the card chooser. */
void card_dev_set_record_fields(CardChooserBody *menu, struct ObjectNodeHeader *request, s32 mode) {
    menu->request = request;
    menu->mode = mode;
}
