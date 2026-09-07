#include "common.h"
#include "m2c_compat.h"

typedef struct S_8195AED0_1 {
    u8 pad_00[0x8];
    void * unk_08;
} S_8195AED0_1;   /* arg0 in func_8195AED0 */

typedef struct S_8195AED0_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_8195AED0_2;   /* ((S_8195AED0_1 *)arg0)->unk_08 in func_8195AED0 */




typedef struct S_8195AED0_0 {
    s32 unk_00;
} S_8195AED0_0;   /* arg0 in func_8195AED0 */

void func_8195AED0(S_8195AED0_0 *arg0, s16 arg1) {
    arg0->unk_00 = (s32) (((S_8195AED0_2 *)(((S_8195AED0_1 *)arg0)->unk_08))->unk_0C + (arg1 * 0x18));
}
