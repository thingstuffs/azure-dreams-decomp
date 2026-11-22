#include "common.h"
#include "frontend/card/save_operation.h"
#include "frontend/card.h"


/* Invoke card_dev_set_object_value. */
void card_dev_run_init_hook(CardSaveOperationBody *menu, struct ObjectNodeHeader *request) {
    card_dev_set_object_value(menu, request);
}
