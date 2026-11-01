/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "shared/town_handler.h"

extern s32 D_80091EB4;
extern s32 D_800D0100;

/* Selects D_800D0100 and installs D_80091EB4 with action count 4. */
void init_height_interpolation_action(TownObjectRecord *record, void *unused, void *handler_context) {
    call_the_handler_selects_nonzero_entry(&D_800D0100, record, handler_context);
    record->unk_00.as_pm = &D_80091EB4;
    record->unk_0A.as_s16 = 4;
}
