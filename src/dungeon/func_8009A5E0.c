#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

s16 func_8009FCF0();                  /* extern */



/* Returns the Chebyshev distance between two record positions. */
s16 func_8009FD40(Rec_D_80082E80 *start_record, Rec_D_80082E80 *end_record) {
    return func_8009FCF0(start_record->unk_24, start_record->unk_25, end_record->unk_24, end_record->unk_25);
}
