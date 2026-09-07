#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_8001E950.h"



extern Rec_D_8001E950 *D_8001E950;

s32 func_8001C2FC(void) {
    return D_8001E950->unk_04 == 1;
}
