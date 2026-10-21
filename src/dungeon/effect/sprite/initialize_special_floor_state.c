#include "shared/runtime_dispatch.h"
#include "common.h"
#include "shared/dungeon_floor.h"



/* Set the state values to 0x20 and 0x31 and enable the associated flags. */
void initialize_special_floor_state(void) {
    runtime_dispatch_state.unk_10 = 0x20;
    runtime_dispatch_state.unk_12 = 0x31;
    runtime_dispatch_state.flags16 |= 1;
    dungeon_floor_flags |= 0x2000;
}
