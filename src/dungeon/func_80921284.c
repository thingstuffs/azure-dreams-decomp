#include "shared/runtime_dispatch.h"
#include "common.h"
#include "shared/dungeon_floor.h"



/* Set the state values to 0x20 and 0x31 and enable the associated flags. */
void func_800F6284(void) {
    D_80082E60.unk_10 = 0x20;
    D_80082E60.unk_12 = 0x31;
    D_80082E60.flags16 |= 1;
    D_800E296C |= 0x2000;
}
