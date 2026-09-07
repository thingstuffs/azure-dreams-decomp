#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

typedef struct GraphicsState {
    u8 pad[0x8D0];
    void *next_prim;
} GraphicsState;

typedef struct Elem {
    u32 color;
    s16 x;
    s16 y;
    u8  a;
    u8  b;
    u16 code;
} Elem;

typedef struct Block {
    u32 tag;
    Elem e[4];
} Block;

typedef struct StackValues {
    u16 arg0;
    u16 arg1;
    u16 arg2;
    u16 arg3;
} StackValues;

extern GraphicsState *D_80083160;
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern void func_8006658C(s32, void *);
extern void func_8006671C(void *);

void func_801750E4(u16 arg0, u16 arg1, u16 arg2, u16 arg3,
                   u16 arg4, u16 arg5, s32 *arg6, s32 *arg7,
                   s32 arg8, s32 arg9, s32 arg10)
{
    StackValues values;
    u16 end;
    u16 count;
    s32 m20;
    s32 m21;
    s32 m00;
    s32 m01;
    register s32 angle ASM_REG("$21");
    s32 sin0;
    s32 cos0;
    s32 old_sin;
    s32 old_cos;
    u8 *blk;
    u8 *anchor;
    register u8 *q ASM_REG("$18");
    GraphicsState **pp;
    register GraphicsState *root ASM_REG("$2");
    register u16 nc ASM_REG("$2");
    s32 x;
    s32 y;
    register s32 start ASM_REG("$18");

    start = (s16)arg9;
    angle = start << 7;
    values.arg0 = arg0;
    pp = &D_80083160;
    root = *pp;
    blk = (u8 *)root->next_prim;
    values.arg1 = arg1;
    values.arg2 = arg2;
    values.arg3 = arg3;
    sin0 = func_80064584(angle) >> 4;
    cos0 = func_800644B8(angle) >> 4;
    end = arg10;
    count = arg9;

    if (start < (s16)arg10) {
        m20 = values.arg2;
        m21 = values.arg3;
        m00 = values.arg0;
        m01 = values.arg1;
        q = blk + 0x1A;
        ASM_USE2(q, m01);
        do {
            ASM_USE_NV(angle); ASM_USE_NV(angle); ASM_USE_NV(angle); ASM_USE_NV(angle);
            ASM_USE_NV(angle); ASM_USE_NV(angle); ASM_USE_NV(angle); ASM_USE_NV(angle);
            ASM_USE_NV(angle); ASM_USE_NV(angle); ASM_USE_NV(angle); ASM_USE_NV(angle);
            ASM_USE_NV(angle); ASM_USE_NV(angle); ASM_USE_NV(angle); ASM_USE_NV(angle);
            ASM_USE_NV(angle); ASM_USE_NV(angle); ASM_USE_NV(angle); ASM_USE_NV(angle);
            ASM_USE_NV(angle); ASM_USE_NV(angle); ASM_USE_NV(angle); ASM_USE_NV(angle);
            ASM_USE_NV(angle); ASM_USE_NV(angle); ASM_USE_NV(angle); ASM_USE_NV(angle);
            ASM_USE_NV(angle); ASM_USE_NV(angle); ASM_USE_NV(angle); ASM_USE_NV(angle);
            ASM_USE_NV(angle); ASM_USE_NV(angle); ASM_USE_NV(angle); ASM_USE_NV(angle);
            ASM_USE_NV(angle); ASM_USE_NV(angle); ASM_USE_NV(angle); ASM_USE_NV(angle);
            angle += 0x80;
            old_sin = sin0;
            sin0 = func_80064584(angle) >> 4;
            old_cos = cos0;
            cos0 = func_800644B8(angle);
            cos0 = cos0 >> 4;

            x = *arg6;
            FIELD(q, u32, -0x0A) = x;
            FIELD(q, u32, -0x16) = x;
            y = *arg7;
            FIELD(q, u32, 0x0E) = y;
            FIELD(q, u32, 0x02) = y;
            func_8006671C(blk);

            FIELD(q, u8, 0x0A) = 1;
            FIELD(q, u8, -0x0E) = 1;
            FIELD(q, u8, 0x16) = 2;
            FIELD(q, u8, -0x02) = 2;
            FIELD(q, u8, -0x01) = 0xFB;
            FIELD(q, u8, -0x0D) = 0xFB;
            FIELD(q, u8, 0x17) = 0xFB;
            FIELD(q, u8, 0x0B) = 0xFB;

            FIELD(q, s16, -0x12) = arg4 + ((m20 * old_sin) >> 8);
            FIELD(q, s16, -0x10) = arg5 + ((m21 * old_cos) >> 8);
            FIELD(q, s16, -0x06) = arg4 + ((m20 * sin0) >> 8);
            FIELD(q, s16, -0x04) = arg5 + ((m21 * cos0) >> 8);
            FIELD(q, s16, 0x06) = arg4 + ((m00 * old_sin) >> 8);
            FIELD(q, s16, 0x08) = arg5 + ((m01 * old_cos) >> 8);
            FIELD(q, s16, 0x12) = arg4 + ((m00 * sin0) >> 8);
            FIELD(q, s16, 0x14) = arg5 + ((m01 * cos0) >> 8);

            FIELD(q, u16, 0) = 0x133;

            anchor = blk;
            func_8006658C(arg8, anchor);
            blk += sizeof(Block);
            nc = count + 1;
            count = nc;
            q += sizeof(Block);
        } while (((s32)(u32)nc << 16) < ((s32)(u32)end << 16));
    }
    (*pp)->next_prim = blk;
}
