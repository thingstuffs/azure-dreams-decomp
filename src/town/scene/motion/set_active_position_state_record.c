#include "modules/town_ovl_3fe0d0_p00.h"

void set_active_position_state_record(void) {
    D_8001794C.pointer = &D_8001781C;
    ((TownPositionState *)D_80016000->unk_1C)->unk_40 = &D_8001857C;
}
