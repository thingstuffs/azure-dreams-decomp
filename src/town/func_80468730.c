#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_8001E950.h"



extern Rec_D_8001E950 *D_8001E950;

/* Increment the record counter if it is below two. */
void func_80019730(void) {
    u8 counter;

    counter = D_8001E950->unk_01;
    if (counter < 2U) {
        D_8001E950->unk_01 = (u8) (counter + 1);
    }
}
