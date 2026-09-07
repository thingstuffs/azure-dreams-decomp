#include "common.h"
#include "m2c_compat.h"

typedef struct S_80024F7C_0 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_80024F7C_0;   /* temp_a1 in func_80024F7C */

typedef struct S_80024F7C_1 {
    s32 unk_00;
    u8 pad_04[0x40];
    s32 unk_44;
} S_80024F7C_1;   /* arg0 in func_80024F7C; pointer addresses record offset 0x10 */


void func_80024F7C(void *arg0) {
    u16 temp_v1;
    S_80024F7C_0 *temp_a1;

    temp_a1 = arg0 - 0x20;
    temp_v1 = temp_a1->unk_1E;
    if (temp_v1 & 0x2000) {
        temp_a1->unk_1E = (u16) (temp_v1 & 0xDFFF);
        ((S_80024F7C_1 *)((u8 *)arg0 - 0x10))->unk_00 = (s32) ((S_80024F7C_1 *)((u8 *)arg0 - 0x10))->unk_44;
    }
}
