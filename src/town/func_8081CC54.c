#include "common.h"

typedef struct S_80026C54_0_pre {
    u16 unk_00;
} S_80026C54_0_pre;   /* the 0x2 bytes before arg0 in func_80026C54, addressed as arg0[-1] */

typedef struct S_80026C54_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    u8 pad_02[0x2];
    void * unk_04;
    s32 unk_08;
} S_80026C54_0;   /* arg0 in func_80026C54 */

typedef struct S_80026C54_1 {
    u8 pad_00[0x1A];
    u16 unk_1A;
} S_80026C54_1;   /* temp_v0 in func_80026C54 */



extern s32 D_800814A0[3];

/* Waits for the linked object flag, then fades the stored value and marks completion. */
void func_80026C54(void *effect) {
    S_80026C54_1 *linked_object;
    s16 state;
    u16 state_value;
    s32 fade_value;

    linked_object = ((S_80026C54_0 *)effect)->unk_04;
    state = ((S_80026C54_0 *)effect)->unk_00.s;
    state_value = *(volatile u16 *)effect;

    switch (state) {
    case 0:
        if (linked_object->unk_1A & 8) {
            ((S_80026C54_0 *)effect)->unk_00.u = state_value + 1;
        }
        break;

    case 1:
        fade_value = ((S_80026C54_0 *)effect)->unk_08 + 0xFFF7F7F8U;
        ((S_80026C54_0 *)effect)->unk_08 = fade_value;
        if (fade_value <= 0x80808) {
            ((S_80026C54_0_pre *)effect)[-1].unk_00 |= 0x8000;
            D_800814A0[0] |= 0x8000;
        }
        break;
    }

}
