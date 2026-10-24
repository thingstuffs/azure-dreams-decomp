#include "frontend/card/service.h"
#include "common.h"
#include "frontend/card.h"

/* Calls card_dev_run_slot_operation with argument 5. */
void card_dev_run_temp_slot_operation(void) {
    card_dev_run_slot_operation(5);
}
