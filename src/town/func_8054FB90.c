#include "common.h"
#include "m2c_compat.h"

typedef struct S_8054FB90_0 {
    u8 pad_00[0x20];
    void * unk_20;
} S_8054FB90_0;   /* D_80016000 in func_8054FB90 */

typedef struct S_8054FB90_1 {
    u8 pad_00[0x1F4];
    M2C_UNK (*unk_1F4)(M2C_UNK);
} S_8054FB90_1;   /* ((S_8054FB90_0 *)D_80016000)->unk_20 in func_8054FB90 */




M2C_UNK func_800177C4();                     /* extern */
extern S_8054FB90_0 *D_80016000;


void func_8054FB90(void) {
    ((S_8054FB90_1 *)(D_80016000->unk_20))->unk_1F4(2);
    func_800177C4(0x596);
}
