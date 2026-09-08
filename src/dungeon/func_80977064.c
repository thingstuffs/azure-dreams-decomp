#include "common.h"
#include "records/Rec_D_80082E80.h"


extern void func_80047784(void *, s32, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern void func_80172958(void) __attribute__((noreturn));

extern s16 D_80083228[5];
extern s32 D_8008346C[5];
extern void *D_80170838[];
extern u8 D_801714D4[];
extern u8 D_80174108[];


typedef struct S_80172864_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    union { u8 n; volatile u8 v; } unk_9B;   /* accessed as both */
    u8 pad_9C[0x2];
    s16 unk_9E;
    u8 pad_A0[0x2];
    s16 unk_A2;
} S_80172864_0;   /* s0 in func_80172864 */


typedef struct S_80172864_2 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_80172864_2;   /* s1 in func_80172864 */

void func_80172864(void *arg0, void *arg1, Rec_D_80082E80 *arg2, void *arg3)
{
    static void *const state_keep[] = {
        &&state_0, &&state_1, &&state_2, &&state_3, &&state_4
    };
    register void *s0 = arg0;
    register void *s1 = arg3;
    u8 state;
    u16 timer;

    state = ((S_80172864_0 *)s0)->unk_9B.n;
    if ((u32)state >= 5) {
        goto done;
    }
    (void)state_keep;
    goto *D_80170838[state];

state_0:
    timer = ((S_80172864_0 *)s0)->unk_96.u;
    ((S_80172864_0 *)s0)->unk_96.u = timer + 1;
    if ((s16)timer < 4 && !(arg2->unk_14.at00_u16.v & 0x8000)) {
        goto done;
    }
    (void)((S_80172864_0 *)s0)->unk_9B.v;
    ((S_80172864_0 *)s0)->unk_96.u = 0;
    func_80172958();

state_1:
    if (((S_80172864_0 *)s0)->unk_A2 != 0 &&
        !(arg2->unk_14.at00_u16.v & 0x8000)) {
        goto done;
    }
    arg2->unk_2C.as_pu8 = D_80174108;
    func_80047784(
        arg2,
        D_80174108[((D_80083228[0] + ((S_80172864_2 *)s1)->unk_2A + 0x100) >> 9) & 7],
        0);
    state = ((S_80172864_0 *)s0)->unk_9B.n;
    ((S_80172864_0 *)s0)->unk_96.u = 0;
    ((S_80172864_0 *)s0)->unk_A2 = 0;
    ((S_80172864_0 *)s0)->unk_9E = 0;
    ((S_80172864_0 *)s0)->unk_9B.n = state + 1;
    return;

state_2:
    timer = ((S_80172864_0 *)s0)->unk_96.u + 1;
    ((S_80172864_0 *)s0)->unk_96.u = timer;
    if ((s16)timer == 9 || (arg2->unk_14.at00_u16.v & 0x8000)) {
        func_8009C12C(s1, arg2, ((S_80172864_2 *)s1)->unk_2A, 1);
        ((S_80172864_0 *)s0)->unk_96.u = 0;
        ((S_80172864_0 *)s0)->unk_9B.n++;
    }
    if (((S_80172864_0 *)s0)->unk_96.s != 6) {
        goto done;
    }
    func_800A56E0(0x808);
    return;

state_3:
state_4:
    state = ((S_80172864_0 *)s0)->unk_9B.n;
    ((S_80172864_0 *)s0)->unk_96.u = 0;
    ((S_80172864_0 *)s0)->unk_9B.n = state + 1;
    if (!(arg2->unk_14.at00_u16.v & 0xE000)) {
        goto done;
    }
    func_800AD594(s1, 0x100);
    ((S_80172864_0 *)s0)->unk_8C = D_801714D4;
    D_8008346C[0] = 0;
    func_800A4ACC(s1);
    ((S_80172864_2 *)s1)->unk_46 &= 0x7FFF;

done:
    return;
}
