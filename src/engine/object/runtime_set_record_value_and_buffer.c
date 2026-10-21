#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "records/Rec_D_80082A38.h"
#include "engine/object.h"


/* Sets two record fields to a shared value and initializes an internal buffer pointer. */
void runtime_set_record_value_and_buffer(void *record, s32 value) {
    ((Rec_D_80082A38 *)record)->unk_34 = value;
    ((Rec_D_80082A38 *)record)->unk_38 = value;
    ((Rec_D_80082A38 *)record)->unk_108 = (s32) (record + 0xC8);
}
