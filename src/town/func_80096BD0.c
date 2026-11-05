/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "shared/town_handler.h"
#include "town.h"

extern s32 D_80090F00;
extern s32 D_800D00C0;

/* Selects D_800D00C0 and installs D_80090F00 with action count 6. */
void initialize_action_object_type_six(TownObjectRecord *record, void *ptr, void *ptr2) {
    call_the_handler_selects_nonzero_entry(&D_800D00C0, record, ptr2);
    record->unk_00 = &D_80090F00;
    record->unk_0A = 6;
}
