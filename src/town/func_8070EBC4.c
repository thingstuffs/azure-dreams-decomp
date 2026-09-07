#include "common.h"
#include "m2c_compat.h"

typedef struct S_80017BC4_0 {
    u8 pad_00[0x20];
    void * unk_20;
} S_80017BC4_0;   /* D_80016000 in func_80017BC4 */

typedef struct S_80017BC4_1 {
    u8 pad_00[0x2F8];
    M2C_UNK (*unk_2F8)(M2C_UNK, M2C_UNK);
} S_80017BC4_1;   /* ((S_80017BC4_0 *)D_80016000)->unk_20 in func_80017BC4 */




M2C_UNK func_80016CC4();                            /* extern */
extern S_80017BC4_0 *D_80016000;


s32 func_80017BC4(void) {
    func_80016CC4();
    ((S_80017BC4_1 *)(D_80016000->unk_20))->unk_2F8(0xF, 0x200);
    return 0;
}
