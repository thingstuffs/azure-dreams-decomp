#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64();                       /* extern */
extern s16 D_80080B04;
extern s32 D_80081508;

typedef struct S_800AC454_0 {
    u8 pad_00[0x20];
    s8 unk_20;
} S_800AC454_0;   /* temp_v0 in func_800AC454 */

void func_800AC454(void) {
    void *temp_v0;

    temp_v0 = func_8003FC64(0);
    D_80081508 = temp_v0 + 0x20;
    ((S_800AC454_0 *)temp_v0)->unk_20 = 0;
    D_80080B04 = 0;
}
