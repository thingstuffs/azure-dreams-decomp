#include "common.h"
#include "m2c_compat.h"
#include "frontend/card.h"
#include "frontend/card/command_panel.h"
#include "shared/object_node.h"

/* Saves and replaces the object's value, setting its control fields to 0 and 3. */
void card_dev_begin_value_transition(ObjectNodeHeader *object, s32 new_value) {
    s32 previous_value;

    if (object != NULL) {
        CardDevCommandPanel *panel = NODE_BODY(object);

        previous_value = panel->target_row;
        panel->frame = 0;
        panel->frames = 3;
        panel->target_row = new_value;
        panel->start_row = previous_value;
    }
}
