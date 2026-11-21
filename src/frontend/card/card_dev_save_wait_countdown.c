#include "common.h"
#include "shared/widget_views.h"
#include "shared/object_node.h"
#include "m2c_compat.h"
#include "frontend/card.h"
#include "frontend/card/save_operation.h"
#include "main/data.h"

/* Decrement the record's counter and replace its pointer when the counter becomes negative. */
void card_dev_save_wait_countdown(void *record_data) {
    CardSaveOperationBody *state = record_data;
    s32 counter;

    counter = state->countdown - 1;
    state->countdown = counter;
    if (counter < 0) {
        NODE_HEADER(record_data)->update_callback = &D_80405CB8;
    }
}
