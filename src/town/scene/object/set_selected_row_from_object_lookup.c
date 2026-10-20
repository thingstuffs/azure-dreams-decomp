#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "m2c_compat.h"



extern u8 D_80019B08;
extern s32 D_80019B8C;


/* Set the selected record index from the current object's lookup entry. */
void set_selected_row_from_object_lookup(void) {
    D_80019B8C = (s32) *((((TownPositionState *)D_80016000->unk_1C)->unk_34 * 4) + &D_80019B08);
}
