#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80033AA8();                     /* extern */
M2C_UNK func_8008F134();                      /* extern */
M2C_UNK func_800C30A4();                      /* extern */

typedef struct S_800C56A8_0 {
    s32 unk_00;
    s32 unk_04;
} S_800C56A8_0;   /* arg1 in func_800C56A8 */

typedef struct S_800C56A8_1 {
    u8 pad_00[0x6C];
    u16 unk_6C;
} S_800C56A8_1;   /* arg0 in func_800C56A8 */

/* Adjust the two state values and run completion actions when the countdown expires. */
void func_800C56A8(S_800C56A8_1 *object, S_800C56A8_0 *state) {
    u16 ticks_left;

    state->unk_00 = (s32) (state->unk_00 + 0xFFFEAAAB);
    state->unk_04 = (s32) (state->unk_04 + 0x40000);
    ticks_left = object->unk_6C - 1;
    object->unk_6C = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        func_80033AA8(0x54);
        func_8008F134(object);
        func_800C30A4(object);
    }
}
