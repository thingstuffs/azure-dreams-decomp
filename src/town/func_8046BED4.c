#include "common.h"
#include "m2c_compat.h"

typedef struct S_8001CED4_0 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_8001CED4_0;   /* D_8001E950 in func_8001CED4 */


extern S_8001CED4_0 *D_8001E950;
extern M2C_UNK D_8001FB20;

M2C_UNK *func_8001CED4(void) {
    D_8001E950->unk_01 = (u8) (D_8001E950->unk_01 + 1);
    return &D_8001FB20;
}
