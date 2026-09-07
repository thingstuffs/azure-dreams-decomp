#include "common.h"
#include "m2c_compat.h"

typedef struct S_8065C1A0_0 {
    u8 pad_00[0x1C];
    void * unk_1C;
} S_8065C1A0_0;   /* D_80016000 in func_8065C1A0 */

typedef struct S_8065C1A0_1 {
    u8 pad_00[0x34];
    s32 unk_34;
} S_8065C1A0_1;   /* ((S_8065C1A0_0 *)D_80016000)->unk_1C in func_8065C1A0 */




extern S_8065C1A0_0 *D_80016000;
extern s32 D_800183D4;


void func_8065C1A0(void) {
    D_800183D4 = ((S_8065C1A0_1 *)(D_80016000->unk_1C))->unk_34;
}
