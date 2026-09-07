#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_8008EFE0();                      /* extern */
M2C_UNK func_8008F134();                      /* extern */
extern M2C_UNK D_8009BDC0;


typedef struct S_8009C0D8_1 {
    u8 pad_00[0x50];
    M2C_UNK * unk_50;
} S_8009C0D8_1;   /* arg0 in func_8009C0D8 */

void func_8009C0D8(S_8009C0D8_1 *arg0, Rec_func_80094268_arg0 *arg1) {
    arg1->unk_15 = 1;
    arg0->unk_50 = &D_8009BDC0;
    func_8008F134(arg1);
    func_8008EFE0(arg1);
}
