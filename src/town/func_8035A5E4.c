#include "common.h"
#include "m2c_compat.h"

typedef struct S_8035A5E4_0 {
    u8 pad_00[0x20];
    void * unk_20;
} S_8035A5E4_0;   /* D_80016000 in func_8035A5E4 */

typedef struct S_8035A5E4_1 {
    u8 pad_00[0x88];
    M2C_UNK (*unk_88)(M2C_UNK);
} S_8035A5E4_1;   /* ((S_8035A5E4_0 *)D_80016000)->unk_20 in func_8035A5E4 */




extern S_8035A5E4_0 *D_80016000;


void func_8035A5E4(void) {
    ((S_8035A5E4_1 *)(D_80016000->unk_20))->unk_88(0);
}
