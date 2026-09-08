#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_8065C1A0_1 {
    u8 pad_00[0x34];
    s32 unk_34;
} S_8065C1A0_1;   /* ((Rec_D_80016000 *)D_80016000)->unk_1C.as_pv in func_8065C1A0 */




extern Rec_D_80016000 *D_80016000;
extern s32 D_800183D4;


/* Copy the linked record's unk_34 value into D_800183D4. */
void func_8065C1A0(void) {
    D_800183D4 = ((S_8065C1A0_1 *)(D_80016000->unk_1C.as_pv))->unk_34;
}
