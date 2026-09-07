#include "common.h"
#include "m2c_compat.h"

typedef struct S_80697764_0 {
    u8 pad_00[0x38];
    void * unk_38;
} S_80697764_0;   /* D_80016000 in func_80697764 */

typedef struct S_80697764_1 {
    u8 pad_00[0x2D5C];
    u32 unk_2D5C;
} S_80697764_1;   /* ((S_80697764_0 *)D_80016000)->unk_38 in func_80697764 */




extern S_80697764_0 *D_80016000;
extern u32 D_80018AE0;


s32 func_80697764(void) {
    return (u32) ((S_80697764_1 *)(D_80016000->unk_38))->unk_2D5C >= (u32) D_80018AE0;
}
