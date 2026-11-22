#include "common.h"
#include "shared/object_node.h"
#include "m2c_compat.h"
#include "frontend/card.h"
#include "main/data.h"
#include "frontend/card/load.h"

/* Decrement the record counter and replace its pointer when the counter becomes negative. */
void card_dev_load_wait_countdown(CardDevLoadSlotScreen *screen) {
    s32 counter;

    counter = screen->countdown - 1;
    screen->countdown = counter;
    if (counter < 0) {
        NODE_HEADER(screen)->update_callback = finish_load_slot_check;
    }
}
