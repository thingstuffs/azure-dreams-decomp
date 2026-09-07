#include "common.h"
#include "m2c_compat.h"

typedef struct S_80017458_0 {
    u8 pad_00[0x20];
    void * unk_20;
} S_80017458_0;   /* D_80016000 in func_80017458 */

typedef struct S_80017458_1 {
    u8 pad_00[0x238];
    M2C_UNK (*unk_238)(M2C_UNK, M2C_UNK);
} S_80017458_1;   /* ((S_80017458_0 *)D_80016000)->unk_20 in func_80017458 */




extern S_80017458_0 *D_80016000;


void func_80017458(void) {
    ((S_80017458_1 *)(D_80016000->unk_20))->unk_238(0x25, 0x200);
}
