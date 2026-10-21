#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "records/Rec_D_80082D58.h"
#include "engine/resource.h"


/* Clears the record's unk_04 field. */
void runtime_clear_record_field_04(Rec_D_80082D58 *record) {
    record->unk_04 = 0;
}
