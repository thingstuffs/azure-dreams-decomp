#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "m2c_compat.h"

/* Set the referenced object's flag at offset 0xB0 to one. */
void func_80017808(void) {
    ((TownProgressState *)D_80016000->unk_40)->unk_B0 = 1;
}
