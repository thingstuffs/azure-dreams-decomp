#include "common.h"
#include "m2c_compat.h"

extern s32 D_80126A10[];
extern s32 D_80126A60;
extern s32 D_80126AD0;

typedef struct S_801237A4_0 {
    u8 pad_00[0x16];
    u8 unk_16;
} S_801237A4_0;   /* arg0 in func_801237A4 */

void func_801237A4(S_801237A4_0 *arg0) {
    D_80126A60 = D_80126A10[arg0->unk_16];
    D_80126AD0 = D_80126A10[arg0->unk_16 ^ 1];
}
