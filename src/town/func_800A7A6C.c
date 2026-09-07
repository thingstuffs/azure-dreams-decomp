#include "common.h"

typedef struct S_800A51CC_0 {
    union { struct { s32 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { s16 s; u16 u; } unk_04;   /* accessed as both */
    u8 pad_06[0xA];
    union { struct { s32 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x2]; u16 v; } at02; } unk_10;   /* overlapping accesses */
    union { s16 s; u16 u; } unk_14;   /* accessed as both */
    u8 pad_16[0x2];
    s32 unk_18;
    u8 pad_1C[0x4];
    void * unk_20;
} S_800A51CC_0;   /* arg0 in func_800A51CC */

typedef struct S_800A51CC_1 {
    u8 pad_00[0xAC];
    union { struct { s32 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x2]; u16 v; } at02; } unk_AC;   /* overlapping accesses */
    union { s16 s; u16 u; } unk_B0;   /* accessed as both */
} S_800A51CC_1;   /* base in func_800A51CC */



extern u8 D_80083160[0xB2];
extern u8 D_800A526C[16];

extern void func_800A5264(void *arg0, s32 arg1, void *arg2);

void func_800A51CC(S_800A51CC_0 *arg0)
{
    u8 *base;
    s32 value;
    u16 component;

    base = D_80083160;
    value = arg0->unk_00.at00.v;
    if ((value != ((S_800A51CC_1 *)base)->unk_AC.at00.v) ||
        (arg0->unk_04.s != ((S_800A51CC_1 *)base)->unk_B0.s)) {
        if ((value != arg0->unk_10.at00.v) ||
            (arg0->unk_04.s != arg0->unk_14.s)) {
            arg0->unk_18 = 9;
            arg0->unk_20 = D_800A526C;
            return func_800A5264(arg0, value, base);
        }

        component = ((S_800A51CC_1 *)base)->unk_AC.at00u.v;
        arg0->unk_00.at00u.v = component;
        arg0->unk_10.at00u.v = component;
        component = ((S_800A51CC_1 *)base)->unk_AC.at02.v;
        arg0->unk_00.at02.v = component;
        arg0->unk_10.at02.v = component;
        component = ((S_800A51CC_1 *)base)->unk_B0.u;
        arg0->unk_04.u = component;
        arg0->unk_14.u = component;
    }
}
