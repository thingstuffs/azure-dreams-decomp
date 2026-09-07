#include "common.h"
#include "m2c_compat.h"

typedef struct S_8065C308_0 {
    u8 pad_00[0x20];
    void * unk_20;
} S_8065C308_0;   /* D_80016000 in func_8065C308 */

typedef struct S_8065C308_1 {
    u8 pad_00[0x4C];
    M2C_UNK (*unk_4C)(s32, s32);
} S_8065C308_1;   /* ((S_8065C308_0 *)D_80016000)->unk_20 in func_8065C308 */




extern S_8065C308_0 *D_80016000;
extern s32 D_800183C8;
extern s32 D_800183D0;


void func_8065C308(void) {
    ((S_8065C308_1 *)(D_80016000->unk_20))->unk_4C(D_800183C8, D_800183D0);
}
