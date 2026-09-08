#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_800362A0_1 {
    u8 pad_00[0x74];
    void * unk_74;
} S_800362A0_1;   /* arg0 in func_800362A0 */

typedef struct S_800362A0_2 {
    u8 pad_00[0x84];
    s8 unk_84;
} S_800362A0_2;   /* ((S_800362A0_1 *)arg0)->unk_74 in func_800362A0 */


typedef struct S_800362A0_0 {
    u8 pad_00[0x50];
    u8 unk_50;
    u8 pad_51[0x17];
    M2C_UNK * unk_68;
} S_800362A0_0;   /* arg0 in func_800362A0 */


extern M2C_UNK func_80036154;

/* If the flag at offset 0x50 is set, marks the linked state and selects func_80036154. */
void func_800362A0(S_800362A0_0 *state) {
    if (state->unk_50 != 0) {
        ((S_800362A0_2 *)(((S_800362A0_1 *)state)->unk_74))->unk_84 = 1;
        state->unk_68 = &func_80036154;
    }
}
