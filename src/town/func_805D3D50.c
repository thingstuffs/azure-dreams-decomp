#include "common.h"
#include "m2c_compat.h"

typedef struct S_805D3D50_0 {
    u8 pad_00[0x1C];
    void * unk_1C;
} S_805D3D50_0;   /* D_80016000 in func_805D3D50 */

typedef struct S_805D3D50_1 {
    u8 pad_00[0x34];
    s32 unk_34;
} S_805D3D50_1;   /* ((S_805D3D50_0 *)D_80016000)->unk_1C in func_805D3D50 */




extern S_805D3D50_0 *D_80016000;
extern u8 D_80019B08;
extern s32 D_80019B8C;


void func_805D3D50(void) {
    D_80019B8C = (s32) *((((S_805D3D50_1 *)(D_80016000->unk_1C))->unk_34 * 4) + &D_80019B08);
}
