#include "common.h"

typedef struct S_800BBDEC_0 {
    u8 pad_00[0x20];
    void * unk_20;
    u8 pad_24[0x4C];
    s16 unk_70;
    s16 unk_72;
    s16 unk_74;
    u8 pad_76[0x2];
    s16 unk_78;
    s16 unk_7A;
    s16 unk_7C;
    u8 pad_7E[0x2];
    s16 unk_80;
    s16 unk_82;
    s16 unk_84;
    u8 pad_86[0x2];
    s16 unk_88;
    s16 unk_8A;
    s16 unk_8C;
    u8 pad_8E[0x32];
    u32 unk_C0;
    u8 pad_C4[0x20];
    s32 unk_E4;
    s32 unk_E8;
    s32 unk_EC;
    u8 pad_F0[0x10];
    u16 unk_100;
    u16 unk_102;
    u16 unk_104;
} S_800BBDEC_0;   /* scratch in func_800BBDEC */

typedef struct S_800BBDEC_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800BBDEC_1;   /* arg1 in func_800BBDEC */

typedef struct S_800BBDEC_2 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_800BBDEC_2;   /* *global in func_800BBDEC */

typedef struct S_800BBDEC_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
} S_800BBDEC_3;   /* arg2 in func_800BBDEC */

typedef struct S_800BBDEC_4 {
    u8 pad_00[0x50];
    u16 unk_50;
} S_800BBDEC_4;   /* arg0 in func_800BBDEC */

typedef struct S_800BBDEC_5 {
    u8 pad_00[0x4];
    union { struct { s32 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; struct { u8 pad[0x3]; u8 v; } at03; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x4];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_800BBDEC_5;   /* prim in func_800BBDEC */



extern void func_80064840(void *, void *, void *);
extern void func_800649A0(void);
extern void func_80064A40(void);
extern void func_80064AE0(void *);
extern void func_80064CF0(void *);
extern void func_80064D80(void *);
extern u32 func_80065590(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern void func_80065820(void *, void *);
extern void func_8006658C(void *, void *);
extern void func_80066708(void *);
extern void func_80067F20(void *, s32, s32, s32, s32);
extern u8 D_80083160[];

/* Projects and queues a shaded quad with optional semitransparency. */
void func_800BBDEC(S_800BBDEC_4 *object, S_800BBDEC_1 *position, S_800BBDEC_3 *appearance)
{
    u8 *scratch = (u8 *)0x1F800000;
    void **render_ctx = (void **)D_80083160;
    u8 *prim;
    u32 depth_index;
    s32 color_word;
    s16 end_z;

    ((S_800BBDEC_0 *)scratch)->unk_20 = (u8 *)*render_ctx + 0xB0;
    ((S_800BBDEC_0 *)scratch)->unk_E4 = position->unk_02;
    ((S_800BBDEC_0 *)scratch)->unk_E8 = position->unk_06;
    ((S_800BBDEC_0 *)scratch)->unk_EC = position->unk_0A;
    prim = ((S_800BBDEC_2 *)(*render_ctx))->unk_8D0;

    func_800649A0();

    ((S_800BBDEC_0 *)scratch)->unk_100 = appearance->unk_16;
    ((S_800BBDEC_0 *)scratch)->unk_104 = appearance->unk_1A;
    ((S_800BBDEC_0 *)scratch)->unk_102 = appearance->unk_18;
    func_80065820(scratch + 0x100, scratch + 0xD0);
    func_80064AE0(scratch + 0x11C);
    func_80064840(scratch + 0x11C, scratch + 0xD0, scratch + 0x50);
    func_80064D80(scratch + 0x50);
    func_80064CF0(scratch + 0x50);

    ((S_800BBDEC_0 *)scratch)->unk_7C = 0;
    ((S_800BBDEC_0 *)scratch)->unk_74 = 0;
    end_z = -object->unk_50;
    ((S_800BBDEC_0 *)scratch)->unk_88 = 0x10;
    ((S_800BBDEC_0 *)scratch)->unk_78 = 0x10;
    ((S_800BBDEC_0 *)scratch)->unk_80 = 0;
    ((S_800BBDEC_0 *)scratch)->unk_70 = 0;
    ((S_800BBDEC_0 *)scratch)->unk_7A = 0;
    ((S_800BBDEC_0 *)scratch)->unk_72 = 0;
    ((S_800BBDEC_0 *)scratch)->unk_8A = 0;
    ((S_800BBDEC_0 *)scratch)->unk_82 = 0;
    ((S_800BBDEC_0 *)scratch)->unk_8C = end_z;
    ((S_800BBDEC_0 *)scratch)->unk_84 = end_z;

    depth_index = func_80065590(scratch + 0x70, scratch + 0x78,
                          scratch + 0x80, scratch + 0x88,
                          prim + 8, prim + 0x10, prim + 0x18, prim + 0x20,
                          scratch + 0x90, scratch + 0x94);
    ((S_800BBDEC_0 *)scratch)->unk_C0 = depth_index;

    if (depth_index < 0x1E0U) {
        color_word = appearance->unk_0C;
        ((S_800BBDEC_5 *)prim)->unk_14 = 0;
        ((S_800BBDEC_5 *)prim)->unk_1C = 0;
        ((S_800BBDEC_5 *)prim)->unk_04.at00.v = color_word;
        ((S_800BBDEC_5 *)prim)->unk_0C = ((S_800BBDEC_5 *)prim)->unk_04.at00u.v >> 2;
        ((S_800BBDEC_5 *)prim)->unk_0D = ((S_800BBDEC_5 *)prim)->unk_04.at01.v >> 2;
        ((S_800BBDEC_5 *)prim)->unk_0E = ((S_800BBDEC_5 *)prim)->unk_04.at02.v >> 2;
        func_80066708(prim);

        if (appearance->unk_14 & 4) {
            ((S_800BBDEC_5 *)prim)->unk_04.at03.v |= 2;
        }

        func_8006658C((u8 *)((S_800BBDEC_0 *)scratch)->unk_20 +
                          ((S_800BBDEC_0 *)scratch)->unk_C0 * 4,
                      prim);
        prim += 0x24;

        if (appearance->unk_14 & 4) {
            func_80067F20(prim, 0, 0, 0x20, 0);
            func_8006658C((u8 *)((S_800BBDEC_0 *)scratch)->unk_20 +
                              ((S_800BBDEC_0 *)scratch)->unk_C0 * 4,
                          prim);
            prim += 0xC;
        }
    }

    func_80064A40();
    ((S_800BBDEC_2 *)(*render_ctx))->unk_8D0 = prim;
}
