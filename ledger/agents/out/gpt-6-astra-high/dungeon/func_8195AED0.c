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

/* Sets the current entry address from the linked base and a 24-byte entry index. */
void func_8195AED0(S_8195AED0_0 *state, s16 entry_index) {
    state->unk_00 = (s32) (((S_8195AED0_2 *)(((S_8195AED0_1 *)state)->unk_08))->unk_0C + (entry_index * 0x18));
}
