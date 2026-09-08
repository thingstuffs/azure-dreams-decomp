#include "common.h"

typedef struct S_800203D8_0_pre {
    u16 unk_00;
} S_800203D8_0_pre;   /* the 0x2 bytes before arg0 in func_800203D8, addressed as arg0[-1] */

typedef struct S_800203D8_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    u8 pad_02[0x2];
    void * unk_04;
    s32 unk_08;
} S_800203D8_0;   /* arg0 in func_800203D8 */

typedef struct S_800203D8_1 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_800203D8_1;   /* temp_v0 in func_800203D8 */



extern s32 D_800814A0[3];

/* Waits for the linked object flag, then dims the color and sets completion flags. */
void func_800203D8(void *fade) {
    S_800203D8_1 *linked_obj;
    s16 state;
    u16 state_value;
    s32 color;

    linked_obj = ((S_800203D8_0 *)fade)->unk_04;
    state = ((S_800203D8_0 *)fade)->unk_00.s;
    state_value = *(volatile u16 *)fade;

    switch (state) {
    case 0:
        if (linked_obj->unk_04 & -32768) {
            ((S_800203D8_0 *)fade)->unk_00.u = state_value + 1;
        }
        break;

    case 1:
        color = ((S_800203D8_0 *)fade)->unk_08 + 0xFFF7F7F8U;
        ((S_800203D8_0 *)fade)->unk_08 = color;
        if (color <= 0x80808) {
            ((S_800203D8_0_pre *)fade)[-1].unk_00 |= 0x8000;
            D_800814A0[0] |= 0x8000;
        }
        break;
    }

}
