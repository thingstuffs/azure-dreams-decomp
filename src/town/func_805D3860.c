#include "common.h"
#include "m2c_compat.h"

typedef struct S_805D3860_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x34];
    s32 unk_40;
} S_805D3860_0;   /* D_80016000 in func_805D3860 */

typedef struct S_805D3860_1 {
    s32 unk_00;
    u8 pad_04[0x2];
    u8 unk_06;
} S_805D3860_1;   /* temp_v1 in func_805D3860 */


extern void *D_80016000;
extern s32 D_80019B00;
extern s32 D_80019B8C;

s32 func_805D3860(void) {
    void *temp_v1;

    temp_v1 = ((S_805D3860_0 *)D_80016000)->unk_40 + (((S_805D3860_0 *)D_80016000)->unk_08 * 8);
    D_80019B8C = (s32) ((S_805D3860_1 *)temp_v1)->unk_06;
    D_80019B00 = (*(s32 *)((u8 *)temp_v1 + 0));
    return ((S_805D3860_1 *)temp_v1)->unk_00;
}
