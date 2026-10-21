#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80175D50.h"


extern Rec_D_80175D50 *beldo_actor_nodes;

/* Checks whether the record's unk_BA field equals the expected value. */
s32 check_shared_actor_state_value(s32 expected_value) {
    return beldo_actor_nodes->unk_BA == expected_value;
}
