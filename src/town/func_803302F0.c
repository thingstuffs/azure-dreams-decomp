#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "m2c_compat.h"


   /* ((S_8001AAF0_1 *)(((Rec_D_80016000 *)D_80016000)->unk_24))->unk_68 in get_current_nested_record_value */

   /* ((S_8001AAF0_2 *)(((S_8001AAF0_1 *)(((Rec_D_80016000 *)D_80016000)->unk_24))->unk_68))->unk_08 in get_current_nested_record_value */


/* Return the signed value at offset 0x0A of the current nested record. */
s16 get_current_nested_record_value(void) {
    return ((TownNestedRecordValueView *)(((TownNestedPayloadView *)(((TownResourceLinks *)D_80016000->unk_24)->unk_68))->unk_08))->unk_0A;
}
