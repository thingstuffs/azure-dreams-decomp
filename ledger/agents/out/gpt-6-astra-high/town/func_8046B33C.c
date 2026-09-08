#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_8001E950.h"



extern Rec_D_8001E950 *D_8001E950;

/* Returns whether D_8001E950->unk_04 equals 3. */
s32 func_8001C33C(void) {
    return D_8001E950->unk_04 == 3;
}
