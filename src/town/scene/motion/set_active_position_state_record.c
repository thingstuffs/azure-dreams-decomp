#include "modules/town_ovl_3fe0d0_p00.h"
#include "town/scene/motion.h"

void set_active_position_state_record(void) {
    birth_step_data_slot.pointer = &D_8001781C;
    town_scene_root->position->default_script = &D_8001857C;
}
