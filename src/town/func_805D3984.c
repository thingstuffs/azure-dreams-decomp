#include "common.h"
#include "m2c_compat.h"

typedef struct S_805D3984_0 {
    u8 pad_00[0x38];
    void * unk_38;
} S_805D3984_0;   /* D_80016000 in func_805D3984 */

typedef struct S_805D3984_1 {
    u8 pad_00[0x2D5C];
    u32 unk_2D5C;
} S_805D3984_1;   /* ((S_805D3984_0 *)D_80016000)->unk_38 in func_805D3984 */




extern S_805D3984_0 *D_80016000;
extern u32 D_80019B00;


s32 func_805D3984(void) {
    return (u32) ((S_805D3984_1 *)(D_80016000->unk_38))->unk_2D5C >= (u32) D_80019B00;
}
