#include "frontend/card/server_imports.h"
#include "frontend/card/choice_panel.h"
#include "common.h"
#include "frontend/card.h"
#include "main/data.h"


/* Run the slot setup sequence with the two shared data tables. */
void card_dev_init_slot_rows(CardDevSlotMenu *panel) {
    initialize_child(panel);
    initialize_two_positioned_object_entries(panel);
    card_boot_update_slot_outputs(panel, D_80408D54, D_80408D5C);
    update_two_slots_using_selection_mapping(panel);
}
