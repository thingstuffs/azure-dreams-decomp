#include "common.h"
#include "m2c_compat.h"

typedef struct S_80019730_0 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_80019730_0;   /* D_8001E950 in func_80019730 */


extern S_80019730_0 *D_8001E950;

void func_80019730(void) {
    u8 temp_v1;

    temp_v1 = D_8001E950->unk_01;
    if (temp_v1 < 2U) {
        D_8001E950->unk_01 = (u8) (temp_v1 + 1);
    }
}
