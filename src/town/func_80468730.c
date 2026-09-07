#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_8001E950.h"



extern Rec_D_8001E950 *D_8001E950;

void func_80019730(void) {
    u8 temp_v1;

    temp_v1 = D_8001E950->unk_01;
    if (temp_v1 < 2U) {
        D_8001E950->unk_01 = (u8) (temp_v1 + 1);
    }
}
