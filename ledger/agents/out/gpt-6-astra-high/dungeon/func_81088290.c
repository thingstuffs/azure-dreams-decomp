#include "common.h"

typedef struct S_80175A90_0 {
    u8 pad_00[0x18];
    union { void * p; u32 * p2; } unk_18;   /* accessed as both */
    u8 pad_1C[0x48];
    u16 unk_64;
    u16 unk_66;
    u16 unk_68;
    u8 pad_6A[0x2];
    union { s16 s; u16 u; } unk_6C;   /* accessed as both */
    union { s16 s; u16 u; } unk_6E;   /* accessed as both */
    union { s16 s; u16 u; } unk_70;   /* accessed as both */
    u8 pad_72[0x2];
    u16 unk_74;
    u16 unk_76;
    u16 unk_78;
    u8 pad_7A[0x3A];
    union { s32 s; u32 u; } unk_B4;   /* accessed as both */
    u8 pad_B8[0x20];
    u16 unk_D8;
    u16 unk_DA;
    u16 unk_DC;
    u16 unk_DE;
    u16 unk_E0;
    u16 unk_E2;
} S_80175A90_0;   /* scratch in func_80175A90 */

typedef struct S_80175A90_1 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_80175A90_1;   /* context in func_80175A90 */

typedef struct S_80175A90_2 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_00;   /* overlapping accesses */
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 unk_07;
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
    u32 unk_1C;
} S_80175A90_2;   /* prim in func_80175A90 */

typedef struct S_80175A90_3 {
    u8 pad_00[0x2];
    union { u16 u; s16 s; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { u16 u; s16 s; } unk_06;   /* accessed as both */
    u8 pad_08[0x2];
    union { u16 u; s16 s; } unk_0A;   /* accessed as both */
} S_80175A90_3;   /* arg0 in func_80175A90 */

typedef struct S_80175A90_4 {
    u8 pad_00[0x2];
    union { s16 s; u16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { s16 s; u16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x2];
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
} S_80175A90_4;   /* arg1 in func_80175A90 */



extern u8 D_80083160[];
extern s32 rand(void);
extern s32 func_80065530(void *, void *, void *, void *, void *, void *, void *, void *);

/* Draw seven shaded polylines with randomized offsets between two positions. */
void func_80175A90(S_80175A90_3 *start_pos, S_80175A90_4 *end_pos)
{
    void **context_ptr = (void **)D_80083160;
    u8 *scratch = (u8 *)0x1F800000;
    u8 *prim;
    s32 line_index = 0;
    s32 endpoint_red = 0xC0;
    u32 addr_mask = 0x00FFFFFF;
    u32 length_mask = 0xFF000000;

    ((S_80175A90_0 *)scratch)->unk_18.p = (u8 *)*context_ptr + 0xB0;

    do {
        S_80175A90_1 *context = *context_ptr;
        s32 offset;

        prim = context->unk_8D0;
        context->unk_8D0 = prim + 0x20;

        ((S_80175A90_2 *)prim)->unk_07 = 0x58;
        ((S_80175A90_2 *)prim)->unk_00.at03.v = 7;
        ((S_80175A90_2 *)prim)->unk_1C = 0x55555555;
        ((S_80175A90_2 *)prim)->unk_07 |= 2;

        ((S_80175A90_0 *)scratch)->unk_64 = start_pos->unk_02.u;
        ((S_80175A90_0 *)scratch)->unk_66 = start_pos->unk_06.u;
        ((S_80175A90_0 *)scratch)->unk_68 = start_pos->unk_0A.u;

        ((S_80175A90_0 *)scratch)->unk_6C.s =
            (start_pos->unk_02.s + end_pos->unk_02.s) / 2;
        ((S_80175A90_0 *)scratch)->unk_6E.s =
            (start_pos->unk_06.s + end_pos->unk_06.s) / 2;
        ((S_80175A90_0 *)scratch)->unk_70.s =
            (start_pos->unk_0A.s + end_pos->unk_0A.s) / 2;

        ((S_80175A90_0 *)scratch)->unk_74 = end_pos->unk_02.u;
        ((S_80175A90_0 *)scratch)->unk_76 = end_pos->unk_06.u;
        ((S_80175A90_0 *)scratch)->unk_78 = end_pos->unk_0A.u;

        offset = (rand() % 9) + 4;
        switch (line_index) {
        case 0:
            ((S_80175A90_0 *)scratch)->unk_64 -= 2;
            ((S_80175A90_0 *)scratch)->unk_6C.u += offset;
            ((S_80175A90_0 *)scratch)->unk_74 -= offset;
            break;
        case 1:
            ((S_80175A90_0 *)scratch)->unk_66 -= 2;
            ((S_80175A90_0 *)scratch)->unk_6E.u += offset;
            ((S_80175A90_0 *)scratch)->unk_76 -= offset;
            break;
        case 2:
            ((S_80175A90_0 *)scratch)->unk_68 -= 2;
            ((S_80175A90_0 *)scratch)->unk_70.u += offset;
            ((S_80175A90_0 *)scratch)->unk_78 -= offset;
            break;
        case 3:
            ((S_80175A90_0 *)scratch)->unk_64 += 2;
            ((S_80175A90_0 *)scratch)->unk_6C.u -= offset;
            ((S_80175A90_0 *)scratch)->unk_74 += offset;
            break;
        case 4:
            ((S_80175A90_0 *)scratch)->unk_66 += 2;
            ((S_80175A90_0 *)scratch)->unk_6E.u -= offset;
            ((S_80175A90_0 *)scratch)->unk_76 += offset;
            break;
        case 5:
            ((S_80175A90_0 *)scratch)->unk_68 += 2;
            ((S_80175A90_0 *)scratch)->unk_70.u -= offset;
            ((S_80175A90_0 *)scratch)->unk_78 += offset;
            break;
        case 6:
            break;
        }

        ((S_80175A90_2 *)prim)->unk_05 = 0x40;
        ((S_80175A90_2 *)prim)->unk_06 = 0x40;
        ((S_80175A90_2 *)prim)->unk_0C = 0x40;
        ((S_80175A90_2 *)prim)->unk_15 = 0x40;
        ((S_80175A90_2 *)prim)->unk_16 = 0x40;
        ((S_80175A90_2 *)prim)->unk_04 = endpoint_red;
        ((S_80175A90_2 *)prim)->unk_0D = 0;
        ((S_80175A90_2 *)prim)->unk_0E = 0;
        ((S_80175A90_2 *)prim)->unk_14 = endpoint_red;

        ((S_80175A90_0 *)scratch)->unk_B4.s = func_80065530(
            scratch + 0x64, scratch + 0x6C, scratch + 0x74,
            scratch + 0xD8, scratch + 0xDC, scratch + 0xE0,
            scratch + 0x84, scratch + 0x88);

        ((S_80175A90_2 *)prim)->unk_08 = ((S_80175A90_0 *)scratch)->unk_D8;
        ((S_80175A90_2 *)prim)->unk_0A = ((S_80175A90_0 *)scratch)->unk_DA;
        ((S_80175A90_2 *)prim)->unk_10 = ((S_80175A90_0 *)scratch)->unk_DC;
        ((S_80175A90_2 *)prim)->unk_12 = ((S_80175A90_0 *)scratch)->unk_DE;
        ((S_80175A90_2 *)prim)->unk_18 = ((S_80175A90_0 *)scratch)->unk_E0;
        ((S_80175A90_2 *)prim)->unk_1A = ((S_80175A90_0 *)scratch)->unk_E2;

        {
            u32 depth = ((S_80175A90_0 *)scratch)->unk_B4.u;
            if (depth < 0x1E0) {
                ((S_80175A90_2 *)prim)->unk_00.at00.v =
                    (((S_80175A90_2 *)prim)->unk_00.at00.v & length_mask) |
                    ((*(u32 *)((u8 *)(((S_80175A90_0 *)scratch)->unk_18.p2) + depth * 4)) & addr_mask);
                (*(u32 *)((u8 *)(((S_80175A90_0 *)scratch)->unk_18.p2) + ((S_80175A90_0 *)scratch)->unk_B4.u * 4)) =
                    ((*(u32 *)((u8 *)(((S_80175A90_0 *)scratch)->unk_18.p2) + ((S_80175A90_0 *)scratch)->unk_B4.u * 4)) & length_mask) |
                    ((u32)prim & addr_mask);
            }
        }

        line_index++;
    } while (line_index < 7);
}
