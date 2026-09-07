#include "common.h"

typedef long long s64;

typedef struct InputPair {
    u32 first;
    u32 second;
} InputPair;

typedef struct OutputPair {
    u16 first;
    u16 second;
    u32 pad;
} OutputPair;

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

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
        ASM_KEEP_NV(initial_ctx);
        obj = FIELD(initial_ctx, u8 *, 0x8D0);
        FIELD(initial_ctx, u8 *, 0x8D0) = obj + 0x24;
        FIELD(obj, u8, 0x16) = arg8;
        FIELD(obj, u8, 0x15) = arg8;
        FIELD(obj, u8, 0x14) = arg8;
        FIELD(obj, u8, 6) = arg8;
        FIELD(obj, u8, 5) = arg8;
        FIELD(obj, u8, 4) = arg8;
        FIELD(obj, u8, 0x1E) = 0;
        FIELD(obj, u8, 0x1D) = 0;
        FIELD(obj, u8, 0x1C) = 0;
        FIELD(obj, u8, 0xE) = 0;
        FIELD(obj, u8, 0xD) = 0;
        FIELD(obj, u8, 0xC) = 0;
        func_80066708(obj, initial_ctx);
    }
    func_80066640(obj, 1);

    value = func_800654B0(&arg0, &arg2, &arg4, &arg6,
                          &out0, &out1, &out2, &out3, &out4, &out5);

    FIELD(obj, u16, 8) = out0.first;
    FIELD(obj, u16, 0xA) = out0.second;
    FIELD(obj, u16, 0x10) = out1.first;
    FIELD(obj, u16, 0x12) = out1.second;
    FIELD(obj, u16, 0x18) = out2.first;
    FIELD(obj, u16, 0x1A) = out2.second;
    FIELD(obj, u16, 0x20) = out3.first;
    FIELD(obj, u16, 0x22) = out3.second;

    if (value >= 0x1E0) {
        value = 0x1DF;
    }
    ASM_USE(value);

    func_8006658C(*(u8 **)D_80083160 + 0xD8, obj);

    ctx = *(u8 **)D_80083160;
    obj = FIELD(ctx, u8 *, 0x8D0);
    FIELD(ctx, u8 *, 0x8D0) = obj + 0xC;
    value = func_80066460(0, 1, 0x140, 0);
    func_80067F20(obj, 0, 0, (u16)value, 0);

    func_8006658C(*(u8 **)D_80083160 + 0xD8, obj);
}

/* MECHANISM: Four address-taken 8-byte aggregate inputs force the a0-a3 homes
   and aggregate lowering orders the a1 store before a0. Four sibling 8-byte
   outputs plus two words make the 0x60 frame; s1/s0 hold page/current record. */
