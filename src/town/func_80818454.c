#include "common.h"
#include "m2c_compat.h"

typedef struct S_80022454_1 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80022454_1;   /* arg0 in func_80022454 */

typedef struct S_80022454_2 {
    u8 pad_00[0x36];
    s16 unk_36;
} S_80022454_2;   /* ((S_80022454_1 *)arg0)->unk_04 in func_80022454 */


typedef struct S_80022454_0 {
    u16 unk_00;
} S_80022454_0;   /* arg0 in func_80022454; pointer addresses record offset 0x2 */


extern s32 D_800814A0[3];

void func_80022454(void *arg0) {
    if (((S_80022454_2 *)(((S_80022454_1 *)arg0)->unk_04))->unk_36 == 8) {
        ((S_80022454_0 *)((u8 *)arg0 - 0x2))->unk_00 = (u16) (((S_80022454_0 *)((u8 *)arg0 - 0x2))->unk_00 | 0x8000);
        D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
    }
}
