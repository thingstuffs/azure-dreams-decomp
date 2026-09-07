#include "common.h"
#include "m2c_compat.h"

typedef struct S_80480494_0 {
    u8 pad_00[0x38];
    void * unk_38;
} S_80480494_0;   /* D_80016000 in func_80480494 */

typedef struct S_80480494_1 {
    u8 pad_00[0x2D5C];
    u32 unk_2D5C;
} S_80480494_1;   /* ((S_80480494_0 *)D_80016000)->unk_38 in func_80480494 */




extern S_80480494_0 *D_80016000;
extern u32 D_80019438;


s32 func_80480494(void) {
    return (u32) ((S_80480494_1 *)(D_80016000->unk_38))->unk_2D5C >= (u32) D_80019438;
}
