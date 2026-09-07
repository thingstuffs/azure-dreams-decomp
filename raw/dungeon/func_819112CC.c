#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))
#define SP16(off) (*(u16 *)(scratch + (off)))
#define SP32(off) (*(u32 *)(scratch + (off)))
#define temp_s1 prim
#define temp_s1_2 prim
#define temp_s1_3 prim
/* Same address as D_80083160 (0x80083178 - 0x18); this spelling keeps its
   page construction shared with the other references below. */
#define GFX_ROOT_SLOT (((u8 *)&D_80083178) - 0x18)

extern s32 func_800644B8();
extern s32 func_80064584();
extern u32 func_80065590();
extern s32 func_80066460();
extern void func_80067F20();
typedef struct {
    u8 pad0[0x8D0];
    u8 *nextPrim;
} RenderContext;
typedef struct {} EmptyArg;
extern RenderContext *D_80083160;

void func_819112CC(void *arg0_in, void *arg1, s16 arg2_in, s16 arg3_in)
{
    void *arg0 = arg0_in;
    s32 arg2 = arg2_in;
    s32 arg3 = arg3_in;
    register u32 low_mask ASM_REG("$20");
    u8 *prim;
    register s32 s0_value ASM_REG("$16");
    s32 sp28;
    s32 sp2C;
    s32 c2;
    s32 sp30;
    s32 sp34;
    s16 temp_v0_12;
    s16 temp_v0_5;
    s16 temp_v0_6;
    s16 temp_v1_2;
    s16 temp_v1_3;
    register u32 *link ASM_REG("$4");
    register s32 call_coord ASM_REG("$4");
    s32 projected_x;
    s32 temp_v0;
    s32 temp_v0_11;
    s32 temp_v0_4;
    s32 temp_v0_9;
    s32 temp_v1;
    s32 var_s5;
    s32 var_v1;
    u16 d10E;
    u16 temp_v0_10;
    u16 temp_v0_2;
    u16 temp_v0_3;
    u16 temp_v0_7;
    u16 temp_v0_8;
    register u32 temp_a0 ASM_REG("$4");
    u8 *temp_a3;
    register s32 idx4 ASM_REG("$2");
    register u8 *scratch ASM_REG("$18");
    u8 *new_var;
    EmptyArg empty_arg;
    u8 *global = *(u8 **)GFX_ROOT_SLOT;

    new_var = GFX_ROOT_SLOT;
    var_s5 = 0;
    scratch = (u8 *)0x1F800000;
    sp30 = arg2 < arg3;
    sp34 = 0x1F800064;
    low_mask = 0x00FFFFFF;
    SP32(0x18) = (u32)global + 0xB0;
    while (var_s5 < 5) {
        var_v1 = var_s5 * 2;
        s0_value = (var_v1 + 1) * 0x199;
        call_coord = s0_value + FIELD(arg0, s16, 0xA);
        projected_x = func_800644B8(call_coord);
        call_coord = FIELD(arg0, s16, 0xA);
        call_coord = s0_value + call_coord;
        s0_value = FIELD(arg1, s32, 0);
        s0_value += (((projected_x >> 4) *
                     FIELD(arg0, s16, 0xE)) << 8);
        ASM_KEEP_NV(s0_value);
        idx4 = func_80064584(call_coord);
        sp28 = s0_value;
        idx4 >>= 4;
        c2 = FIELD(arg1, s32, 4) +
            ((idx4 * FIELD(arg0, s16, 0xE)) << 8);
        sp2C = c2;
        {
            RenderContext **pool = (RenderContext **)new_var;
            temp_s1 = (*pool)->nextPrim;
            (*pool)->nextPrim = temp_s1 + 0x24;
        }
        FIELD(temp_s1, s8, 3) = 8;
        FIELD(temp_s1, s8, 7) = 0x3A;
        FIELD(temp_s1, u8, 4) = FIELD(arg0, u8, 0x40);
        FIELD(temp_s1, u8, 5) = FIELD(arg0, u8, 0x41);
        FIELD(temp_s1, u8, 6) = FIELD(arg0, u8, 0x42);
        FIELD(temp_s1, u8, 0xC) = FIELD(arg0, u8, 0x40);
        FIELD(temp_s1, u8, 0xD) = FIELD(arg0, u8, 0x41);
        FIELD(temp_s1, u8, 0xE) = FIELD(arg0, u8, 0x42);
        FIELD(temp_s1, u8, 0x14) = FIELD(arg0, u8, 0x40);
        FIELD(temp_s1, u8, 0x15) = FIELD(arg0, u8, 0x41);
        FIELD(temp_s1, u8, 0x16) = FIELD(arg0, u8, 0x42);
        FIELD(temp_s1, u8, 0x1C) = FIELD(arg0, u8, 0x40);
        FIELD(temp_s1, u8, 0x1D) = FIELD(arg0, u8, 0x41);
        idx4 = var_s5 * 4;
        temp_a3 = (u8 *)arg0 + idx4;
        FIELD(temp_s1, u8, 0x1E) = FIELD(arg0, u8, 0x42);
        temp_v0_2 = FIELD(temp_a3, u16, 0x1A);
        SP16(0x74) = temp_v0_2;
        SP16(0x64) = temp_v0_2;
        temp_v1 = s0_value - FIELD(temp_a3, s32, 0x18);
        SP32(0x108) = temp_v1;
        if (sp30 != 0) {
            SP32(0x108) = (temp_v1 / arg3) * arg2;
        }
        temp_v1_2 = FIELD(temp_a3, u16, 0x1A) + SP16(0x10A);
        SP16(0x7C) = temp_v1_2;
        SP16(0x6C) = temp_v1_2;
        temp_v0_3 = FIELD(temp_a3, u16, 0x2E);
        SP16(0x76) = temp_v0_3;
        SP16(0x66) = temp_v0_3;
        temp_v0_4 = c2 - FIELD(temp_a3, s32, 0x2C);
        SP32(0x10C) = temp_v0_4;
        if (sp30 != 0) {
            SP32(0x10C) = (temp_v0_4 / arg3) * arg2;
        }
        temp_v0_5 = FIELD(temp_a3, u16, 0x2E) + SP16(0x10E);
        SP16(0x7E) = temp_v0_5;
        SP16(0x6E) = temp_v0_5;
        temp_v0_6 = FIELD(arg1, u16, 0xA) - FIELD(arg0, u16, 0x10);
        SP16(0x70) = temp_v0_6;
        SP16(0x68) = temp_v0_6;
        temp_v0_7 = FIELD(arg1, u16, 0xA);
        SP32(0xB4) = func_80065590(sp34, scratch + 0x6C,
                                  scratch + 0x74, scratch + 0x7C,
                                  scratch + 0xD8, scratch + 0xDC,
                                  scratch + 0xE0, scratch + 0xE4,
                                  scratch + 0x84, scratch + 0x88,
                                  (SP16(0x78) = temp_v0_7,
                                   SP16(0x80) = temp_v0_7,
                                   empty_arg));
        FIELD(temp_s1, u16, 8) = SP16(0xD8);
        FIELD(temp_s1, u16, 0xA) = SP16(0xDA);
        FIELD(temp_s1, u16, 0x10) = SP16(0xDC);
        FIELD(temp_s1, u16, 0x12) = SP16(0xDE);
        FIELD(temp_s1, u16, 0x18) = SP16(0xE0);
        FIELD(temp_s1, u16, 0x1A) = SP16(0xE2);
        FIELD(temp_s1, u16, 0x20) = SP16(0xE4);
        FIELD(temp_s1, u16, 0x22) = SP16(0xE6);
        temp_a0 = SP32(0xB4);
        if (temp_a0 < 0x1E0U) {
            idx4 = temp_a0 << 2;
            s0_value = (s32)0xFF000000;
            idx4 += SP32(0x18);
            FIELD(temp_s1, u32, 0) = (FIELD(temp_s1, u32, 0) & (u32)s0_value) |
                (*(u32 *)idx4 & low_mask);
            link = (u32 *)((SP32(0xB4) << 2) + SP32(0x18));
            *link = (*link & (u32)s0_value) | ((u32)temp_s1 & low_mask);
            {
                RenderContext *ctx = *(RenderContext **)new_var;
                    temp_s1_2 = ctx->nextPrim;
                ctx->nextPrim = temp_s1_2 + 0xC;
            }
            func_80067F20(temp_s1_2, 0, 0,
                         func_80066460(0, FIELD(arg0, s16, 0x12), 0, 0) & 0xFFFF,
                         0);
            FIELD(temp_s1_2, u32, 0) = (FIELD(temp_s1_2, u32, 0) & (u32)s0_value) |
                (((u32 *)SP32(0x18))[SP32(0xB4)] & low_mask);
            link = (u32 *)((SP32(0xB4) << 2) + SP32(0x18));
            *link = (*link & (u32)s0_value) | ((u32)temp_s1_2 & low_mask);
        }
        {
            RenderContext **pool = (RenderContext **)new_var;
            temp_s1_3 = (*pool)->nextPrim;
            (*pool)->nextPrim = temp_s1_3 + 0x24;
        }
        FIELD(temp_s1_3, s8, 3) = 8;
        FIELD(temp_s1_3, s8, 7) = 0x3A;
        FIELD(temp_s1_3, u8, 4) = FIELD(arg0, u8, 0x40);
        FIELD(temp_s1_3, u8, 5) = FIELD(arg0, u8, 0x41);
        FIELD(temp_s1_3, u8, 6) = FIELD(arg0, u8, 0x42);
        var_s5 += 1;
        FIELD(temp_s1_3, u8, 0xC) = FIELD(arg0, u8, 0x40);
        FIELD(temp_s1_3, u8, 0xD) = FIELD(arg0, u8, 0x41);
        FIELD(temp_s1_3, u8, 0xE) = FIELD(arg0, u8, 0x42);
        FIELD(temp_s1_3, u8, 0x14) = FIELD(arg0, u8, 0x40);
        FIELD(temp_s1_3, u8, 0x15) = FIELD(arg0, u8, 0x41);
        FIELD(temp_s1_3, u8, 0x16) = FIELD(arg0, u8, 0x42);
        FIELD(temp_s1_3, u8, 0x1C) = FIELD(arg0, u8, 0x40);
        FIELD(temp_s1_3, u8, 0x1D) = FIELD(arg0, u8, 0x41);
        idx4 = FIELD(arg0, u8, 0x42);
        FIELD(temp_s1_3, u8, 0x1E) = idx4;
        idx4 = var_s5 % 5;
        idx4 *= 4;
        temp_a3 = (u8 *)arg0 + idx4;
        ASM_KEEP_NV(var_s5);
        temp_v0_8 = FIELD(temp_a3, u16, 0x1A);
        SP16(0x74) = temp_v0_8;
        SP16(0x64) = temp_v0_8;
        temp_v0_9 = sp28 - FIELD(temp_a3, s32, 0x18);
        SP32(0x108) = temp_v0_9;
        if (sp30 != 0) {
            SP32(0x108) = (temp_v0_9 / arg3) * arg2;
        }
        temp_v1_3 = FIELD(temp_a3, u16, 0x1A) + SP16(0x10A);
        SP16(0x7C) = temp_v1_3;
        SP16(0x6C) = temp_v1_3;
        temp_v0_10 = FIELD(temp_a3, u16, 0x2E);
        SP16(0x76) = temp_v0_10;
        SP16(0x66) = temp_v0_10;
        temp_v0_11 = sp2C - FIELD(temp_a3, s32, 0x2C);
        SP32(0x10C) = temp_v0_11;
        if (sp30 != 0) {
            SP32(0x10C) = (temp_v0_11 / arg3) * arg2;
        }
        temp_v0_12 = FIELD(temp_a3, u16, 0x2E);
        d10E = SP16(0x10E);
        SP32(0xB4) = func_80065590(sp34, scratch + 0x6C,
                                  scratch + 0x74, scratch + 0x7C,
                                  scratch + 0xD8, scratch + 0xDC,
                                  scratch + 0xE0, scratch + 0xE4,
                                  scratch + 0x84, scratch + 0x88,
                                  (temp_v0_12 += d10E,
                                   SP16(0x7E) = temp_v0_12,
                                   SP16(0x6E) = temp_v0_12,
                                   empty_arg));
        FIELD(temp_s1_3, u16, 8) = SP16(0xD8);
        FIELD(temp_s1_3, u16, 0xA) = SP16(0xDA);
        FIELD(temp_s1_3, u16, 0x10) = SP16(0xDC);
        FIELD(temp_s1_3, u16, 0x12) = SP16(0xDE);
        FIELD(temp_s1_3, u16, 0x18) = SP16(0xE0);
        FIELD(temp_s1_3, u16, 0x1A) = SP16(0xE2);
        FIELD(temp_s1_3, u16, 0x20) = SP16(0xE4);
        FIELD(temp_s1_3, u16, 0x22) = SP16(0xE6);
        temp_a0 = SP32(0xB4);
        if (temp_a0 < 0x1E0U) {
            idx4 = temp_a0 << 2;
            s0_value = (s32)0xFF000000;
            idx4 += SP32(0x18);
            FIELD(temp_s1_3, u32, 0) = (FIELD(temp_s1_3, u32, 0) & (u32)s0_value) |
                (*(u32 *)idx4 & low_mask);
            link = (u32 *)((SP32(0xB4) << 2) + SP32(0x18));
            *link = (*link & (u32)s0_value) | ((u32)temp_s1_3 & low_mask);
            {
                RenderContext *ctx = *(RenderContext **)new_var;
                    temp_s1_2 = ctx->nextPrim;
                ctx->nextPrim = temp_s1_2 + 0xC;
            }
            func_80067F20(temp_s1_2, 0, 0,
                         func_80066460(0, FIELD(arg0, s16, 0x12), 0, 0) & 0xFFFF,
                         0);
            FIELD(temp_s1_2, u32, 0) = (FIELD(temp_s1_2, u32, 0) & (u32)s0_value) |
                (((u32 *)SP32(0x18))[SP32(0xB4)] & low_mask);
            link = (u32 *)((SP32(0xB4) << 2) + SP32(0x18));
            *link = (*link & (u32)s0_value) | ((u32)temp_s1_2 & low_mask);
        }
    }
}
