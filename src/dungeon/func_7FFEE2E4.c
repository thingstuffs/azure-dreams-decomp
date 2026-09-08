#include "common.h"
#include "m2c_compat.h"

typedef struct S_8008BA44_0 {
    void * unk_00;
    u8 pad_04[0x60];
    union { volatile s16 s; s16 u; } unk_64;   /* accessed as both */
    s16 unk_66;
    M2C_UNK * unk_68;
    s32 unk_6C;
} S_8008BA44_0;   /* arg0 in func_8008BA44 */

typedef struct S_8008BA44_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_8008BA44_1;   /* temp_v0 in func_8008BA44 */

typedef struct S_8008BA44_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_8008BA44_2;   /* temp_v1 in func_8008BA44 */


extern M2C_UNK D_8008BC58;
extern s8 D_800CFC70[];
extern s32 D_800CFC7C[];

/* Decrement the object value by 0x100 and initialize the next state on underflow. */
void func_8008BA44(S_8008BA44_0 *state) {
    S_8008BA44_1 *object;
    S_8008BA44_2 *checked_object;
    s32 next_value;

    object = state->unk_00;
    object->unk_0A = (u16) (object->unk_0A - 0x100);
    checked_object = state->unk_00;
    if ((s16) checked_object->unk_0A < 0) {
        checked_object->unk_0A = 0U;
        state->unk_68 = &D_8008BC58;
        state->unk_64.s = (s16) (s8) D_800CFC70[state->unk_66];
        next_value = D_800CFC7C[state->unk_66];
        state->unk_64.u = 0x16;
        state->unk_6C = next_value;
    }
}
