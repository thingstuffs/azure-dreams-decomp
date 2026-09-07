#include "common.h"
#include "m2c_compat.h"

typedef struct S_818B68B8_0_pre {
    u16 unk_00;
} S_818B68B8_0_pre;   /* the 0x2 bytes before arg0 in func_818B68B8, addressed as arg0[-1] */

typedef struct S_818B68B8_0 {
    void * unk_00;
    u16 unk_04;
} S_818B68B8_0;   /* arg0 in func_818B68B8 */

typedef struct S_818B68B8_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_818B68B8_1;   /* temp_v1 in func_818B68B8 */

typedef struct S_818B68B8_2 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_818B68B8_2;   /* arg1 in func_818B68B8 */

typedef struct S_818B68B8_3 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_818B68B8_3;   /* arg2 in func_818B68B8 */


M2C_UNK func_800478B8();                      /* extern */
extern s32 D_800814A0[3];

/* Increment counters, reduce the stored value, and propagate status flags. */
void func_818B68B8(void *counter_state, S_818B68B8_2 *value_state, S_818B68B8_3 *status) {
    S_818B68B8_1 *linked_counter;

    linked_counter = ((S_818B68B8_0 *)counter_state)->unk_00;
    linked_counter->unk_14 = (u16) (linked_counter->unk_14 + 1);
    ((S_818B68B8_0 *)counter_state)->unk_04 = (u16) (((S_818B68B8_0 *)counter_state)->unk_04 + 1);
    value_state->unk_08 = (s32) (value_state->unk_08 + 0xFFF60000);
    func_800478B8(status);
    if (status->unk_14 & 0x6000) {
        ((S_818B68B8_0_pre *)counter_state)[-1].unk_00 = (u16) (((S_818B68B8_0_pre *)counter_state)[-1].unk_00 | 0x8000);
        D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
    }
}
