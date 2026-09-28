#include "common.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "m2c_compat.h"



extern u8 D_800DD878;

/* Restore bit 4 of the current record flags when it was saved as set. */
void func_800A68F4(void) {
    if (D_800DD878 != 0) {
        D_800E3D7C->flags1C = (s32) (D_800E3D7C->flags1C | 0x10);
    }
}
