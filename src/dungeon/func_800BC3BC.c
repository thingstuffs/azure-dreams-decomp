#include "common.h"


typedef struct {
    u8 pad[0xA];
    u16 field_A;
} D_80083460_t;

extern u8 D_80082E80[];
extern s32 D_80082EB0[];
extern D_80083460_t D_80083460;
extern u8 D_80083780[];
extern u16 D_800DDE84[];
extern u8 D_800E14D8[];
extern u8 D_800E14EB[];
extern u8 D_800E1514[];
extern u8 *D_800E3D7C;

extern void func_8008D344(void *, void *, void *, void *);
extern void func_80098864(s32, s32);
extern void func_80098B38(s32);
extern s32 func_800990FC(void);
extern s32 func_80099194(void *, s32);
extern void func_80099290(s32);
extern s32 func_800992E8(void *, s32);
extern void func_800A56E0(s32);
extern void func_800A5720(s32);
extern void func_800A5F38(void *, s32);
extern void func_800A6480(void *, s32, s16);
extern s32 func_800AD6FC(void *, s32, s32);
extern s32 func_800C1C90(void);
extern s32 func_800C1CC0(void);


typedef struct S_800C1B1C_0 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0xFC];
    s32 unk_110;
} S_800C1B1C_0;   /* arg0 in func_800C1B1C */

typedef struct S_800C1B1C_1 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800C1B1C_1;   /* base in func_800C1B1C */

typedef struct S_800C1B1C_2 {
    u8 pad_00[0x1];
    u8 unk_01;
    union { s8 s; u8 u; } unk_02;   /* accessed as both */
} S_800C1B1C_2;   /* ((S_800C1B1C_1 *)base)->unk_04 in func_800C1B1C */

s32 func_800C1B1C(S_800C1B1C_0 *arg0, s32 arg1, s16 arg2, s32 arg3)
{
    s32 *base;
    s32 value;
    s32 result;

    if (arg2 == 13) {
        func_80098864(arg1, arg3);
        return func_800C1CC0();
    }

    if (arg0 == D_800E3D7C) {
        arg0->unk_110 = arg1;
        func_8008D344(arg0, D_80083780, D_80082E80, arg0);
        func_800C1CC0();
        return 0;
    }

    if ((u32)arg0 <= 0x9FFFFFFF) {
        func_800A6480(arg0, arg1, arg2);
        if (func_800AD6FC(
                arg0, D_800DDE84[arg0->unk_13] & 3, 0) == 0) {
            func_800A5F38(arg0, arg1);
            func_800C1CC0();
            return 1;
        }
    } else {
        value = func_800990FC();
        base = D_80082EB0;
        if (((S_800C1B1C_2 *)(((S_800C1B1C_1 *)base)->unk_04))->unk_01 == 4) {
            result = func_80099194(
                D_800E14EB,
                func_800992E8(
                    ((S_800C1B1C_1 *)base)->unk_04,
                    func_80099194(D_800E14D8, value)));
            func_800A56E0(0x80F);
            if (((S_800C1B1C_2 *)(((S_800C1B1C_1 *)base)->unk_04))->unk_02.s < 99) {
                ((S_800C1B1C_2 *)(((S_800C1B1C_1 *)base)->unk_04))->unk_02.u++;
                return func_800C1C90();
            }
        } else {
            result = func_80099194(D_800E1514, value);
        }
        func_80099290(result);
        func_800A5720(value);
    }

    D_80083460.field_A--;
    func_80098B38(arg1);
    return 1;
}

/* MECHANISM: The 0x28 frame comes from four natural saved roles: arg0/result,
   arg1, the D_80082EB0 base, and the message handle. Direct typed table and
   counter accesses preserve the retail halfword-scaled addressing and merge. */
