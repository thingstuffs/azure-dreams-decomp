#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_8008F2D4_arg0.h"
#include "records/Rec_func_8008F2D4_arg1.h"

/* cfail-repair: tf7-phase1-cache-v3 */


/* Sets the record flag and initializes the state with the supplied value. */
void set_the_flag_initializes_state(Rec_func_8008F2D4_arg0 *record, Rec_func_8008F2D4_arg1 *state, s32 value) {
    record->unk_36 = 1;
    state->unk_00 = value;
    state->unk_0C = 0;
}
