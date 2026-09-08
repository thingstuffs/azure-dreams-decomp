#include "common.h"

typedef struct S_800D1824_0 {
    u8 pad_00[0x20];
    volatile u8 * unk_20;
    u8 pad_24[0x4];
    volatile s32 unk_28;
    volatile s16 unk_2C;
    u8 pad_2E[0x42];
    volatile s16 unk_70;
    volatile s16 unk_72;
    volatile u16 unk_74;
    u8 pad_76[0x2];
    volatile s16 unk_78;
    volatile s16 unk_7A;
    volatile u16 unk_7C;
    u8 pad_7E[0x2];
    volatile s16 unk_80;
    volatile s16 unk_82;
    volatile u16 unk_84;
    u8 pad_86[0x2];
    volatile s16 unk_88;
    volatile s16 unk_8A;
    volatile u16 unk_8C;
    u8 pad_8E[0x32];
    volatile s32 unk_C0;
    u8 pad_C4[0x8];
    volatile s32 unk_CC;
    u8 pad_D0[0x44];
    volatile s32 unk_114;
} S_800D1824_0;   /* scratch in func_800D1824 */

typedef struct S_800D1824_1 {
    u8 * unk_00;
    u8 pad_04[0x1DC];
    u8 * unk_1E0;
} S_800D1824_1;   /* globals in func_800D1824 */

typedef struct S_800D1824_2 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_800D1824_2;   /* root in func_800D1824 */

typedef struct S_800D1824_3_pre {
    u8 unk_00;
} S_800D1824_3_pre;   /* the 0x1 bytes before rec in func_800D1824, addressed as rec[-1] */

typedef struct S_800D1824_3 {
    union { u16 s; volatile u16 u; } unk_00;   /* accessed as both */
} S_800D1824_3;   /* rec in func_800D1824 */

typedef struct S_800D1824_4 {
    u8 pad_00[0x8];
    u32 unk_08;
    u32 unk_0C;
    u8 pad_10[0x2];
    u16 unk_12;
    u16 unk_14;
} S_800D1824_4;   /* style in func_800D1824 */

typedef struct S_800D1824_5 {
    u8 pad_00[0x10];
    u8 * unk_10;
} S_800D1824_5;   /* ((S_800D1824_1 *)globals)->unk_1E0 in func_800D1824 */

typedef struct S_800D1824_6 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_800D1824_6;   /* ((S_800D1824_1 *)globals)->unk_00 in func_800D1824 */



extern u8 D_80083160[];
extern void func_80065034(void *arg0, void *arg1, void *arg2);
extern void func_8006658C(s32 arg0, void *arg1);

void func_800D1824(u8 *arg0)
{
    register u8 *scratch ASM_REG("$16") = (u8 *)0x1F800000;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    u8 *globals = D_80083160;
    u8 *input = arg0;
    u8 *style;
    register u8 *prim ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 *rec;
    register u8 *cmd ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    u8 *gte0;
    u8 *root;
    u8 *draw_prim;
    u8 *vertex1;
    u8 *vertex2;
    s32 x;
    s32 y;
    s32 depth;
    s32 otz;
    u16 rec_value;

    ((S_800D1824_0 *)scratch)->unk_28 = 0;
    root = ((S_800D1824_1 *)globals)->unk_00;
    style = ((S_800D1824_5 *)(((S_800D1824_1 *)globals)->unk_1E0))->unk_10;
    prim = ((S_800D1824_2 *)root)->unk_8D0;
    ((S_800D1824_0 *)scratch)->unk_2C = -0x1000;
    ((S_800D1824_0 *)scratch)->unk_20 = root + 0xB0;

    ASM_KEEP(input);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    if (*input != 0) {
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        gte0 = scratch + 0x70;
        ASM_KEEP_NV(scratch);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        rec = arg0 + 2;
        cmd = prim + 3;

        do {
            if (((S_800D1824_3 *)rec)->unk_00.s != 0x8000) {
                do { vertex1 = scratch + 0x78; } while (0);
                x = (s32)*input << 6;
                ((S_800D1824_0 *)scratch)->unk_80 = (s16)x;
                ((S_800D1824_0 *)scratch)->unk_70 = (s16)x;
                x += 0x40;
                ((S_800D1824_0 *)scratch)->unk_88 = (s16)x;
                ((S_800D1824_0 *)scratch)->unk_78 = (s16)x;

                y = (s32)((S_800D1824_3_pre *)rec)[-1].unk_00 << 6;
                ((S_800D1824_0 *)scratch)->unk_7A = (s16)y;
                ((S_800D1824_0 *)scratch)->unk_72 = (s16)y;
                y += 0x40;
                ((S_800D1824_0 *)scratch)->unk_8A = (s16)y;
                ((S_800D1824_0 *)scratch)->unk_82 = (s16)y;

                rec_value = ((S_800D1824_3 *)rec)->unk_00.s;
                ((S_800D1824_0 *)scratch)->unk_84 = rec_value;
                ((S_800D1824_0 *)scratch)->unk_7C = rec_value;
                ((S_800D1824_0 *)scratch)->unk_74 = rec_value;

                vertex2 = scratch + 0x80;
                gte_ldv3(gte0, vertex1, vertex2);
                ((S_800D1824_0 *)scratch)->unk_8C =
                    ((S_800D1824_3 *)rec)->unk_00.u;
                gte_rtpt_nn();
                gte_nclip();
                gte_stopz(scratch + 0x114);

                if (((S_800D1824_0 *)scratch)->unk_114 > 0) {
                    gte_stsxy3_g3(prim);
                    gte_avsz3();
                    gte_stotz(scratch + 0xC0);
                    gte_ldv0(scratch + 0x88);
                    otz = ((S_800D1824_0 *)scratch)->unk_C0;
                    otz = otz * 3;
                    ((S_800D1824_0 *)scratch)->unk_C0 = otz;

                    gte_rtps_nn();
                    gte_stszotz(scratch + 0xCC);
                    depth = (((S_800D1824_0 *)scratch)->unk_C0 +
                             ((S_800D1824_0 *)scratch)->unk_CC) >> 2;
                    ((S_800D1824_0 *)scratch)->unk_C0 = depth;

                    if ((u32)depth < 0x1E0) {
                        gte_stsxy(prim + 0x20);
                        draw_prim = prim;
                        func_80065034(scratch + 0x28, globals + 0xA8,
                                     prim + 4);

                        (*(u32 *)((u8 *)cmd + 9)) = ((S_800D1824_4 *)style)->unk_08;
                        (*(u32 *)((u8 *)cmd + 0x11)) = ((S_800D1824_4 *)style)->unk_0C;
                        (*(u16 *)((u8 *)cmd + 0x19)) = ((S_800D1824_4 *)style)->unk_12;
                        prim += 0x28;
                        (*(u16 *)((u8 *)cmd + 0x21)) = ((S_800D1824_4 *)style)->unk_14;
                        cmd[0] = 9;
                        cmd += 0x28;
                        func_8006658C(
                            (s32)((S_800D1824_0 *)scratch)->unk_20 +
                                (((S_800D1824_0 *)scratch)->unk_C0 << 2),
                            draw_prim);
                    }
                }
            }

            input += 4;
            rec += 4;
        } while (*input != 0);
    }

    ((S_800D1824_6 *)(((S_800D1824_1 *)globals)->unk_00))->unk_8D0 = prim;
}
