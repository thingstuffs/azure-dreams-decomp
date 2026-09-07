#include "common.h"

typedef long long s64;

typedef struct S_800A2E30_0 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_800A2E30_0;   /* initial_ctx in func_800A2E30 */

typedef struct S_800A2E30_1 {
    u8 pad_00[0x4];
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 pad_07[0x1];
    u16 unk_08;
    u16 unk_0A;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u16 unk_12;
    u8 unk_14;
    u8 unk_15;
    u8 unk_16;
    u8 pad_17[0x1];
    u16 unk_18;
    u16 unk_1A;
    u8 unk_1C;
    u8 unk_1D;
    u8 unk_1E;
    u8 pad_1F[0x1];
    u16 unk_20;
    u16 unk_22;
} S_800A2E30_1;   /* obj in func_800A2E30 */

typedef struct S_800A2E30_2 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_800A2E30_2;   /* ctx in func_800A2E30 */


typedef struct InputPair {
    u32 first;
    u32 second;
} InputPair;

typedef struct OutputPair {
    u16 first;
    u16 second;
    u32 pad;
} OutputPair;


extern u8 D_80083160[];

extern s32 func_800654B0(InputPair *, InputPair *, InputPair *, InputPair *,
                        OutputPair *, OutputPair *, OutputPair *, OutputPair *,
                        u32 *, u32 *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_8006658C(void *, void *);
extern void func_80066640(void *, s32);
extern void func_80066708(void *, void *);
extern void func_80067F20(void *, s32, s32, u16, s32);

void func_800A2E30(InputPair arg0, InputPair arg2, InputPair arg4,
                   InputPair arg6, u16 arg8)
{
    OutputPair out0;
    OutputPair out1;
    OutputPair out2;
    OutputPair out3;
    u32 out4;
    u32 out5;
    s32 value;
    u8 *ctx;
    u8 *obj;

    {
        u8 *initial_ctx;

        initial_ctx = *(u8 **)D_80083160;
        obj = ((S_800A2E30_0 *)initial_ctx)->unk_8D0;
        ((S_800A2E30_0 *)initial_ctx)->unk_8D0 = obj + 0x24;
        ((S_800A2E30_1 *)obj)->unk_16 = arg8;
        ((S_800A2E30_1 *)obj)->unk_15 = arg8;
        ((S_800A2E30_1 *)obj)->unk_14 = arg8;
        ((S_800A2E30_1 *)obj)->unk_06 = arg8;
        ((S_800A2E30_1 *)obj)->unk_05 = arg8;
        ((S_800A2E30_1 *)obj)->unk_04 = arg8;
        ((S_800A2E30_1 *)obj)->unk_1E = 0;
        ((S_800A2E30_1 *)obj)->unk_1D = 0;
        ((S_800A2E30_1 *)obj)->unk_1C = 0;
        ((S_800A2E30_1 *)obj)->unk_0E = 0;
        ((S_800A2E30_1 *)obj)->unk_0D = 0;
        ((S_800A2E30_1 *)obj)->unk_0C = 0;
        func_80066708(obj, initial_ctx);
    }
    func_80066640(obj, 1);

    value = func_800654B0(&arg0, &arg2, &arg4, &arg6,
                          &out0, &out1, &out2, &out3, &out4, &out5);

    ((S_800A2E30_1 *)obj)->unk_08 = out0.first;
    ((S_800A2E30_1 *)obj)->unk_0A = out0.second;
    ((S_800A2E30_1 *)obj)->unk_10 = out1.first;
    ((S_800A2E30_1 *)obj)->unk_12 = out1.second;
    ((S_800A2E30_1 *)obj)->unk_18 = out2.first;
    ((S_800A2E30_1 *)obj)->unk_1A = out2.second;
    ((S_800A2E30_1 *)obj)->unk_20 = out3.first;
    ((S_800A2E30_1 *)obj)->unk_22 = out3.second;

    if (value >= 0x1E0) {
        value = 0x1DF;
    }
    ASM_USE(value);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */

    func_8006658C(*(u8 **)D_80083160 + 0xD8, obj);

    ctx = *(u8 **)D_80083160;
    obj = ((S_800A2E30_2 *)ctx)->unk_8D0;
    ((S_800A2E30_2 *)ctx)->unk_8D0 = obj + 0xC;
    value = func_80066460(0, 1, 0x140, 0);
    func_80067F20(obj, 0, 0, (u16)value, 0);

    func_8006658C(*(u8 **)D_80083160 + 0xD8, obj);
}

/* MECHANISM: Four address-taken 8-byte aggregate inputs force the a0-a3 homes
   and aggregate lowering orders the a1 store before a0. Four sibling 8-byte
   outputs plus two words make the 0x60 frame; s1/s0 hold page/current record. */
