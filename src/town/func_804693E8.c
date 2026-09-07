#include "common.h"
#include "m2c_compat.h"

typedef struct S_8001A3E8_0 {
    u8 pad_00[0x2];
    u8 unk_02;
} S_8001A3E8_0;   /* D_8001E950 in func_8001A3E8 */


M2C_UNK func_8001A414();                            /* extern */
extern S_8001A3E8_0 *D_8001E950;

void func_8001A3E8(void) {
    D_8001E950->unk_02 = 0xFF;
    func_8001A414();
}
