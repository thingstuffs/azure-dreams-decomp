#include "common.h"
#include "m2c_compat.h"

typedef struct S_80018860_0 {
    u8 pad_00[0x20];
    void * unk_20;
} S_80018860_0;   /* D_80016000 in func_80018860 */

typedef struct S_80018860_1 {
    u8 pad_00[0x1E8];
    M2C_UNK (*unk_1E8)(M2C_UNK);
} S_80018860_1;   /* ((S_80018860_0 *)D_80016000)->unk_20 in func_80018860 */




s32 func_8001ADE0();                         /* extern */
extern S_80018860_0 *D_80016000;


void func_80018860(void) {
    if ((func_8001ADE0(0x1200) == 0) && (func_8001ADE0(0x1201) == 0)) {
        ((S_80018860_1 *)(D_80016000->unk_20))->unk_1E8(8);
    }
}
