#include "common.h"
#include "m2c_compat.h"

typedef struct S_8081508C_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8081508C_0;   /* arg1 in func_8081508C */

typedef struct S_8081508C_1_pre {
    u16 unk_00;
} S_8081508C_1_pre;   /* the 0x2 bytes before arg0 in func_8081508C, addressed as arg0[-1] */

typedef struct S_8081508C_1 {
    u8 pad_00[0xE];
    u16 unk_0E;
} S_8081508C_1;   /* arg0 in func_8081508C */


extern s32 D_80084D5C;

/* Advance the three motion components and set completion flags when the countdown expires. */
void func_8081508C(void *timer_state, void *motion) {
    u16 ticks_left;

    ((S_8081508C_0 *)motion)->unk_00 = (s32) (((S_8081508C_0 *)motion)->unk_00 + ((S_8081508C_0 *)motion)->unk_0C);
    ((S_8081508C_0 *)motion)->unk_04 = (s32) (((S_8081508C_0 *)motion)->unk_04 + ((S_8081508C_0 *)motion)->unk_10);
    ((S_8081508C_0 *)motion)->unk_08 = (s32) (((S_8081508C_0 *)motion)->unk_08 + ((S_8081508C_0 *)motion)->unk_14);
    ticks_left = ((S_8081508C_1 *)timer_state)->unk_0E - 1;
    ((S_8081508C_1 *)timer_state)->unk_0E = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        (*(u16 *)((u8 *)timer_state + -2)) = (u16) (((S_8081508C_1_pre *)timer_state)[-1].unk_00 | 0x8000);
        D_80084D5C |= 0x8000;
    }
}
