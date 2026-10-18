#include "modules/dungeon_engine_dungeon_util_fragment_c1094.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "m2c_compat.h"



/* Save and clear bit 4 of the current record flags. */
void save_and_clear_entity_flag_ten(void) {
    D_800DD878 = ((u32) ((u32)D_800E3D7C->flags1C) >> 4) & 1;
    D_800E3D7C->flags1C = (u32) (((u32)D_800E3D7C->flags1C) & ~0x10);
}
