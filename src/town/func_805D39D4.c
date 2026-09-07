#include "common.h"
#include "m2c_compat.h"

typedef struct S_805D39D4_0 {
    u8 pad_00[0x38];
    void * unk_38;
} S_805D39D4_0;   /* D_80016000 in func_805D39D4 */

typedef struct S_805D39D4_1 {
    u8 pad_00[0x2D5C];
    u32 unk_2D5C;
} S_805D39D4_1;   /* ((S_805D39D4_0 *)D_80016000)->unk_38 in func_805D39D4 */




extern S_805D39D4_0 *D_80016000;


s32 func_805D39D4(u32 arg0) {
    return (u32) ((S_805D39D4_1 *)(D_80016000->unk_38))->unk_2D5C < arg0;
}
