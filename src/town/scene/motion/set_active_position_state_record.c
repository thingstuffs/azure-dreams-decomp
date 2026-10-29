#include "modules/town_ovl_3fe0d0_p00.h"
#include "town/scene/motion.h"

void set_active_position_state_record(void) {
    D_8001794C.pointer = &D_8001781C;
    ((TownPositionState *)town_scene_root->position)->unk_40 = &D_8001857C;
}
