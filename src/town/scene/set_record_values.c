#include "frontend/card/server_imports.h"
#include "frontend/libcard/card_chooser.h"

/* Retain the request node and selector read by the card chooser. */
void set_record_values(CardChooserBody *menu, struct ObjectNodeHeader *request, s32 mode) {
    menu->request = request;
    menu->mode = mode;
}
