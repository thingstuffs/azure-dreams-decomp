#include "common.h"
#include "m2c_compat.h"

typedef struct S_801720D0_0 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_801720D0_0;   /* arg1 in func_801720D0 */

typedef struct S_801720D0_1 {
    u16 unk_00;
    u8 pad_02[0x16];
    u16 unk_18;
} S_801720D0_1;   /* arg0 in func_801720D0; pointer addresses record offset 0x2 */


M2C_UNK func_80171F30(); /* extern */
extern s32 D_800814A0[3];

/* Advance the countdown, update every other tick, and flag completion when it expires. */
void func_801720D0(void *record_data, S_801720D0_0 *state) {
    u16 ticks_left;

    state->unk_0A = (u16) (state->unk_0A - 4);
    if (!(((S_801720D0_1 *)((u8 *)record_data - 0x2))->unk_18 & 1)) {
        func_80171F30(record_data - 0x20, 0x8080, 8, 0);
    }
    ticks_left = ((S_801720D0_1 *)((u8 *)record_data - 0x2))->unk_18 - 1;
    ((S_801720D0_1 *)((u8 *)record_data - 0x2))->unk_18 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        ((S_801720D0_1 *)((u8 *)record_data - 0x2))->unk_00 = (u16) (((S_801720D0_1 *)((u8 *)record_data - 0x2))->unk_00 | 0x8000);
        D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
    }
}
