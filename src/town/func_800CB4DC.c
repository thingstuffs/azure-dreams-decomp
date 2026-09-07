#include "common.h"

typedef struct S_800C8C3C_0 {
    s32 unk_00;
    s32 unk_04;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800C8C3C_0;   /* arg1 in func_800C8C3C */

typedef struct S_800C8C3C_1 {
    u8 pad_00[0x90];
    u16 unk_90;
} S_800C8C3C_1;   /* arg0 in func_800C8C3C */



extern void func_80033D08(void *);
extern void func_80095388(void *);
extern s16 func_800C2AE8(void *);
extern void func_800C8B5C(void *, void *, s32);
extern void func_800C8D18(void);
extern void func_800C8D34(void *, void *, s32);
extern s32 D_800D636C[2];

void func_800C8C3C(S_800C8C3C_1 *arg0, S_800C8C3C_0 *arg1, s32 arg2)
{
    s32 *velocity;
    u16 temp_v0;

    velocity = D_800D636C;
    arg1->unk_00 += velocity[0];
    arg1->unk_04 += velocity[1];
    arg1->unk_08.at00.v += arg1->unk_14;
    if (func_800C2AE8(arg1) < arg1->unk_08.at02.v) {
        arg1->unk_08.at02.v = func_800C2AE8(arg1);
        temp_v0 = arg0->unk_90 - 1;
        arg0->unk_90 = temp_v0;
        if ((s16)temp_v0 < 0) {
            func_80033D08(arg0);
            func_800C8D34(arg0, arg1, arg2);
            return;
        }
        func_800C8B5C(arg0, arg1, arg2);
        return;
    }
    func_80095388(arg1);
}
