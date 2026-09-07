#include "common.h"
#include "m2c_compat.h"

typedef struct S_80017808_0 {
    u8 pad_00[0x40];
    void * unk_40;
} S_80017808_0;   /* D_80016000 in func_80017808 */

typedef struct S_80017808_1 {
    u8 pad_00[0xB0];
    s32 unk_B0;
} S_80017808_1;   /* ((S_80017808_0 *)D_80016000)->unk_40 in func_80017808 */




extern S_80017808_0 *D_80016000;


void func_80017808(void) {
    ((S_80017808_1 *)(D_80016000->unk_40))->unk_B0 = 1;
}
