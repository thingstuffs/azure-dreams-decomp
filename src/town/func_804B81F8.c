#include "common.h"
#include "m2c_compat.h"

typedef struct S_800169F8_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x34];
    s32 unk_40;
} S_800169F8_0;   /* D_80016000 in func_800169F8 */

typedef struct S_800169F8_1 {
    u8 pad_00[0x2];
    u8 unk_02;
} S_800169F8_1;   /* temp_v1 in func_800169F8 */


s32 func_8001894C();                         /* extern */
extern S_800169F8_0 *D_80016000;

void func_800169F8(void) {
    u8 temp_v0;
    S_800169F8_1 *temp_v1;

    if (func_8001894C(0x514) != 0) {
        temp_v1 = (D_80016000->unk_08 * 8) + D_80016000->unk_40;
        temp_v0 = temp_v1->unk_02;
        if (temp_v0 != 0) {
            temp_v1->unk_02 = (u8) (temp_v0 - 1);
        }
    }
}
