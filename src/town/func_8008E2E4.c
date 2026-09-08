#include "common.h"

typedef struct S_8008BA44_0 {
    void * unk_00;
    u8 pad_04[0x60];
    union { volatile s16 s; s16 u; } unk_64;   /* accessed as both */
    s16 unk_66;
    void * unk_68;
    s32 unk_6C;
} S_8008BA44_0;   /* obj in func_8008BA44 */

typedef struct S_8008BA44_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_8008BA44_1;   /* inner in func_8008BA44 */

typedef struct S_8008BA44_2 {
    u8 pad_00[0xA];
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
} S_8008BA44_2;   /* test_inner in func_8008BA44 */



extern u8 D_8008BC58[];
extern u8 D_800CFC70[];
extern s32 D_800CFC7C[];

/* Decrement the inner value, clamping it to zero and resetting object state if it becomes negative. */
void func_8008BA44(S_8008BA44_0 *obj)
{
    S_8008BA44_1 *state;
    S_8008BA44_2 *signed_state;
    s32 reset_data;

    state = obj->unk_00;
    state->unk_0A = (u16)(state->unk_0A - 0x100);
    signed_state = obj->unk_00;
    if (signed_state->unk_0A.s < 0) {
        signed_state->unk_0A.u = 0;
        obj->unk_68 = D_8008BC58;
        obj->unk_64.s = (s8)D_800CFC70[obj->unk_66];
        reset_data = D_800CFC7C[obj->unk_66];
        obj->unk_64.u = 0x16;
        obj->unk_6C = reset_data;
    }
}
