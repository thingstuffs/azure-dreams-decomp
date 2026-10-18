/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"



void copy_town_record_pair_fields();


/* Pass the callback-selected table value to the destination handler. */
void copy_callback_value_to_destination(s32 destination, s32 *values) {
    copy_town_record_pair_fields(destination, *((D_80016000->unk_20->callback_2D4(0)) + values));
}
