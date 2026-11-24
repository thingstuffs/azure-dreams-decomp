#include "town/scene/hooks.h"
#include "common.h"
#include "town/player/state.h"
#include "town/scene.h"

#include "town/scene/state_data.h"

/* Set the script flag named by the saved scene choice. */
void set_saved_choice_entry_flag(void) {
    set_script_flag_bit(scene_saved_choice_row->entry_flag);
}
