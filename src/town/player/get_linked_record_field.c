#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"



/* Returns the field at offset 0x2D60 in the record linked through D_80016000. */
s32 get_linked_record_field_2_d_60(void) {
    return D_80016000->unk_38->unk_2D60;
}
