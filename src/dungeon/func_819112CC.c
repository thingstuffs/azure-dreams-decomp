#include "common.h"

typedef struct S_819112CC_0 {
    u8 pad_00[0xA];
    s16 unk_0A;
    u8 pad_0C[0x2];
    s16 unk_0E;
    u16 unk_10;
    s16 unk_12;
    u8 pad_14[0x2C];
    u8 unk_40;
    u8 unk_41;
    u8 unk_42;
} S_819112CC_0;   /* arg0 in func_819112CC */

typedef struct S_819112CC_1 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_819112CC_1;   /* arg1 in func_819112CC */

typedef struct S_819112CC_2 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; s8 v; } at03; } unk_00;   /* overlapping accesses */
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    s8 unk_07;
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
} S_819112CC_2;   /* temp_s1 in func_819112CC */

typedef struct S_819112CC_3 {
    u8 pad_00[0x18];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_18;   /* overlapping accesses */
    u8 pad_1C[0x10];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_2C;   /* overlapping accesses */
} S_819112CC_3;   /* temp_a3 in func_819112CC */

typedef struct S_819112CC_4 {
    u32 unk_00;
} S_819112CC_4;   /* temp_s1_2 in func_819112CC */

typedef struct S_819112CC_5 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; s8 v; } at03; } unk_00;   /* overlapping accesses */
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    s8 unk_07;
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
} S_819112CC_5;   /* temp_s1_3 in func_819112CC */


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

void func_819112CC(void *arg0_in, S_819112CC_1 *arg1, s16 arg2_in, s16 arg3_in)
{
    void *arg0 = arg0_in;
    s32 arg2 = arg2_in;
    s32 arg3 = arg3_in;
    register u32 low_mask ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *prim;
    register s32 s0_value ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
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
    register u32 *link ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 call_coord ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
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
    register u32 temp_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 *temp_a3;
    register s32 idx4 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register u8 *scratch ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
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
        call_coord = s0_value + ((S_819112CC_0 *)arg0)->unk_0A;
        projected_x = func_800644B8(call_coord);
        call_coord = ((S_819112CC_0 *)arg0)->unk_0A;
        call_coord = s0_value + call_coord;
        s0_value = arg1->unk_00;
        s0_value += (((projected_x >> 4) *
                     ((S_819112CC_0 *)arg0)->unk_0E) << 8);
        ASM_KEEP_NV(s0_value);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        idx4 = func_80064584(call_coord);
        sp28 = s0_value;
        idx4 >>= 4;
        c2 = arg1->unk_04 +
            ((idx4 * ((S_819112CC_0 *)arg0)->unk_0E) << 8);
        sp2C = c2;
        {
            RenderContext **pool = (RenderContext **)new_var;
            temp_s1 = (*pool)->nextPrim;
            (*pool)->nextPrim = temp_s1 + 0x24;
        }
        ((S_819112CC_2 *)temp_s1)->unk_00.at03.v = 8;
        ((S_819112CC_2 *)temp_s1)->unk_07 = 0x3A;
        ((S_819112CC_2 *)temp_s1)->unk_04 = ((S_819112CC_0 *)arg0)->unk_40;
        ((S_819112CC_2 *)temp_s1)->unk_05 = ((S_819112CC_0 *)arg0)->unk_41;
        ((S_819112CC_2 *)temp_s1)->unk_06 = ((S_819112CC_0 *)arg0)->unk_42;
        ((S_819112CC_2 *)temp_s1)->unk_0C = ((S_819112CC_0 *)arg0)->unk_40;
        ((S_819112CC_2 *)temp_s1)->unk_0D = ((S_819112CC_0 *)arg0)->unk_41;
        ((S_819112CC_2 *)temp_s1)->unk_0E = ((S_819112CC_0 *)arg0)->unk_42;
        ((S_819112CC_2 *)temp_s1)->unk_14 = ((S_819112CC_0 *)arg0)->unk_40;
        ((S_819112CC_2 *)temp_s1)->unk_15 = ((S_819112CC_0 *)arg0)->unk_41;
        ((S_819112CC_2 *)temp_s1)->unk_16 = ((S_819112CC_0 *)arg0)->unk_42;
        ((S_819112CC_2 *)temp_s1)->unk_1C = ((S_819112CC_0 *)arg0)->unk_40;
        ((S_819112CC_2 *)temp_s1)->unk_1D = ((S_819112CC_0 *)arg0)->unk_41;
        idx4 = var_s5 * 4;
        temp_a3 = (u8 *)arg0 + idx4;
        ((S_819112CC_2 *)temp_s1)->unk_1E = ((S_819112CC_0 *)arg0)->unk_42;
        temp_v0_2 = ((S_819112CC_3 *)temp_a3)->unk_18.at02.v;
        SP16(0x74) = temp_v0_2;
        SP16(0x64) = temp_v0_2;
        temp_v1 = s0_value - ((S_819112CC_3 *)temp_a3)->unk_18.at00.v;
        SP32(0x108) = temp_v1;
        if (sp30 != 0) {
            SP32(0x108) = (temp_v1 / arg3) * arg2;
        }
        temp_v1_2 = ((S_819112CC_3 *)temp_a3)->unk_18.at02.v + SP16(0x10A);
        SP16(0x7C) = temp_v1_2;
        SP16(0x6C) = temp_v1_2;
        temp_v0_3 = ((S_819112CC_3 *)temp_a3)->unk_2C.at02.v;
        SP16(0x76) = temp_v0_3;
        SP16(0x66) = temp_v0_3;
        temp_v0_4 = c2 - ((S_819112CC_3 *)temp_a3)->unk_2C.at00.v;
        SP32(0x10C) = temp_v0_4;
        if (sp30 != 0) {
            SP32(0x10C) = (temp_v0_4 / arg3) * arg2;
        }
        temp_v0_5 = ((S_819112CC_3 *)temp_a3)->unk_2C.at02.v + SP16(0x10E);
        SP16(0x7E) = temp_v0_5;
        SP16(0x6E) = temp_v0_5;
        temp_v0_6 = arg1->unk_0A - ((S_819112CC_0 *)arg0)->unk_10;
        SP16(0x70) = temp_v0_6;
        SP16(0x68) = temp_v0_6;
        temp_v0_7 = arg1->unk_0A;
        SP32(0xB4) = func_80065590(sp34, scratch + 0x6C,
                                  scratch + 0x74, scratch + 0x7C,
                                  scratch + 0xD8, scratch + 0xDC,
                                  scratch + 0xE0, scratch + 0xE4,
                                  scratch + 0x84, scratch + 0x88,
                                  (SP16(0x78) = temp_v0_7,
                                   SP16(0x80) = temp_v0_7,
                                   empty_arg));
        ((S_819112CC_2 *)temp_s1)->unk_08 = SP16(0xD8);
        ((S_819112CC_2 *)temp_s1)->unk_0A = SP16(0xDA);
        ((S_819112CC_2 *)temp_s1)->unk_10 = SP16(0xDC);
        ((S_819112CC_2 *)temp_s1)->unk_12 = SP16(0xDE);
        ((S_819112CC_2 *)temp_s1)->unk_18 = SP16(0xE0);
        ((S_819112CC_2 *)temp_s1)->unk_1A = SP16(0xE2);
        ((S_819112CC_2 *)temp_s1)->unk_20 = SP16(0xE4);
        ((S_819112CC_2 *)temp_s1)->unk_22 = SP16(0xE6);
        temp_a0 = SP32(0xB4);
        if (temp_a0 < 0x1E0U) {
            idx4 = temp_a0 << 2;
            s0_value = (s32)0xFF000000;
            idx4 += SP32(0x18);
            ((S_819112CC_2 *)temp_s1)->unk_00.at00.v = (((S_819112CC_2 *)temp_s1)->unk_00.at00.v & (u32)s0_value) |
                (*(u32 *)idx4 & low_mask);
            link = (u32 *)((SP32(0xB4) << 2) + SP32(0x18));
            *link = (*link & (u32)s0_value) | ((u32)temp_s1 & low_mask);
            {
                RenderContext *ctx = *(RenderContext **)new_var;
                    temp_s1_2 = ctx->nextPrim;
                ctx->nextPrim = temp_s1_2 + 0xC;
            }
            func_80067F20(temp_s1_2, 0, 0,
                         func_80066460(0, ((S_819112CC_0 *)arg0)->unk_12, 0, 0) & 0xFFFF,
                         0);
            ((S_819112CC_4 *)temp_s1_2)->unk_00 = (((S_819112CC_4 *)temp_s1_2)->unk_00 & (u32)s0_value) |
                (((u32 *)SP32(0x18))[SP32(0xB4)] & low_mask);
            link = (u32 *)((SP32(0xB4) << 2) + SP32(0x18));
            *link = (*link & (u32)s0_value) | ((u32)temp_s1_2 & low_mask);
        }
        {
            RenderContext **pool = (RenderContext **)new_var;
            temp_s1_3 = (*pool)->nextPrim;
            (*pool)->nextPrim = temp_s1_3 + 0x24;
        }
        ((S_819112CC_5 *)temp_s1_3)->unk_00.at03.v = 8;
        ((S_819112CC_5 *)temp_s1_3)->unk_07 = 0x3A;
        ((S_819112CC_5 *)temp_s1_3)->unk_04 = ((S_819112CC_0 *)arg0)->unk_40;
        ((S_819112CC_5 *)temp_s1_3)->unk_05 = ((S_819112CC_0 *)arg0)->unk_41;
        ((S_819112CC_5 *)temp_s1_3)->unk_06 = ((S_819112CC_0 *)arg0)->unk_42;
        var_s5 += 1;
        ((S_819112CC_5 *)temp_s1_3)->unk_0C = ((S_819112CC_0 *)arg0)->unk_40;
        ((S_819112CC_5 *)temp_s1_3)->unk_0D = ((S_819112CC_0 *)arg0)->unk_41;
        ((S_819112CC_5 *)temp_s1_3)->unk_0E = ((S_819112CC_0 *)arg0)->unk_42;
        ((S_819112CC_5 *)temp_s1_3)->unk_14 = ((S_819112CC_0 *)arg0)->unk_40;
        ((S_819112CC_5 *)temp_s1_3)->unk_15 = ((S_819112CC_0 *)arg0)->unk_41;
        ((S_819112CC_5 *)temp_s1_3)->unk_16 = ((S_819112CC_0 *)arg0)->unk_42;
        ((S_819112CC_5 *)temp_s1_3)->unk_1C = ((S_819112CC_0 *)arg0)->unk_40;
        ((S_819112CC_5 *)temp_s1_3)->unk_1D = ((S_819112CC_0 *)arg0)->unk_41;
        idx4 = ((S_819112CC_0 *)arg0)->unk_42;
        ((S_819112CC_5 *)temp_s1_3)->unk_1E = idx4;
        idx4 = var_s5 % 5;
        idx4 *= 4;
        temp_a3 = (u8 *)arg0 + idx4;
        ASM_KEEP_NV(var_s5);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        temp_v0_8 = ((S_819112CC_3 *)temp_a3)->unk_18.at02.v;
        SP16(0x74) = temp_v0_8;
        SP16(0x64) = temp_v0_8;
        temp_v0_9 = sp28 - ((S_819112CC_3 *)temp_a3)->unk_18.at00.v;
        SP32(0x108) = temp_v0_9;
        if (sp30 != 0) {
            SP32(0x108) = (temp_v0_9 / arg3) * arg2;
        }
        temp_v1_3 = ((S_819112CC_3 *)temp_a3)->unk_18.at02.v + SP16(0x10A);
        SP16(0x7C) = temp_v1_3;
        SP16(0x6C) = temp_v1_3;
        temp_v0_10 = ((S_819112CC_3 *)temp_a3)->unk_2C.at02.v;
        SP16(0x76) = temp_v0_10;
        SP16(0x66) = temp_v0_10;
        temp_v0_11 = sp2C - ((S_819112CC_3 *)temp_a3)->unk_2C.at00.v;
        SP32(0x10C) = temp_v0_11;
        if (sp30 != 0) {
            SP32(0x10C) = (temp_v0_11 / arg3) * arg2;
        }
        temp_v0_12 = ((S_819112CC_3 *)temp_a3)->unk_2C.at02.v;
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
        ((S_819112CC_5 *)temp_s1_3)->unk_08 = SP16(0xD8);
        ((S_819112CC_5 *)temp_s1_3)->unk_0A = SP16(0xDA);
        ((S_819112CC_5 *)temp_s1_3)->unk_10 = SP16(0xDC);
        ((S_819112CC_5 *)temp_s1_3)->unk_12 = SP16(0xDE);
        ((S_819112CC_5 *)temp_s1_3)->unk_18 = SP16(0xE0);
        ((S_819112CC_5 *)temp_s1_3)->unk_1A = SP16(0xE2);
        ((S_819112CC_5 *)temp_s1_3)->unk_20 = SP16(0xE4);
        ((S_819112CC_5 *)temp_s1_3)->unk_22 = SP16(0xE6);
        temp_a0 = SP32(0xB4);
        if (temp_a0 < 0x1E0U) {
            idx4 = temp_a0 << 2;
            s0_value = (s32)0xFF000000;
            idx4 += SP32(0x18);
            ((S_819112CC_5 *)temp_s1_3)->unk_00.at00.v = (((S_819112CC_5 *)temp_s1_3)->unk_00.at00.v & (u32)s0_value) |
                (*(u32 *)idx4 & low_mask);
            link = (u32 *)((SP32(0xB4) << 2) + SP32(0x18));
            *link = (*link & (u32)s0_value) | ((u32)temp_s1_3 & low_mask);
            {
                RenderContext *ctx = *(RenderContext **)new_var;
                    temp_s1_2 = ctx->nextPrim;
                ctx->nextPrim = temp_s1_2 + 0xC;
            }
            func_80067F20(temp_s1_2, 0, 0,
                         func_80066460(0, ((S_819112CC_0 *)arg0)->unk_12, 0, 0) & 0xFFFF,
                         0);
            ((S_819112CC_4 *)temp_s1_2)->unk_00 = (((S_819112CC_4 *)temp_s1_2)->unk_00 & (u32)s0_value) |
                (((u32 *)SP32(0x18))[SP32(0xB4)] & low_mask);
            link = (u32 *)((SP32(0xB4) << 2) + SP32(0x18));
            *link = (*link & (u32)s0_value) | ((u32)temp_s1_2 & low_mask);
        }
    }
}
