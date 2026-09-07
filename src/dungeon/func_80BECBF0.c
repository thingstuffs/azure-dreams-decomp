#include "common.h"

typedef struct S_801723F0_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_801723F0_0;   /* arg0 in func_801723F0 */

typedef struct S_801723F0_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_801723F0_1;   /* arg2 in func_801723F0 */

typedef struct S_801723F0_2 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_801723F0_2;   /* arg3 in func_801723F0 */

typedef struct S_801723F0_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_801723F0_3;   /* arg1 in func_801723F0 */



extern void func_80047784(void *, u8, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern s16 D_80083228;
extern s32 D_8008346C;
extern u8 D_80171014[];
extern u8 D_8017423C[];

void func_801723F0(void *arg0, void *arg1, void *arg2, void *arg3) {
    s32 state;
    u16 counter;

    state = ((S_801723F0_0 *)arg0)->unk_9B;
    if (state == 1) {
        goto state1;
    }
    if (state >= 2) {
        goto state_ge2;
    }
    if (state == 0) {
        goto set_state1;
    }
    goto done;

state_ge2:
    if (state == 2) {
        goto state2;
    }
    if (state == 3) {
        goto state3;
    }
    goto done;

set_state1:
    ((S_801723F0_0 *)arg0)->unk_9B = 1;

state1:
    if (((S_801723F0_1 *)arg2)->unk_14 & 0x8000) {
        ((S_801723F0_0 *)arg0)->unk_9B = 3;
        ((S_801723F0_1 *)arg2)->unk_14 |= 0x6000;
        func_8009C12C(arg3, arg2, ((S_801723F0_2 *)arg3)->unk_2A, 1);
        goto done;
    }
    ((S_801723F0_3 *)arg1)->unk_14 = 0;
    ((S_801723F0_3 *)arg1)->unk_10 = 0;
    ((S_801723F0_3 *)arg1)->unk_0C = 0;
    (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_8017423C;
    func_80047784(arg2,
        D_8017423C[((s32)(D_80083228 + ((S_801723F0_2 *)arg3)->unk_2A + 0x100) >> 9) & 7],
        0);
    ((S_801723F0_0 *)arg0)->unk_96 = 0;
    ((S_801723F0_0 *)arg0)->unk_9B++;
    func_800A56E0(0x804);
    goto done;

state2:
    counter = ((S_801723F0_0 *)arg0)->unk_96 + 1;
    ((S_801723F0_0 *)arg0)->unk_96 = counter;
    if (((s16)counter == 8) || (((S_801723F0_1 *)arg2)->unk_14 & 0x8000)) {
        func_8009C12C(arg3, arg2, ((S_801723F0_2 *)arg3)->unk_2A, 1);
    }

state3:
    if (((S_801723F0_1 *)arg2)->unk_14 & 0xE000) {
        func_800AD594(arg3, 0x100);
        ((S_801723F0_0 *)arg0)->unk_8C = D_80171014;
        D_8008346C = 0;
        (*(u16 *)((u8 *)arg3 + 0x46)) &= 0x7FFF;
        func_800A4ACC(arg3);
    }

done:
    return;
}
