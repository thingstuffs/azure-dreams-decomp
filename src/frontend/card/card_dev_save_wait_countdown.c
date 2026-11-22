#include "common.h"
#include "frontend/card/save_operation.h"
#include "shared/object_node.h"
#include "m2c_compat.h"
#include "frontend/card.h"
#include "main/data.h"

/* Decrement the record's counter and replace its pointer when the counter becomes negative. */
void card_dev_save_wait_countdown(CardSaveOperationBody *menu) {
    s32 counter;

    counter = menu->countdown - 1;
    menu->countdown = counter;
    if (counter < 0) {
        NODE_HEADER(menu)->update_callback = &D_80405CB8;
    }
}
