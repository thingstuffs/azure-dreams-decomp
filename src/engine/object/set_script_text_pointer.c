#include "common.h"
#include "m2c_compat.h"

#include "records/Rec_D_80082A38.h"
#include "engine/object.h"


/* Sets two record fields to a shared value and initializes an internal buffer pointer. */
void set_script_text_pointer(void *record_arg, s32 value) {
    Rec_D_80082A38 *record = record_arg;

    record->unk_34 = value;
    record->unk_38 = value;
    record->unk_108 = (s32) (record_arg + 0xC8);
}
