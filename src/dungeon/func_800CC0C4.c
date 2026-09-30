#include "common.h"
#include "shared/game_work.h"

typedef struct S_800D1824_0 {
    u8 pad_00[0x20];
    u8 * unk_20;
    u8 pad_24[0x4];
    s32 unk_28;
    s16 unk_2C;
    u8 pad_2E[0x42];
    s16 unk_70;
    s16 unk_72;
    u16 unk_74;
    u8 pad_76[0x2];
    s16 unk_78;
    s16 unk_7A;
    u16 unk_7C;
    u8 pad_7E[0x2];
    s16 unk_80;
    s16 unk_82;
    u16 unk_84;
    u8 pad_86[0x2];
    s16 unk_88;
    s16 unk_8A;
    u16 unk_8C;
    u8 pad_8E[0x32];
    s32 unk_C0;
    u8 pad_C4[0x8];
    s32 unk_CC;
    u8 pad_D0[0x44];
    s32 unk_114;
} S_800D1824_0;   /* scratch in func_800D1824 */

typedef struct S_800D1824_2 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_800D1824_2;   /* root in func_800D1824 */

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


extern void func_80065034(void *arg0, void *arg1, void *arg2);
extern void func_8006658C(s32 arg0, void *arg1);

/* Transform grid tiles into quads and add visible ones to the ordering table. */
void func_800D1824(u8 *tiles)
{
    u8 *scratch = (u8 *)0x1F800000;
    GameWork *globals = &gameWork;
    u8 *style;
    u8 *prim;
    u8 *render_state;
    s32 x;
    s32 y;
    s32 depth;
    s32 tri_depth;
    u16 z;

    ((S_800D1824_0 *)scratch)->unk_28 = 0;
    render_state = ((u8 *)globals->unk_000);
    style = ((S_800D1824_5 *)(((u8 *)globals->map.unk_04)))->unk_10;
    prim = ((S_800D1824_2 *)render_state)->unk_8D0;
    ((S_800D1824_0 *)scratch)->unk_2C = -0x1000;
    ((S_800D1824_0 *)scratch)->unk_20 = render_state + 0xB0;

    while (*tiles != 0) {
        if (*(u16 *)(tiles + 2) != 0x8000) {
            x = (s32)tiles[0] << 6;
            ((S_800D1824_0 *)scratch)->unk_80 = (s16)x;
            ((S_800D1824_0 *)scratch)->unk_70 = (s16)x;
            x += 0x40;
            ((S_800D1824_0 *)scratch)->unk_88 = (s16)x;
            ((S_800D1824_0 *)scratch)->unk_78 = (s16)x;

            y = (s32)tiles[1] << 6;
            ((S_800D1824_0 *)scratch)->unk_7A = (s16)y;
            ((S_800D1824_0 *)scratch)->unk_72 = (s16)y;
            y += 0x40;
            ((S_800D1824_0 *)scratch)->unk_8A = (s16)y;
            ((S_800D1824_0 *)scratch)->unk_82 = (s16)y;

            z = *(u16 *)(tiles + 2);
            ((S_800D1824_0 *)scratch)->unk_84 = z;
            ((S_800D1824_0 *)scratch)->unk_7C = z;
            ((S_800D1824_0 *)scratch)->unk_74 = z;

            gte_ldv3(scratch + 0x70, scratch + 0x78, scratch + 0x80);
            ((S_800D1824_0 *)scratch)->unk_8C = *(u16 *)(tiles + 2);
            gte_rtpt_nn();
            gte_nclip();
            gte_stopz(scratch + 0x114);

            if (((S_800D1824_0 *)scratch)->unk_114 > 0) {
                gte_stsxy3_g3(prim);
                gte_avsz3();
                gte_stotz(scratch + 0xC0);
                gte_ldv0(scratch + 0x88);
                tri_depth = ((S_800D1824_0 *)scratch)->unk_C0;
                tri_depth = tri_depth * 3;
                ((S_800D1824_0 *)scratch)->unk_C0 = tri_depth;

                gte_rtps_nn();
                gte_stszotz(scratch + 0xCC);
                depth = (((S_800D1824_0 *)scratch)->unk_C0 +
                         ((S_800D1824_0 *)scratch)->unk_CC) >> 2;
                ((S_800D1824_0 *)scratch)->unk_C0 = depth;

                if ((u32)depth < 0x1E0) {
                    gte_stsxy(prim + 0x20);
                    func_80065034(scratch + 0x28, (u8 *)globals + 0xA8, prim + 4);
                    *(u32 *)(prim + 0xC) = ((S_800D1824_4 *)style)->unk_08;
                    *(u32 *)(prim + 0x14) = ((S_800D1824_4 *)style)->unk_0C;
                    *(u16 *)(prim + 0x1C) = ((S_800D1824_4 *)style)->unk_12;
                    *(u16 *)(prim + 0x24) = ((S_800D1824_4 *)style)->unk_14;
                    prim[3] = 9;
                    func_8006658C(
                        (s32)((S_800D1824_0 *)scratch)->unk_20 +
                            (((S_800D1824_0 *)scratch)->unk_C0 << 2),
                        prim);
                    prim += 0x28;
                }
            }
        }
        tiles += 4;
    }

    ((S_800D1824_6 *)(((u8 *)globals->unk_000)))->unk_8D0 = prim;
}
