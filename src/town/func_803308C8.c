#include "common.h"
#include "m2c_compat.h"

typedef struct S_8001B0C8_0 {
    u8 pad_00[0x38];
    void * unk_38;
} S_8001B0C8_0;   /* D_80016000 in func_8001B0C8 */

typedef struct S_8001B0C8_1 {
    u8 pad_00[0x2D60];
    s32 unk_2D60;
} S_8001B0C8_1;   /* ((S_8001B0C8_0 *)D_80016000)->unk_38 in func_8001B0C8 */




extern S_8001B0C8_0 *D_80016000;


s32 func_8001B0C8(void) {
    return ((S_8001B0C8_1 *)(D_80016000->unk_38))->unk_2D60;
}
