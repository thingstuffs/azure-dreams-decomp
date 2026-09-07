#include "common.h"
#include "m2c_compat.h"

typedef struct S_800AF96C_1 {
    void * unk_00;
} S_800AF96C_1;   /* arg0 in func_800AF96C */

typedef struct S_800AF96C_2 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_800AF96C_2;   /* ((S_800AF96C_1 *)arg0)->unk_00 in func_800AF96C */


typedef struct S_800AF96C_0 {
    s32 unk_00;
    u8 pad_04[0x10];
    s32 unk_14;
} S_800AF96C_0;   /* arg0 in func_800AF96C; pointer addresses record offset 0x10 */


s32 func_800AF8B0();                                /* extern */

void func_800AF96C(void *arg0) {
    ((S_800AF96C_2 *)(((S_800AF96C_1 *)arg0)->unk_00))->unk_04 = func_800AF8B0();
    if (((S_800AF96C_2 *)(((S_800AF96C_1 *)arg0)->unk_00))->unk_04 != 0) {
        ((S_800AF96C_0 *)((u8 *)arg0 - 0x10))->unk_00 = (s32) ((S_800AF96C_0 *)((u8 *)arg0 - 0x10))->unk_14;
    }
}
