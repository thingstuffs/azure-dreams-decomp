#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_8001E950.h"



extern Rec_D_8001E950 *D_8001E950;

/* Checks whether D_8001E950's unk_04 field equals 6. */
s32 func_8001C35C(void) {
    return D_8001E950->unk_04 == 6;
}
