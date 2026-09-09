#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"


extern void func_80047784(void *, s32, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);

extern s16 D_80083228;
extern s32 D_8008346C;
extern u8 D_80170838[16];
extern u8 D_801716F4[];
extern u8 D_80175584[];


typedef struct S_80172F94_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80172F94_0;   /* arg0 in func_80172F94 */



typedef struct S_80172F94_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80172F94_3;   /* arg1 in func_80172F94 */

void func_80172F94(void *arg0, void *arg1, void *arg2, void *arg3)
{
    u8 state;
    static void *const keepalive[] = { &&L0, &&L1, &&L2, &&L3, &&L4 };

    state = ((S_80172F94_0 *)arg0)->unk_9B;
    if ((u32)state >= 5) {
        return;
    }
    goto *(((void **)D_80170838)[state]);

L0:
    if (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x8000) {
        ((S_80172F94_0 *)arg0)->unk_9B = 4;
        ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v |= 0x6000;
        func_8009C12C(arg3, arg2, ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16, 1);
        return;
    }
    ((S_80172F94_3 *)arg1)->unk_14 = 0;
    ((S_80172F94_3 *)arg1)->unk_10 = 0;
    ((S_80172F94_3 *)arg1)->unk_0C = 0;
    goto reset_state;

L1:
    if ((s16)++((S_80172F94_0 *)arg0)->unk_96.u == 4 ||
        (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x8000)) {
        (*(u8 * *)((u8 *)arg2 + (0x2C))) = D_80175584;
        func_80047784(arg2,
            D_80175584[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
        ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v |= 0x0800;
    }
    if (((S_80172F94_0 *)arg0)->unk_96.s == 7 ||
        (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x8000)) {
        ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v &= 0xF7FF;
reset_state:
        ((S_80172F94_0 *)arg0)->unk_96.u = 0;
        ((S_80172F94_0 *)arg0)->unk_9B++;
        return;
    }
    return;

L2:
    ((S_80172F94_0 *)arg0)->unk_96.u = 0;
    ((S_80172F94_0 *)arg0)->unk_9B++;

L3:
    if ((s16)++((S_80172F94_0 *)arg0)->unk_96.u == 7 ||
        (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x8000)) {
        func_8009C12C(arg3, arg2, ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16, 1);
    }

L4:
    if (((S_80172F94_0 *)arg0)->unk_96.s == 3) {
        func_800A56E0(0x814);
    }
    if (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000) {
        func_800AD594(arg3, 0x100);
        ((S_80172F94_0 *)arg0)->unk_8C = D_801716F4;
        D_8008346C = 0;
        func_800A4ACC(arg3);
        ((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v &= 0x7FFF;
    }
    return;
}
