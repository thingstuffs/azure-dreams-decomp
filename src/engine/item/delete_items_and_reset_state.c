#include "common.h"

#include "common.h"
#include "engine/entity.h"
#include "engine/item.h"
#include "engine/scene.h"
#include "engine/town.h"

/* Runs the three Konami runtime routines in sequence. */
void delete_items_and_reset_state(void) {
    reset_entry_flags();
    delete_all_town_items();
    clear_selected_scene_entry_flags();
}
