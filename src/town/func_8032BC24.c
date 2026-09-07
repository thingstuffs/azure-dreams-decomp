#include "common.h"
#include "m2c_compat.h"

typedef struct S_80016424_0 {
    u8 pad_00[0x20];
    void * unk_20;
} S_80016424_0;   /* D_80016000 in func_80016424 */

typedef struct S_80016424_1 {
    u8 pad_00[0x344];
    M2C_UNK (*unk_344)(M2C_UNK *, M2C_UNK);
} S_80016424_1;   /* ((S_80016424_0 *)D_80016000)->unk_20 in func_80016424 */




extern S_80016424_0 *D_80016000;
extern M2C_UNK D_8001BF80;


void func_80016424(void) {
    ((S_80016424_1 *)(D_80016000->unk_20))->unk_344(&D_8001BF80, 0x14);
}
