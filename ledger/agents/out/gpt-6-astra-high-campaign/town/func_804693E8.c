#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_8001E950.h"



M2C_UNK func_8001A414(s32, s32, s32);                            /* extern */
extern Rec_D_8001E950 *D_8001E950;

/* Set unk_02 to 0xFF before forwarding three values to func_8001A414. */
void func_8001A3E8(s32 first_value, s32 second_value, s32 third_value) {
    D_8001E950->unk_02 = 0xFF;
    func_8001A414(first_value, second_value, third_value);
}
