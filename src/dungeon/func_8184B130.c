#include "common.h"

typedef struct S_80024930_0 {
    u8 pad_00[0x18];
    union { void * p; u8 * p2; } unk_18;   /* accessed as both */
    u8 pad_1C[0x48];
    s16 unk_64;
    s16 unk_66;
    s16 unk_68;
    u8 pad_6A[0x2];
    s16 unk_6C;
    s16 unk_6E;
    s16 unk_70;
    u8 pad_72[0x2];
    s16 unk_74;
    s16 unk_76;
    s16 unk_78;
    u8 pad_7A[0x2];
    s16 unk_7C;
    s16 unk_7E;
    s16 unk_80;
    u8 pad_82[0x32];
    u32 unk_B4;
    u8 pad_B8[0x20];
    u16 unk_D8;
    u16 unk_DA;
    u16 unk_DC;
    u16 unk_DE;
    u16 unk_E0;
    u16 unk_E2;
    u16 unk_E4;
    u16 unk_E6;
} S_80024930_0;   /* scratch in func_80024930 */

typedef struct S_80024930_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80024930_1;   /* arg1 in func_80024930 */

typedef struct S_80024930_2 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_80024930_2;   /* *global_page in func_80024930 */

typedef struct S_80024930_3 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_00;   /* overlapping accesses */
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 unk_07;
    u16 unk_08;
    u16 unk_0A;
    u8 unk_0C;
    u8 unk_0D;
    u16 unk_0E;
    u8 unk_10;
    u8 unk_11;
    u8 unk_12;
    u8 pad_13[0x1];
    u16 unk_14;
    u16 unk_16;
    u8 unk_18;
    u8 unk_19;
    u16 unk_1A;
    u8 unk_1C;
    u8 unk_1D;
    u8 unk_1E;
    u8 pad_1F[0x1];
    u16 unk_20;
    u16 unk_22;
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x2];
    u8 unk_28;
    u8 unk_29;
    u8 unk_2A;
    u8 pad_2B[0x1];
    u16 unk_2C;
    u16 unk_2E;
    u8 unk_30;
    u8 unk_31;
} S_80024930_3;   /* prim in func_80024930 */

typedef struct S_80024930_4 {
    u32 unk_00;
} S_80024930_4;   /* (void *)offset in func_80024930 */



extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern u32 func_80065590(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern u8 D_80083160[];

s32 func_80024930(void *arg0, S_80024930_1 *arg1, s32 arg2, s16 arg3,
                  s32 arg4, s16 arg5, u8 arg6, u8 arg7)
{
    u8 *scratch = (u8 *)0x1F800000;
    s32 edge;
    s16 i;
    void **global_page = (void **)D_80083160;

    ((S_80024930_0 *)scratch)->unk_18.p = (u8 *)(*global_page) + 0xB0;
    edge = arg1->unk_0A - arg4 + 1;
    ((S_80024930_0 *)scratch)->unk_70 = edge;
    ((S_80024930_0 *)scratch)->unk_68 = edge;
    edge = arg1->unk_0A;
    ((S_80024930_0 *)scratch)->unk_78 = edge;
    ((S_80024930_0 *)scratch)->unk_80 = edge;

    for (i = 0; i < 16; i++) {
        register u8 *prim;
        register s32 angle1 ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        s32 scaled;
        s32 rawAngle;
        s32 adjusted;
        s32 angle0;

        prim = ((S_80024930_2 *)(*global_page))->unk_8D0;

        ((S_80024930_2 *)(*global_page))->unk_8D0 = prim + 0x34;
        ((S_80024930_3 *)prim)->unk_00.at03.v = 12;
        ((S_80024930_3 *)prim)->unk_07 = 0x3C;

        if (arg6 == 4) {
            ((S_80024930_3 *)prim)->unk_1A = func_80066460(0, 0, 0x280, 0x100);
        } else {
            ((S_80024930_3 *)prim)->unk_07 = 0x3E;
            ((S_80024930_3 *)prim)->unk_1A =
                func_80066460(0, arg6, 0x280, 0x100);
        }

        {
            register s32 flag ASM_REG("$3") = 0x3F;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

            ((S_80024930_3 *)prim)->unk_0C = 0;
            ((S_80024930_3 *)prim)->unk_18 = flag;
            ((S_80024930_3 *)prim)->unk_24 = 0;
            ((S_80024930_3 *)prim)->unk_30 = flag;
        }
        ((S_80024930_3 *)prim)->unk_04 = 0;
        ((S_80024930_3 *)prim)->unk_05 = 0;
        ((S_80024930_3 *)prim)->unk_06 = 0;
        ((S_80024930_3 *)prim)->unk_10 = 0;
        ((S_80024930_3 *)prim)->unk_11 = 0;
        ((S_80024930_3 *)prim)->unk_12 = 0;
        ((S_80024930_3 *)prim)->unk_1C = arg7;
        ((S_80024930_3 *)prim)->unk_1D = arg7;
        ((S_80024930_3 *)prim)->unk_1E = arg7;
        ((S_80024930_3 *)prim)->unk_28 = arg7;
        ((S_80024930_3 *)prim)->unk_29 = arg7;
        ((S_80024930_3 *)prim)->unk_2A = arg7;

        scaled = (s16)i * 0x100;
        rawAngle = scaled + arg3;
        adjusted = rawAngle;
        ((S_80024930_3 *)prim)->unk_0E = 0x7E00;
        ((S_80024930_3 *)prim)->unk_0D = 0x80;
        ((S_80024930_3 *)prim)->unk_19 = 0x80;
        ((S_80024930_3 *)prim)->unk_25 = 0xBF;
        ((S_80024930_3 *)prim)->unk_31 = 0xBF;
        if (rawAngle < 0) {
            adjusted = rawAngle + 0xFFF;
        }
        scaled = (adjusted >> 12) << 12;
        angle0 = rawAngle - scaled;

        ((S_80024930_0 *)scratch)->unk_74 = arg1->unk_02 +
            ((func_800644B8(angle0) >> 4) * arg5 >> 8);
        ((S_80024930_0 *)scratch)->unk_64 = ((S_80024930_0 *)scratch)->unk_74;

        angle1 = ((((s16)i + 1) % 16) * 0x100 + arg3) % 0x1000;
        ((S_80024930_0 *)scratch)->unk_7C = arg1->unk_02 +
            ((func_800644B8(angle1) >> 4) * arg5 >> 8);
        ((S_80024930_0 *)scratch)->unk_6C = ((S_80024930_0 *)scratch)->unk_7C;

        ((S_80024930_0 *)scratch)->unk_76 = arg1->unk_06 +
            ((func_80064584(angle0) >> 4) * arg5 >> 8);
        ((S_80024930_0 *)scratch)->unk_66 = ((S_80024930_0 *)scratch)->unk_76;

        ((S_80024930_0 *)scratch)->unk_7E = arg1->unk_06 +
            ((func_80064584(angle1) >> 4) * arg5 >> 8);
        ((S_80024930_0 *)scratch)->unk_6E = ((S_80024930_0 *)scratch)->unk_7E;

        ((S_80024930_0 *)scratch)->unk_B4 = func_80065590(
            scratch + 0x64, scratch + 0x6C, scratch + 0x74, scratch + 0x7C,
            scratch + 0xD8, scratch + 0xDC, scratch + 0xE0, scratch + 0xE4,
            scratch + 0x84, scratch + 0x88);

        ((S_80024930_3 *)prim)->unk_08 = ((S_80024930_0 *)scratch)->unk_D8;
        ((S_80024930_3 *)prim)->unk_0A = ((S_80024930_0 *)scratch)->unk_DA;
        ((S_80024930_3 *)prim)->unk_14 = ((S_80024930_0 *)scratch)->unk_DC;
        ((S_80024930_3 *)prim)->unk_16 = ((S_80024930_0 *)scratch)->unk_DE;
        ((S_80024930_3 *)prim)->unk_20 = ((S_80024930_0 *)scratch)->unk_E0;
        ((S_80024930_3 *)prim)->unk_22 = ((S_80024930_0 *)scratch)->unk_E2;
        ((S_80024930_3 *)prim)->unk_2C = ((S_80024930_0 *)scratch)->unk_E4;
        ((S_80024930_3 *)prim)->unk_2E = ((S_80024930_0 *)scratch)->unk_E6;

        {
            u32 index = ((S_80024930_0 *)scratch)->unk_B4;

            if (index < 0x1E0U) {
                register u32 lowMask ASM_REG("$4") = 0x00FFFFFFU;   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
                u32 offset = index * 4;

                index = 0xFF000000U;
                offset += (u32)((S_80024930_0 *)scratch)->unk_18.p2;
                ((S_80024930_3 *)prim)->unk_00.at00.v = (((S_80024930_3 *)prim)->unk_00.at00.v & index) |
                    (((S_80024930_4 *)((void *)offset))->unk_00 & lowMask);
                (*(u32 *)((u8 *)(((S_80024930_0 *)scratch)->unk_18.p2) + ((S_80024930_0 *)scratch)->unk_B4 * 4)) =
                    ((*(u32 *)((u8 *)(((S_80024930_0 *)scratch)->unk_18.p2) + ((S_80024930_0 *)scratch)->unk_B4 * 4)) & index) |
                    ((u32)prim & lowMask);
            }
        }
    }

    return 0;
}
