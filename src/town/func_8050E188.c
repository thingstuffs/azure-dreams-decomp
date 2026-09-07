#include "common.h"
#include "m2c_compat.h"

typedef struct S_8050E188_0 {
    u8 pad_00[0x38];
    void * unk_38;
} S_8050E188_0;   /* D_80016000 in func_8050E188 */

typedef struct S_8050E188_1 {
    u8 pad_00[0x35BE];
    s16 unk_35BE;
} S_8050E188_1;   /* ((S_8050E188_0 *)D_80016000)->unk_38 in func_8050E188 */




extern S_8050E188_0 *D_80016000;


s32 func_8050E188(void) {
    return ((S_8050E188_1 *)(D_80016000->unk_38))->unk_35BE >= 0x33;
}
