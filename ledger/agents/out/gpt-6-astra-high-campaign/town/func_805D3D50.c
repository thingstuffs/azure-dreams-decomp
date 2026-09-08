#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_805D3D50_1 {
    u8 pad_00[0x34];
    s32 unk_34;
} S_805D3D50_1;   /* ((Rec_D_80016000 *)D_80016000)->unk_1C.as_pv in func_805D3D50 */




extern Rec_D_80016000 *D_80016000;
extern u8 D_80019B08;
extern s32 D_80019B8C;


/* Set the selected record index from the current object's lookup entry. */
void func_805D3D50(void) {
    D_80019B8C = (s32) *((((S_805D3D50_1 *)(D_80016000->unk_1C.as_pv))->unk_34 * 4) + &D_80019B08);
}
