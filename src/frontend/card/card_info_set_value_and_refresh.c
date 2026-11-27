#include "frontend/card/slot_details.h"
#include "common.h"
#include "frontend/card.h"
void card_dev_clear_slot_words(CardDevSlotDetails *panel);

/* Store the value and process embedded data when the object exists. */
void card_info_set_value_and_refresh(ObjectNodeHeader *object, s32 value) {
    CardDevSlotDetails *embedded_data;

    if (object != 0) {
        embedded_data = NODE_BODY(object);
        embedded_data->selected_slot = value;
        card_dev_clear_slot_words(embedded_data);
        select_memory_task_exit(embedded_data);
    }
}
