#include "common.h"
#include "m2c_compat.h"

typedef struct S_80500158_0 {
    u8 pad_00[0x38];
    void * unk_38;
} S_80500158_0;   /* D_80016000 in func_80500158 */

typedef struct S_80500158_1 {
    u8 pad_00[0x35BC];
    s16 unk_35BC;
} S_80500158_1;   /* ((S_80500158_0 *)D_80016000)->unk_38 in func_80500158 */




extern S_80500158_0 *D_80016000;


s16 func_80500158(void) {
    return ((S_80500158_1 *)(D_80016000->unk_38))->unk_35BC;
}
