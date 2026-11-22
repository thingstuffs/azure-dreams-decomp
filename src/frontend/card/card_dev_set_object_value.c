#include "common.h"
#include "frontend/card/save_operation.h"
#include "frontend/card.h"

/* Retain the request node while the save menu is active. */
void card_dev_set_object_value(CardSaveOperationBody *menu, struct ObjectNodeHeader *request) {
    menu->request = request;
}
