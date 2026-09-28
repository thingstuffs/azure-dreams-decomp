#include "common.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "m2c_compat.h"



extern s8 D_800DD878;

/* Save and clear bit 4 of the current record flags. */
void func_800A68C0(void) {
    D_800DD878 = ((u32) ((u32)((EntityRec *)D_800E3D7C)->flags1C) >> 4) & 1;
    ((EntityRec *)D_800E3D7C)->flags1C = (u32) (((u32)((EntityRec *)D_800E3D7C)->flags1C) & ~0x10);
}
