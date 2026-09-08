#include "common.h"
#include "m2c_compat.h"

typedef struct S_80020510_0_pre {
    u16 unk_00;
} S_80020510_0_pre;   /* the 0x2 bytes before arg0 in func_80020510, addressed as arg0[-1] */

typedef struct S_80020510_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    u16 unk_02;
    s32 unk_04;
    u8 pad_08[0x4];
    void * unk_0C;
    u8 pad_10[0xC];
    u16 unk_1C;
} S_80020510_0;   /* arg0 in func_80020510 */

typedef struct S_80020510_1 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_80020510_1;   /* temp_s2 in func_80020510 */


M2C_UNK func_800537D0();               /* extern */
s32 strlen();                             /* extern */
extern s16 D_800272A0[];
extern s32 D_800814A0;

/* Advances a text entry's delay, processes its string, and propagates the linked object's flag. */
void func_80020510(void *entry) {
    s16 state;
    s32 value_index;
    s32 value_sum;
    u16 ticks_left;
    void *linked_object;

    value_sum = 0;
    value_index = 7;
    linked_object = ((S_80020510_0 *)entry)->unk_0C;
    do {
        value_sum += D_800272A0[value_index];
        value_index -= 1;
    } while (value_index >= 0);
    state = ((S_80020510_0 *)entry)->unk_00.s;
    if (state == 0) {
        goto state_zero;
    }
    if (state == 1) {
        goto state_one;
    }
    goto done;

state_zero:
    ticks_left = ((S_80020510_0 *)entry)->unk_02 - 1;
    ((S_80020510_0 *)entry)->unk_02 = ticks_left;
    if ((ticks_left << 0x10) > 0) {
        goto done;
    }
    ((S_80020510_0 *)entry)->unk_1C =
        (u16) (((S_80020510_0 *)entry)->unk_1C & 0xFFFD);
    ((S_80020510_0 *)entry)->unk_00.u =
        (u16) (((S_80020510_0 *)entry)->unk_00.u + 1);
    goto done;

state_one:
    func_800537D0(value_sum, strlen(((S_80020510_0 *)entry)->unk_04),
                  ((S_80020510_0 *)entry)->unk_04);
    if (((S_80020510_1 *)linked_object)->unk_2A & 1) {
        (*(u16 *)((u8 *)entry + -2)) =
            (u16) (((S_80020510_0_pre *)entry)[-1].unk_00 | 0x8000);
        D_800814A0 |= 0x8000;
    }

done:
    return;
}
