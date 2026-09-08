#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_8001E950.h"



extern Rec_D_8001E950 *D_8001E950;
extern M2C_UNK D_8001FB20;

/* Increment the record's byte counter and return D_8001FB20. */
M2C_UNK *func_8001CED4(void) {
    D_8001E950->unk_01 = (u8) (D_8001E950->unk_01 + 1);
    return &D_8001FB20;
}
