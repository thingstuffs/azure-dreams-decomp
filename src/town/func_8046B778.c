#include "common.h"
#include "m2c_compat.h"

typedef struct S_8001C778_0 {
    u8 pad_00[0x38];
    void * unk_38;
} S_8001C778_0;   /* D_80016000 in func_8001C778 */

typedef struct S_8001C778_1 {
    u8 pad_00[0x2D68];
    u32 unk_2D68;
} S_8001C778_1;   /* ((S_8001C778_0 *)D_80016000)->unk_38 in func_8001C778 */




extern S_8001C778_0 *D_80016000;


s32 func_8001C778(void) {
    return (u32) ((S_8001C778_1 *)(D_80016000->unk_38))->unk_2D68 >= 0x2710U;
}
