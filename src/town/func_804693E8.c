#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_8001E950.h"



M2C_UNK func_8001A414();                            /* extern */
extern Rec_D_8001E950 *D_8001E950;

void func_8001A3E8(void) {
    D_8001E950->unk_02 = 0xFF;
    func_8001A414();
}
